/**
 *  LaunchContainer.cpp
 *
 *  This file is part of the MRH project.
 *  See the AUTHORS file for Copyright information.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

// C / C++
#include <cstring>

// External
#include <libmrhevdata.h>
#include <libmrhpsb/MRH_EventStorage.h>
#include <libmrhpsb/MRH_PSBLogger.h>

// Project
#include "./LaunchContainer.h"

// Pre-defined
#ifndef MRH_APP_SERVICE_TIMED_LAUNCH_FILE_PATH
    #define MRH_APP_SERVICE_TIMED_LAUNCH_FILE_PATH "/var/mrh/mrhpsapp/TimedLaunch.mrhbf"
#endif
#define LAUNCH_WAIT_TIMEOUT_S 900

namespace
{
    enum Identifier
    {
        // Block Name
        BLOCK_NAME = 0,
        
        // Block Key
        KEY_OWNER_PACKAGE_PATH = 1,
        KEY_LAUNCH_PACKAGE_PATH = 2,
        KEY_LAUNCH_INPUT = 3,
        KEY_LAUNCH_COMMAND_ID = 4,
        KEY_LAUNCH_TIMEPOINT_S = 5,
        
        // Bounds
        IDENTIFIER_MAX = KEY_LAUNCH_TIMEPOINT_S,
        
        IDENTIFIER_COUNT = IDENTIFIER_MAX + 1
    };

    const char* p_Identifier[IDENTIFIER_COUNT] =
    {
        // Block Name
        "TimedLaunch",
        
        // Block Key
        "OwnerPackagePath",
        "LaunchPackagePath",
        "LaunchInput",
        "LaunchCommandID",
        "LaunchTimepointS"
    };
}


//*************************************************************************************
// Constructor / Destructor
//*************************************************************************************

LaunchContainer::LaunchContainer() : s_OwnerPackagePath(""),
                                     b_Update(true)
{
    try
    {
        c_File.Read(MRH_APP_SERVICE_TIMED_LAUNCH_FILE_PATH);
        
        for (auto& Block : c_File.l_Block)
        {
            if (Block.GetName().compare(p_Identifier[BLOCK_NAME]) != 0)
            {
                continue;
            }
            
            try
            {
                l_TimedLaunch.emplace_back(Block.GetValue(p_Identifier[KEY_OWNER_PACKAGE_PATH]),
                                           Block.GetValue(p_Identifier[KEY_LAUNCH_PACKAGE_PATH]),
                                           Block.GetValue(p_Identifier[KEY_LAUNCH_INPUT]),
                                           std::stoi(Block.GetValue(p_Identifier[KEY_LAUNCH_COMMAND_ID])),
                                           std::stoull(Block.GetValue(p_Identifier[KEY_LAUNCH_TIMEPOINT_S])));
            }
            catch (MRH_BFException& e)
            {
                MRH_PSBLogger::Singleton().Log(MRH_PSBLogger::INFO, e.what(),
                                               "LaunchContainer.cpp", __LINE__);
            }
        }
    }
    catch (MRH_BFException& e)
    {
        // Missing files will simply be created again
        MRH_PSBLogger::Singleton().Log(MRH_PSBLogger::INFO, e.what(),
                                       "LaunchContainer.cpp", __LINE__);
    }
    
    // Start thread after adding all saved launches
    c_Thread = std::thread(TimedUpdate, this);
}

LaunchContainer::~LaunchContainer() noexcept
{
    b_Update = false;
    c_Condition.notify_all();
    c_Thread.join();
}

/**************************************************************************************
 * Thread
 **************************************************************************************/

