#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include <stdlib.h>
#include <unistd.h>
#include "myMessage_m.h"

using namespace omnetpp;

class Node : public cSimpleModule
{
private:
    MyMessage *myMsg;
    MyMessage *selfMsg;

    //record latency and priority
    cOutVector latencyVector;
    cHistogram prioStats;
    cOutVector prioVector;


public:
    Node();
    virtual ~Node();


protected:
    virtual MyMessage *generateMessage();
    virtual MyMessage *generateSelfMsg();
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

//for test5, finish to record Stats
    virtual void finish() override;
};

Define_Module(Node);


Node::Node()
{
    selfMsg = nullptr;          // set 2 pointer as nullptr to avoid crash of destructor
    myMsg = nullptr;
}
Node::~Node()
{
    cancelAndDelete(selfMsg);           // Dispose of dynamically allocated the objects
    delete myMsg;
}


void Node::initialize()
{
    selfMsg = generateSelfMsg();
    srand(getpid());
    // if isMaster is true, means this node is master, here master is node[0]
    if(par("isMaster").boolValue() == true){
        EV << "Master send a message to Slaves"<<endl;
        scheduleAt(simTime()+0.08, selfMsg);
        int k = gateSize("out");
        for(int i=0;i<k;i++){
            MyMessage *myMsg = generateMessage();
            send(myMsg, "out", i);
        }
    }
}

void Node::handleMessage(cMessage *msg)
{
    MyMessage *receivedMsg = check_and_cast<MyMessage *>(msg);
    if(receivedMsg == selfMsg && par("isMaster").boolValue()){
        selfMsg = generateSelfMsg();
        // send a selfMessage,so evety 80ms the master can send a new message
        scheduleAt(simTime()+0.08, selfMsg);
        int k = gateSize("out");
        for(int i=0;i<k;i++){
            MyMessage *myMsg = generateMessage();
            send(myMsg, "out", i);}
        EV << "Master send a new message to Slaves"<<endl;
    }
    else if(receivedMsg != selfMsg && !par("isMaster").boolValue()){
        //2 delays, the processingDelay can also use a selfMessage, but here we use sendDelayed, it not influence the results and the structure is simpler.
        simtime_t processingDelay = truncnormal(200,100)/1000000;
        simtime_t responseDelay = receivedMsg->getPriority()*0.01;
        EV << "Message arrived, after Processing delay"<<processingDelay<<"and Response delay"<<responseDelay<<"secs... send message back so Master\n";
        sendDelayed(receivedMsg, processingDelay+responseDelay, "out", 0);
        }
    else if(receivedMsg != selfMsg && par("isMaster").boolValue()){
        EV << "Master received message, the delivery is over."<<endl;
        simtime_t latency = simTime()-receivedMsg->getTimestamp();
        latencyVector.record(latency);
    }

}

MyMessage *Node::generateMessage()
{
    // get the random priority from 1 to 3
    MyMessage *msg = new MyMessage("theMsgisGruppeD");
    int priority = rand()% 3+1;
    EV << "The priority of this message is:"<<priority<<endl;
    //update statistics
    prioVector.record(priority);
    prioStats.collect(priority);
    msg -> setTimestamp(simTime());
    msg -> setPriority(priority);
    return msg;
}

MyMessage *Node::generateSelfMsg()
{
    MyMessage *msg = new MyMessage("selfMsg");
    return msg;
}


void Node::finish(){
    prioStats.recordAs("Priority");
}

