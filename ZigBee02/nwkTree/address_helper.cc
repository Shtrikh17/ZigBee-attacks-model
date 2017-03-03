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
#include "address_helper.h"

void address_helper::initialize(){
    PANAddresses.clear();
}

void address_helper::addAddress(int PANAddress){
    PANAddresses.push_back(PANAddress);
    for(int i=0; i<PANAddresses.size(); i++) EV << PANAddresses[i] << " ";
    EV << "\n";
}

int address_helper::getAddress(int index){
    if(getParentModule()->par("numNodes").longValue()>index) return this->PANAddresses[index];
    else return this->PANAddresses[intuniform(0, getParentModule()->par("numNodes").longValue()-1)];
}

int address_helper::getNumNodes(){
    return this->PANAddresses.size();
}

int address_helper::getIndex(int address){
    for(int i=0; i<PANAddresses.size(); i++){
        if(PANAddresses[i]==address) return i;
    }
}
