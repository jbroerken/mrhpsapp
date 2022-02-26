********
Building
********
The project files are already prepared and include everything except the 
required dependencies. This document lists both dependencies as well as the 
build process to create the library from source.

Supported Platforms
-------------------
The supported platforms for mrhpsapp are UNIX-likes, primarily 
Debian-based GNU/Linux Distributions like the Rapsberry Pi OS.

Dependencies
------------
This project has the following dependencies:

* mrhshared: https://github.com/jbroerken/mrhshared/
* libmrhbf: https://github.com/jbroerken/libmrhbf/
* libmrhevdata: https://github.com/jbroerken/libmrhevdata/
* libmrhpsb: https://github.com/jbroerken/libmrhpsb/

Build Tools
-----------
This release includes a CMake script (CMakeLists.txt) for a simplified build 
process. The minimal required version for CMake is 3.1.
Also needed is the GNU C++ Compiler. Full C++14 support is required.

Changing Pre-defined Settings
-----------------------------
Listed in the CMakeLists.txt file are preprocessor macros used to specify 
default file paths and other information. Change these to fit the requirements 
of the target use case.

.. list-table::
    :header-rows: 1

    * - Macro
      - Description
    * - MRH_APP_SERVICE_THREAD_COUNT
      - The number of threads to use for callbacks.
    * - MRH_APP_SERVICE_TIMED_LAUNCH_FILE_PATH
      - The file path for reading and writing timed launches.
      

Build Process
-------------
The build process should be relatively straightforward:

1. Compile Makefiles with the included CMakeLists.txt
2. Move to the "build" folder and run make.
3. Now run make install to move the binary to its location.
4. Acquire and install any required files from the mrh_os_files 
   (https://github.com/jbroerken/mrh_os_files/) repository.
   