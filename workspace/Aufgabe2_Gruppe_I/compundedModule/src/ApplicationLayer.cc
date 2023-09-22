//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include <stdlib.h>
#include <unistd.h>

#include "myMessage_m.h"

using namespace omnetpp;


class ApplicationLayer : public cSimpleModule
{
private:
    MyMessage *myMsg;
    MyMessage *selfMsg;

    //record latency and priority
    cOutVector latencyVector;
    cHistogram prioStats;
    cOutVector prioVector;

    int msgcount;
public:
    ApplicationLayer();
    virtual ~ApplicationLayer();

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual MyMessage *generateMessage();
    virtual MyMessage *generateSelfMsg();

    virtual void finish() override;
};

Define_Module(ApplicationLayer);

ApplicationLayer::ApplicationLayer()
{
    // set 2 pointer as nullptr to avoid crash of destructor
    selfMsg = nullptr;
    myMsg = nullptr;
}

ApplicationLayer::~ApplicationLayer()
{
    cancelAndDelete(selfMsg);
    cancelAndDelete(myMsg);
    delete myMsg;
}

void ApplicationLayer::initialize()
{
    latencyVector.setName("latency Vector");
    prioVector.setName("Priority Vector");

    srand(getpid());
    selfMsg = generateSelfMsg();

    if(par("isMaster").boolValue() == true){
        EV << "Master send a message to 2 Slaves\n";
        // send a selfMessage
        scheduleAt(simTime()+0.08, selfMsg);
        int k=gateSize("appOut");
        for(int i=0;i<k;i++){
            MyMessage *myMsg = generateMessage();
            send(myMsg, "appOut", i);
        }
    }


}

void ApplicationLayer::handleMessage(cMessage *msg)
{
    MyMessage *receivedMsg = check_and_cast<MyMessage *>(msg);
    auto priority = receivedMsg->getPriority();

    if(receivedMsg == myMsg){
        EV<<"Is the received message my message "<<endl;
    }
            if(receivedMsg == selfMsg && par("isMaster").boolValue()){

        selfMsg = generateSelfMsg();
        // send a selfMessage,so evety 80ms the master can send a new message
        scheduleAt(simTime()+0.08, selfMsg);
        EV << "Master send a new message to 2 Slaves"<<endl;
        int k = gateSize("appOut");
        // send a new message from gates appOut[0] and appOut[1]
        for(int i=0;i<k;i++){
            MyMessage *myMsg = generateMessage();
            send(myMsg, "appOut", i);
        }
    }
    else if(receivedMsg != selfMsg && !par("isMaster").boolValue()){
        cGate *arrivalGate = receivedMsg->getArrivalGate();
        int gateIndex = arrivalGate->getIndex();
        // the 2 delays, the processingDelay can also use a selfMessage, but here we use sendDelayed, it not influence the results and the structure is simpler.
        simtime_t processingDelay = truncnormal(200,100)/1000000;
        simtime_t responseDelay = priority*0.01;



        EV<<"With Delay Arrived"<<endl;
        EV << "Message arrived, after Processing delay"<<processingDelay<<"and Response delay"<<responseDelay<<"secs... send message back so Master\n";
        sendDelayed(receivedMsg, processingDelay+responseDelay, "appOut", gateIndex);

    }
    else if(receivedMsg != selfMsg && par("isMaster").boolValue()){
        EV << "Master received message, the delivery is over."<<endl;
        simtime_t latency = simTime()-receivedMsg->getTimestamp();
        latencyVector.record(latency);


     }
            cancelAndDelete(receivedMsg);

}

MyMessage *ApplicationLayer::generateMessage()
{
    // get the random priority from 1 to 3
    MyMessage *msg = new MyMessage("theMsgisGruppeD");
    int priority = rand()% 3+1;
    EV << "The priority of this message is:"<<priority<<endl;
    //update statistics

    bool hastimestamp = 1;
    msg -> setTimestamp(simTime());
    msg -> setPriority(priority);
    msg -> setHastimestamp(hastimestamp);

    prioVector.record(priority);
     prioStats.collect(priority);

    return msg;
}

MyMessage *ApplicationLayer::generateSelfMsg()
{
    MyMessage *msg = new MyMessage("selfMsg");
    return msg;
}

void ApplicationLayer::finish(){

  prioStats.recordAs("Priority");

}

