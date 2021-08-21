#########################################################################
#
#  CMAKE
#
#########################################################################

###
#  Minimum Version
#  ---------------
#  The CMake version required.
###
cmake_minimum_required(VERSION 3.1)

###
#  CMake Configuration
#  -------------------
#  Configuration settings for CMake.
#
#  NOTE:
#  These settings have to be applied before the project() setting!
###
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 14)

###
#  Project Info
#  ------------
#  General simple information about our project.
###
project(mrhpsapp VERSION 1.0
                 DESCRIPTION "MRH application platform service executable"
                 LANGUAGES CXX)


#########################################################################
#
#  PATHS
#
#########################################################################

###
#  Binary Paths
#  ------------
#  The paths for our created binary file(s).
###
set(BIN_DIR_PATH "${CMAKE_SOURCE_DIR}/bin/")
file(MAKE_DIRECTORY ${BIN_DIR_PATH})

###
#  Build Paths
#  -----------
#  The paths for the cmake build.
###
set(BUILD_DIR_PATH "${CMAKE_SOURCE_DIR}/build/")
file(MAKE_DIRECTORY ${BUILD_DIR_PATH})

###
#  Source Paths
#  ------------
#  The paths to the source files to use.
#  Add OS specific source files in their own list.
###
set(SRC_DIR_PATH "${CMAKE_SOURCE_DIR}/src/")
			 
set(SRC_LIST_CALLBACK "${SRC_DIR_PATH}/Callback/Service/CBAvail.cpp"
					  "${SRC_DIR_PATH}/Callback/Service/CBAvail.h"
					  "${SRC_DIR_PATH}/Callback/Service/CBReset.cpp"
					  "${SRC_DIR_PATH}/Callback/Service/CBReset.h"
					  "${SRC_DIR_PATH}/Callback/Service/CBCustomCommand.cpp"
					  "${SRC_DIR_PATH}/Callback/Service/CBCustomCommand.h"
					  "${SRC_DIR_PATH}/Callback/Launch/CBLaunchSOA.cpp"
					  "${SRC_DIR_PATH}/Callback/Launch/CBLaunchSOA.h"
					  "${SRC_DIR_PATH}/Callback/Launch/CBLaunchSOATimer.cpp"
					  "${SRC_DIR_PATH}/Callback/Launch/CBLaunchSOATimer.h"
					  "${SRC_DIR_PATH}/Callback/Launch/CBClearLaunchSOA.cpp"
					  "${SRC_DIR_PATH}/Callback/Launch/CBClearLaunchSOA.h"
					  "${SRC_DIR_PATH}/Callback/Launch/CBClearLaunchSOATimer.cpp"
					  "${SRC_DIR_PATH}/Callback/Launch/CBClearLaunchSOATimer.h"
					  "${SRC_DIR_PATH}/Callback/DefaultApp/CBGetDefault.cpp"
					  "${SRC_DIR_PATH}/Callback/DefaultApp/CBGetDefault.h"
					  "${SRC_DIR_PATH}/Callback/DefaultApp/CBSetDefault.cpp"
					  "${SRC_DIR_PATH}/Callback/DefaultApp/CBSetDefault.h")
                      
set(SRC_LIST_LAUNCH "${SRC_DIR_PATH}/Launch/TimedLaunch.cpp"
					"${SRC_DIR_PATH}/Launch/TimedLaunch.h"
					"${SRC_DIR_PATH}/Launch/LaunchContainer.cpp"
					"${SRC_DIR_PATH}/Launch/LaunchContainer.h")
                      
set(SRC_LIST_DEFAULT_APP "${SRC_DIR_PATH}/DefaultApp/DefaultAppFile.cpp"
					     "${SRC_DIR_PATH}/DefaultApp/DefaultAppFile.h")
                     
set(SRC_LIST_SERVICE "${SRC_DIR_PATH}/Exception.h"
					 "${SRC_DIR_PATH}/Revision.h"
					 "${SRC_DIR_PATH}/Main.cpp")

###
#  Library Paths
#  -------------
#  The paths to the external libraries to use. 
#  Both the binary and include paths should be set here.
#  Add OS specific libraries in their own lists.
###
set(LIB_DIR_PATH "${CMAKE_SOURCE_DIR}/lib/")
set(INCLUDE_DIR_PATH "${CMAKE_SOURCE_DIR}/include/")

set(LIB_BIN_LIST "${LIB_DIR_PATH}/libmrhev.a"
				 "${LIB_DIR_PATH}/libmrhcevs.a"
				 "${LIB_DIR_PATH}/libmrhbf.a"
				 "${LIB_DIR_PATH}/libmrhpsb.a")
set(LIB_INCLUDE_LIST "${INCLUDE_DIR_PATH}/mrhshared"
					 "${INCLUDE_DIR_PATH}/libmrhev"
					 "${INCLUDE_DIR_PATH}/libmrhcevs"
					 "${INCLUDE_DIR_PATH}/libmrhbf"
					 "${INCLUDE_DIR_PATH}/libmrhpsb")


#########################################################################
#
#  TARGET
#
#########################################################################

###
#  Target
#  ------
#  The target(s) to build.
###
add_executable(mrhpsapp ${SRC_LIST_CALLBACK}
                        ${SRC_LIST_LAUNCH}
                        ${SRC_LIST_DEFAULT_APP}
                        ${SRC_LIST_SERVICE})
set_target_properties(mrhpsapp
    		          PROPERTIES
    		          ARCHIVE_OUTPUT_DIRECTORY ${BIN_DIR_PATH}
    		          LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR_PATH}
    		          RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR_PATH})

###
#  Required Libraries
#  ------------------
#  Libraries required by this platform service.
###
target_link_libraries(mrhpsapp PUBLIC ${LIB_BIN_LIST})
include_directories(${LIB_INCLUDE_LIST})

###
#  Source Definitions
#  ------------------
#  Preprocessor source definitions.
###
target_compile_definitions(mrhpsapp PRIVATE MRH_APP_SERVICE_THREAD_COUNT=2)
target_compile_definitions(mrhpsapp PRIVATE MRH_APP_SERVICE_DEFAULT_APP_FILE_PATH="/etc/mrhpservice/Application.conf")
target_compile_definitions(mrhpsapp PRIVATE MRH_APP_SERVICE_TIMED_LAUNCH_FILE_PATH="/var/mrhpsapp/TimedLaunch.mrhbf")