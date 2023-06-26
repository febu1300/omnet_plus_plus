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

#include "LinMaster.h"

Define_Module(LinMaster)

LinMaster::LinMaster() {
}

LinMaster::~LinMaster() {
    cancelAndDelete(sendNewMsg);
    cancelAndDelete(selfEvent);
    cancelAndDelete(changeSporadic);
}

void LinMaster::initialize() {
    needSporadic = false;
    changeSporadic = new cMessage("changeSporadic");
    scheduleAt(simTime() + SimTime(omnetpp::uniform(getRNG(0), 2, 4), SimTimeUnit::SIMTIME_S), changeSporadic);

    /*
     * todo: initialize all variables needed and schedule the first LIN-frame for the time step 10ms
     */

}

void LinMaster::finish() {

    test();

    /*
     * Record final statistics
     */
}

void LinMaster::handleSelfMessage(cMessage *msg) {

    if (msg == changeSporadic) {
        needSporadic = true;
        scheduleAt(simTime() + SimTime(omnetpp::uniform(getRNG(0), 2, 4), SimTimeUnit::SIMTIME_S), changeSporadic);
    }

    /*
     * todo: handle self messages in order to send next packet or check timeouts
     */

}

void LinMaster::receiveFrame(cMessage *msg) {

    /*
     * todo: handle received Frames, check for collisions
     */

    delete msg;
}


int LinMaster::getRandomMessageId(FRAME_TYPE frameType) const {
    switch (frameType){
    case (FRAME_TYPE::UNCONDITIONAL_FRAME):{
        return omnetpp::intuniform(getRNG(1), FIRST_UNCONDITIONAL, LAST_UNCONDITIONAL);
    }
    case (FRAME_TYPE::SPORADIC_FRAME):{
        return omnetpp::intuniform(getRNG(1), FIRST_SPORADIC, LAST_SPORADIC);
        }
    case (FRAME_TYPE::EVENT_TRIGGERED_FRAME):{
        return omnetpp::intuniform(getRNG(1), FIRST_EVENT_TRIGGERED, LAST_EVENT_TRIGGERED);
        }
    default:{
        ASSERT2(false, "No message id can be generated for the type UNKNOWN!");
    }
    }
    return -1;
}

void LinMaster::sendLinRequest(int messageId) {

    std::cout << simTime().ustr() << ": Master sends ";
    auto frameType = getFrameType(messageId);
    switch(frameType){
    case UNCONDITIONAL_FRAME:{
        std::cout << "an unconditional frame ";
        break;
    }
    case SPORADIC_FRAME:{
        std::cout << "a sporadic frame ";
        break;
    }
    case EVENT_TRIGGERED_FRAME:{
        std::cout << "an event-triggered frame ";
        break;
    }
    default: {}
    }
    std::cout << "with ID " << messageId << std::endl;


    LinRequestFrame *frame = new LinRequestFrame();
    frame->setMessageId(messageId);
    sendFrame(frame);

    auto t = simTime();
    if (t < .2){  // Record the start
        testRecording0.push_back(messageId);
    } else if (t >= 2.9 && t < 3.08){// Record somewhere in the middle
        testRecording1.push_back(messageId);
    }
    testSent[frameType]++;
}

void LinMaster::test() const {
    std::cout << std::endl << "**************** STARTING TESTS ****************" << std::endl;

    bool testRecordingsMatch = true;
    std::cout << "Testing the start of the simulation..." << std::endl;
    std::vector<int> toBeRecording0 = {37, 12, 8, 9, 11, 5, 50, 0, 1, 2, 3, 16, 1, 57, 6, 25, 20, 37, 18};
    for ( int i = 0; i < toBeRecording0.size(); i++){
        if (toBeRecording0[i] != testRecording0[i]){
            std::cout << toBeRecording0[i] << " expected. Got " << testRecording0[i] << std::endl;
            testRecordingsMatch = false;
        }
    }

    if (testRecordingsMatch){
        std::cout << "Testing the middle of the simulation..." << std::endl;
        std::vector<int> toBeRecording1 = {2, 3, 32, 28, 57, 28, 29, 30, 31, 18, 48, 53, 12, 48, 13, 14, 15, 32};
        for ( int i = 0; i < toBeRecording1.size(); i++){
            if (toBeRecording1[i] != testRecording1[i]){
                std::cout << toBeRecording1[i] << " expected. Got " << testRecording1[i] << std::endl;
                testRecordingsMatch = false;
            }
        }
    }


    std::cout << "Checking the amount of sent request frames..." << std::endl;
    std::vector<int> toBeSent = {5104, 857, 39};
    if (toBeSent[UNCONDITIONAL_FRAME] != testSent[UNCONDITIONAL_FRAME]){
        std::cout << toBeSent[UNCONDITIONAL_FRAME] << " unconditional frames expected. Got " << testSent[UNCONDITIONAL_FRAME] << std::endl;
    }
    if (toBeSent[SPORADIC_FRAME] != testSent[SPORADIC_FRAME]){
        std::cout << toBeSent[SPORADIC_FRAME] << " sporadic frames expected. Got " << testSent[SPORADIC_FRAME] << std::endl;
    }
    if (toBeSent[EVENT_TRIGGERED_FRAME] != testSent[EVENT_TRIGGERED_FRAME]){
        std::cout << toBeSent[EVENT_TRIGGERED_FRAME] << " event-triggered frames expected. Got " << testSent[EVENT_TRIGGERED_FRAME] << std::endl;
    }

    if (getRNG(0)->getNumbersDrawn() != 23){
        std::cout << "It seems you have used the RNG(0) somewhere! Don't use it! This messed up the needSporadic interval." << std::endl;
    }

    if (getRNG(1)->getNumbersDrawn() != 3638){
        std::cout << "It seems you have requested to " << (getRNG(1)->getNumbersDrawn() > 3638 ? "many" : "few") << " random message IDs! You might want to check your scheduling logic." << std::endl;
    }

    if (getRNG(2)->getNumbersDrawn() != 39){
        std::cout << "It seems you have sent to " << (getRNG(2)->getNumbersDrawn() > 39 ? "many" : "few") << " sporadic frames! You might want to check your scheduling logic." << std::endl;
    }

    if (getRNG(3)->getNumbersDrawn() != 3428){
        std::cout << "It seems you have responded " << (getRNG(3)->getNumbersDrawn() > 3428 ? "to often" : "to rarely") << " to event-triggered frames sporadic frames! You might want to check your scheduling logic." << std::endl;
    }

    std::cout << std::endl << "**************** TESTS FINISHED ****************" << std::endl;
}
