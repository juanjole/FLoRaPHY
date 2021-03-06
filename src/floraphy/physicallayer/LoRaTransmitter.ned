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

import inet.physicallayer.contract.packetlevel.ITransmitter;

module LoRaTransmitter like ITransmitter
{
    parameters:
        @class(LoRaTransmitter);
        @display("i=block/wrx");
        int headerBitLength @unit(b) = default(20b); // number of header bits added to the length of the MAC frame
        double power @unit(W) = default(25 mW);
        int spreadingFactor;
        int codingRate;
        int preambleSymbols;
        double carrierFrequency @unit(Hz); // center frequency of the band where the transmitter transmits on the medium
        double bandwidth @unit(Hz);        // bandwidth of the band where the transmitter transmits on the medium
        string modulation;                 // "BPSK", "16-QAM", "256-QAM"
}
