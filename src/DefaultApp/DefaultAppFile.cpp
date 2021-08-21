/**
 *  DefaultAppFile.cpp
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
#include <libmrhbf.h>

// Project
#include "./DefaultAppFile.h"

// Pre-defined
#ifndef MRH_APP_SERVICE_DEFAULT_APP_FILE_PATH
    #define MRH_APP_SERVICE_DEFAULT_APP_FILE_PATH "/etc/mrhpservice/Application.conf"
#endif

namespace
{
    enum Identifier
    {
        // Block Name
        BLOCK_DEFAULT_PACKAGE = 0,
        
        // Default Package Key
        KEY_DEFAULT_PACKAGE_CALENDAR = 1,
        KEY_DEFAULT_PACKAGE_CALCULATOR = 2,
        KEY_DEFAULT_PACKAGE_NOTES = 3,
        KEY_DEFAULT_PACKAGE_WEB_SEARCH = 4,
        
        // Bounds
        IDENTIFIER_MAX = KEY_DEFAULT_PACKAGE_WEB_SEARCH,
        
        IDENTIFIER_COUNT = IDENTIFIER_MAX + 1
    };

    const char* p_Identifier[IDENTIFIER_COUNT] =
    {
        // Block Name
        "DefaultPackage",
        
        // Default Package Key
        "Calendar",
        "Calculator",
        "Notes",
        "WebSearch"
    };
}


//*************************************************************************************
// Constructor / Destructor
//*************************************************************************************

DefaultAppFile::DefaultAppFile() noexcept
{
    for (DefaultAppIdentifier i = 0; i < DEFAULT_APP_COUNT; ++i)
    {
        v_Value.emplace_back(new Value(""));
    }
}

DefaultAppFile::~DefaultAppFile() noexcept
{
    for (auto Value : v_Value)
    {
        delete Value;
    }
}

DefaultAppFile::Value::Value(std::string const& s_PackagePath) noexcept
{
    this->s_PackagePath = s_PackagePath;
}

DefaultAppFile::Value::~Value() noexcept
{
    // Finish jobs
    std::lock_guard<std::mutex> s_Guard(s_Mutex);
}

//*************************************************************************************
// Singleton
//*************************************************************************************

DefaultAppFile& DefaultAppFile::Singleton() noexcept
{
    static DefaultAppFile s_DefaultAppFile;
    return s_DefaultAppFile;
}

//*************************************************************************************
// File
//*************************************************************************************

void DefaultAppFile::Read()
{
    try
    {
        MRH_BlockFile c_File(MRH_APP_SERVICE_DEFAULT_APP_FILE_PATH);
        
        for (auto& Block : c_File.l_Block)
        {
            if (Block.GetName().compare(p_Identifier[BLOCK_DEFAULT_PACKAGE]) != 0)
            {
                continue;
            }
            
            v_Value[CALENDAR]->SetPackagePath(Block.GetValue(p_Identifier[KEY_DEFAULT_PACKAGE_CALENDAR]));
            v_Value[CALCULATOR]->SetPackagePath(Block.GetValue(p_Identifier[KEY_DEFAULT_PACKAGE_CALCULATOR]));
            v_Value[NOTES]->SetPackagePath(Block.GetValue(p_Identifier[KEY_DEFAULT_PACKAGE_NOTES]));
            v_Value[WEB_SEARCH]->SetPackagePath(Block.GetValue(p_Identifier[KEY_DEFAULT_PACKAGE_WEB_SEARCH]));
        }
    }
    catch (MRH_BFException& e)
    {
        throw Exception(e.what2() + " (" + e.filepath2() + ")");
    }
}

void DefaultAppFile::Write()
{
    try
    {
        MRH_BlockFile c_File;
        c_File.l_Block.emplace_back(p_Identifier[BLOCK_DEFAULT_PACKAGE],
                                    MRH_APP_SERVICE_DEFAULT_APP_FILE_PATH);
        
        c_File.l_Block.back().Add(std::make_pair(p_Identifier[KEY_DEFAULT_PACKAGE_CALENDAR], v_Value[CALENDAR]->GetPackagePath()));
        c_File.l_Block.back().Add(std::make_pair(p_Identifier[KEY_DEFAULT_PACKAGE_CALCULATOR], v_Value[CALCULATOR]->GetPackagePath()));
        c_File.l_Block.back().Add(std::make_pair(p_Identifier[KEY_DEFAULT_PACKAGE_NOTES], v_Value[NOTES]->GetPackagePath()));
        c_File.l_Block.back().Add(std::make_pair(p_Identifier[KEY_DEFAULT_PACKAGE_WEB_SEARCH], v_Value[WEB_SEARCH]->GetPackagePath()));
        
        c_File.Write(MRH_APP_SERVICE_DEFAULT_APP_FILE_PATH);
    }
    catch (MRH_BFException& e)
    {
        throw Exception(e.what2() + " (" + e.filepath2() + ")");
    }
}

//*************************************************************************************
// Getters
//*************************************************************************************

std::string DefaultAppFile::Value::GetPackagePath() noexcept
{
    std::lock_guard<std::mutex> s_Guard(s_Mutex);
    return s_PackagePath;
}

std::string DefaultAppFile::GetDefaultApp(DefaultAppIdentifier u8_Identifier)
{
    if (u8_Identifier > DEFAULT_APP_MAX)
    {
        throw Exception("Invalid config identifier!");
    }
    
    std::string s_Result = v_Value[u8_Identifier]->GetPackagePath();
    
    if (s_Result.length() == 0)
    {
        throw Exception("Identifier " + std::to_string(u8_Identifier) + " has no value!");
    }
    
    return s_Result;
}

//*************************************************************************************
// Setters
//*************************************************************************************

void DefaultAppFile::Value::SetPackagePath(std::string const& s_PackagePath) noexcept
{
    std::lock_guard<std::mutex> s_Guard(s_Mutex);
    this->s_PackagePath = s_PackagePath;
}

void DefaultAppFile::SetDefaultApp(DefaultAppIdentifier u8_Identifier, std::string const& s_PackagePath)
{
    if (u8_Identifier > DEFAULT_APP_MAX)
    {
        throw Exception("Invalid config identifier!");
    }
    
    v_Value[u8_Identifier]->SetPackagePath(s_PackagePath);
}
