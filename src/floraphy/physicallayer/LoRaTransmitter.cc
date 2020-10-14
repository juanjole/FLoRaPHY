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

#include "LoRaTransmitter.h"

Define_Module(LoRaTransmitter);

LoRaTransmitter::LoRaTransmitter() :
        FlatTransmitterBase() {
}

void LoRaTransmitter::initialize(int stage) {
    NarrowbandTransmitterBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        spreadingFactor = par("spreadingFactor");
        codingRate = par("codingRate");
        power = W(par("power"));
        carrierFrequency = Hz(par("carrierFrequency"));
        bandwidth = Hz(par("bandwidth"));
        bitrate = bps(
                spreadingFactor * bandwidth.get() / pow(2, spreadingFactor));
        preambleSymbols = par("preambleSymbols");
        preambleDuration = LoRaRadio::getPreambleTime(preambleSymbols,
                spreadingFactor, bitrate);
        headerBitLength = par("headerBitLength");
    }
}

std::ostream& LoRaTransmitter::printToStream(std::ostream &stream,
        int level) const {
    stream << "LoRaTransmitter";
    if (level <= PRINT_LEVEL_TRACE)
        stream << ", spreadingFactor = " << spreadingFactor << ", codingRate = "
                << codingRate << ", preambleSymbols = " << preambleSymbols;
    return FlatTransmitterBase::printToStream(stream, level);
}

const ITransmission* LoRaTransmitter::createTransmission(
        const IRadio *transmitter, const cPacket *macFrame,
        const simtime_t startTime) const {

    double headerSymbols = LoRaRadio::getHeaderSymbols(headerBitLength);
    simtime_t Theader = LoRaRadio::getHeaderTime(headerBitLength,
            spreadingFactor, bitrate);

    double payloadSymbols = LoRaRadio::getPayloadSymbols(
            macFrame->getByteLength(), spreadingFactor, codingRate);
    simtime_t Tpayload = LoRaRadio::getPayloadTime(macFrame->getByteLength(),
            spreadingFactor, codingRate, bitrate);

    const simtime_t duration = preambleDuration + Tpayload;
    const simtime_t endTime = startTime + duration;
    IMobility *mobility = transmitter->getAntenna()->getMobility();
    const Coord startPosition = mobility->getCurrentPosition();
    const Coord endPosition = mobility->getCurrentPosition();
    const EulerAngles startOrientation = mobility->getCurrentAngularPosition();
    const EulerAngles endOrientation = mobility->getCurrentAngularPosition();

    return new LoRaTransmission(transmitter, macFrame, startTime, endTime,
            preambleDuration, Theader, Tpayload, startPosition, endPosition,
            startOrientation, endOrientation, modulation,
            headerSymbols * spreadingFactor, payloadSymbols * spreadingFactor,
            carrierFrequency, bandwidth, bitrate, power, spreadingFactor,
            codingRate);

}
