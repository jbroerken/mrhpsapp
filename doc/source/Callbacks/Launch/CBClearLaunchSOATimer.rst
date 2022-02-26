CBClearLaunchSOATimer
=====================
The CBClearLaunchSOATimer callback is used to clear currently 
waiting timed launches.

Action
------
The callback will create the clear launch response event and add 
it directly to the events to be sent to the currently used package.

Only timed launches created by the currently used user package, 
identified as the owner package, will be cleared. This is set on 
recieving a service reset event, and handled by the :doc:`../Service/CBReset` 
callback.

Recieved Events
---------------
* MRH_EVENT_APP_LAUNCH_SOA_CLEAR_TIMER_U

Returned Events
---------------
* MRH_EVENT_APP_LAUNCH_SOA_CLEAR_TIMER_S

Files
-----
The callback is implemented in the following files:

.. code-block:: c

    Callback/Launch/CBClearLaunchSOATimer.cpp
    Callback/Launch/CBClearLaunchSOATimer.h