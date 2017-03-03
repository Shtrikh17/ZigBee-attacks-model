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

#include "address_appointment_m.h"

#include <vector>
#include "address_helper.h"

#include "mac_frameTree_m.h"
#include "nwkPacketTree_m.h"

#include "../collector.h"


using namespace omnetpp;

class nwkTreeNormal: public cSimpleModule{
protected:
    bool am_i_coordinator;
    int firstChildAddress;
    int lastChildAddress;
    int numChildren;
    int myPANAddress;
    address_helper* address_helper_module;

    int numRFDs;
    double packet_size_parametr_geometric;
    double packet_generation_period;
    double dev_packet_generation_period;

    double delay;

    collector* collectorModule;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage* msg) override;
    virtual nwkPacketTree* generateDataPacket();
    macFrameTree* encapsulateDataPacket(nwkPacketTree*);
    void sendingProcedure(macFrameTree*);

};

Define_Module(nwkTreeNormal);

class nwkTreeDenialOfSleep: public nwkTreeNormal{
private:
    int attack_address;
    int attack_pan;
protected:
    virtual void initialize() override;
    nwkPacketTree* generateDataPacket() override;
};

Define_Module(nwkTreeDenialOfSleep);

class nwkTreeRepeatedTransmission: public nwkTreeNormal{
private:
    simtime_t repeat_period;
    int select_period;
    int current_select_number;
    std::vector<macFrameTree*> repeat_queue;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage*) override;
};

Define_Module(nwkTreeRepeatedTransmission);

class nwkTreeRepeatedTransmissionExactSrc: public nwkTreeNormal{
private:
    simtime_t repeat_period;
    int select_period;
    int current_select_number;
    int select_address;
    int select_pan;
    std::vector<macFrameTree*> repeat_queue;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage*) override;
};

Define_Module(nwkTreeRepeatedTransmissionExactSrc);

class nwkTreeRepeatedTransmissionExactDest: public nwkTreeNormal{
private:
    simtime_t repeat_period;
    int select_period;
    int current_select_number;
    int select_address;
    int select_pan;
    std::vector<macFrameTree*> repeat_queue;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage*) override;
};

Define_Module(nwkTreeRepeatedTransmissionExactDest);


class nwkTreeSelectiveForward: public nwkTreeNormal{
private:
    int select_period;
    int current_select_number;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage*) override;
};

Define_Module(nwkTreeSelectiveForward);

class nwkTreeSelectiveForwardExactSrc: public nwkTreeNormal{
private:
    int select_period;
    int current_select_number;
    int select_address;
    int select_pan;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage*) override;
};

Define_Module(nwkTreeSelectiveForwardExactSrc);

class nwkTreeSelectiveForwardExactDest: public nwkTreeNormal{
private:
    int select_period;
    int current_select_number;
    int select_address;
    int select_pan;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage*) override;
};

Define_Module(nwkTreeSelectiveForwardExactDest);

class nwkTreeSpoofing: public nwkTreeNormal{
private:
    int spoof_period;
    int current_spoof;
protected:
    virtual void initialize() override;
    virtual nwkPacketTree* generateDataPacket() override;
};

Define_Module(nwkTreeSpoofing);

class nwkTreeSpoofingExactSrc: public nwkTreeNormal{
private:
    int spoof_period;
    int current_spoof;
    int spoof_address;
    int spoof_pan;
protected:
    virtual void initialize() override;
    virtual nwkPacketTree* generateDataPacket() override;
};

Define_Module(nwkTreeSpoofingExactSrc);

class nwkTreeSpoofingExactDest: public nwkTreeNormal{
private:
    int spoof_period;
    int current_spoof;
    int spoof_address;
    int spoof_pan;
protected:
    virtual void initialize() override;
    virtual nwkPacketTree* generateDataPacket() override;
};

Define_Module(nwkTreeSpoofingExactDest);

class nwkTreeWormhole: public nwkTreeNormal{
private:
    cModule* second_module;
    int current_wormhole_counter;
    int wormhole_period;
protected:
    virtual void handleMessage(cMessage* msg) override;
    virtual void initialize() override;
};

Define_Module(nwkTreeWormhole);



