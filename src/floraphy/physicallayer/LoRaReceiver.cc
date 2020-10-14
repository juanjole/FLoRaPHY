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

#include "LoRaReceiver.h"

Define_Module(LoRaReceiver);

void LoRaReceiver::initialize(int stage) {
    NarrowbandReceiverBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        spreadingFactor = par("spreadingFactor");
        codingRate = par("codingRate");
        sensitivity = getLoRaSensitivity(spreadingFactor, bandwidth);
        energyDetection = W(math::dBm2mW(-148) / 1000);
        errorModel = dynamic_cast<IErrorModel*>(getSubmodule("errorModel"));
    }
}

const IListening* LoRaReceiver::createListening(const IRadio *radio,
        const simtime_t startTime, const simtime_t endTime,
        const Coord startPosition, const Coord endPosition) const {

    return new LoRaListening(radio, startTime, endTime, startPosition,
            endPosition, carrierFrequency, bandwidth, spreadingFactor,
            codingRate);
}

bool LoRaReceiver::computeIsReceptionPossible(const IListening *listening,
        const ITransmission *transmission) const {
    if (!NarrowbandReceiverBase::computeIsReceptionPossible(listening,
            transmission))
        return false;
    else {
        const LoRaTransmission *loRaTransmission = check_and_cast<
                const LoRaTransmission*>(transmission);
        return spreadingFactor == loRaTransmission->getSpreadingFactor()
                && codingRate == loRaTransmission->getCodingRate();
    }
}

bool LoRaReceiver::computeIsReceptionAttempted(const IListening *listening,
        const IReception *reception, IRadioSignal::SignalPart part,
        const IInterference *interference) const {

    auto interferingReceptions = interference->getInterferingReceptions();
    const LoRaReception *loRaReception = check_and_cast<const LoRaReception*>(
                        reception);
    W signalRSSI_w = loRaReception->getPower();
    for (auto interferingReception : *interferingReceptions) {
        const LoRaReception *loRaInterference = check_and_cast<
                        const LoRaReception*>(interferingReception);
        W interferenceRSSI_w = loRaInterference->getPower();
        EV << "Comparing signal power ("<< signalRSSI_w <<") to interference power ("<< interferenceRSSI_w << ").\n";
        if(interferenceRSSI_w > signalRSSI_w){
            EV << "Interference is more powerful\n.";
            return false;
        }
    }
    return true;

}

const IReceptionDecision* LoRaReceiver::computeReceptionDecision(
        const IListening *listening, const IReception *reception,
        IRadioSignal::SignalPart part, const IInterference *interference,
        const ISNIR *snir) const { //COLLISION

    const LoRaListening *loRaListening = check_and_cast<const LoRaListening*>(
            listening);
    const LoRaReception *loRaReception = check_and_cast<const LoRaReception*>(
            reception);
    if (loRaListening->getSpreadingFactor()
            == loRaReception->getSpreadingFactor()
            && loRaListening->getCodingRate() == loRaReception->getCodingRate()
            && !isPacketCollided(reception, part, interference))
        return FlatReceiverBase::computeReceptionDecision(listening, reception,
                part, interference, snir);
    else
        return new ReceptionDecision(reception, part, false, false, false);

}

const ReceptionIndication* LoRaReceiver::computeReceptionIndication(
        const ISNIR *snir) const {
    ReceptionIndication *indication =
            const_cast<ReceptionIndication*>(FlatReceiverBase::computeReceptionIndication(
                    snir));
    const LoRaReception *loRaReception = check_and_cast<const LoRaReception*>(
            snir->getReception());
    indication->setMinRSSI(loRaReception->getPower());
    return indication;

}

