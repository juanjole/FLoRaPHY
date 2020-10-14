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

#include "LoRaAnalogModel.h"

Define_Module(LoRaAnalogModel);

const IReception* LoRaAnalogModel::computeReception(const IRadio *receiverRadio,
        const ITransmission *transmission, const IArrival *arrival) const {
    const LoRaTransmission *loRaTransmission = check_and_cast<
            const LoRaTransmission*>(transmission);
    const simtime_t receptionStartTime = arrival->getStartTime();
    const simtime_t receptionEndTime = arrival->getEndTime();
    arrival->getStartOrientation();
    const EulerAngles receptionStartOrientation =
            arrival->getStartOrientation();
    const EulerAngles receptionEndOrientation = arrival->getEndOrientation();
    const Coord receptionStartPosition = arrival->getStartPosition();
    const Coord receptionEndPosition = arrival->getEndPosition();
    W receivedPower = computeReceptionPower(receiverRadio, transmission,
            arrival);
    Hz LoRaCF = loRaTransmission->getCarrierFrequency();
    int LoRaSF = loRaTransmission->getSpreadingFactor();
    Hz LoRaBW = loRaTransmission->getBandwidth();
    int LoRaCR = loRaTransmission->getCodingRate();
    return new LoRaReception(receiverRadio, transmission, receptionStartTime,
            receptionEndTime, receptionStartPosition, receptionEndPosition,
            receptionStartOrientation, receptionEndOrientation, LoRaCF, LoRaBW,
            receivedPower, LoRaSF, LoRaCR);
}
