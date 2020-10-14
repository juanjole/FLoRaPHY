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

#ifndef LORAPHY_LORARECEPTION_H_
#define LORAPHY_LORARECEPTION_H_

#include "inet/physicallayer/analogmodel/packetlevel/ScalarReception.h"


using namespace inet;
using namespace inet::physicallayer;

class LoRaReception: public ScalarReception {

protected:
    const int spreadingFactor;
    const int codingRate;

public:
    LoRaReception(const IRadio *radio, const ITransmission *transmission,
            const simtime_t startTime, const simtime_t endTime,
            const Coord startPosition, const Coord endPosition,
            const EulerAngles startOrientation,
            const EulerAngles endOrientation, Hz carrierFrequency, Hz bandwidth,
            W power, int spreadingFactor, int codingRate);

    virtual int getCodingRate() const {
        return codingRate;
    }

    virtual int getSpreadingFactor() const {
        return spreadingFactor;
    }

    virtual std::ostream& printToStream(std::ostream& stream, int level) const override;
};

#endif /* LORAPHY_LORARECEPTION_H_ */
