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

#include "LoRaPathLossOulu.h"

Define_Module(LoRaPathLossOulu);

LoRaPathLossOulu::LoRaPathLossOulu() {
}

void LoRaPathLossOulu::initialize(int stage) {
    FreeSpacePathLoss::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        d0 = m(par("d0"));
        n = par("n");
        B = par("B");
        sigma = par("sigma");
        antennaGain = par("antennaGain");
    }
}

double LoRaPathLossOulu::computePathLoss(mps propagationSpeed, Hz frequency,
        m distance) const {
    double PL_db = B + 10 * n * log10(unit(distance / d0).get()) - antennaGain
            + uniform(-sigma, sigma);
    return math::dB2fraction(-PL_db);
}
