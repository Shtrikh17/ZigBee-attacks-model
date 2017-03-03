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
#include <string.h>

void nwkTreeNormal::initialize(){
    am_i_coordinator = par("coordinator").boolValue();
    if(am_i_coordinator){
        scheduleAt(0.0, new cMessage("init_address_resolution"));
    }
    address_helper_module = dynamic_cast<address_helper*>(getParentModule()->getSubmodule("address_helper"));
    numRFDs = par("numRFDs");
    packet_size_parametr_geometric = par("packet_size_parametr_geometric").doubleValue();

    packet_generation_period = par("packet_generation_period").doubleValue();
    dev_packet_generation_period = par("dev_packet_generation_period").doubleValue();

    collectorModule = dynamic_cast<collector*>(getParentModule()->getSubmodule("collector"));

    delay = (double)(par("delay"));
}

void nwkTreeNormal::handleMessage(cMessage* msg){

    if(msg->isPacket()){
        macFrameTree* frame_sequence = dynamic_cast<macFrameTree*>(msg);
        nwkPacketTree* packet = dynamic_cast<nwkPacketTree*>(frame_sequence->decapsulate());

        // num_packets
        collectorModule->incNumPackets();
        if(packet->getDestAddress()!=0) collectorModule->incNumPackets();

        // num_frames
        collectorModule->addNumFrames(frame_sequence->getNumFrames());
        if(packet->getDestAddress()!=0) collectorModule->addNumFrames(frame_sequence->getNumFrames());

        // num_packets_in
        collectorModule->incNumPacketsIn(address_helper_module->getIndex(myPANAddress), 0, numChildren+1);
        if((packet->getDestPANAddress()==myPANAddress)&&(packet->getDestAddress()!=0)){
            collectorModule->incNumPacketsIn(address_helper_module->getIndex(myPANAddress), packet->getDestAddress(), 1);
        }

        // num_frames_in
        collectorModule->addNumFramesIn(frame_sequence->getNumFrames(), address_helper_module->getIndex(myPANAddress), 0, numChildren+1);
        if((packet->getDestPANAddress()==myPANAddress)&&(packet->getDestAddress()!=0)){
            collectorModule->addNumFramesIn(frame_sequence->getNumFrames(), address_helper_module->getIndex(myPANAddress), packet->getDestAddress(), 1);
        }


        if(!(strcmp(packet->getName(), "data"))){

            if(packet->getDestPANAddress()!=myPANAddress){

                frame_sequence->encapsulate(packet);
                collectorModule->addForwardedPackets(address_helper_module->getIndex(myPANAddress));
                sendingProcedure(frame_sequence);
                return;
            }

            //Acquired data packet either for me or for RFDs
            //num_packets_equal_src
            //num_packets_equal_dest
            collectorModule->incNumPacketsEqualSrc(address_helper_module->getIndex(packet->getSrcPANAddress()), packet->getSrcAddress());
            collectorModule->incNumPacketsEqualDest(address_helper_module->getIndex(packet->getDestPANAddress()), packet->getDestAddress());


            return;
        }
    }
    else{

        if(!strcmp(msg->getName(), "init_address_resolution")){
            myPANAddress = 0;
            address_helper_module->addAddress(myPANAddress);
            firstChildAddress = 1;
            lastChildAddress = par("numAddresses").longValue()-1;
            numChildren = gateSize("children");

            for(int i=0; i<numChildren; i++){
                addressAppointment* addr_msg = new addressAppointment("address_appointment");
                addr_msg->setFirstAddress(firstChildAddress + i * ((1 + lastChildAddress - firstChildAddress)/numChildren));
                addr_msg->setLastAddress(firstChildAddress + (i+1) * ((1 +lastChildAddress - firstChildAddress)/numChildren) - 1);
                send(addr_msg, gateHalf("children", cGate::OUTPUT, i));
            }

            scheduleAt(simTime() + SimTime(truncnormal(packet_generation_period, dev_packet_generation_period) + intuniform(0, 20), SIMTIME_S), new cMessage("generate_packet"));
        }

        if(!(strcmp(msg->getName(), "address_appointment"))){
            addressAppointment* incoming_address_msg = dynamic_cast<addressAppointment*>(msg);
            myPANAddress = incoming_address_msg->getFirstAddress();
            address_helper_module->addAddress(myPANAddress);
            firstChildAddress = myPANAddress+1;
            lastChildAddress = incoming_address_msg->getLastAddress();
            numChildren = gateSize("children");

            collectorModule->incNumRouteMsgs();

            for(int i=0; i<numChildren; i++){
                addressAppointment* addr_msg = new addressAppointment("address_appointment");
                addr_msg->setFirstAddress(firstChildAddress + i * ((1 + lastChildAddress - firstChildAddress)/numChildren));
                addr_msg->setLastAddress(firstChildAddress + (i+1) * ((1 + lastChildAddress - firstChildAddress)/numChildren) - 1);
                send(addr_msg, gateHalf("children", cGate::OUTPUT, i));
            }

            scheduleAt(simTime() + SimTime(truncnormal(packet_generation_period, dev_packet_generation_period) + intuniform(0, 20), SIMTIME_S), new cMessage("generate_packet"));
        }

        if(!(strcmp(msg->getName(), "generate_packet"))){

            nwkPacketTree* newPacket = generateDataPacket();
            macFrameTree* frame_sequence = encapsulateDataPacket(newPacket);
            sendingProcedure(frame_sequence);

            scheduleAt(simTime() + SimTime(truncnormal(packet_generation_period, dev_packet_generation_period), SIMTIME_S), new cMessage("generate_packet"));
        }
    }
}

