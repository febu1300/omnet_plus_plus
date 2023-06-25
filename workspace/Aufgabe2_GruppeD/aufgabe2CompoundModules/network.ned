//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//
simple AppL
{
    parameters:
        bool applIsMaster = default(false);
        @display("i=block/routing");
    gates:
        input appLIn[];
        output appLOut[];
}

simple TimeL
{
    parameters:
        @display("i=block/routing");
    gates:
        input timeLIn[];
        output timeLOut[];
}

channel Channel1 extends ned.DelayChannel
{
    delay = 0ms;
}
channel Channel2 extends ned.DelayChannel
{
    delay = 0ms;
}

module ComMoudle
{
    parameters:
        bool isMaster = default(false);
        @display("bgb=346,212");
    gates:
        input in[];
        output out[];
    submodules:
        appL: AppL {
            parameters:
                @display("i=,cyan;p=86,106");
        }
            timeL: TimeL {
                parameters:
                    @display("i=,gold;p=183,90");
            }
    connections:
        appL.appLOut++ --> Channel1 --> timeL.timeLIn++;     //appLOut[0]--timLOut[0]
        appL.appLIn++ <-- Channel1 <-- timeL.timeLOut++;
        
        appL.appLOut++ --> Channel2 --> timeL.timeLIn++;     //appLOut[1]--timeLOut[1]
        appL.appLIn++ <-- Channel2 <-- timeL.timeLOut++;
		
	timeL.timeLOut++ --> Channel1 -->out++;      //timLOut[2]--out[0]
        timeL.timeLIn++ <-- Channel1 <-- in++ ;   
        
        timeL.timeLOut++ --> Channel2 -->out++;      //timLOut[3]--out[1]
        timeL.timeLIn++ <-- Channel2 <-- in++ ; 
}

network Network
{
    @display("bgb=234,159");
    submodules:
        comMoudle[3]: ComMoudle {
            @display("i=device/pc4;p=76.159996,54.739998");
        }
    connections:
        comMoudle[1].out++ --> comMoudle[2].in++;  //0-0
        comMoudle[1].in++ <-- comMoudle[2].out++; 
        
        comMoudle[0].out++ --> comMoudle[1].in++;  //0-1
        comMoudle[0].in++ <-- comMoudle[1].out++; 

	comMoudle[0].out++ --> comMoudle[2].in++;  //1-1
        comMoudle[0].in++ <-- comMoudle[2].out++; 
}

