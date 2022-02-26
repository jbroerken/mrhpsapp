CBReset
=======
The CBReset callback is used to react to a new user package 
being used.

Action
------
The callback will set the current package path to use as the 
owner package path for the timed launch container. The owner 
package path is used when storing and clearing timed package 
launches.

Recieved Events
---------------
* MRH_EVENT_PS_RESET_REQUEST_U

Returned Events
---------------
None.

Files
-----
The callback is implemented in the following files:

.. code-block:: c

    Callback/Service/CBReset.cpp
    Callback/Service/CBReset.h