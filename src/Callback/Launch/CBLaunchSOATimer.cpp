/**
 *  Copyright (C) 2021 - 2022 The MRH Project Authors.
 * 
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

// C / C++

// External
#include <libmrhpsb/MRH_PSBLogger.h>

// Project
#include "./CBLaunchSOATimer.h"


//*************************************************************************************
// Constructor / Destructor
//*************************************************************************************

CBLaunchSOATimer::CBLaunchSOATimer(std::shared_ptr<LaunchContainer>& p_Container) noexcept : p_Container(p_Container)
{}

CBLaunchSOATimer::~CBLaunchSOATimer() noexcept
{}

//*************************************************************************************
// Callback
//*************************************************************************************

void CBLaunchSOATimer::Callback(const MRH_Event* p_Event, MRH_Uint32 u32_GroupID) noexcept
{
    MRH_EvD_A_LaunchSOATimer_U c_Data;
    
    if (MRH_EVD_ReadEvent(&c_Data, MRH_EVENT_APP_LAUNCH_SOA_TIMER_U, p_Event) < 0)
    {
        MRH_PSBLogger::Singleton().Log(MRH_PSBLogger::ERROR, "Failed to read request event!",
                                       "CBLaunchSOATimer.cpp", __LINE__);
        return;
    }
    
    MRH_Event* p_Result = MRH_EVD_CopyEvent(p_Event);
    
    if (p_Result == NULL)
    {
        MRH_PSBLogger::Singleton().Log(MRH_PSBLogger::ERROR, "Failed to create response event!",
                                       "CBLaunchSOATimer.cpp", __LINE__);
        return;
    }
    
    p_Result->u32_Type = MRH_EVENT_APP_LAUNCH_SOA_TIMER_S;
    p_Result->u32_GroupID = u32_GroupID;
    
    try
    {
        p_Container->Add(TimedLaunch(p_Container->GetOwnerPackagePath(),
                                     c_Data.p_PackagePath,
                                     c_Data.p_LaunchInput,
                                     c_Data.s32_LaunchCommandID,
                                     c_Data.u64_LaunchTimepointS));
        
        MRH_EventStorage::Singleton().Add(p_Result);
    }
    catch (std::exception& e) // Container and event creation, both result in no event
    {
        MRH_PSBLogger::Singleton().Log(MRH_PSBLogger::ERROR, e.what(),
                                       "CBLaunchSOATimer.cpp", __LINE__);
        MRH_EVD_DestroyEvent(p_Result);
    }
}
