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
  protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

// The module class needs to be registered with OMNeT++
Define_Module(Knot);

void Knot::initialize()
{


    if (strcmp("k1", getName()) == 0) {

        cMessage *msg = new cMessage("the Message");
        send(msg, "out");
    }
}

void Knot::handleMessage(cMessage *msg)
{

    send(msg, "out"); // send out the message
}

