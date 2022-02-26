************
Service Info
************
mrhpsapp is the default application service used by the MRH platform. 
This service only implements default application events.

Service Identifiers
-------------------
The service uses the following identifiers:

.. list-table::
    :header-rows: 1

    * - Identifier
      - Value
    * - Supplier ID
      - MRH (0x4d524800)
    * - Binary ID
      - APP (0x41505000)
    * - Version
      - 1


Features
--------
The following features are provided by the service:
  
.. list-table::
    :header-rows: 1

    * - Feature
      - Description
    * - Handle launch request
      - The service can recieve and mirror launch requests.
    * - Handle timed launch request
      - The service can recieve and store timed launch requests. These 
        requests are performed sent once the set time point is reached. 
        The service will send a timed launch reminder together with the 
        launch event.
    * - Clear all set launch
      - The service can clear all set launches on request.
    * - Clear all timed launches
      - The service can clear all currently stored timed launches.

  
Events
------
The following events are handled by the service:

* MRH_EVENT_PS_RESET_REQUEST_U
* MRH_EVENT_APP_AVAIL_U
* MRH_EVENT_APP_CUSTOM_COMMAND_U
* MRH_EVENT_APP_LAUNCH_SOA_U
* MRH_EVENT_APP_LAUNCH_SOA_TIMER_U
* MRH_EVENT_APP_LAUNCH_SOA_CLEAR_U
* MRH_EVENT_APP_LAUNCH_SOA_CLEAR_TIMER_U

.. note::
    
    Custom command events will return the event MRH_EVENT_NOT_IMPLEMENTED_S!