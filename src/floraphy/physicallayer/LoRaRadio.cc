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

#include "LoRaRadio.h"

Define_Module(LoRaRadio);

LoRaRadio::LoRaRadio() :
        FlatRadioBase() {
}

void LoRaRadio::initialize(int stage) {

    Radio::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        //collisionRateVector.setName("collisionRate:vector");

        //WATCH(receptionCounter);
        //WATCH(collisionCounter);
    }
}

void LoRaRadio::handleUpperCommand(cMessage *message) {
    if (message->getKind() == RADIO_C_CONFIGURE) {
        FlatRadioBase::handleUpperCommand(message);
        /* TODO
         * ConfigureRadioCommand *configureCommand = check_and_cast<
         ConfigureRadioCommand*>(message->getControlInfo());*/
        /*int newSpreadingFactor = configureCommand->getSpreadingFactor();
         if (!std::isnan(newSpreadingFactor))
         setSpreadingFactor(newSpreadingFactor);
         int newCodingRate = configureCommand->getCodingRate();
         if (!std::isnan(newCodingRate))
         setCodingRate(newCodingRate);*/
    } else
        FlatRadioBase::handleUpperCommand(message);
}

void LoRaRadio::setSpreadingFactor(int newSpreadingFactor) {
    LoRaTransmitter *loRaTransmitter =
            const_cast<LoRaTransmitter*>(check_and_cast<const LoRaTransmitter*>(
                    transmitter));
    loRaTransmitter->setSpreadingFactor(newSpreadingFactor);
    LoRaReceiver *loRaReceiver = const_cast<LoRaReceiver*>(check_and_cast<
            const LoRaReceiver*>(receiver));
    loRaReceiver->setSpreadingFactor(newSpreadingFactor);
}

void LoRaRadio::setCodingRate(int newCodingRate) {
    LoRaTransmitter *loRaTransmitter =
            const_cast<LoRaTransmitter*>(check_and_cast<const LoRaTransmitter*>(
                    transmitter));
    loRaTransmitter->setCodingRate(newCodingRate);
    LoRaReceiver *loRaReceiver = const_cast<LoRaReceiver*>(check_and_cast<
            const LoRaReceiver*>(receiver));
    loRaReceiver->setCodingRate(newCodingRate);
}

double LoRaRadio::getPreambleSymbols(int preambleSymbols) {
    return preambleSymbols + 4.25;
}

simtime_t LoRaRadio::getPreambleTime(int preambleSymbols, int spreadingFactor,
        bps bitrate) {
    return getPreambleSymbols(preambleSymbols) * spreadingFactor / bitrate.get();
}

double LoRaRadio::getHeaderSymbols(int headerBitLength) {
    return headerBitLength * (8 / 4);
}

simtime_t LoRaRadio::getHeaderTime(int headerBitLength, int spreadingFactor,
        bps bitrate) {
    return getHeaderSymbols(headerBitLength) * spreadingFactor / bitrate.get();
}

double LoRaRadio::getPayloadSymbols(int payloadByteLenght, int spreadingFactor,
        int codingRate) {
    return 8
            + math::max(
                    ceil(
                            double(
                                    8 * payloadByteLenght - 4 * spreadingFactor
                                            + 28 + 16)
                                    / double(4 * spreadingFactor))
                            * (codingRate + 4), 0); // Header enabled and no optimization of the datarate
}

simtime_t LoRaRadio::getPayloadTime(int payloadByteLenght, int spreadingFactor,
        int codingRate, bps bitrate) {

    return getPayloadSymbols(payloadByteLenght, spreadingFactor, codingRate)
            * spreadingFactor / bitrate.get();
}

simtime_t LoRaRadio::getTotalTimeOnAir(cPacket *macFrame, int preambleSymbols,
        int spreadingFactor, int codingRate, bps bitrate) {
    return getPreambleTime(preambleSymbols, spreadingFactor, bitrate)
            + getPayloadTime(macFrame->getByteLength(), spreadingFactor,
                    codingRate, bitrate);
}

simtime_t LoRaRadio::getTotalTimeOnAir(cPacket *macFrame) {
    LoRaTransmitter *loRaTransmitter =
            const_cast<LoRaTransmitter*>(check_and_cast<const LoRaTransmitter*>(
                    transmitter));
    int preambleSymbols = loRaTransmitter->getPreambleSymbols();
    int spreadingFactor = loRaTransmitter->getSpreadingFactor();
    int codingRate = loRaTransmitter->getCodingRate();
    bps bitrate = loRaTransmitter->getBitrate();
    return LoRaRadio::getTotalTimeOnAir(macFrame, preambleSymbols,
            spreadingFactor, codingRate, bitrate);
}

