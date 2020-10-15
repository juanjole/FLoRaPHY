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

#ifndef PINGPONG_PINGPONG_H_
#define PINGPONG_PINGPONG_H_

#include <omnetpp.h>
#include "floraphy/physicallayer/LoRaRadio.h"
#include "inet/common/ModuleAccess.h"
#include "inet/linklayer/base/MACProtocolBase.h"

using namespace omnetpp;

class PingPong: public MACProtocolBase {

protected:
    LoRaRadio *radio = nullptr;
    IRadio::TransmissionState transmissionState =
            IRadio::TRANSMISSION_STATE_UNDEFINED;
    cMessage *endTransmission = nullptr;

    bool ping;

    cFSM fsm;

    enum State {
        INIT = 0, SEND = FSM_Steady(1), RECEIVE = FSM_Steady(2),
    };

    virtual ~PingPong();

    virtual void initialize(int stage) override;

    virtual void handleSelfMessage(cMessage*) override;
    virtual void handleLowerPacket(cPacket*) override;
    virtual void handleUpperPacket(cPacket*) override;
    virtual void handleWithFsm(cMessage*);

    virtual void receiveSignal(cComponent*, simsignal_t, long, cObject*)
            override;

    virtual InterfaceEntry *createInterfaceEntry() override {
        return nullptr;
    }

};

#endif /* PINGPONG_PINGPONG_H_ */
