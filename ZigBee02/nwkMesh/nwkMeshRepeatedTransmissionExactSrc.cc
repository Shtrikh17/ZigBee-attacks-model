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

void nwkMeshRepeatedTransmissionExactSrc::initialize(){
    nwkMeshNormal::initialize();
    select_period = par("select_period");
    select_address = par("select_address");
    select_pan = par("select_pan");
    repeat_period = SimTime(par("repeat_period").longValue(), SIMTIME_S);
    repeat_queue.clear();
    current_select_number = 0;
    scheduleAt(repeat_period, new cMessage("repeat"));
}

void nwkMeshRepeatedTransmissionExactSrc::handleMessage(cMessage* msg){

    if(msg->isPacket()){
        macFrame* frame = dynamic_cast<macFrame*>(msg);
        nwkPacket* packet = dynamic_cast<nwkPacket*>(frame->decapsulate());

        //=======================================================================================
        //num_packets
        collectorModule->incNumPackets();
        if(packet->getDestAddress()!=0) collectorModule->incNumPackets();

        //num_frames
        collectorModule->addNumFrames(frame->getNumFrames());
        if(packet->getDestAddress()!=0) collectorModule->addNumFrames(frame->getNumFrames());

        //num_packets_in
        collectorModule->incNumPacketsIn(myPANAddress, 0, port_resolution_table.size());
        if((packet->getDestAddress()!=0)&&(packet->getDestPANAddress()==myPANAddress)){
            collectorModule->incNumPacketsIn(myPANAddress, packet->getSrcAddress(), port_resolution_table.size());
        }

        //num_frames_in
        collectorModule->addNumFramesIn(frame->getNumFrames(), myPANAddress, 0, port_resolution_table.size());
        if((packet->getDestAddress()!=0)&&(packet->getDestPANAddress()==myPANAddress)){
            collectorModule->addNumFramesIn(frame->getNumFrames(), myPANAddress, packet->getSrcAddress(), port_resolution_table.size());
        }


        //=======================================================================================

        if(packet->getType()==0){       //Data

            if(packet->getDestPANAddress()!=myPANAddress){
                frame->encapsulate(packet);
                if((packet->getSrcAddress()==select_address)&&(packet->getSrcPANAddress()==select_pan)){
                    current_select_number++;
                    if(current_select_number>=select_period){
                        repeat_queue.push_back(frame->dup());
                        current_select_number = 0;
                    }
                }

                collectorModule->addForwardedPackets(myPANAddress);
                forward(frame);
                return;
            }

            //Acquired data packet either for me or for RFDs
            collectorModule->incNumPacketsEqualSrc(packet->getSrcPANAddress(), packet->getSrcAddress());
            collectorModule->incNumPacketsEqualDest(packet->getDestPANAddress(), packet->getDestAddress());

            //EV << "Data packet acquired from: " << packet->getSrcPANAddress() << "(" <<packet->getSrcAddress() << ")" << std::endl;

            return;
        }
        else if(packet->getType()==1){  //RREQ
            collectorModule->incNumRouteMsgs();
            handleRREQ(packet);
        }
        else if(packet->getType()==2){  //RREP
            collectorModule->incNumRouteMsgs();
            handleRREP(packet);
        }
    }
    else{
        /*
         * Creation of gate-address resolution table. It works!
         */
        if(!strcmp(msg->getName(),"make_resolution_table")){
            make_resolution_table();
            for(int j=0; j < port_resolution_table.size(); j++){
                RT_entry* newEntry = new RT_entry();
                newEntry->destPANAddress = port_resolution_table[j];
                newEntry->nextHopPANAddress = port_resolution_table[j];
                newEntry->status = 1;
                RT.push_back(newEntry);
                //EV << getName() << ": " << j << " - " << port_resolution_table[j] << std::endl;
            }
            scheduleAt(simTime() + SimTime(truncnormal(mean_packet_period, std_dev_packet_period), SIMTIME_S), new cMessage("generatePacket"));
        }
        //============================================================
        /*
         * Generation of a new packet, call of sendingProcedure, scheduling a new packet.
         */
        if(!strcmp(msg->getName(), "generatePacket")){
            nwkPacket* newDataPacket = generateDataPacket();
            macFrame* frame_sequence = encapsulateDataPacket(newDataPacket);
            sendingProcedure(frame_sequence);
            scheduleAt(simTime() + SimTime(truncnormal(mean_packet_period, std_dev_packet_period), SIMTIME_S), new cMessage("generatePacket"));
        }
        //============================================================
        if(!strcmp(msg->getName(), "repeat")){
            scheduleAt(simTime() + repeat_period, new cMessage("repeat"));
            if(repeat_queue.empty()) return;
            collectorModule->addForwardedPackets(myPANAddress);
            macFrame* to_repeat = repeat_queue.front();
            repeat_queue.erase(repeat_queue.begin());
            forward(to_repeat);
        }
    }
}
