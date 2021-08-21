/**
 *  CBGetDefault.cpp
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
#include "./CBGetDefault.h"
#include "../../DefaultApp/DefaultAppFile.h"


//*************************************************************************************
// Constructor / Destructor
//*************************************************************************************

CBGetDefault::CBGetDefault() noexcept
{}

CBGetDefault::~CBGetDefault() noexcept
{}

//*************************************************************************************
// Callback
//*************************************************************************************

void CBGetDefault::Callback(const MRH_EVBase* p_Event, MRH_Uint32 u32_GroupID) noexcept
{
    AppDefaultPackage e_App;
    std::string s_PackagePath = "";
    bool b_Result = true;
    
    try
    {
        e_App = static_cast<const MRH_A_GET_DEFAULT_PACKAGE_U*>(p_Event)->GetDefaultPackage();
        
        switch (e_App)
        {
            case CALENDAR:
            case CALCULATOR:
            case NOTES:
            case WEB_SEARCH:
                s_PackagePath = DefaultAppFile::Singleton().GetDefaultApp(e_App);
                break;
                
            default:
                throw Exception("Invalid default app " + std::to_string(e_App) + " to get!");
        }
    }
    catch (std::exception& e)
    {
        MRH_PSBLogger::Singleton().Log(MRH_PSBLogger::WARNING, e.what(),
                                       "CBGetDefault.cpp", __LINE__);
        b_Result = false;
    }
    
    try
    {
        MRH_A_GET_DEFAULT_PACKAGE_S c_Result(e_App,
                                             s_PackagePath,
                                             b_Result);
        MRH_EventStorage::Singleton().Add(c_Result, u32_GroupID);
    }
    catch (MRH_PSBException& e)
    {
        MRH_PSBLogger::Singleton().Log(MRH_PSBLogger::ERROR, e.what(),
                                       "CBGetDefault.cpp", __LINE__);
    }
}