W LoRaReceiver::getLoRaSensitivity(int sf, Hz bw) {
    //function returns sensitivity -- according to LoRa documentation, it changes with LoRa parameters
    //Sensitivity values from Semtech SX1276/77/78/79 datasheet, table 10, Rev 6, January 2019

    switch (sf) {
    case 6:
        if (bw == Hz(125000))
            return W(math::dBm2mW(-118) / 1000);
        if (bw == Hz(250000))
            return W(math::dBm2mW(-115) / 1000);
        if (bw == Hz(500000))
            return W(math::dBm2mW(-111) / 1000);
        break;
    case 7:
        if (bw == Hz(125000))
            return W(math::dBm2mW(-123) / 1000);
        if (bw == Hz(250000))
            return W(math::dBm2mW(-120) / 1000);
        if (bw == Hz(500000))
            return W(math::dBm2mW(-116) / 1000);
        break;
    case 8:
        if (bw == Hz(125000))
            return W(math::dBm2mW(-126) / 1000);
        if (bw == Hz(250000))
            return W(math::dBm2mW(-123) / 1000);
        if (bw == Hz(500000))
            return W(math::dBm2mW(-119) / 1000);
        break;
    case 9:
        if (bw == Hz(125000))
            return W(math::dBm2mW(-129) / 1000);
        if (bw == Hz(250000))
            return W(math::dBm2mW(-125) / 1000);
        if (bw == Hz(500000))
            return W(math::dBm2mW(-122) / 1000);
        break;
    case 10:
        if (bw == Hz(125000))
            return W(math::dBm2mW(-132) / 1000);
        if (bw == Hz(250000))
            return W(math::dBm2mW(-128) / 1000);
        if (bw == Hz(500000))
            return W(math::dBm2mW(-125) / 1000);
        break;
    case 11:
        if (bw == Hz(125000))
            return W(math::dBm2mW(-133) / 1000);
        if (bw == Hz(250000))
            return W(math::dBm2mW(-130) / 1000);
        if (bw == Hz(500000))
            return W(math::dBm2mW(-128) / 1000);
        break;
    case 12:
        if (bw == Hz(125000))
            return W(math::dBm2mW(-136) / 1000);
        if (bw == Hz(250000))
            return W(math::dBm2mW(-133) / 1000);
        if (bw == Hz(500000))
            return W(math::dBm2mW(-130) / 1000);
        break;
    }
    return W(NaN);
}

bool LoRaReceiver::isPacketCollided(const IReception *reception,
        IRadioSignal::SignalPart part,
        const IInterference *interference) const {
    auto interferingReceptions = interference->getInterferingReceptions();
    const LoRaReception *loRaReception = check_and_cast<const LoRaReception*>(
            reception);
    simtime_t m_x =
            (loRaReception->getStartTime() + loRaReception->getEndTime()) / 2;
    simtime_t d_x =
            (loRaReception->getEndTime() - loRaReception->getStartTime()) / 2;
    W signalRSSI_w = loRaReception->getPower();
    double signalRSSI_mw = signalRSSI_w.get() * 1000;
    double signalRSSI_dBm = math::mW2dBm(signalRSSI_mw);
    int receptionSF = loRaReception->getSpreadingFactor();
    for (auto interferingReception : *interferingReceptions) {
        bool overlap = false;
        bool frequencyCollision = false;
        bool captureEffect = false;
        bool timingCollision = false; //Collision is acceptable in first part of preamble
        const LoRaReception *loRaInterference = check_and_cast<
                const LoRaReception*>(interferingReception);

        simtime_t m_y = (loRaInterference->getStartTime()
                + loRaInterference->getEndTime()) / 2;
        simtime_t d_y = (loRaInterference->getEndTime()
                - loRaInterference->getStartTime()) / 2;
        if (omnetpp::fabs(m_x - m_y) < d_x + d_y) {
            overlap = true;
        }

        if (loRaReception->getCarrierFrequency()
                == loRaInterference->getCarrierFrequency()) {
            frequencyCollision = true;
        }

        W interferenceRSSI_w = loRaInterference->getPower();
        double interferenceRSSI_mw = interferenceRSSI_w.get() * 1000;
        double interferenceRSSI_dBm = math::mW2dBm(interferenceRSSI_mw);
        int interferenceSF = loRaInterference->getSpreadingFactor();

        // If difference in power between two signals is greater than threshold, no collision
        if (signalRSSI_dBm - interferenceRSSI_dBm
                >= nonOrthDelta[receptionSF - 7][interferenceSF - 7]) {
            captureEffect = true;
        }

        EV << "[MSDEBUG] Received packet at SF: " << receptionSF
                  << " with power " << signalRSSI_dBm << endl;
        EV << "[MSDEBUG] Received interference at SF: " << interferenceSF
                  << " with power " << interferenceRSSI_dBm << endl;
        EV << "[MSDEBUG] Acceptable diff is equal "
                  << nonOrthDelta[receptionSF - 7][interferenceSF - 7] << endl;
        EV << "[MSDEBUG] Diff is equal "
                  << signalRSSI_dBm - interferenceRSSI_dBm << endl;
        if (captureEffect == false) {
            EV << "[MSDEBUG] Packet is discarded" << endl;
        } else
            EV << "[MSDEBUG] Packet is not discarded" << endl;

        // If last 6 symbols of preamble are received, no collision
        double nPreamble = LoRaRadio::getPreambleSymbols(preambleSymbols); //from the paper "Do Lora networks..."
        simtime_t Tsym = (pow(2, loRaReception->getSpreadingFactor()))
                / (loRaReception->getBandwidth().get() / 1000) / 1000;
        simtime_t csBegin = loRaReception->getPreambleStartTime()
                + Tsym * (nPreamble - 6);
        if (csBegin < loRaInterference->getEndTime()) {
            timingCollision = true;
        }

        if (overlap && frequencyCollision && !captureEffect
                && timingCollision) {
            return true;
        }
    }
    return false;
}