nwkPacketTree* nwkTreeNormal::generateDataPacket(){
    nwkPacketTree* newPacket = new nwkPacketTree("data");

    int srcAddress = intuniform(0, numRFDs);

    int destAddress = intuniform(0, numRFDs);
    int srcPANAddress = myPANAddress;

    int tmpAddress = 0;

    int destPANAddress = myPANAddress;
    while(destPANAddress == myPANAddress){
        tmpAddress = intuniform(0, address_helper_module->getNumNodes()-1);
        destPANAddress = address_helper_module->getAddress(tmpAddress);
    }

    newPacket->setSrcAddress(srcAddress);
    newPacket->setDestAddress(destAddress);
    newPacket->setDestPANAddress(destPANAddress);
    newPacket->setSrcPANAddress(srcPANAddress);

    return newPacket;
}

macFrameTree* nwkTreeNormal::encapsulateDataPacket(nwkPacketTree* newPacket){
    macFrameTree* frame_sequence = new macFrameTree("macFrame");
    frame_sequence->setNumFrames(geometric(packet_size_parametr_geometric)+1);
    frame_sequence->setFramesLeft(frame_sequence->getNumFrames()-1);
    frame_sequence->encapsulate(newPacket);
    return frame_sequence;
}


void nwkTreeNormal::sendingProcedure(macFrameTree* frame_sequence){

    nwkPacketTree* packet = dynamic_cast<nwkPacketTree*>(frame_sequence->getEncapsulatedPacket());

    //num_packets_out
    nwkPacketTree* tmp = dynamic_cast<nwkPacketTree*>(frame_sequence->getEncapsulatedPacket());
    collectorModule->incNumPacketsOut(address_helper_module->getIndex(myPANAddress), 0);
    if((tmp->getSrcAddress()!=0)&&(tmp->getSrcPANAddress()==myPANAddress)){
        collectorModule->incNumPacketsOut(address_helper_module->getIndex(myPANAddress), tmp->getSrcAddress());
    }

    //num_frames_out
    collectorModule->addNumFramesOut(frame_sequence->getNumFrames(), address_helper_module->getIndex(myPANAddress), 0);
    if((tmp->getSrcAddress()!=0)&&(tmp->getSrcPANAddress()==myPANAddress)){
        collectorModule->addNumFramesOut(frame_sequence->getNumFrames(), address_helper_module->getIndex(myPANAddress), tmp->getSrcAddress());
    }

    //num_packets_created
    if((tmp->getSrcPANAddress()==myPANAddress)){
        collectorModule->incNumPacketsCreated(address_helper_module->getIndex(myPANAddress), tmp->getSrcAddress());
    }


    int destPANAddress = packet->getDestPANAddress();
    int destPort = 0;

    if((destPANAddress >= firstChildAddress) && (destPANAddress <= lastChildAddress)){
        for(int i=0; i<numChildren; i++){
            int First = firstChildAddress + i * ((1 + lastChildAddress - firstChildAddress)/numChildren);
            int Last = firstChildAddress + (i + 1) * ((1 + lastChildAddress - firstChildAddress)/numChildren) - 1;
            if((destPANAddress >= First) && (destPANAddress <= Last)){
                destPort = i;
                break;
            }
        }

        sendDelayed(frame_sequence, delay, gateHalf("children", cGate::OUTPUT, destPort));
    }
    else{
        sendDelayed(frame_sequence, delay, gateHalf("parent", cGate::OUTPUT));
    }

}
