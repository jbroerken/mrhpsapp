/**
 *  TimedLaunch.h
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
     *  \param i_LaunchCommandID The launch command id to supply to the application.
     *  \param u64_TimepointS The time point in seconds to send the launch event.
     */
    
    TimedLaunch(std::string const& s_OwnerPackagePath,
                std::string const& s_LaunchPackagePath,
                std::string const& s_LaunchInput,
                int i_LaunchCommandID,
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
    
    int GetLaunchCommandID() const noexcept;
    
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
    int i_LaunchCommandID;
    MRH_Uint64 u64_TimepointS;
    
protected:
    
};

#endif /* TimedLaunch_h */
