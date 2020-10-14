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

#include "LoRaTransmission.h"

LoRaTransmission::LoRaTransmission(const IRadio *transmitter,
        const cPacket *macFrame, const simtime_t startTime,
        const simtime_t endTime, const simtime_t preambleDuration,
        const simtime_t headerDuration, const simtime_t dataDuration,
        const Coord startPosition, const Coord endPosition,
        const EulerAngles startOrientation, const EulerAngles endOrientation,
        const IModulation *modulation, int headerBitLength,
        int payloadBitLength, Hz carrierFrequency, Hz bandwidth, bps bitrate,
        W power, int spreadingFactor, int codingRate) :
        ScalarTransmission(transmitter, macFrame, startTime, endTime,
                preambleDuration, headerDuration, dataDuration, startPosition,
                endPosition, startOrientation, endOrientation, modulation,
                headerBitLength, payloadBitLength, carrierFrequency, bandwidth,
                bitrate, power), spreadingFactor(spreadingFactor), codingRate(
                codingRate) {

}

std::ostream& LoRaTransmission::printToStream(std::ostream &stream,
        int level) const {
    stream << "LoRaTransmission";
    if (level <= PRINT_LEVEL_DETAIL)
        stream << ", spreadingFactor = " << spreadingFactor << ", codingRate = "
                << codingRate;
    return TransmissionBase::printToStream(stream, level);
}
