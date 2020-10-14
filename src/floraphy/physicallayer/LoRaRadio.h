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

#ifndef LORA_LORARADIO_H_
#define LORA_LORARADIO_H_

#include "LoRaReceiver.h"
#include "LoRaTransmitter.h"
#include "inet/physicallayer/base/packetlevel/FlatRadioBase.h"
#include "inet/physicallayer/common/packetlevel/Radio.h"
#include "inet/common/LayeredProtocolBase.h"
#include "inet/physicallayer/common/packetlevel/RadioMedium.h"

using namespace inet;
using namespace inet::physicallayer;

class LoRaRadio: public FlatRadioBase {
protected:
    void handleUpperCommand(cMessage *message) override;
    virtual void initialize(int stage) override;

    //cOutVector collisionRateVector;
    //double collisionCounter = 0;
    //double receptionCounter = 0;

public:
    LoRaRadio();

    virtual void setSpreadingFactor(int newSpreadingFactor);
    virtual void setCodingRate(int codingRate);

    static double getPreambleSymbols(int preambleSymbols);
    static simtime_t getPreambleTime(int preambleSymbols, int spreadingFactor,
            bps bitrate);

    static double getHeaderSymbols(int headerBitLength);
    static simtime_t getHeaderTime(int headerBitLength, int spreadingFactor,
            bps bitrate);

    static double getPayloadSymbols(int payloadByteLenght, int spreadingFactor,
            int codingRate);
    static simtime_t getPayloadTime(int payloadByteLenght, int spreadingFactor,
            int codingRate, bps bitrate);

    static simtime_t getTotalTimeOnAir(cPacket *macFrame, int preambleSymbols,
            int spreadingFactor, int codingRate, bps bitrate);

    simtime_t getTotalTimeOnAir(cPacket *macFrame);

    virtual void startReception(cMessage *timer, IRadioSignal::SignalPart part) override;
    virtual void endReception(cMessage *timer) override;

};

#endif /* LORA_LORARADIO_H_ */
