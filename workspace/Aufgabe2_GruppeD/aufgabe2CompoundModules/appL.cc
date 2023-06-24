//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include <stdlib.h>
#include <unistd.h>
#include"myMessage_m.h"

using namespace omnetpp;


class AppL : public cSimpleModule
{
private:
    MyMessage *myMsg;
    MyMessage *selfMsg;

    //record latency and priority
    cOutVector latencyVector;
    cHistogram prioStats;
    cOutVector prioVector;

public:
    AppL();
    virtual ~AppL();

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual MyMessage *generateMessage();
    virtual MyMessage *generateSelfMsg();

    virtual void finish() override;
};

Define_Module(AppL);

AppL::AppL()
{
    // set 2 pointer as nullptr to avoid crash of destructor
    selfMsg = nullptr;
    myMsg = nullptr;
}

AppL::~AppL()
{
    cancelAndDelete(selfMsg);
    delete myMsg;
}

void AppL::initialize()
{
    srand(getpid());
    selfMsg = generateSelfMsg();
    if(par("applIsMaster").boolValue() == true){
        EV << "Master send a message to 2 Slaves\n";
        // send a selfMessage
        scheduleAt(simTime()+0.08, selfMsg);
        int k=gateSize("appLOut");
        for(int i=0;i<k;i++){
            MyMessage *myMsg = generateMessage();
            send(myMsg, "appLOut", i);
        }
    }
}

void AppL::handleMessage(cMessage *msg)
{
    MyMessage *receivedMsg = check_and_cast<MyMessage *>(msg);
    if(receivedMsg == selfMsg && par("applIsMaster").boolValue()){
        selfMsg = generateSelfMsg();
        // send a selfMessage,so evety 80ms the master can send a new message
        scheduleAt(simTime()+0.08, selfMsg);
        EV << "Master send a new message to 2 Slaves"<<endl;
        int k = gateSize("appLOut");
        // send a new message from gates appLOut[0] and appLout[1]
        for(int i=0;i<k;i++){
            MyMessage *myMsg = generateMessage();
            send(myMsg, "appLOut", i);
        }
    }
    else if(receivedMsg != selfMsg && !par("applIsMaster").boolValue()){
        cGate *arrivalGate = receivedMsg->getArrivalGate();
        int gateIndex = arrivalGate->getIndex();
        // the 2 delays, the processingDelay can also use a selfMessage, but here we use sendDelayed, it not influence the results and the structure is simpler.
        simtime_t processingDelay = truncnormal(200,100)/1000000;
        simtime_t responseDelay = receivedMsg->getPriority()*0.01;
        EV << "Message arrived, after Processing delay"<<processingDelay<<"and Response delay"<<responseDelay<<"secs... send message back so Master\n";
        sendDelayed(receivedMsg, processingDelay+responseDelay, "appLOut", gateIndex);
    }
    else if(receivedMsg != selfMsg && par("applIsMaster").boolValue()){
        EV << "Master received message, the delivery is over."<<endl;
        simtime_t latency = simTime()-receivedMsg->getTimestamp();
        latencyVector.record(latency);
     }
}

MyMessage *AppL::generateMessage()
{
    // get the random priority from 1 to 3
    MyMessage *msg = new MyMessage("theMsgisGruppeD");
    int priority = rand()% 3+1;
    EV << "The priority of this message is:"<<priority<<endl;
    //update statistics
    prioVector.record(priority);
    prioStats.collect(priority);
    bool hastimestamp = 1;
    msg -> setTimestamp(simTime());
    msg -> setPriority(priority);
    msg -> setHastimestamp(hastimestamp);
    return msg;
}

MyMessage *AppL::generateSelfMsg()
{
    MyMessage *msg = new MyMessage("selfMsg");
    return msg;
}

void AppL::finish(){
    prioStats.recordAs("Priority");
}


