*********
Callbacks
*********
The service uses callbacks to react to recieved events. All callbacks are 
given to libmrhpsb and executed on a callback thread. Each callback handles 
one specific event. 

Service Callbacks
-----------------
.. toctree::
  :maxdepth: 1

  Service/CBAvail
  Service/CBReset
  Service/CBCustomCommand
  
  
Launch Callbacks
----------------
.. toctree::
  :maxdepth: 1

  Launch/CBLaunchSOA
  Launch/CBLaunchSOATimer
  Launch/CBClearLaunchSOA
  Launch/CBClearLaunchSOATimer