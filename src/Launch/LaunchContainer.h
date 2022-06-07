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

#ifndef LaunchContainer_h
#define LaunchContainer_h

// C / C++
#include <thread>
#include <mutex>
#include <condition_variable>
#include <list>
#include <atomic>

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