void LaunchContainer::TimedUpdate(LaunchContainer* p_Instance) noexcept
{
    MRH_PSBLogger& c_Logger = MRH_PSBLogger::Singleton();
    MRH_EventStorage& c_Storage = MRH_EventStorage::Singleton();
    
    MRH_EvD_A_LaunchSOA_S c_LaunchData;
    MRH_Event* p_Launch;
    MRH_Event* p_Reminder;
    
    std::list<TimedLaunch>& l_TimedLaunch = p_Instance->l_TimedLaunch;
    size_t us_TimeoutS;
    
    while (p_Instance->b_Update == true)
    {
        // Reset timer to max, in case no launch is waiting.
        // @NOTE: The thread will wake as soon as a request was added, running
        //        through the available requests and adjust the wait time to match
        us_TimeoutS = LAUNCH_WAIT_TIMEOUT_S;
        
        // Check usable requests
        p_Instance->c_RequestMutex.lock();
        
        for (auto It = l_TimedLaunch.begin(); It != l_TimedLaunch.end();)
        {
            if (It->GetTimepointS() > time(NULL))
            {
                // Not launchable, but is the launch sooner than the
                // current timeout?
                size_t us_TimeS = It->GetTimepointS() - time(NULL);
                
                if (us_TimeS < us_TimeoutS)
                {
                    us_TimeoutS = us_TimeS;
                }
                
                ++It;
                continue;
            }
            
            // Send both reminder for the current app and launch request
            // @NOTE: mrhcore only reacts to normal launches, send that
            memset((c_LaunchData.p_PackagePath), '\0', MRH_EVD_A_STRING_LAUNCH_BUFFER_MAX_TERMINATED);
            memset((c_LaunchData.p_LaunchInput), '\0', MRH_EVD_A_STRING_LAUNCH_BUFFER_MAX_TERMINATED);
            
            strncpy((c_LaunchData.p_PackagePath),
                    It->GetLaunchPackagePath().c_str(),
                    MRH_EVD_A_STRING_LAUNCH_BUFFER_MAX);
            strncpy((c_LaunchData.p_LaunchInput),
                    It->GetLaunchInput().c_str(),
                    MRH_EVD_A_STRING_LAUNCH_BUFFER_MAX);
            
            c_LaunchData.s32_LaunchCommandID = It->GetLaunchCommandID();
            
            if ((p_Launch = MRH_EVD_CreateSetEvent(MRH_EVENT_APP_LAUNCH_SOA_S, &c_LaunchData)) == NULL ||
                (p_Reminder = MRH_EVD_CreateEvent(MRH_EVENT_APP_LAUNCH_SOA_TIMER_REMINDER_S, NULL, 0)) == NULL)
            {
                p_Launch = MRH_EVD_DestroyEvent(p_Launch); // @NOTE: Checks NULL
                
                ++It;
                continue;
            }
            
            try
            {
                c_Storage.Add(p_Reminder);
                c_Storage.Add(p_Launch);
            }
            catch (MRH_PSBException& e)
            {
                c_Logger.Log(MRH_PSBLogger::ERROR, e.what(),
                             "LaunchContainer.cpp", __LINE__);
                
                p_Reminder = MRH_EVD_DestroyEvent(p_Launch);
                p_Launch = MRH_EVD_DestroyEvent(p_Launch);
            }
            
            It = l_TimedLaunch.erase(It);
            p_Instance->WriteContainer();
        }
        
        p_Instance->c_RequestMutex.unlock();
        
        c_Logger.Log(MRH_PSBLogger::INFO, "Next timed launch update happens in " +
                                          std::to_string(us_TimeoutS) +
                                          " seconds...",
                     "LaunchContainer.cpp", __LINE__);
        
        // Wait for next launch
        std::unique_lock<std::mutex> c_Unique(p_Instance->c_ConditionMutex);
        p_Instance->c_Condition.wait_for(c_Unique, std::chrono::seconds(us_TimeoutS));
    }
}

/**************************************************************************************
 * Clear
 **************************************************************************************/

void LaunchContainer::Clear() noexcept
{
    std::lock_guard<std::mutex> c_Guard(c_RequestMutex);
    
    // Remove launches for package
    for (auto It = l_TimedLaunch.begin(); It != l_TimedLaunch.end();)
    {
        if (It->GetOwnerPackagePath().compare(s_OwnerPackagePath) == 0)
        {
            It = l_TimedLaunch.erase(It);
        }
        else
        {
            ++It;
        }
    }
    
    // Now write the file
    WriteContainer();
    
    // No reason to wake thread, stuff was removed
}

/**************************************************************************************
 * Add
 **************************************************************************************/

void LaunchContainer::Add(TimedLaunch const& c_Request) noexcept
{
    std::lock_guard<std::mutex> c_Guard(c_RequestMutex);
    
    l_TimedLaunch.emplace_back(c_Request);
    WriteContainer();
    
    // New request, timeout might be smaller now
    c_Condition.notify_one();
}

/**************************************************************************************
 * File
 **************************************************************************************/

void LaunchContainer::WriteContainer() noexcept
{
    // Clear and re-add all launches
    // @TODO: Inefficient
    c_File.l_Block.clear();
    
    for (auto It = l_TimedLaunch.begin(); It != l_TimedLaunch.end(); ++It)
    {
        c_File.l_Block.emplace_back(p_Identifier[BLOCK_NAME],
                                    MRH_APP_SERVICE_TIMED_LAUNCH_FILE_PATH);
        
        try
        {
            MRH_ValueBlock& c_Block = c_File.l_Block.back();
            
            c_Block.Add(std::make_pair(p_Identifier[KEY_OWNER_PACKAGE_PATH], It->GetOwnerPackagePath()));
            c_Block.Add(std::make_pair(p_Identifier[KEY_LAUNCH_PACKAGE_PATH], It->GetLaunchPackagePath()));
            c_Block.Add(std::make_pair(p_Identifier[KEY_LAUNCH_INPUT], It->GetLaunchInput()));
            c_Block.Add(std::make_pair(p_Identifier[KEY_LAUNCH_COMMAND_ID], std::to_string(It->GetLaunchCommandID())));
            c_Block.Add(std::make_pair(p_Identifier[KEY_LAUNCH_TIMEPOINT_S], std::to_string(It->GetTimepointS())));
        }
        catch (...)
        {
            c_File.l_Block.pop_back();
        }
    }
    
    // All updated, now write the file
    try
    {
        c_File.Write(MRH_APP_SERVICE_TIMED_LAUNCH_FILE_PATH);
    }
    catch (MRH_BFException& e)
    {
        MRH_PSBLogger::Singleton().Log(MRH_PSBLogger::WARNING, e.what(),
                                       "LaunchContainer.cpp", __LINE__);
    }
}

/**************************************************************************************
 * Getters
 **************************************************************************************/

std::string LaunchContainer::GetOwnerPackagePath() const noexcept
{
    return s_OwnerPackagePath;
}

/**************************************************************************************
 * Setters
 **************************************************************************************/

void LaunchContainer::SetOwnerPackagePath(std::string const& s_PackagePath)
{
    s_OwnerPackagePath = s_PackagePath;
}
