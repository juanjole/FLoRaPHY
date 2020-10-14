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

package floraphy.physicallayer.energyconsumer;

import inet.physicallayer.energyconsumer.StateBasedEpEnergyConsumer;

simple LoRaStateBasedEpEnergyConsumer extends StateBasedEpEnergyConsumer
{
    parameters:
        double supplyVoltage = default(3.3);
        offPowerConsumption @unit(W) = default(supplyVoltage*0.0002mW); //Sleep: 0.2 uA
        sleepPowerConsumption @unit(W) = default(supplyVoltage*0.0015mW); //Idle: 1.5 uA
        switchingPowerConsumption @unit(W) = default(0mW); //TODO
        receiverIdlePowerConsumption @unit(W) = default(supplyVoltage*1.6mW); //Standby: 1.6 mA
        receiverBusyPowerConsumption @unit(W) = default(supplyVoltage*1.6mW); //Standby: 1.6 mA
        receiverReceivingPowerConsumption @unit(W) = default(supplyVoltage*10.3mW); //Receive, LnaBoost off, band 1, 125kHz: 10.3 mA
        transmitterIdlePowerConsumption @unit(W) = default(supplyVoltage*1.6mW); //Standby: 1.6 mA
        transmitterTransmittingPowerConsumption @unit(W) = default(supplyVoltage*29mW); //Transmit, Impedance matching, 13 dBm output: 29 mA
        
}