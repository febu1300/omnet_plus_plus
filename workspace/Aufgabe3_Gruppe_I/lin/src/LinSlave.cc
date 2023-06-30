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

        LinRequestFrame *receivedFrame = dynamic_cast<LinRequestFrame*>(msg);

              int responseMessageId = receivedFrame->getMessageId();
              bool isSproadConditional = (getIndex() == responseMessageId);

              EV <<"Sporadic "<< isSproadConditional <<"\n";
             int response;
             bool isMyMsg = (getIndex() == responseMessageId);

                if(responseMessageId >= 50){
                    std::list<int> collisionId = getEventTriggeredIds(responseMessageId);
                    for(int id : collisionId){
                        if(id == getIndex())
                            isMyMsg = true;
                    }
                }

                if(isMyMsg && isSproadConditional==0){

              if(responseMessageId  >= 50){
                      EV <<"Recieved Message ID"<< responseMessageId <<"\n";
                      response = getResponse();

                      sendLinResponse(responseMessageId , response);
              }
              else  if(responseMessageId  >= 40 && responseMessageId <= 49){
                      EV <<"Recieved Message ID  "<< responseMessageId  <<"\n";
                      response = getResponse();
                      scheduleAt(simTime(), msg);

                      sendLinResponse(responseMessageId , response);
                  }
              if(responseMessageId  >= 0 && responseMessageId  <= 39){
                  scheduleAt(simTime(), msg);
                      EV <<"Recieved Message ID  "<< responseMessageId  <<"\n";
                      response = getResponse();
                      sendLinResponse(responseMessageId , response);
              }

                }

    delete msg;
}

void LinSlave::sendLinResponse(int messageId, int response) {
    std::cout << simTime().ustr() << ": Slave " << getIndex() << " sends response on " << messageId << " with " << response << std::endl;
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
