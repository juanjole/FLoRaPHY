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

#ifndef LORAPHY_LORAANALOGMODEL_H_
#define LORAPHY_LORAANALOGMODEL_H_

#include "LoRaReception.h"
#include "LoRaTransmission.h"
#include "inet/physicallayer/base/packetlevel/ScalarAnalogModelBase.h"

using namespace inet;
using namespace inet::physicallayer;

class LoRaAnalogModel : public ScalarAnalogModelBase{

public:

  virtual const IReception *computeReception(const IRadio *radio, const ITransmission *transmission, const IArrival *arrival) const override;

};

#endif /* LORAPHY_LORAANALOGMODEL_H_ */
