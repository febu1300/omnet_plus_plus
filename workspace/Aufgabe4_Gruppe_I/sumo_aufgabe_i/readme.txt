To convert trips file to route file 
 duarouter -n net.net.xml --route-files trips.trips.xml -o paris.rou.xml 

To generate a route file directly we can use -r  option and specify the rou.xml file, we wish to save on. 

  randomTrips.py -b 0 -e 600 -p 0.2 -r routes.rou.xml --trip-attributes="departLane=\"best\" departSpeed=\"max\" departPos=\"random\"" -n net.net.xml
  sumo-gui -c net.sumo.cfg 

poly.xml and sumo.cfg file can be imported from Sumo website

Types of trafic participants 
Beim kreuzungen overlap the vehichle output 
