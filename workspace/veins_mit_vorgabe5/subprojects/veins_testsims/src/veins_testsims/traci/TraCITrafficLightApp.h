//
// Copyright (C) 2018 Tobias Hardes <hardes@ccs-labs.org>
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

#pragma once

#include <veins/modules/application/ieee80211p/BaseWaveApplLayer.h>
#include "veins/veins.h"

#include "veins/modules/mobility/traci/TraCIMobility.h"
#include "veins/modules/mobility/traci/TraCICommandInterface.h"

using Veins::TraCICommandInterface;
using Veins::TraCIMobility;

namespace Veins {

class TraCITrafficLightApp : public BaseWaveApplLayer {
protected:
    /** @brief this function is called upon receiving a BasicSafetyMessage, also referred to as a beacon  */
    virtual void onBSM(DemoSafetyMessage* bsm);

    /** @brief handle messages from below and calls the onWSM, onBSM, and onWSA functions accordingly */
    virtual void handleLowerMsg(cMessage* msg);

    /** @brief Called every time a message arrives*/
    virtual void handleMessage(cMessage* msg);
};

} // namespace Veins
