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

#ifndef LORAPHY_LORALISTENING_H_
#define LORAPHY_LORALISTENING_H_

#include "inet/physicallayer/common/packetlevel/BandListening.h"

using namespace inet;
using namespace inet::physicallayer;

class LoRaListening: public BandListening {

protected:
    const int spreadingFactor;
    const int codingRate;

public:
    LoRaListening(const IRadio *radio, simtime_t startTime, simtime_t endTime,
            Coord startPosition, Coord endPosition, Hz carrierFrequency,
            Hz bandwidth, int spreadingFactor, int codingRate);

    virtual std::ostream& printToStream(std::ostream &stream, int level) const
            override;

    const int getSpreadingFactor() const {
        return spreadingFactor;
    }

    const int getCodingRate() const {
        return codingRate;
    }
};

#endif /* LORAPHY_LORALISTENING_H_ */
