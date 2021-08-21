/**
 *  TimedLaunch.cpp
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

// Project
#include "./TimedLaunch.h"


//*************************************************************************************
// Constructor / Destructor
//*************************************************************************************

TimedLaunch::TimedLaunch(std::string const& s_OwnerPackagePath,
                         std::string const& s_LaunchPackagePath,
                         std::string const& s_LaunchInput,
                         int i_LaunchCommandID,
                         MRH_Uint64 u64_TimepointS) : s_OwnerPackagePath(s_OwnerPackagePath),
                                                      s_LaunchPackagePath(s_LaunchPackagePath),
                                                      s_LaunchInput(s_LaunchInput),
                                                      i_LaunchCommandID(i_LaunchCommandID),
                                                      u64_TimepointS(u64_TimepointS)
{
    if (s_OwnerPackagePath.size() == 0)
    {
        throw Exception("Invalid owner package path!");
    }
    else if (s_LaunchPackagePath.size() == 0)
    {
        throw Exception("Invalid launch package path!");
    }
}

TimedLaunch::~TimedLaunch() noexcept
{}

//*************************************************************************************
// Getters
//*************************************************************************************

std::string TimedLaunch::GetOwnerPackagePath() const noexcept
{
    return s_OwnerPackagePath;
}

std::string TimedLaunch::GetLaunchPackagePath() const noexcept
{
    return s_LaunchPackagePath;
}

std::string TimedLaunch::GetLaunchInput() const noexcept
{
    return s_LaunchInput;
}

int TimedLaunch::GetLaunchCommandID() const noexcept
{
    return i_LaunchCommandID;
}

MRH_Uint64 TimedLaunch::GetTimepointS() const noexcept
{
    return u64_TimepointS;
}
