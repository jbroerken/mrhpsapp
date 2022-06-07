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

// Project
#include "./TimedLaunch.h"


//*************************************************************************************
// Constructor / Destructor
//*************************************************************************************

TimedLaunch::TimedLaunch(std::string const& s_OwnerPackagePath,
                         std::string const& s_LaunchPackagePath,
                         std::string const& s_LaunchInput,
                         MRH_Sint32 s32_LaunchCommandID,
                         MRH_Uint64 u64_TimepointS) : s_OwnerPackagePath(s_OwnerPackagePath),
                                                      s_LaunchPackagePath(s_LaunchPackagePath),
                                                      s_LaunchInput(s_LaunchInput),
                                                      s32_LaunchCommandID(s32_LaunchCommandID),
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
    return s32_LaunchCommandID;
}

MRH_Uint64 TimedLaunch::GetTimepointS() const noexcept
{
    return u64_TimepointS;
}
