CBLaunchSOA
===========
The CBLaunchSOA callback is used to mirror a recieved launch 
package event to set the next launch after the current user 
package is closed.

Action
------
The callback will create the launch package response event by 
mirroring the recieved event and setting the event type to that 
of a service event. The event is added directly to 
the events to be sent to the currently used package.

.. note::

    The mirrored event will be seen by mrhcore, which only sets a 
    package to launch when the event is sent as a service event from 
    the service side.

Recieved Events
---------------
* MRH_EVENT_APP_LAUNCH_SOA_U

Returned Events
---------------
* MRH_EVENT_APP_LAUNCH_SOA_S

Files
-----
The callback is implemented in the following files:

.. code-block:: c

    Callback/Launch/CBLaunchSOA.cpp
    Callback/Launch/CBLaunchSOA.h