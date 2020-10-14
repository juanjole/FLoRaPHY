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

package floraphy.physicallayer;

import inet.physicallayer.base.packetlevel.FlatRadioBase;

module LoRaRadio extends FlatRadioBase
{
    parameters:

        @class(LoRaRadio);
        antennaType = default("IsotropicAntenna");
        transmitterType = default("LoRaTransmitter");
        receiverType = default("LoRaReceiver");

        carrierFrequency = default(868 MHz);
        bandwidth = default(125 kHz);
        
        string modulation = default("DSSS-OQPSK-16");
        *.modulation = modulation;
        int spreadingFactor = default(7);
        *.spreadingFactor = spreadingFactor;
        int codingRate = default(1);
        *.codingRate = codingRate;
        int preambleSymbols = default(8);
        *.preambleSymbols = preambleSymbols;

        radioMediumModule = "LoRaMedium";

}
