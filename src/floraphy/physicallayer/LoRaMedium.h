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

#ifndef FLORAPHY_PHYSICALLAYER_LORAMEDIUM_H_
#define FLORAPHY_PHYSICALLAYER_LORAMEDIUM_H_

#include "inet/physicallayer/common/packetlevel/RadioMedium.h"

using namespace inet;
using namespace inet::physicallayer;

class LoRaMedium : public RadioMedium {

public:

    virtual bool isReceptionPossible(const IRadio *receiver, const ITransmission *transmission, IRadioSignal::SignalPart part) const override;
};

#endif /* FLORAPHY_PHYSICALLAYER_LORAMEDIUM_H_ */
