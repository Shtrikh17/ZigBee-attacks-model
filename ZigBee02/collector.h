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
#include <map>
#include <stdio.h>

using namespace omnetpp;

#define MAX_NODES_IN_PAN 10

class collector: public cSimpleModule{
private:

    simtime_t period;

    int num_packets;
    int num_frames;

    std::vector<std::map<int,int>*> num_packets_out;
    int num_nodes_in_transfer;

    std::vector<std::map<int,int>*> num_packets_in;
    std::vector<int> numPANNeighbours;
    int num_nodes_in_receipt;

    std::vector<std::map<int,int>*> num_packets_equal_src;
    std::vector<std::map<int,int>*> num_packets_equal_dest;
    int num_src_nodes;
    int num_src_pans;
    int num_dest_nodes;
    int num_dest_pans;

    std::vector<std::map<int,int>*> num_frames_out;
    std::vector<std::map<int,int>*> num_frames_in;
    int num_nodes_in_transfer_frames;
    int num_nodes_in_receipt_frames;

    int num_route_msgs;
    std::vector<int> _num_forwarded_packets;

    FILE* output_file;
    FILE* output_headed;

    std::vector<std::map<int,int>*> num_packets_created;
    int num_nodes_creators;

public:
    void incNumPackets();
    void addNumFrames(int);

    void incNumPacketsOut(int PANAddress, int address);
    void incNumPacketsCreated(int PANAddress, int address);
    void incNumPacketsIn(int PANAddress, int address, int numNeighbours);

    void incNumPacketsEqualSrc(int PANAddress, int address);
    void incNumPacketsEqualDest(int PANAddress, int address);

    void addNumFramesOut(int num, int PANAddress, int address);
    void addNumFramesIn(int num, int PANAddress, int address, int numNeighbours);

    void incNumRouteMsgs(void);

    void addFailedFrames(int);

    void addForwardedPackets(int);
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage*) override;
    virtual void finish() override;
};

Define_Module(collector);
