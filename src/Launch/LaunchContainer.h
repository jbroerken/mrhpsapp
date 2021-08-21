/**
 *  LaunchContainer.h
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

#ifndef LaunchContainer_h
#define LaunchContainer_h

// C / C++
#include <thread>
#include <mutex>
#include <condition_variable>
#include <list>

// External
#include <libmrhbf.h>

// Project
#include "./TimedLaunch.h"
#include "../Exception.h"


class LaunchContainer
{
public:
    
    /**************************************************************************************
     * Constructor / Destructor
     **************************************************************************************/
    
    /**
     *  Default constructor.
     */
    
    LaunchContainer();
    
    /**
     *  Copy Constructor. Disabled for this class.
     *
     *  \param c_LaunchContainer LaunchContainer class source.
     */
    
    LaunchContainer(LaunchContainer const& s_LaunchContainer) = delete;
    
    /**
     *  Default destructor.
     */
    
    ~LaunchContainer() noexcept;
    
    /**************************************************************************************
     * Clear
     **************************************************************************************/
    
    /**
     *  Clear all timed launch requests for the current package.
     */
    
    void Clear() noexcept;
    
    /**************************************************************************************
     * Add
     **************************************************************************************/
    
    /**
     *  Add a timed launch request for the current package.
     *
     *  \param c_Request The timed launch request.
     */
    
    void Add(TimedLaunch const& c_Request) noexcept;
    
    /**************************************************************************************
     * Getters
     **************************************************************************************/
    
    /**
     *  Get the current owner package.
     *
     *  \return The current owner package.
     */
    
    std::string GetOwnerPackagePath() const noexcept;
    
    /**************************************************************************************
     * Setters
     **************************************************************************************/
    
    /**
     *  Set the current owner package.
     *
     *  \param s_PackagePath The full owner package path.
     */
    
    void SetOwnerPackagePath(std::string const& s_PackagePath);
    
private:
    
    /**************************************************************************************
     * Thread
     **************************************************************************************/
    
    /**
     *  Update the timed launch thread.
     *
     *  \param p_Instance The launch container instance to update with.
     */
    
    static void TimedUpdate(LaunchContainer* p_Instance) noexcept;
    
    /**************************************************************************************
     * File
     **************************************************************************************/
    
    /**
     *  Write the current container state to file.
     */
    
    void WriteContainer() noexcept;
    
    /**************************************************************************************
     * Data
     **************************************************************************************/
    
    std::thread c_Thread;
    std::atomic<bool> b_Update;
    
    std::mutex c_RequestMutex;
    std::mutex c_ConditionMutex;
    std::condition_variable c_Condition;
    
    std::string s_OwnerPackagePath; // Active Package
    std::list<TimedLaunch> l_TimedLaunch; // All launches of all packages
    MRH_BlockFile c_File; // Storage
    
protected:
    
};

#endif /* LaunchContainer_h */
