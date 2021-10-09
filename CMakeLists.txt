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
project(mrhpsapp VERSION 1.0.0
                 DESCRIPTION "MRH application platform service executable"
                 LANGUAGES CXX)

#########################################################################
#
#  PATHS
#
#########################################################################

###
#  Install Paths
#  -------------
#  The paths for our created binary file(s).
###
set(BIN_INSTALL_PATH "/usr/local/bin/")

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
                      "${SRC_DIR_PATH}/Callback/Launch/CBClearLaunchSOATimer.h")
                      
set(SRC_LIST_LAUNCH "${SRC_DIR_PATH}/Launch/TimedLaunch.cpp"
                    "${SRC_DIR_PATH}/Launch/TimedLaunch.h"
                    "${SRC_DIR_PATH}/Launch/LaunchContainer.cpp"
                    "${SRC_DIR_PATH}/Launch/LaunchContainer.h")
                     
set(SRC_LIST_SERVICE "${SRC_DIR_PATH}/Exception.h"
                     "${SRC_DIR_PATH}/Revision.h"
                     "${SRC_DIR_PATH}/Main.cpp")

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
                        ${SRC_LIST_SERVICE})

###
#  Required Libraries
#  ------------------
#  Libraries required by this platform service.
###
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)

find_package(Threads REQUIRED)
find_library(libmrhbf NAMES mrhbf REQUIRED)
find_library(libmrhev NAMES mrhev REQUIRED)
find_library(libmrhcevs NAMES mrhcevs REQUIRED)
find_library(libmrhpsb NAMES mrhpsb REQUIRED)

target_link_libraries(mrhpsapp PUBLIC Threads::Threads)
target_link_libraries(mrhpsapp PUBLIC mrhbf)
target_link_libraries(mrhpsapp PUBLIC mrhev)
target_link_libraries(mrhpsapp PUBLIC mrhcevs)
target_link_libraries(mrhpsapp PUBLIC mrhpsb)

###
#  Source Definitions
#  ------------------
#  Preprocessor source definitions.
###
target_compile_definitions(mrhpsapp PRIVATE MRH_APP_SERVICE_THREAD_COUNT=1)
target_compile_definitions(mrhpsapp PRIVATE MRH_APP_SERVICE_TIMED_LAUNCH_FILE_PATH="/var/mrh/mrhpsapp/TimedLaunch.mrhbf")

###
#  Install
#  -------
#  Application installation.
###
install(TARGETS mrhpsapp
        DESTINATION ${BIN_INSTALL_PATH})