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

#ifndef LORAPHY_LORARECEIVER_H_
#define LORAPHY_LORARECEIVER_H_

#include "LoRaListening.h"
#include "LoRaReception.h"
#include "LoRaTransmission.h"
#include "inet/physicallayer/contract/packetlevel/IRadioMedium.h"
#include "inet/physicallayer/common/packetlevel/ReceptionResult.h"
#include "inet/physicallayer/common/packetlevel/BandListening.h"
#include "inet/physicallayer/common/packetlevel/ListeningDecision.h"
#include "inet/physicallayer/common/packetlevel/ReceptionDecision.h"
#include "inet/physicallayer/analogmodel/packetlevel/ScalarNoise.h"
#include "inet/physicallayer/analogmodel/packetlevel/ScalarSNIR.h"
#include "inet/physicallayer/base/packetlevel/FlatReceiverBase.h"
#include "LoRaRadio.h"

using namespace inet;
using namespace inet::physicallayer;

class LoRaReceiver: public FlatReceiverBase {
protected:
    int spreadingFactor;
    int codingRate;
    int preambleSymbols;

    int nonOrthDelta[6][6] = { { 0, -8, -9, -9, -9, -9 }, { -11, 0, -11, -12,
            -13, -13 }, { -15, -13, 0, -13, -14, -15 }, { -19, -18, -17, 0, -17,
            -18 }, { -22, -22, -21, -20, 0, -20 },
            { -25, -25, -25, -24, -23, 0 } };

public:

    void initialize(int stage) override;

    virtual W getMinInterferencePower() const override {
        return W(NaN);
    }
    virtual W getMinReceptionPower() const override {
        return W(NaN);
    }

    virtual const IListening* createListening(const IRadio *radio,
            const simtime_t startTime, const simtime_t endTime,
            const Coord startPosition, const Coord endPosition) const override;
    virtual bool computeIsReceptionPossible(const IListening *listening,
            const ITransmission *transmission) const override;
    virtual bool computeIsReceptionAttempted(const IListening *listening,
            const IReception *reception, IRadioSignal::SignalPart part,
            const IInterference *interference) const override;
    virtual const IReceptionDecision* computeReceptionDecision(
            const IListening *listening, const IReception *reception,
            IRadioSignal::SignalPart part, const IInterference *interference,
            const ISNIR *snir) const override;
    virtual const ReceptionIndication* computeReceptionIndication(
            const ISNIR *snir) const override;

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

    bool isPacketCollided(const IReception *reception,
            IRadioSignal::SignalPart part,
            const IInterference *interference) const;

    static W getLoRaSensitivity(int sf, Hz bw);

};

#endif /* LORAPHY_LORARECEIVER_H_ */
