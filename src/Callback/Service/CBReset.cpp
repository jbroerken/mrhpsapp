/**
 *  CBReset.cpp
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
#include "./CBReset.h"


//*************************************************************************************
// Constructor / Destructor
//*************************************************************************************

CBReset::CBReset(std::shared_ptr<LaunchContainer>& p_Container) noexcept : p_Container(p_Container)
{}

CBReset::~CBReset() noexcept
{}

//*************************************************************************************
// Callback
//*************************************************************************************

void CBReset::Callback(const MRH_Event* p_Event, MRH_Uint32 u32_GroupID) noexcept
{
    MRH_EvD_Sys_ResetRequest_U c_Data;
    
    if (MRH_EVD_ReadEvent(&c_Data, MRH_EVENT_PS_RESET_REQUEST_U, p_Event) < 0)
    {
        MRH_PSBLogger::Singleton().Log(MRH_PSBLogger::ERROR, "Failed to read event data!",
                                       "CBReset.cpp", __LINE__);
        return;
    }
    
    try
    {
        p_Container->SetOwnerPackagePath(c_Data.p_PackagePath);
    }
    catch (Exception& e)
    {
        MRH_PSBLogger::Singleton().Log(MRH_PSBLogger::ERROR, e.what(),
                                       "CBReset.cpp", __LINE__);
    }
}
