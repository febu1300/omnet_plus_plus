#include <stdio.h>
#include <string.h>
#include <omnetpp.h>

#include "myMessage_m.h"

using namespace omnetpp;


class TimestampLayer : public cSimpleModule
{
private:
  //  MyMessage *myMsg;

protected:
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(TimestampLayer);


void TimestampLayer::handleMessage(cMessage *msg)
{
    MyMessage *receivedMsg = check_and_cast<MyMessage *>(msg);
    cGate *arrivalGate = receivedMsg->getArrivalGate();
    int gateIndex = arrivalGate->getIndex();
    if(gateIndex <2){
        if(!receivedMsg->getHastimestamp()){
            EV << "the message has not timestamp, add a timestamp\n";
            receivedMsg -> setTimestamp(simTime());
            receivedMsg -> setHastimestamp(1);
        }
        else{
            EV << "the message has timestamp, do nothing\n";
        }
        EV<< "timestamp is sending msg"<<endl;
        send(receivedMsg, "tstampOut", gateIndex+2);
    }
    else{
        send(receivedMsg, "tstampOut", gateIndex-2);
    }
}
