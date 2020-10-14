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

#include "LoRaMedium.h"

Define_Module(LoRaMedium);

bool LoRaMedium::isReceptionPossible(const IRadio *receiver, const ITransmission *transmission, IRadioSignal::SignalPart part) const
{
    const IReception *reception = getReception(receiver, transmission);
    const IListening *listening = getListening(receiver, transmission);
    // TODO: why compute?
    const IInterference *interference = computeInterference(receiver, listening, transmission, const_cast<const std::vector<const ITransmission *> *>(&transmissions));
    //bool isReceptionPossible = receiver->getReceiver()->computeIsReceptionAttempted(listening, reception, part, interference); //JUAN
    bool isReceptionPossible = receiver->getReceiver()->computeIsReceptionPossible(listening, transmission);
    isReceptionPossible = isReceptionPossible && receiver->getReceiver()->computeIsReceptionPossible(listening, reception, part);
    delete interference;
    return isReceptionPossible;
}
