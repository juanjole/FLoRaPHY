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

#ifndef LORAPHY_LORATRANSMITTER_H_
#define LORAPHY_LORATRANSMITTER_H_

#include "LoRaTransmission.h"
#include "inet/physicallayer/base/packetlevel/FlatTransmitterBase.h"
#include "LoRaRadio.h"

using namespace inet;
using namespace inet::physicallayer;

class LoRaTransmitter: public FlatTransmitterBase {
protected:
    int spreadingFactor;
    int codingRate;
    int preambleSymbols;

    virtual void initialize(int stage) override;

public:
    LoRaTransmitter();
    virtual std::ostream& printToStream(std::ostream &stream, int level) const
            override;
    virtual const ITransmission* createTransmission(const IRadio *radio,
            const cPacket *macFrame, const simtime_t startTime) const override;

    int getCodingRate() const {
        return codingRate;
    }

    void setCodingRate(int codingRate) {
        this->codingRate = codingRate;
    }

    int getSpreadingFactor() const {
        return spreadingFactor;
    }

    void setSpreadingFactor(int spreadingFactor) {
        this->spreadingFactor = spreadingFactor;
    }

    int getPreambleSymbols() const {
        return preambleSymbols;
    }

    void setPreambleSymbols(int preambleSymbols) {
        this->preambleSymbols = preambleSymbols;
    }
};

#endif /* LORAPHY_LORATRANSMITTER_H_ */
