//
// Copyright (C) 2006-2011 Christoph Sommer <christoph.sommer@uibk.ac.at>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#include "veins/modules/application/ieee80211p/SimpleWaveApp.h"

using Veins::AnnotationManagerAccess;

Define_Module(SimpleWaveApp);

void SimpleWaveApp::initialize(int stage) {
    BaseWaveApplLayer::initialize(stage);
    if (stage == 0) {
        mobi = dynamic_cast<LinearMobility*> (getParentModule()->getSubmodule("mobility"));
        ASSERT(mobi);
    }
}

//function will be called when beacon packet has been received
void SimpleWaveApp::onBSM(DemoSafetyMessage* bsm) {
    findHost()->getDisplayString().updateWith("r=16,yellow");
}

//function will be called when data packet has been received
void SimpleWaveApp::onWSM(BaseFrame1609_4* wsm) {
    findHost()->getDisplayString().updateWith("r=16,green");
}

//function will be called when node has been moved. see parent class how to access a node's position
void SimpleWaveApp::handlePositionUpdate(cObject* obj) {
}

void SimpleWaveApp::sendWSM(BaseFrame1609_4* wsm) {
    sendDelayedDown(wsm,someOffset);
}

void SimpleWaveApp::sendBSM(DemoSafetyMessage* bsm) {
    sendDelayedDown(bsm,someOffset);
}
