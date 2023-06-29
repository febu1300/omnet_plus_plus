/*
 * txt1.cc
 *
 *  Created on: May 29, 2023
 *      Author: Buruk
 */


#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;


class Knoten : public cSimpleModule
{
  private:
   // bool role;
    cMessage* sendNewMsg = nullptr;
    cMessage* event = nullptr;

  protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
  public:
        Knoten();
        virtual ~Knoten();
};
Knoten::Knoten()
    {
        // Set the pointer to nullptr, so that the destructor won't crash
        // even if initialize() doesn't get called because of a runtime
        // error or user cancellation during the startup process.
        event = sendNewMsg = nullptr;
    }

Knoten::~Knoten ()
    {
        // Dispose of dynamically allocated the objects
        cancelAndDelete(event);
        delete sendNewMsg;
    }
// The module class needs to be registered with OMNeT++
Define_Module(Knoten);

void Knoten::initialize()
{
  //  role = par("isMaster");
  // If you are a master (isMaster==true), then you should schedule yourself to send messages every 80 ms

    // This can be done using scheduleAt(simTime(), sendNewMsg);
    event = new cMessage("event");
    if (par("isMaster")) {
        sendNewMsg = new cMessage("hi");
        sendNewMsg->setPriority();

        scheduleAt(0.08, event);
       // scheduleAt(simTime()+0.01,sendNewMsg);
        send(sendNewMsg, "out", 0);

    }

}

void Knoten::handleMessage(cMessage *msg){

    // If the msg is sendNewMsg, new messages have to be sent to the slaves
    // We need a priority for each message and send it directly
    // That meens we use send(anotherMsg, "out", k)

    int n = gateSize("out");
    int k = intuniform(0, n-1);

    // If msg is a response of a slave, then the latency is recorded
        if(msg==event){

            send(sendNewMsg, "out",k);


            sendNewMsg = nullptr;

        }
        else{

            sendNewMsg = msg;

            scheduleAt(simTime()+ msg*0.0001, event);

        }

       // send out the message–

}

