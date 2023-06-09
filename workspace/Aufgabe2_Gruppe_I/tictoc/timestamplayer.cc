/*
 * txt1.cc
 *
 *  Created on: May 29, 2023
 *      Author: Buruk
 */




#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;


class TimeStampLayer : public cSimpleModule
{
  private:
   // bool role;
    cMessage* sendNewMsg = nullptr;
    cMessage* timeMsg = nullptr;

  protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

// The module class needs to be registered with OMNeT++
Define_Module(TimeStampLayer);

void TimeStampLayer::initialize()
{
  //  role = par("isMaster");
  // If you are a master (isMaster==true), then you should schedule yourself to send messages every 80 ms
    sendNewMsg = new cMessage("message");
    // This can be done using scheduleAt(simTime(), sendNewMsg);

    if (par("isMaster")) {
        cMessage *msg = new cMessage("hi");
        send(msg, "port_out");
    }

}

void TimeStampLayer::handleMessage(cMessage *msg){

    // If the msg is sendNewMsg, new messages have to be sent to the slaves
    // We need a priority for each message and send it directly
    // That meens we use send(anotherMsg, "out", k)


    // If msg is a response of a slave, then the latency is recorded

    if(!par("isMaster")){

        }

   // int n = gateSize("out");
    //int k = intuniform(0, n-1);

    msg->addPar("isMaster");
   // msg->setTimestamp();

    //EV << "Forwarding message " << msg->getName() << msg->getTimestamp() <<" on gate[" << k+1 << "]\n";

    send(msg, "port_out"); // send out the message–

}

