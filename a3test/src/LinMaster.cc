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
}

void LinMaster::initialize() {
    needSporadic = true;
    changeSporadic = new cMessage("changeSporadic");
    scheduleAt(simTime() + SimTime(omnetpp::uniform(getRNG(0), 2, 4), SimTimeUnit::SIMTIME_S), changeSporadic);

    /*
     * todo: initialize all variables needed and schedule the first LIN-frame for the time step 10ms
     */

     //unconditional = new cMessage("unconditional");
     //scheduleAt(simTime() + 0.01, unconditional);

     //sporadic = new cMessage("sporadic");
     //scheduleAt(simTime() + 0.03, sporadic);

     //eventTriggered = new cMessage("eventTriggered");
     //scheduleAt(simTime() + 0.07, eventTriggered);

     checkAntwort = new cMessage("checkAntwort");
     numcollision = 0;

     selfMessage = new cMessage("selfMessage");
     scheduleAt(simTime() + 0.01, selfMessage);
}

void LinMaster::finish() {

    test();

    /*
     * Record final statistics
     */
}

void LinMaster::handleSelfMessage(cMessage *msg) {
    int64_t rawTime = simTime().raw();
    int64_t millisecondTime = static_cast<int64_t>(rawTime / 1000000000);

    //EV << "now simeTime : "<< static_cast<int>(simTime().dbl() * 1000) << "ms" << endl;
    EV << "now millisecondTime : "<< millisecondTime << "ms" << endl;

    if (msg == changeSporadic) {
        needSporadic = true;
        EV << "Master send a new selfmessage changeSporadic"<<endl;
        scheduleAt(simTime() + SimTime(omnetpp::uniform(getRNG(0), 2, 4), SimTimeUnit::SIMTIME_S), changeSporadic);
    }

    /*
     * todo: handle self messages in order to send next packet or check timeouts
     */

    if(msg == checkAntwort){
        if(numcollision > 1)
            numcollision = UNCONDITIONALS_PER_EVENT_TRIGGERED;
        else{
            numcollision = 0;
            collisionId.clear();
        }
    }
    

    if(msg == selfMessage){
        scheduleAt(simTime() + 0.01, selfMessage);

        if(millisecondTime%70 == 0){
            //EV << "now simeTime : "<< millisecondTime << "ms" << endl;
            EV << "Master received a selfmessage eventTriggered"<<endl;
            int messageId = getRandomMessageId(FRAME_TYPE::EVENT_TRIGGERED_FRAME);
            EV << "Master send a new eventTriggered message to salves : " << messageId << endl;
            recordMsgId.record(messageId);
            sendLinRequest(messageId);
            EV << "Master send a new selfmessage checkAntwort"<<endl;
            scheduleAt(simTime() + 0.001, checkAntwort);
        }

        else if (millisecondTime%30 ==0 && needSporadic) {
            //EV << "now simeTime : "<< millisecondTime << "ms" << endl;
            EV << "Master received a selfmessage sporadic and the value of needSporadic is "<< needSporadic <<endl;

                int messageId = getRandomMessageId(FRAME_TYPE::SPORADIC_FRAME);
                EV << "Master send a new sporadic message to salves : " << messageId << endl;
                recordMsgId.record(messageId);
                sendLinRequest(messageId);
        }
        else{
            //EV << "Master received a selfmessage unconditional"<<endl;
            if(numcollision > 0){
                EV << "There are now "<< numcollision << " slaves waiting to be checked" << endl;
                //sendLinRequest(collisionId[UNCONDITIONALS_PER_EVENT_TRIGGERED-numcollision]);
                std::list<int>::iterator iter = collisionId.begin();
                std::advance(iter, UNCONDITIONALS_PER_EVENT_TRIGGERED - numcollision);
                EV << "Master send a new unconditional message and see what is going wrong: " << *iter << endl;
                recordMsgId.record(*iter);
                sendLinRequest(*iter);
                numcollision--;
                if(numcollision == 0) collisionId.clear();
                return;
            }
            int messageId = getRandomMessageId(FRAME_TYPE::UNCONDITIONAL_FRAME);
            EV << "Master send a new unconditional message to salves : " << messageId << endl;
            recordMsgId.record(messageId);
            sendLinRequest(messageId);
        }

    }

    /*
     if(millisecondTime%70 == 0 && msg == eventTriggered){
        //EV << "now simeTime : "<< millisecondTime << "ms" << endl;
        EV << "Master send a new selfmessage eventTriggered"<<endl;
        scheduleAt(simTime() + 0.07, eventTriggered);
        int messageId = getRandomMessageId(FRAME_TYPE::EVENT_TRIGGERED_FRAME);
        EV << "Master send a new eventTriggered message to salves : " << messageId << endl;
        recordMsgId.record(messageId);
        sendLinRequest(messageId);
        EV << "Master send a new selfmessage checkAntwort"<<endl;
        scheduleAt(simTime() + 0.001, checkAntwort);
    }

    else if (millisecondTime%30 == 0 && msg == sporadic) {
        //EV << "now simeTime : "<< millisecondTime << "ms" << endl;
        EV << "Master send a new selfmessage sporadic and the value of needSporadic is "<< needSporadic <<endl;
        scheduleAt(simTime() + 0.03, sporadic);
        if(millisecondTime%70 == 0 || !needSporadic) return;
        int messageId = getRandomMessageId(FRAME_TYPE::SPORADIC_FRAME);
        EV << "Master send a new sporadic message to salves : " << messageId << endl;
        recordMsgId.record(messageId);
        sendLinRequest(messageId);
    }

    else if(millisecondTime%10 == 0 && msg == unconditional){
        //EV << "now simeTime : "<< millisecondTime << "ms" << endl;
        EV << "Master send a new selfmessage unconditional"<<endl;
        scheduleAt(simTime() + 0.01, unconditional);
        if(millisecondTime%70 == 0 || (millisecondTime%30 == 0 && needSporadic)) return;
        if(numcollision > 0){
            EV << "There are now "<< numcollision << " slaves waiting to be checked" << endl;
            //sendLinRequest(collisionId[UNCONDITIONALS_PER_EVENT_TRIGGERED-numcollision]);
            std::list<int>::iterator iter = collisionId.begin();
            std::advance(iter, UNCONDITIONALS_PER_EVENT_TRIGGERED - numcollision);
            EV << "Master send a new unconditional message and see what is going wrong: " << *iter << endl;
            recordMsgId.record(*iter);
            sendLinRequest(*iter);
            numcollision--;
            if(numcollision == 0) collisionId.clear();
            return;
        }
        int messageId = getRandomMessageId(FRAME_TYPE::UNCONDITIONAL_FRAME);
        EV << "Master send a new unconditional message to salves : " << messageId << endl;
        recordMsgId.record(messageId);
        sendLinRequest(messageId);
    }
    */

}

