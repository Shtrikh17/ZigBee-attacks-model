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

/*
 * Initialization procedure. All local variables get values here.
 */
void nwkMeshNormal::initialize(){
    mean_packet_period = par("packet_generation_period");
    std_dev_packet_period = par("dev_packet_generation_period");
    packet_size_parametr_geometric = par("packet_size_parametr_geometric");
    numRFDs = par("numRFDs");
    myPANAddress = par("address");
    RREQ_counter = 0;

    collectorModule = dynamic_cast<collector*>(getParentModule()->getSubmodule("collector"));

    delay = (double)(par("delay"));

    scheduleAt(0.0, new cMessage("make_resolution_table"));
}


/*
 * Handles all messages: both self-messages and incoming packets
 */
void nwkMeshNormal::handleMessage(cMessage* msg){


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
            collectorModule->incNumPacketsIn(myPANAddress, packet->getSrcAddress(), 1);
        }

        //num_frames_in
        collectorModule->addNumFramesIn(frame->getNumFrames(), myPANAddress, 0, port_resolution_table.size());
        if((packet->getDestAddress()!=0)&&(packet->getDestPANAddress()==myPANAddress)){
            collectorModule->addNumFramesIn(frame->getNumFrames(), myPANAddress, packet->getSrcAddress(), 1);
        }


        //=======================================================================================

        if(packet->getType()==0){       //Data

            if(packet->getDestPANAddress()!=myPANAddress){
                frame->encapsulate(packet);
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
            scheduleAt(simTime() + SimTime(truncnormal(mean_packet_period, std_dev_packet_period) + intuniform(0, 20), SIMTIME_S), new cMessage("generatePacket"));
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
    }
}

/*
 * Get address from nodes connected to all ports. Execution - at te beginning.
 */
void nwkMeshNormal::make_resolution_table(){
    cGate* currentGate;
    cModule* neighbour;
    int neighbour_address;
    for(int j=0; j<gateSize("port"); j++){
        currentGate = gateHalf("port", cGate::OUTPUT, j);
        neighbour = currentGate->getNextGate()->getOwnerModule();
        neighbour_address = neighbour->par("address");
        port_resolution_table[j]=neighbour_address;
    }
}

/*
 * Generation of Data Packet with random address.
 *
 * RELOAD for attackers
 */
