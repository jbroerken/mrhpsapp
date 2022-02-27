CBClearLaunchSOA
================
The CBClearLaunchSOA callback is used to mirror a recieved 
clear launch event.

Action
------
The callback will create the clear launch response event by 
mirroring the recieved event and setting the event type to that 
of a service event. The event is added directly to the events to 
be sent to the currently used package.

.. note::

    The mirrored event will be seen by mrhcore, which only clears a 
    currently set launch when the event is sent as a service event 
    from the service side.

Recieved Events
---------------
* MRH_EVENT_APP_LAUNCH_SOA_CLEAR_U

Returned Events
---------------
* MRH_EVENT_APP_LAUNCH_SOA_CLEAR_S

Files
-----
The callback is implemented in the following files:

.. code-block:: c

    Callback/Launch/CBClearLaunchSOA.cpp
    Callback/Launch/CBClearLaunchSOA.h