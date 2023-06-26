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

#ifndef SimpleWaveApp_H
#define SimpleWaveApp_H

#include <veins/modules/application/ieee80211p/BaseWaveApplLayer.h>
#include "veins/modules/world/annotations/AnnotationManager.h"
#include "veins/modules/mobility/LinearMobility.h"

using namespace Veins;

using Veins::AnnotationManager;

/**
 * Small RSU Demo using 11p
 */
class SimpleWaveApp : public BaseWaveApplLayer {
	public:
		virtual void initialize(int stage);
    protected:
		LinearMobility* mobi;
		simtime_t someOffset = 0;
	protected:
		virtual void onBSM(DemoSafetyMessage* wsm);
		virtual void onWSM(BaseFrame1609_4* wsm);
		void sendMessage(std::string blockedRoadId);
        virtual void sendWSM(BaseFrame1609_4* wsm);
        virtual void sendBSM(DemoSafetyMessage* wsm);
		virtual void handlePositionUpdate(cObject* obj);

};

#endif
