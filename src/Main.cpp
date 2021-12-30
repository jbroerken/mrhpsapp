/**
 *  Main.cpp
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
#include <cstdlib>

// External
#include <libmrhpsb.h>

// Project
#include "./Callback/Service/CBAvail.h"
#include "./Callback/Service/CBReset.h"
#include "./Callback/Service/CBCustomCommand.h"
#include "./Callback/Launch/CBLaunchSOA.h"
#include "./Callback/Launch/CBLaunchSOATimer.h"
#include "./Callback/Launch/CBClearLaunchSOA.h"
#include "./Callback/Launch/CBClearLaunchSOATimer.h"
#include "./Launch/LaunchContainer.h"
#include "./Revision.h"

// Pre-defined
#ifndef MRH_APP_SERVICE_THREAD_COUNT
    #define MRH_APP_SERVICE_THREAD_COUNT 1
#endif


//*************************************************************************************
// Exit
//*************************************************************************************

static int Exit(libmrhpsb* p_Context, const char* p_Exception, int i_Result)
{
    if (p_Context != NULL)
    {
        delete p_Context;
    }
    
    if (p_Exception != NULL)
    {
        MRH_PSBLogger::Singleton().Log(MRH_PSBLogger::ERROR, p_Exception,
                                       "Main.cpp", __LINE__);
    }
    
    return i_Result;
}

//*************************************************************************************
// Main
//*************************************************************************************

int main(int argc, const char* argv[])
{
    // Setup service base
    MRH_PSBLogger& c_Logger = MRH_PSBLogger::Singleton();
    libmrhpsb* p_Context;
    
    try
    {
        p_Context = new libmrhpsb("mrhpsapp",
                                  argc,
                                  argv,
                                  MRH_APP_SERVICE_THREAD_COUNT);
    }
    catch (MRH_PSBException& e)
    {
        return Exit(NULL, e.what(), EXIT_FAILURE);
    }
    catch (std::exception& e)
    {
        return Exit(NULL, e.what(), EXIT_FAILURE);
    }
    
    // Setup service specific data
    c_Logger.Log(MRH_PSBLogger::INFO, "Initializing mrhpsapp (" + std::string(VERSION_NUMBER) + ")...", "Main.cpp", __LINE__);
    
    try
    {
        std::shared_ptr<LaunchContainer> p_LaunchContainer(new LaunchContainer());
        
        std::shared_ptr<MRH_Callback> p_CBAvail(new CBAvail());
        std::shared_ptr<MRH_Callback> p_CBReset(new CBReset(p_LaunchContainer));
        std::shared_ptr<MRH_Callback> p_CBCustomCommand(new CBCustomCommand());
        
        std::shared_ptr<MRH_Callback> p_CBLaunchSOA(new CBLaunchSOA());
        std::shared_ptr<MRH_Callback> p_CBLaunchSOATimer(new CBLaunchSOATimer(p_LaunchContainer));
        std::shared_ptr<MRH_Callback> p_CBClearLaunchSOA(new CBClearLaunchSOA());
        std::shared_ptr<MRH_Callback> p_CBClearLaunchSOATimer(new CBClearLaunchSOATimer(p_LaunchContainer));
        
        p_Context->AddCallback(p_CBAvail, MRH_EVENT_APP_AVAIL_U);
        p_Context->AddCallback(p_CBReset, MRH_EVENT_PS_RESET_REQUEST_U);
        p_Context->AddCallback(p_CBCustomCommand, MRH_EVENT_APP_CUSTOM_COMMAND_U);
        
        p_Context->AddCallback(p_CBLaunchSOA, MRH_EVENT_APP_LAUNCH_SOA_U);
        p_Context->AddCallback(p_CBLaunchSOATimer, MRH_EVENT_APP_LAUNCH_SOA_TIMER_U);
        p_Context->AddCallback(p_CBClearLaunchSOA, MRH_EVENT_APP_LAUNCH_SOA_CLEAR_U);
        p_Context->AddCallback(p_CBClearLaunchSOATimer, MRH_EVENT_APP_LAUNCH_SOA_CLEAR_TIMER_U);
    }
    catch (MRH_PSBException& e)
    {
        return Exit(p_Context, e.what(), EXIT_FAILURE);
    }
    catch (std::exception& e)
    {
        return Exit(p_Context, e.what(), EXIT_FAILURE);
    }
    
    c_Logger.Log(MRH_PSBLogger::INFO, "Successfully intialized mrhpsapp service!",
                 "Main.cpp", __LINE__);
    
    // Update service until termination
    p_Context->Update();
    
    // Exit
    c_Logger.Log(MRH_PSBLogger::INFO, "Terminating service.",
                 "Main.cpp", __LINE__);
    delete p_Context;
    return EXIT_SUCCESS;
}
