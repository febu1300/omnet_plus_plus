//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "LinSlave.h"

Define_Module(LinSlave)

LinSlave::LinSlave()
{}

LinSlave::~LinSlave()
{}

void LinSlave::receiveFrame(cMessage *msg) {
    /*
     * todo: handle received Frames, send responses
     */

    //EV << "slave " << getIndex() << " received Frame: " << *msg << endl;
    LinRequestFrame *receivedMsg = check_and_cast<LinRequestFrame *>(msg);
    int messageId = receivedMsg -> getMessageId();
    int response;
    //response = getResponse();
    bool isMyMsg = (getIndex() == messageId);
    if(messageId >= 50){
        std::list<int> collisionId = getEventTriggeredIds(messageId);
        for(int id : collisionId){
            if(id == getIndex())
                isMyMsg = true;
        }
    }
    //EV << "slave " << getIndex() << " isMyMsg : " << isMyMsg << endl;

    if(isMyMsg){
    //EV << "slave " << getIndex() << " isMyMsg : " << endl;

        if(messageId >= 50){
            EV << "slave " << getIndex() << " received a eventTriggered message : " << messageId << endl;
            if(hasUpdatedData()){
                response = getResponse();
                sendLinResponse(messageId, response);
            }
        }
        else if(messageId >= 40 && messageId <= 49){
            EV << "slave " << getIndex() << " received a sporadic message : " << messageId << endl;
            response = getResponse();
            sendLinResponse(messageId, response);
        }
        else if(messageId >= 0 && messageId <= 39){
            EV << "slave " << getIndex() << " received a unconditional message : " << messageId << endl;
            response = getResponse();
            sendLinResponse(messageId, response);
        }
    }

    delete msg;
}

void LinSlave::sendLinResponse(int messageId, int response) {
    std::cout << simTime().ustr() << ": Slave " << getIndex() << " sends response on " << messageId << " with " << response << std::endl;
    EV << simTime().ustr() << ": Slave " << getIndex() << " sends response on " << messageId << " with " << response << endl;
    LinResponseFrame* frame = new LinResponseFrame();
    frame->setMessageId(messageId);
    frame->setResponse(response);

    sendFrame(frame);
}

int LinSlave::getResponse() const {
    return getFrameType(getIndex()) != SPORADIC_FRAME ? 42 : omnetpp::intuniform(getRNG(2), 0, 1);
}

bool LinSlave::hasUpdatedData() const {
    return omnetpp::intuniform(getRNG(3), 0, 1);
}
