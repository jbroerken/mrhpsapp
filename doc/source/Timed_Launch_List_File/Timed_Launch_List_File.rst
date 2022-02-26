**********************
Timed Launch List File
**********************
mrhpsapp uses a timed launch list file to store requested timed launches. This file 
is loaded on service start and written to once a new timed launch is recieved or a 
requested timed launch is performed.

The timed launch list file uses the MRH Block File format.

File Structure
--------------
The block file stores multiple blocks of the same name, one for each timed launch 
to performed. The name of this block is **TimedLaunch** and contains the timed launch 
info required to perform a package launch.

Timed Launch Block
------------------
Every timed launch block is arranged the same way. Stored are the following values:

.. list-table::
    :header-rows: 1

    * - Key
      - Description
    * - OwnerPackagePath
      - The full package path of the package which requested the launch.
    * - LaunchPackagePath
      - The full package path of the package to launch.
    * - LaunchInput
      - The launch input to launch the package with.
    * - LaunchCommandID
      - The launch command id to launch the package with.
    * - LaunchTimepointS
      - The time point in seconds from epoch when the launch should be 
        performed.


Example
-------
The following example shows a timed launch list file with a single 
stored timed launch:

.. code-block:: c

    <MRHBF_1>
    
    <TimedLaunch>{
        <OwnerPackagePath></opt/mrh/owner.soa>
        <LaunchPackagePath></opt/mrh/launch.soa>
        <LaunchInput><Hello world!>
        <LaunchCommandID><0>
        <LaunchTimepointS><123456789>
    }
    
