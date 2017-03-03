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
#include <omnetpp.h>
#include <vector>

using namespace omnetpp;

class address_helper: public cSimpleModule{
private:
    std::vector<int> PANAddresses;
protected:
    virtual void initialize() override;
public:
    void addAddress(int PANAddress);
    int getAddress(int index);
    int getNumNodes();
    int getIndex(int address);
};

Define_Module(address_helper);
