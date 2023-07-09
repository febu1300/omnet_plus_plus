#!/usr/bin/env python
#
# 2009, Christoph Sommer <christoph.sommer@informatik.uni-erlangen.de>
#
# I, the author of this work, hereby release it into the public domain.
# This applies worldwide. In case this is not legally possible:
# I grant anyone the right to use this work for any purpose, without any
# conditions, unless such conditions are required by law.
#

from string import Template
import math
import random

random.seed(123)

VEHCOLOR = ['0,1,0', '0,0,1', '1,0,0', '1,0,1']

name = 'crossing'

lanes = 3
totalcars = 2000
totaltime = 1000
runglen = 400
lanespeed = 50 / 3.6

nodfname = Template('${name}.nod.xml').substitute(name=name)
edgfname = Template('${name}.edg.xml').substitute(name=name)
confname = Template('${name}.con.xml').substitute(name=name)
netcfname = Template('${name}.netc.cfg').substitute(name=name)
netfname = Template('${name}.net.xml').substitute(name=name)
roufname = Template('${name}.rou.xml').substitute(name=name)
sumocfname = Template('${name}.sumo.cfg').substitute(name=name)

rung1 = runglen * .7
rung2 = runglen * .6
rung3 = runglen * .8
rung4 = runglen * .9 

nodtemplate = '''\
<nodes>
	<node id="c" x="0.0" y="0.0" type="traffic_light"/>
	<node id="n" x="0.0" y="$rung1" type="priority"/>
	<node id="e" x="$rung2" y="0.0" type="priority"/>
	<node id="s" x="0.0" y="-$rung3" type="priority"/>
	<node id="w" x="-$runglen" y="0.0" type="priority"/>
</nodes>
'''
nods = Template(nodtemplate).substitute(rung1 = ("%.2f" % rung1),rung2 = ("%.2f" % rung2),rung3 = ("%.2f" % rung3), runglen = ("%.2f" % runglen))

edgtemplate = '''\
<edges>
	<edge id="n" from="n" to="c" numLanes="$lanes" speed="$lanespeed" />
	<edge id="e" from="e" to="c" numLanes="$lanes" speed="$lanespeed" />
	<edge id="s" from="s" to="c" numLanes="$lanes" speed="$lanespeed" />
	<edge id="w" from="w" to="c" numLanes="$lanes" speed="$lanespeed" />
	<edge id="-n" from="c" to="n" numLanes="$lanes" speed="$lanespeed" />
	<edge id="-e" from="c" to="e" numLanes="$lanes" speed="$lanespeed" />
	<edge id="-s" from="c" to="s" numLanes="$lanes" speed="$lanespeed" />
	<edge id="-w" from="c" to="w" numLanes="$lanes" speed="$lanespeed" />
</edges>
'''
edgs = Template(edgtemplate).substitute(lanes="%d"%lanes, lanespeed="%d"%lanespeed)

contemplate = '''\
<connections>
        <connection from="w" to="-e" fromLane="0" toLane="0" />
        <connection from="w" to="-e" fromLane="1" toLane="1" />
        <connection from="w" to="-e" fromLane="2" toLane="2" />
        <connection from="w" to="-s" fromLane="0" toLane="0" />
        <connection from="w" to="-n" fromLane="2" toLane="2" />
        <connection from="w" to="-w" fromLane="2" toLane="0" />

        <connection from="e" to="-w" fromLane="0" toLane="0" />
        <connection from="e" to="-w" fromLane="1" toLane="1" />
        <connection from="e" to="-w" fromLane="2" toLane="2" />
        <connection from="e" to="-n" fromLane="0" toLane="0" />
        <connection from="e" to="-s" fromLane="2" toLane="2" />
        <connection from="e" to="-e" fromLane="2" toLane="0" />


        <connection from="s" to="-n" fromLane="0" toLane="0" />
        <connection from="s" to="-n" fromLane="1" toLane="1" />
        <connection from="s" to="-n" fromLane="2" toLane="2" />
        <connection from="s" to="-e" fromLane="0" toLane="0" />
        <connection from="s" to="-w" fromLane="2" toLane="2" />
        <connection from="s" to="-s" fromLane="2" toLane="0" />

        <connection from="n" to="-s" fromLane="0" toLane="0" />
        <connection from="n" to="-s" fromLane="1" toLane="1" />
        <connection from="n" to="-s" fromLane="2" toLane="2" />
        <connection from="n" to="-w" fromLane="0" toLane="0" />
        <connection from="n" to="-e" fromLane="2" toLane="2" />
        <connection from="n" to="-n" fromLane="2" toLane="0" />
</connections>
'''
cons = Template(contemplate).substitute()

