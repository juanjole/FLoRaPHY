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

#include "LoRaReception.h"

LoRaReception::LoRaReception(const IRadio *radio,
        const ITransmission *transmission, const simtime_t startTime,
        const simtime_t endTime, const Coord startPosition,
        const Coord endPosition, const EulerAngles startOrientation,
        const EulerAngles endOrientation, Hz carrierFrequency, Hz bandwidth,
        W power, int spreadingFactor, int codingRate) :
        ScalarReception(radio, transmission, startTime, endTime, startPosition,
                endPosition, startOrientation, endOrientation, carrierFrequency,
                bandwidth, power), spreadingFactor(spreadingFactor), codingRate(
                codingRate) {

}

std::ostream& LoRaReception::printToStream(std::ostream &stream,
        int level) const {
    stream << "LoRaReception";
    if (level <= PRINT_LEVEL_DETAIL)
        stream << ", spreadingFactor = " << spreadingFactor << ", codingRate = "
                << codingRate;
    return ScalarReception::printToStream(stream, level);
}
