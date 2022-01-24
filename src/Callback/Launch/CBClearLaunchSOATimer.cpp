/**
 *  CBClearLaunchSOATimer.cpp
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
#include "./CBClearLaunchSOATimer.h"


//*************************************************************************************
// Constructor / Destructor
//*************************************************************************************

CBClearLaunchSOATimer::CBClearLaunchSOATimer(std::shared_ptr<LaunchContainer>& p_Container) noexcept : p_Container(p_Container)
{}

CBClearLaunchSOATimer::~CBClearLaunchSOATimer() noexcept
{}

//*************************************************************************************
// Callback
//*************************************************************************************

void CBClearLaunchSOATimer::Callback(const MRH_Event* p_Event, MRH_Uint32 u32_GroupID) noexcept
{
    MRH_Event* p_Result = MRH_EVD_CreateEvent(MRH_EVENT_APP_LAUNCH_SOA_CLEAR_TIMER_S, NULL, 0);
    
    if (p_Result == NULL)
    {
        MRH_PSBLogger::Singleton().Log(MRH_PSBLogger::ERROR, "Failed to create response event!",
                                       "CBClearLaunchSOATimer.cpp", __LINE__);
        return;
    }
    
    p_Result->u32_GroupID = u32_GroupID;
    
    try
    {
        p_Container->Clear();
        
        MRH_EventStorage::Singleton().Add(p_Result);
    }
    catch (MRH_PSBException& e)
    {
        MRH_PSBLogger::Singleton().Log(MRH_PSBLogger::ERROR, e.what(),
                                       "CBClearLaunchSOATimer.cpp", __LINE__);
        MRH_EVD_DestroyEvent(p_Result);
    }
}
