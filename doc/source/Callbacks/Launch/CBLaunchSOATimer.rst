CBLaunchSOATimer
================
The CBLaunchSOATimer callback is used create a timed launch
to set once the specified timepoint is reached.

Action
------
The callback will create the new timed launch which will be 
stored in the :doc:`../../Timed_Launch_List_File/Timed_Launch_List_File`.
A response event for the timed launch is then created and added 
directly to the events to be sent to the currently used package.

The timed launch will be sent as a default service launch event once 
the specified time point is reached, together with a timed launch 
reminder event. 

The timed launch will be removed once the timepoint is reached. The actual 
launch of the package does not matter for removing the timed launch.

Recieved Events
---------------
* MRH_EVENT_APP_LAUNCH_SOA_TIMER_U

Returned Events
---------------
* MRH_EVENT_APP_LAUNCH_SOA_TIMER_U
* MRH_EVENT_APP_LAUNCH_SOA_S
* MRH_EVENT_APP_LAUNCH_SOA_TIMER_REMINDER_S

Files
-----
The callback is implemented in the following files:

.. code-block:: c

    Callback/Launch/CBLaunchSOATimer.cpp
    Callback/Launch/CBLaunchSOATimer.h