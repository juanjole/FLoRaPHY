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

#ifndef LORARADIO_LORAPATHLOSSOULU_H_
#define LORARADIO_LORAPATHLOSSOULU_H_

#include "inet/physicallayer/pathloss/FreeSpacePathLoss.h"

using namespace inet;
using namespace inet::physicallayer;;

/**
 * This class implements the log normal shadowing model.
 */
class LoRaPathLossOulu : public FreeSpacePathLoss
{
  protected:
    m d0;
    double n;
    double B;
    double sigma;
    double antennaGain;

  protected:
    virtual void initialize(int stage) override;

  public:
    LoRaPathLossOulu();
    virtual double computePathLoss(mps propagationSpeed, Hz frequency, m distance) const override;
};

#endif /* LORARADIO_LORAPATHLOSSOULU_H_ */