nwkPacket* nwkMeshNormal::generateDataPacket(){
    nwkPacket* newPacket = new nwkPacket("data");

    int srcAddress = intuniform(0, numRFDs);

    int destAddress = intuniform(0, numRFDs);
    int srcPANAddress = myPANAddress;

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

/*
 * Procedure for generated Data packets. Encapsulates them into sequence of frames.
 */
macFrame* nwkMeshNormal::encapsulateDataPacket(nwkPacket* newPacket){
    macFrame* frame_sequence = new macFrame("macFrame");
    frame_sequence->setNumFrames(geometric(packet_size_parametr_geometric)+1);
    frame_sequence->setFramesLeft(frame_sequence->getNumFrames()-1);
    frame_sequence->encapsulate(newPacket);
    frame_sequence->setBroadcast(false);
    return frame_sequence;
}

/*
 * Procedure checks if dest address is known (is present in RT).
 * If it is - sends it to sendToMac.
 * Otherwise - puts into queue and starts AODV procedure.
 */
void nwkMeshNormal::sendingProcedure(macFrame* frame_sequence){
    nwkPacket* packet = dynamic_cast<nwkPacket*>(frame_sequence->getEncapsulatedPacket());

    int destPANAddress = packet->getDestPANAddress();

    if(routeKnown(destPANAddress)){
        int nearestAddress = routeChoiceProcedure(destPANAddress);
        int destPort = addressResolution(nearestAddress);
        frame_sequence->setGateNumber(destPort);
        sendToMac(frame_sequence);
    }
    else{
        pending_frame_sequences.push_back(frame_sequence);
        //EV << "Starting search for: " << destPANAddress << std::endl;
        startAODV(destPANAddress);
    }
}

/*
 * Returns 'true' if there is active (status==1) record in RT for given PANaddress (looks through RT)
 */
bool nwkMeshNormal::routeKnown(int PANaddress){
    bool record_found = false;
    RT_entry* currentEntry;
    for(int j=0; j<RT.size(); j++){
        currentEntry = RT[j];
        if((currentEntry->destPANAddress==PANaddress)&&(currentEntry->status==1)){
            record_found = true;
            break;
        }
    }
    return record_found;
}

/*
 * Returns next-hop for given PANaddress (looks through RT)
 * Not protected against RT with no given address.
 */
int nwkMeshNormal::routeChoiceProcedure(int PANaddress){
    int nextHop;
    RT_entry* currentEntry;
    for(int j=0; j<RT.size(); j++){
        currentEntry = RT[j];
        if((currentEntry->destPANAddress==PANaddress)&&(currentEntry->status==1)){
            nextHop = currentEntry->nextHopPANAddress;
            break;
        }
    }
    return nextHop;
}

/*
 * Returns gate number for given address
 */
int nwkMeshNormal::addressResolution(int address){
    int port = 0;
    for(int j=0; j<port_resolution_table.size(); j++){
        if(port_resolution_table[j]==address){
            port = j;
            break;
        }
    }
    return port;
}

/*
 * Currently it simply sends data directly to another node.
 * Later it will be interface to MAC layer
 */
void nwkMeshNormal::sendToMac(macFrame* frame_sequence){

    //num_packets_out
    nwkPacket* tmp = dynamic_cast<nwkPacket*>(frame_sequence->getEncapsulatedPacket());
    collectorModule->incNumPacketsOut(myPANAddress, 0);
    if((tmp->getSrcAddress()!=0)&&(tmp->getSrcPANAddress()==myPANAddress)){
        collectorModule->incNumPacketsOut(myPANAddress, tmp->getSrcAddress());
    }

    //num_frames_out
    collectorModule->addNumFramesOut(frame_sequence->getNumFrames(), myPANAddress, 0);
    if((tmp->getSrcAddress()!=0)&&(tmp->getSrcPANAddress()==myPANAddress)){
        collectorModule->addNumFramesOut(frame_sequence->getNumFrames(), myPANAddress, tmp->getSrcAddress());
    }

    //num_packets_created
    if((tmp->getSrcPANAddress()==myPANAddress)){
        collectorModule->incNumPacketsCreated(myPANAddress, tmp->getSrcAddress());
    }


    sendDelayed(frame_sequence, delay, gateHalf("port", cGate::OUTPUT, frame_sequence->getGateNumber()));
}

/*
 * Start of AODV procedure
 * Generation of RREQ and broadcast
 */
void nwkMeshNormal::startAODV(int pan_address_to_find){
    nwkPacket* packet_rreq = generateRREQ(pan_address_to_find);
    broadcast(packet_rreq);
}


/*
 * Actual generation of RREQ for given address (actually in the model it is address of PAN)
 */
nwkPacket* nwkMeshNormal::generateRREQ(int address_to_find){

    //Create RREQ packet
    RREQ* rreq = new RREQ();
    rreq->setRREQID(RREQ_counter++);
    rreq->setHopCount(1);
    rreq->setDestPANAddress(address_to_find);
    rreq->setOriginatorPANAddress(myPANAddress);
    rreq->setHopPANAddress(myPANAddress);

    //Create RT record
    RT_entry* rt_entry = new RT_entry();
    rt_entry->destPANAddress = address_to_find;
    rt_entry->status=0;
    RT.push_back(rt_entry);

    //Crete RDT record
    RDT_entry* rdt_entry = new RDT_entry();
    rdt_entry->RREQID=RREQ_counter-1;
    rdt_entry->hopCount = 0;
    rdt_entry->hopsLeft = getParentModule()->par("numNodes").longValue()+1;
    rdt_entry->originatorPANAddress = myPANAddress;
    rdt_entry->prevHopPANAddress = myPANAddress;
    RDT.push_back(rdt_entry);

    //Create packet for RREQ
    nwkPacket* packet = new nwkPacket();
    packet->setSpoofed(false);
    packet->setSrcAddress(0);
    packet->setSrcPANAddress(myPANAddress);
    packet->setType(1);
    packet->encapsulate(rreq);

    return packet;
}

/*
 * Broadcast procedure. Later it must be substituted by MAC procedure
 */
void nwkMeshNormal::broadcast(nwkPacket* packet){

    macFrame* newFrame = new macFrame("broadcast");
    newFrame->setBroadcast(true);
    newFrame->setNumFrames(1);
    newFrame->setFramesLeft(0);
    newFrame->encapsulate(packet);
    //switch to mac broadcast
    for(int j=0; j<gateSize("port"); j++){
        sendDelayed(newFrame->dup(), delay, gateHalf("port", cGate::OUTPUT, j));
    }
}

/*
 * Procedure called on receipt of RREQ:
 * a) if for me -> generate response
 * b) otherwise -> rebroadcast RREQ (with preliminary changes in DRT, RT and RREQ itself)
 */
void nwkMeshNormal::handleRREQ(nwkPacket* packet){

    RREQ* rreq = dynamic_cast<RREQ*>(packet->decapsulate());

    //Check if there is value in rdt for the search
    bool rdt_present = false;
    bool rdt_rec_renewed = false;
    RDT_entry* entry;

    for(int i=0; i<RDT.size(); i++){
        entry = RDT[i];
        if((rreq->getRREQID()==entry->RREQID)&&(rreq->getOriginatorPANAddress()==entry->originatorPANAddress)){
            rdt_present = true;
            break;
        }
    }

    if(rdt_present){
        //EV<<"RDT present!"<<std::endl;

        if(entry->hopCount>rreq->getHopCount()){
            entry->hopCount = rreq->getHopCount();
            entry->prevHopPANAddress = rreq->getHopPANAddress();
            rdt_rec_renewed = true;
        }
        if(rreq->getDestPANAddress()!=myPANAddress) return;
    }
    else{
        //EV<<"RDT no present"<<std::endl;

        RDT_entry* rdt_entry = new RDT_entry();
        rdt_entry->RREQID=rreq->getRREQID();
        rdt_entry->originatorPANAddress=rreq->getOriginatorPANAddress();
        rdt_entry->prevHopPANAddress=rreq->getHopPANAddress();
        rdt_entry->hopCount=rreq->getHopCount();
        rdt_entry->hopsLeft=getParentModule()->par("numNodes").longValue()+1;
        RDT.push_back(rdt_entry);
        entry = rdt_entry;
    }

    if(rreq->getDestPANAddress()==myPANAddress){
        //If RREQ is for me

        if(rdt_rec_renewed){
            entry->hopsLeft=0;
        }
        else{
            if(rreq->getHopCount()>entry->hopCount) return;
        }

        nwkPacket* rrep_packet = generateRREP(rreq);
        rrep_packet->setDestPANAddress(rreq->getHopPANAddress());

        macFrame* frame_sequence = new macFrame("macFrame");
        frame_sequence->setNumFrames(1);
        frame_sequence->setFramesLeft(0);
        frame_sequence->setBroadcast(false);
        frame_sequence->encapsulate(rrep_packet);
        sendingProcedure(frame_sequence);
        return;
    }
    else{

        //EV <<"Oh, the RREQ is not for me!"<<std::endl;

        // If it is not for me:
        // 1. Create RT record (if there is none for destAddress)
        bool rt_entry_present = false;
        RT_entry* rt_entry;
        for(int i=0;i<RT.size(); i++){
            rt_entry=RT[i];
            if(rt_entry->destPANAddress==rreq->getDestPANAddress()){
                rt_entry_present = true;
                break;
            }
        }
        if(!rt_entry_present){
            rt_entry = new RT_entry();
            rt_entry->destPANAddress = rreq->getDestPANAddress();
            rt_entry->status = 0;
            RT.push_back(rt_entry);
        }

        // 2. Renew RREQ records
        rreq->setHopCount(rreq->getHopCount()+1);
        rreq->setHopPANAddress(myPANAddress);

        // 3.Broadcast RREQ
        nwkPacket* newPacket = new nwkPacket();
        newPacket->setSpoofed(false);
        newPacket->setSrcAddress(0);
        newPacket->setSrcPANAddress(myPANAddress);
        newPacket->setType(1);
        newPacket->encapsulate(rreq);
        broadcast(newPacket);
    }
}

/*
 * Generation of RREP packet for given rreq
 */
nwkPacket* nwkMeshNormal::generateRREP(RREQ* rreq){
    //Create RREP
    RREP* rrep = new RREP();
    rrep->setRREQID(rreq->getRREQID());
    rrep->setOriginatorPANAddress(rreq->getOriginatorPANAddress());
    rrep->setHopsLeft(1);
    rrep->setDestPANAddress(rreq->getDestPANAddress());
    rrep->setHopPANAddress(myPANAddress);

    //Create nwk packet
    nwkPacket* packet = new nwkPacket();
    packet->setSpoofed(false);
    packet->setSrcAddress(0);
    packet->setSrcPANAddress(myPANAddress);
    packet->setDestAddress(0);
    packet->setType(2);
    packet->encapsulate(rrep);

    return packet;
}

/*
 * Procedure called on receipt of RREP:
 * 1. If for me -> update RT and RDT and call fixFrameQueue
 * 2. Otherwise -> update RT and RDT and send to prevHop (if requirements are met)
 */
void nwkMeshNormal::handleRREP(nwkPacket* packet){
    //Get fields
    RREP* rrep = dynamic_cast<RREP*>(packet->decapsulate());


    //Get entries from tables
    RT_entry* rt_entry;
    RDT_entry* rdt_entry;
    bool rdt_found = false;

    //1. Get entries
    for(int i=0; i<RDT.size(); i++){
        rdt_entry = RDT[i];
        if((rdt_entry->RREQID==rrep->getRREQID())&&(rdt_entry->originatorPANAddress==rrep->getOriginatorPANAddress())){
            rdt_found = true;
            break;
        }
    }

    for(int i=0; i<RT.size(); i++){
        rt_entry = RT[i];
        if(rt_entry->destPANAddress==rrep->getDestPANAddress()) break;
    }

    //2. Return if rrep is longer than existing path
    if(rdt_entry->hopsLeft<rrep->getHopsLeft()) return;

    //3. Renew DRT
    rdt_entry->hopsLeft = rrep->getHopsLeft();

    //4. Renew RT
    rt_entry->nextHopPANAddress = rrep->getHopPANAddress();
    rt_entry->status = 1;

    if(rrep->getOriginatorPANAddress()==myPANAddress){
        //EV << "Got response!" << std::endl;
        fixFrameQueue();
        return;
    }
    else{

        //5. increment hops left in rrep
        rrep->setHopsLeft(rrep->getHopsLeft()+1);
        rrep->setHopPANAddress(myPANAddress);

        nwkPacket* new_packet = new nwkPacket();
        new_packet->setSpoofed(false);
        new_packet->setSrcAddress(0);
        new_packet->setSrcPANAddress(myPANAddress);
        new_packet->setDestAddress(0);
        new_packet->setDestPANAddress(rdt_entry->prevHopPANAddress);
        new_packet->setType(2);
        new_packet->encapsulate(rrep);

        macFrame* frame_sequence = new macFrame("macFrame");
        frame_sequence->setNumFrames(1);
        frame_sequence->setFramesLeft(0);
        frame_sequence->setBroadcast(false);
        frame_sequence->encapsulate(new_packet);
        sendingProcedure(frame_sequence);
    }
}

/*
 * Primitive which only calls sendingProcedure
 * It is invoked for clarity on packets to forward
 */
void nwkMeshNormal::forward(macFrame* frame_sequence){
    sendingProcedure(frame_sequence);
}

/*
 * After receipt of RREP (initiated by current node) it is necessary to check if the queue is empty.
 * If it is not, sending attempt is to be held on each of pending frames.
 */
void nwkMeshNormal::fixFrameQueue(){
    macFrame* currentFrame;
    int counter = pending_frame_sequences.size();


    for(int i=0; i<counter; i++){
        currentFrame = pending_frame_sequences.front();
        pending_frame_sequences.erase(pending_frame_sequences.begin());
        sendingProcedure(currentFrame);
    }
}
