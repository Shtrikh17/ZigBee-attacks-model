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

#include "nwkTreeNormal.h"

void nwkTreeSpoofingExactDest::initialize(){
    nwkTreeNormal::initialize();
    spoof_period = par("spoof_period").longValue();
    current_spoof = 1;
    spoof_address = par("spoof_address");
    spoof_pan = par("spoof_pan");
}

nwkPacketTree* nwkTreeSpoofingExactDest::generateDataPacket(){
    nwkPacketTree* newPacket = new nwkPacketTree("data");

    int srcAddress = intuniform(0, numRFDs);

    int destAddress;
    int srcPANAddress = myPANAddress;

    int destPANAddress;
    int tmpAddress = 0;

    if(current_spoof<spoof_period){
        srcPANAddress = myPANAddress;
        current_spoof++;
        destAddress = intuniform(0, numRFDs);
        destPANAddress = myPANAddress;
        while(destPANAddress == myPANAddress){
            tmpAddress = intuniform(0, address_helper_module->getNumNodes()-1);
            destPANAddress = address_helper_module->getAddress(tmpAddress);
        }
    }
    else{
        destAddress = spoof_address;
        destPANAddress = spoof_pan;
        srcPANAddress = address_helper_module->getAddress(intuniform(0, address_helper_module->getNumNodes()-1));
        collectorModule->addForwardedPackets(address_helper_module->getIndex(myPANAddress));
        current_spoof = 1;
    }

    newPacket->setSrcAddress(srcAddress);
    newPacket->setDestAddress(destAddress);
    newPacket->setDestPANAddress(destPANAddress);
    newPacket->setSrcPANAddress(srcPANAddress);

    return newPacket;
}

