/*
 * txt1.cc
 *
 *  Created on: May 29, 2023
 *      Author: adm_bur7746m
 */




#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;


class Knot : public cSimpleModule
{
  private:
   // bool role;

  protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

// The module class needs to be registered with OMNeT++
Define_Module(Knot);

void Knot::initialize()
{
  //  role = par("isMaster");

    if (par("isMaster")) {

        cMessage *msg = new cMessage("hi");

        send(msg, "out", 0);

    } else if(!par("isMaster")){

    }


}

void Knot::handleMessage(cMessage *msg)

{
    int n = gateSize("out");
    int k = intuniform(0, n-1);

    msg->addPar("isMaster");
    msg->setTimestamp();

    EV << "Forwarding message " << msg->getName() << msg->getArrivalTime() <<" on gate[" << k+1 << "]\n";

    send(msg, "out",k); // send out the message–



}

