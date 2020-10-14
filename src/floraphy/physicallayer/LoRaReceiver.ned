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

import inet.physicallayer.contract.packetlevel.IErrorModel;
import inet.physicallayer.contract.packetlevel.IReceiver;

module LoRaReceiver like IReceiver
{
    parameters:
        @class(LoRaReceiver);
        @display("i=block/wrx");
        int spreadingFactor;
        int codingRate;
        int preambleSymbols;
        double snirThreshold @unit(dB) = default(-6 dB);    // reception is not successful if the SNIR is below this threshold (unsuccessful reception)
        double carrierFrequency @unit(Hz); // center frequency of the band where this receiver listens on the medium
        double bandwidth @unit(Hz);        // bandwidth of the band where this receiver listens on the medium
        string errorModelType = default("");             // NED type of the error model
        string modulation;                 // one of "BPSK", "16-QAM", "256-QAM"

    submodules:
        errorModel: <errorModelType> like IErrorModel if errorModelType != "";
}
