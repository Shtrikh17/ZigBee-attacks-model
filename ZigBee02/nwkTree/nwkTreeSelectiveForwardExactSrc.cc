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

void nwkTreeSelectiveForwardExactSrc::initialize(){
    nwkTreeNormal::initialize();
    select_period = par("select_period");
    current_select_number = 1;
    select_address = par("select_address");
    select_pan = par("select_pan");
}

void nwkTreeSelectiveForwardExactSrc::handleMessage(cMessage* msg){

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

                if((packet->getSrcAddress()==select_address)&&(packet->getSrcPANAddress()==select_pan)){
                    current_select_number++;
                }

                if(current_select_number>=select_period){
                    current_select_number = 0;
                    return;
                }
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

            scheduleAt(simTime() + SimTime(normal(packet_generation_period, dev_packet_generation_period) + intuniform(0, 20), SIMTIME_S), new cMessage("generate_packet"));
        }

        if(!(strcmp(msg->getName(), "address_appointment"))){
            addressAppointment* incoming_address_msg = dynamic_cast<addressAppointment*>(msg);
            myPANAddress = incoming_address_msg->getFirstAddress();
            address_helper_module->addAddress(myPANAddress);
            firstChildAddress = myPANAddress+1;
            lastChildAddress = incoming_address_msg->getLastAddress();
            numChildren = gateSize("children");

            for(int i=0; i<numChildren; i++){
                addressAppointment* addr_msg = new addressAppointment("address_appointment");
                addr_msg->setFirstAddress(firstChildAddress + i * ((1 + lastChildAddress - firstChildAddress)/numChildren));
                addr_msg->setLastAddress(firstChildAddress + (i+1) * ((1 + lastChildAddress - firstChildAddress)/numChildren) - 1);
                send(addr_msg, gateHalf("children", cGate::OUTPUT, i));
            }

            scheduleAt(simTime() + SimTime(normal(packet_generation_period, dev_packet_generation_period) + intuniform(0, 20), SIMTIME_S), new cMessage("generate_packet"));
        }

        if(!(strcmp(msg->getName(), "generate_packet"))){

            nwkPacketTree* newPacket = generateDataPacket();
            macFrameTree* frame_sequence = encapsulateDataPacket(newPacket);
            sendingProcedure(frame_sequence);

            scheduleAt(simTime() + SimTime(normal(packet_generation_period, dev_packet_generation_period), SIMTIME_S), new cMessage("generate_packet"));
        }
    }
}
