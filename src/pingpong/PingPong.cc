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

#include "PingPong.h"

Define_Module(PingPong);

PingPong::~PingPong() {
}

void PingPong::initialize(int stage) {
    MACProtocolBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {

        cModule *radioModule = inet::getModuleFromPar<cModule>(
                par("radioModule"), this);
        radioModule->subscribe(IRadio::transmissionStateChangedSignal, this);
        radio = check_and_cast<LoRaRadio*>(radioModule);

        ping = par("ping");

        scheduleAt(simTime(), new cMessage("Init"));
    }
}

void PingPong::handleSelfMessage(cMessage *msg) {
    handleWithFsm(msg);
}

void PingPong::handleUpperPacket(cPacket *msg) {

}

void PingPong::handleLowerPacket(cPacket *msg) {
    handleWithFsm(msg);
}

void PingPong::handleWithFsm(cMessage *msg) {
    FSM_Switch(fsm)
    {
    case FSM_Exit(INIT):
        if (ping) {
            FSM_Goto(fsm, SEND);
        } else {
            FSM_Goto(fsm, RECEIVE);
        }
        break;

    case FSM_Enter(SEND):
        radio->setRadioMode(IRadio::RADIO_MODE_TRANSMITTER);
        EV << fsm.getStateName() << " (enter): Sending Ping.\n";
        sendDown(new cPacket("PingPong"));
        break;

    case FSM_Exit(SEND):
        if (msg == endTransmission) {
            EV << fsm.getStateName() << " (exit): Ping sent.\n";
            FSM_Goto(fsm, RECEIVE);
        }
        break;

    case FSM_Enter(RECEIVE):
        EV << fsm.getStateName() << " (enter): Waiting for Pong.\n";
        radio->setRadioMode(IRadio::RADIO_MODE_RECEIVER);
        break;

    case FSM_Exit(RECEIVE):
        EV << fsm.getStateName() << " (exit): Pong received.\n";
        FSM_Goto(fsm, SEND);
        break;
    }
}

void PingPong::receiveSignal(cComponent *source, simsignal_t signalID,
        long value, cObject *details) {
    Enter_Method_Silent
    ();
    if (signalID == IRadio::transmissionStateChangedSignal) {
        IRadio::TransmissionState newRadioTransmissionState =
                (IRadio::TransmissionState) value;
        if (transmissionState == IRadio::TRANSMISSION_STATE_TRANSMITTING
                && newRadioTransmissionState
                        == IRadio::TRANSMISSION_STATE_IDLE) {
            handleWithFsm(endTransmission);
        }
        transmissionState = newRadioTransmissionState;
    }
}
