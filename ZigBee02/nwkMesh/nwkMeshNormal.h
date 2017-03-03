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
#include <map>
#include <string.h>
#include <vector>

using namespace omnetpp;

#include "nwkPacket_m.h"
#include "mac_frame_m.h"

#include "../collector.h"


struct RT_entry{
    int destPANAddress;
    int nextHopPANAddress;
    int status;
};

struct RDT_entry{
    int RREQID;
    int originatorPANAddress;
    int prevHopPANAddress;
    int hopCount;
    int hopsLeft;
};


class nwkMeshNormal: public cSimpleModule{
protected:
    std::map<int, int> port_resolution_table;
    std::vector<macFrame*> pending_frame_sequences;
    std::vector<RT_entry*> RT;
    std::vector<RDT_entry*> RDT;

    double mean_packet_period;
    double std_dev_packet_period;
    double packet_size_parametr_geometric;
    int numRFDs;
    int myPANAddress;

    int RREQ_counter;

    double delay;

    collector* collectorModule;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage* msg) override;
protected:
    void make_resolution_table();
    virtual nwkPacket* generateDataPacket();
    macFrame* encapsulateDataPacket(nwkPacket*);
    int routeChoiceProcedure(int);
    bool routeKnown(int);
    void sendingProcedure(macFrame*);
    int addressResolution(int);
    void sendToMac(macFrame*);

    void startAODV(int);
    nwkPacket* generateRREQ(int);
    void broadcast(nwkPacket*);
    void handleRREQ(nwkPacket*);
    nwkPacket* generateRREP(RREQ*);
    void forward(macFrame*);
    void handleRREP(nwkPacket*);
    void fixFrameQueue();
};

Define_Module(nwkMeshNormal);

class nwkMeshDenialOfSleep: public nwkMeshNormal{
private:
    int attack_address;
    int attack_pan;
protected:
    virtual void initialize() override;
    nwkPacket* generateDataPacket() override;
};

Define_Module(nwkMeshDenialOfSleep);

class nwkMeshSelectiveForward: public nwkMeshNormal{
private:
    int select_period;
    int current_select_number;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage*) override;
};

Define_Module(nwkMeshSelectiveForward);

class nwkMeshSelectiveForwardExactSrc: public nwkMeshNormal{
private:
    int select_period;
    int current_select_number;
    int select_address;
    int select_pan;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage*) override;
};

Define_Module(nwkMeshSelectiveForwardExactSrc);

class nwkMeshSelectiveForwardExactDest: public nwkMeshNormal{
private:
    int select_period;
    int current_select_number;
    int select_address;
    int select_pan;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage*) override;
};

Define_Module(nwkMeshSelectiveForwardExactDest);

class nwkMeshRepeatedTransmission: public nwkMeshNormal{
private:
    simtime_t repeat_period;
    int select_period;
    int current_select_number;
    std::vector<macFrame*> repeat_queue;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage*) override;
};

Define_Module(nwkMeshRepeatedTransmission);

class nwkMeshRepeatedTransmissionExactSrc: public nwkMeshNormal{
private:
    simtime_t repeat_period;
    int select_period;
    int current_select_number;
    std::vector<macFrame*> repeat_queue;
    int select_address;
    int select_pan;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage*) override;
};

Define_Module(nwkMeshRepeatedTransmissionExactSrc);

class nwkMeshRepeatedTransmissionExactDest: public nwkMeshNormal{
private:
    simtime_t repeat_period;
    int select_period;
    int current_select_number;
    std::vector<macFrame*> repeat_queue;
    int select_address;
    int select_pan;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage*) override;
};

Define_Module(nwkMeshRepeatedTransmissionExactDest);

class nwkMeshSpoofing: public nwkMeshNormal{
private:
    int spoof_period;
    int current_spoof;
protected:
    virtual void initialize() override;
    virtual nwkPacket* generateDataPacket() override;
};

Define_Module(nwkMeshSpoofing);

class nwkMeshSpoofingExactSrc: public nwkMeshNormal{
private:
    int spoof_period;
    int current_spoof;
    int spoof_address;
    int spoof_pan;
protected:
    virtual void initialize() override;
    virtual nwkPacket* generateDataPacket() override;
};

Define_Module(nwkMeshSpoofingExactSrc);

class nwkMeshSpoofingExactDest: public nwkMeshNormal{
private:
    int spoof_period;
    int current_spoof;
    int spoof_address;
    int spoof_pan;
protected:
    virtual void initialize() override;
    virtual nwkPacket* generateDataPacket() override;
};

Define_Module(nwkMeshSpoofingExactDest);

class nwkMeshWormhole: public nwkMeshNormal{
private:
    cModule* second_module;
    int current_wormhole_counter;
    int wormhole_period;
protected:
    virtual void handleMessage(cMessage* msg) override;
    virtual void initialize() override;
};

Define_Module(nwkMeshWormhole);
