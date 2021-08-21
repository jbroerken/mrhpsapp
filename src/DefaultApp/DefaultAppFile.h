/**
 *  DefaultAppFile.h
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

#ifndef DefaultAppFile_h
#define DefaultAppFile_h

// C / C++
#include <vector>
#include <string>
#include <mutex>

// External
#include <MRH_Typedefs.h>

// Project
#include "../Exception.h"


class DefaultAppFile
{
public:

    //*************************************************************************************
    // Types
    //*************************************************************************************

    typedef MRH_Uint8 DefaultAppIdentifier;
    enum DefaultApp
    {
        CALENDAR = 0,
        CALCULATOR = 1,
        NOTES = 2,
        WEB_SEARCH = 3,

        DEFAULT_APP_MAX = WEB_SEARCH,

        DEFAULT_APP_COUNT = DEFAULT_APP_MAX + 1
    };
    
    //*************************************************************************************
    // Singleton
    //*************************************************************************************
    
    /**
     *  Get the class instance.
     *
     *  \return The class instance.
     */
    
    static DefaultAppFile& Singleton() noexcept;
    
    //*************************************************************************************
    // File
    //*************************************************************************************

    /**
     *  Read the default app file. This function is thread safe.
     */

    void Read();

    /**
     *  Write the default app file. This function is thread safe.
     */

    void Write();
    
    //*************************************************************************************
    // Getters
    //*************************************************************************************
    
    /**
     *  Get a default app. This function is thread safe.
     *
     *  \param u8_Identifier The default app identifier.
     *
     *  \return The full package path.
     */
    
    std::string GetDefaultApp(DefaultAppIdentifier u8_Identifier);

    //*************************************************************************************
    // Setters
    //*************************************************************************************
    
    /**
     *  Set a default app. This function is thread safe.
     *
     *  \param u8_Identifier The default app identifier.
     *  \param s_PackagePath The full package path for the identifier.
     */
    
    void SetDefaultApp(DefaultAppIdentifier u8_Identifier, std::string const& s_PackagePath);
    
private:

    //*************************************************************************************
    // Value
    //*************************************************************************************
    
    class Value
    {
    public:
        
        //*************************************************************************************
        // Constructor / Destructor
        //*************************************************************************************
        
        /**
         *  Default constructor.
         *
         *  \param s_PackagePath The full package path for the identifier.  
         */
        
        Value(std::string const& s_PackagePath) noexcept;
        
        /**
         *  Default destructor.
         */
        
        ~Value() noexcept;
        
        //*************************************************************************************
        // Getters
        //*************************************************************************************
        
        /**
         *  Get the value package path. This function is thread safe.
         *
         *  \return The full package path.
         */
        
        std::string GetPackagePath() noexcept;
        
        //*************************************************************************************
        // Setters
        //*************************************************************************************
        
        /**
         *  Set the value package path. This function is thread safe.
         *
         *  \param s_PackagePath The full package path.
         */
        
        void SetPackagePath(std::string const& s_PackagePath) noexcept;
        
    private:
        
        //*************************************************************************************
        // Data
        //*************************************************************************************
        
        std::mutex s_Mutex;
        std::string s_PackagePath;
        
    protected:
        
    };
    
    //*************************************************************************************
    // Constructor / Destructor
    //*************************************************************************************
    
    /**
     *  Default constructor.
     */
    
    DefaultAppFile() noexcept;
    
    /**
     *  Default destructor.
     */
    
    ~DefaultAppFile() noexcept;
    
    //*************************************************************************************
    // Data
    //*************************************************************************************
    
    std::mutex s_Mutex;
    std::vector<Value*> v_Value;
    
protected:

};

#endif /* DefaultAppFile_h */
