//    OMNeT++ model for ZigBee attack simulations
//    Copyright (C) 2017 Ilya Shilov
//    ilia.shilov@yandex.ru
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <nwkMeshNormal.h>

void nwkMeshSpoofingExactSrc::initialize(){
    nwkMeshNormal::initialize();
    spoof_period = par("spoof_period").longValue();
    current_spoof = 1;
    spoof_address = par("spoof_address");
    spoof_pan = par("spoof_pan");
}

nwkPacket* nwkMeshSpoofingExactSrc::generateDataPacket(){
    nwkPacket* newPacket = new nwkPacket("data");

    int srcAddress = spoof_address;

    int destAddress = intuniform(0, numRFDs);
    int srcPANAddress;

    if(current_spoof<spoof_period){
        srcPANAddress = myPANAddress;
        current_spoof++;
    }
    else{
        srcPANAddress = spoof_pan;
        collectorModule->addForwardedPackets(myPANAddress);
        current_spoof = 1;
    }

    int destPANAddress = myPANAddress;
    while(destPANAddress == myPANAddress){
        destPANAddress = intuniform(0, getParentModule()->par("numNodes").longValue()-1);
    }

    newPacket->setSrcAddress(srcAddress);
    newPacket->setDestAddress(destAddress);
    newPacket->setDestPANAddress(destPANAddress);
    newPacket->setSrcPANAddress(srcPANAddress);

    newPacket->setSpoofed(false);
    newPacket->setType(0);
    return newPacket;

}