void LinMaster::receiveFrame(cMessage *msg) {

    /*
     * todo: handle received Frames, check for collisions
     */

    LinResponseFrame *receivedMsg = check_and_cast<LinResponseFrame *>(msg);
    int messageId = receivedMsg -> getMessageId();
    if(messageId >= 50){
        EV << "Master received a eventTriggered message : " << messageId << endl;
        numcollision ++;
        EV << "now the number of collision : " << numcollision << endl;
        collisionId = getEventTriggeredIds(messageId);    
    }
    if(messageId >= 40 && messageId <= 49){
        EV << "Master received a sporadic message : " << messageId << "with response" << receivedMsg -> getResponse() << endl;
        needSporadic = !(receivedMsg -> getResponse());
        //record
    }
    if(messageId >= 0 && messageId <= 39){
        EV << "Master received a unconditional message : " << messageId << endl;
        //record
    }

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
    //std::cout << "Testing the start of the simulation..." << std::endl;
    EV << "Testing the start of the simulation..." << endl;
    std::vector<int> toBeRecording0 = {37, 12, 8, 9, 11, 5, 50, 0, 1, 2, 3, 16, 1, 57, 6, 25, 20, 37, 18};
    for ( int i = 0; i < toBeRecording0.size(); i++){
        if (toBeRecording0[i] != testRecording0[i]){
            //std::cout << toBeRecording0[i] << " expected. Got " << testRecording0[i] << std::endl;
            EV << toBeRecording0[i] << " expected. Got " << testRecording0[i] <<endl;
            testRecordingsMatch = false;
        }
    }

    if (!testRecordingsMatch){
        //std::cout << "Testing the middle of the simulation..." << std::endl;
        EV << "Testing the middle of the simulation..." << endl;
        std::vector<int> toBeRecording1 = {2, 3, 32, 28, 57, 28, 29, 30, 31, 18, 48, 53, 12, 48, 13, 14, 15, 32};
        for ( int i = 0; i < toBeRecording1.size(); i++){
            if (toBeRecording1[i] != testRecording1[i]){
                //std::cout << toBeRecording1[i] << " expected. Got " << testRecording1[i] << std::endl;
                EV << toBeRecording1[i] << " expected. Got " << testRecording1[i] << endl;
                testRecordingsMatch = false;
            }
        }
    }


    //std::cout << "Checking the amount of sent request frames..." << std::endl;
    EV << "Checking the amount of sent request frames..." << endl;
    std::vector<int> toBeSent = {5104, 857, 39};
    if (toBeSent[UNCONDITIONAL_FRAME] != testSent[UNCONDITIONAL_FRAME]){
        EV << toBeSent[UNCONDITIONAL_FRAME] << " unconditional frames expected. Got " << testSent[UNCONDITIONAL_FRAME] << endl;
    }
    if (toBeSent[SPORADIC_FRAME] != testSent[SPORADIC_FRAME]){
        EV << toBeSent[SPORADIC_FRAME] << " sporadic frames expected. Got " << testSent[SPORADIC_FRAME] << endl;
    }
    if (toBeSent[EVENT_TRIGGERED_FRAME] != testSent[EVENT_TRIGGERED_FRAME]){
        EV << toBeSent[EVENT_TRIGGERED_FRAME] << " event-triggered frames expected. Got " << testSent[EVENT_TRIGGERED_FRAME] << endl;
    }

    if (getRNG(0)->getNumbersDrawn() != 23){
        EV << "It seems you have used the RNG(0) somewhere! Don't use it! This messed up the needSporadic interval." << endl;
    }

    if (getRNG(1)->getNumbersDrawn() != 3638){
        EV << "It seems you have requested to " << (getRNG(1)->getNumbersDrawn() > 3638 ? "many" : "few") << " random message IDs! You might want to check your scheduling logic." << endl;
    }

    if (getRNG(2)->getNumbersDrawn() != 39){
        EV << "It seems you have sent to " << (getRNG(2)->getNumbersDrawn() > 39 ? "many" : "few") << " sporadic frames! You might want to check your scheduling logic." << endl;
    }

    if (getRNG(3)->getNumbersDrawn() != 3428){
        EV << "It seems you have responded " << (getRNG(3)->getNumbersDrawn() > 3428 ? "to often" : "to rarely") << " to event-triggered frames sporadic frames! You might want to check your scheduling logic." << endl;
    }

    //std::cout << std::endl << "**************** TESTS FINISHED ****************" << std::endl;
    EV << std::endl << "**************** TESTS FINISHED ****************" <<endl;
}
