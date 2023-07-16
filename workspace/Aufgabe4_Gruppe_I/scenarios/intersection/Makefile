all: crossing.net.xml

crossing.net.xml: crossing.edg.xml
	netconvert -c crossing.netc.cfg

crossing.edg.xml: crossing-gen.py
	./crossing-gen.py
