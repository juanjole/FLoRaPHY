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

package pingpong;

import floraphy.physicallayer.LoRaRadio;

import inet.mobility.static.StationaryMobility;
import inet.power.contract.IEnergyStorage;

module PingPongNode
{
    parameters:
        @networkNode();
        string energyStorageType = default("IdealEpEnergyStorage");
        *.energySourceModule = default(energyStorageType != "" ? absPath(".energyStorage") : "");
    
    submodules:
        energyStorage: <energyStorageType> like IEnergyStorage if energyStorageType != "" {
            @display("p=44.426666,120.58666;i=block/plug");
        }
        mobility: StationaryMobility {
            @display("p=122.96666,118.206665");
        }
        phy: LoRaRadio {
            @display("p=44,47");
            energyConsumerType = "LoRaStateBasedEpEnergyConsumer";
        }
        pingpong: PingPong {
            @display("p=121,46");
        }

    connections allowunconnected:
        phy.upperLayerIn <-- pingpong.lowerLayerOut;
        phy.upperLayerOut --> pingpong.lowerLayerIn;
}
