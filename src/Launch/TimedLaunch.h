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

#ifndef TimedLaunch_h
#define TimedLaunch_h

// C / C++

// External
#include <MRH_Typedefs.h>

// Project
#include "../Exception.h"


class TimedLaunch
{
public:
    
    /**************************************************************************************
     * Constructor / Destructor
     **************************************************************************************/
    
    /**
     *  Default constructor.
     *
     *  \param s_OwnerPackagePath The full package path for the application creating the launch.
     *  \param s_LaunchPackagePath The full package path for the application to launch.
     *  \param s_LaunchInput The UTF-8 launch input to supply to the application.
     *  \param s32_LaunchCommandID The launch command id to supply to the application.
     *  \param u64_TimepointS The time point in seconds to send the launch event.
     */
    
    TimedLaunch(std::string const& s_OwnerPackagePath,
                std::string const& s_LaunchPackagePath,
                std::string const& s_LaunchInput,
                MRH_Sint32 s32_LaunchCommandID,
                MRH_Uint64 u64_TimepointS);
    
    /**
     *  Default destructor.
     */
    
    ~TimedLaunch() noexcept;
    
    //*************************************************************************************
    // Getters
    //*************************************************************************************
    
    /**
     *  Get the owner package path.
     *
     *  \return The owner package path.
     */
    
    std::string GetOwnerPackagePath() const noexcept;
    
    /**
     *  Get the launch package path.
     *
     *  \return The launch package path.
     */
    
    std::string GetLaunchPackagePath() const noexcept;
    
    /**
     *  Get the launch input.
     *
     *  \return The UTF-8 launch input string.
     */
    
    std::string GetLaunchInput() const noexcept;
    
    /**
     *  Get the launch command id.
     *
     *  \return The launch command id.
     */
    
    MRH_Sint32 GetLaunchCommandID() const noexcept;
    
    /**
     *  Get the launch time point.
     *
     *  \return The launch time point in seconds.
     */
    
    MRH_Uint64 GetTimepointS() const noexcept;
    
private:
    
    /**************************************************************************************
     * Data
     **************************************************************************************/
    
    std::string s_OwnerPackagePath;
    std::string s_LaunchPackagePath;
    std::string s_LaunchInput;
    MRH_Sint32 s32_LaunchCommandID;
    MRH_Uint64 u64_TimepointS;
    
protected:
    
};

#endif /* TimedLaunch_h */
