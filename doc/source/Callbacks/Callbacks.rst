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

  Service Availability <Service/CBAvail>
  Service Reset <Service/CBReset>
  Custom Command <Service/CBCustomCommand>
  
  
Launch Callbacks
----------------
.. toctree::
  :maxdepth: 1

  Request Launch <Launch/CBLaunchSOA>
  Request Timed Launch <Launch/CBLaunchSOATimer>
  Clear Launch <Launch/CBClearLaunchSOA>
  Clear Timed Launch <Launch/CBClearLaunchSOATimer>