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

#ifndef CBClearLaunchSOATimer_h
#define CBClearLaunchSOATimer_h

// C / C++
#include <memory>

// External
#include <libmrhpsb/MRH_Callback.h>

// Project
#include "../../Launch/LaunchContainer.h"


class CBClearLaunchSOATimer : public MRH_Callback
{
public:

    //*************************************************************************************
    // Constructor / Destructor
    //*************************************************************************************
    
    /**
     *  Default constructor.
     *
     *  \param p_Container The launch container to clear.
     */
    
    CBClearLaunchSOATimer(std::shared_ptr<LaunchContainer>& p_Container) noexcept;
    
    /**
     *  Default destructor.
     */
    
    ~CBClearLaunchSOATimer() noexcept;
    
    //*************************************************************************************
    // Callback
    //*************************************************************************************
    
    /**
     *  Perform a callback with a recieved clear all timed launches event.
     *
     *  \param p_Event The recieved launch event.
     *  \param u32_GroupID The event group id for the user event.
     */
    
    void Callback(const MRH_Event* p_Event, MRH_Uint32 u32_GroupID) noexcept override;
    
private:
    
    //*************************************************************************************
    // Data
    //*************************************************************************************
    
    std::shared_ptr<LaunchContainer> p_Container;
    
protected:

};

#endif /* CBClearLaunchSOATimer_h */