void LoRaRadio::startReception(cMessage *timer, IRadioSignal::SignalPart part) {
    auto radioFrame = static_cast<RadioFrame*>(timer->getControlInfo());
    auto arrival = radioFrame->getArrival();
    auto reception = radioFrame->getReception();
// TODO: should be this, but it breaks fingerprints: if (receptionTimer == nullptr && isReceiverMode(radioMode) && arrival->getStartTime(part) == simTime()) {
    if (isReceiverMode(radioMode) && arrival->getStartTime(part) == simTime()) {
        auto transmission = radioFrame->getTransmission();
        auto isReceptionAttempted = medium->isReceptionAttempted(this,
                transmission, part);
        EV_INFO << "Reception started: "
                       << (isReceptionAttempted ?
                               "attempting" : "not attempting") << " "
                       << (IRadioFrame*) radioFrame << " "
                       << IRadioSignal::getSignalPartName(part) << " as "
                       << reception << endl;

        auto isReceptionPossible =
                medium->isReceptionPossible(this, transmission, part);
        EV_INFO << "Reception started: "
                       << (isReceptionPossible ?
                               "successfully" : "unsuccessfully") << " for "
                       << (IRadioFrame*) radioFrame << " "
                       << IRadioSignal::getSignalPartName(part) << " as "
                       << reception << endl;

        if (isReceptionAttempted && isReceptionPossible) {
            receptionTimer = timer;
        }
    } else
        EV_INFO << "Reception started: ignoring " << (IRadioFrame*) radioFrame
                       << " " << IRadioSignal::getSignalPartName(part) << " as "
                       << reception << endl;
    timer->setKind(part);
    scheduleAt(arrival->getEndTime(part), timer);
    updateTransceiverState();
    updateTransceiverPart();
    //check_and_cast<LoRaMedium *>(medium)->fireReceptionStarted(reception);
    check_and_cast<RadioMedium*>(medium)->emit(
            IRadioMedium::receptionStartedSignal,
            check_and_cast<const cObject*>(reception));
}

void LoRaRadio::endReception(cMessage *timer) {
    auto part = (IRadioSignal::SignalPart) timer->getKind();
    auto radioFrame = static_cast<RadioFrame*>(timer->getControlInfo());
    auto arrival = radioFrame->getArrival();
    auto reception = radioFrame->getReception();
    if (timer == receptionTimer && isReceiverMode(radioMode)
            && arrival->getEndTime() == simTime()) {
        auto transmission = radioFrame->getTransmission();
// TODO: this would draw twice from the random number generator in isReceptionSuccessful: auto isReceptionSuccessful = medium->isReceptionSuccessful(this, transmission, part);
        auto isReceptionSuccessful =
                medium->getReceptionDecision(this, radioFrame->getListening(),
                        transmission, part)->isReceptionSuccessful();
        EV_INFO << "Reception ended: "
                       << (isReceptionSuccessful ?
                               "successfully" : "unsuccessfully") << " for "
                       << (IRadioFrame*) radioFrame << " "
                       << IRadioSignal::getSignalPartName(part) << " as "
                       << reception << endl;
        auto macFrame = medium->receivePacket(this, radioFrame);
        //receptionCounter++;
        if (isReceptionSuccessful) {
            emit(LayeredProtocolBase::packetSentToUpperSignal, macFrame);
            sendUp(macFrame);
        } else {
            //collisionCounter++;
            //emit(LoRaRadio::droppedPacket, 0);
            delete macFrame;
        }
        //collisionRateVector.record(collisionCounter / receptionCounter);
        receptionTimer = nullptr;
    } else {
        EV_INFO << "Reception ended: ignoring " << (IRadioFrame*) radioFrame
                       << " " << IRadioSignal::getSignalPartName(part) << " as "
                       << reception << endl;
        if (timer == receptionTimer)
            receptionTimer = nullptr;
    }
    updateTransceiverState();
    updateTransceiverPart();
    check_and_cast<RadioMedium*>(medium)->emit(
            IRadioMedium::receptionEndedSignal,
            check_and_cast<const cObject*>(reception));
    delete timer;
}
