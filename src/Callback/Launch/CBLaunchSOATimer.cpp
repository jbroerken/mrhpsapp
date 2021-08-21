/**
 *  CBLaunchSOATimer.cpp
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

void CBLaunchSOATimer::Callback(const MRH_EVBase* p_Event, MRH_Uint32 u32_GroupID) noexcept
{
    try
    {
        const MRH_A_LAUNCH_SOA_TIMER_U* p_Cast = static_cast<const MRH_A_LAUNCH_SOA_TIMER_U*>(p_Event);
        
        p_Container->Add(TimedLaunch(p_Container->GetOwnerPackagePath(),
                                     p_Cast->GetPackagePath(),
                                     p_Cast->GetLaunchInput(),
                                     p_Cast->GetLaunchCommandID(),
                                     p_Cast->GetTimepointS()));
        
        MRH_A_LAUNCH_SOA_TIMER_S c_Result(p_Cast->GetPackagePath(),
                                          p_Cast->GetLaunchInput(),
                                          p_Cast->GetLaunchCommandID(),
                                          p_Cast->GetTimepointS());
        MRH_EventStorage::Singleton().Add(c_Result, u32_GroupID);
    }
    catch (std::exception& e) // Container and event creation, both result in no event
    {
        MRH_PSBLogger::Singleton().Log(MRH_PSBLogger::ERROR, e.what(),
                                       "CBLaunchSOATimer.cpp", __LINE__);
    }
}