netctemplate = '''\
<configuration>
    <input>
        <node-files value="crossing.nod.xml"/>
        <edge-files value="crossing.edg.xml"/>
        <connection-files value="crossing.con.xml"/>
    </input>
    <output>
        <output-file value="crossing.net.xml"/>
    </output>
    <processing>
        <no-turnarounds value="false"/>
        <offset.disable-normalization value="true"/>
    </processing>
    <report>
        <verbose value="true"/>
    </report>
</configuration>
'''
netc = Template(netctemplate).substitute(nodfname=nodfname, edgfname=edgfname, confname=confname, netfname=netfname)


cartemplate = '''\
   <vehicle id="veh$i" type="typedist1" route="routedist1" depart="$depart" departPos="0" departSpeed="max" />
'''
vehicles = ''
for i in range(0, totalcars):
    depart = totaltime/totalcars * i
    vehicles += Template(cartemplate).substitute(i=i,depart=depart)

routemplate = '''\
<routes>
    <routeDistribution id="routedist1">
        <route id="ns" edges="n -s" probability="0.200"/>
        <route id="ne" edges="n -e" probability="0.022"/>
        <route id="nw" edges="n -w" probability="0.022"/>
        <route id="nn" edges="n -n" probability="0.006"/>

        <route id="sn" edges="s -n" probability="0.200"/>
        <route id="se" edges="s -e" probability="0.022"/>
        <route id="sw" edges="s -w" probability="0.022"/>
        <route id="ss" edges="s -s" probability="0.006"/>

        <route id="ew" edges="e -w" probability="0.200"/>
        <route id="es" edges="e -s" probability="0.022"/>
        <route id="en" edges="e -n" probability="0.022"/>
        <route id="ee" edges="e -e" probability="0.006"/>

        <route id="we" edges="w -e" probability="0.200"/>
        <route id="ws" edges="w -s" probability="0.022"/>
        <route id="wn" edges="w -n" probability="0.022"/>
        <route id="ww" edges="w -w" probability="0.006"/>
    </routeDistribution>
    <vTypeDistribution id="typedist1">
        <vType id="type1" accel="0.8" length="5" maxSpeed="70" probability="0.9"/>
        <vType id="type2" accel="1.8" length="15" maxSpeed="50" probability="0.1"/>
    </vTypeDistribution>
$vehicles
</routes>
'''
rou = Template(routemplate).substitute(vehicles=vehicles)

sctemplate = '''\
<configuration>
	<input>
		<net-file value="$netfname"/>
		<route-files value="$roufname"/>
	</input>
	<time>
		<begin value="0"/>
		<end value="4000"/>
	</time>
	<report>
		<verbose value="true"/>
	</report>
</configuration>
'''
sc = Template(sctemplate).substitute(netfname=netfname, roufname=roufname)

print "Generating %s..." % nodfname
nodfile = open(nodfname, "w")
nodfile.write(nods)
nodfile.close()

print "Generating %s..." % edgfname
edgfile = open(edgfname, "w")
edgfile.write(edgs)
edgfile.close()

print "Generating %s..." % confname
confile = open(confname, "w")
confile.write(cons)
confile.close()

print "Generating %s..." % netcfname
netcfile = open(netcfname, "w")
netcfile.write(netc)
netcfile.close()

print "Generating %s..." % roufname
roufile = open(roufname, "w")
roufile.write(rou)
roufile.close()

print "Generating %s..." % sumocfname
sumocfile = open(sumocfname, "w")
sumocfile.write(sc)
sumocfile.close()

print "Done."

print ""
print "You can now run:"
print "netconvert -c %s" % netcfname


