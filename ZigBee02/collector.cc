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


#include "collector.h"
#include <string.h>
#include <math.h>
#include <climits>

/*
* All initialization steps: set all local variables to 0, resize and clear all containers.
*/
void collector::initialize(){

    period = SimTime(par("period").doubleValue(), SIMTIME_S);

    output_file = fopen("/media/shtrikh17/Data/ZigBee/results/output.csv", "w");
    /*output_headed = fopen("/media/shtrikh17/Data/results/output_headed.csv", "w");
    fprintf(output_headed,"num_frames;num_frames_avg;num_packets;num_packets_avg;/"
            "num_packets_out_avg;num_packets_out_max;num_packets_out_min;/"
            "num_packets_in_avg;num_packets_in_max;num_packets_out_avg;/"
            "weighted_num_packets_in_avg;weighted_num_packets_in_max;weighted_num_packets_in_min;/"
            "frac_packets_in_out_avg;frac_packets_in_out_max;frac_packets_in_out_min;/"
            "frac_packets_in_out_pan_avg;frac_packets_in_out_pan_max;frac_packets_in_out_pan_min;/"
            "num_packets_equal_src_avg;num_packets_equal_src_max;num_packets_equal_src_min;/"
            "num_packets_equal_src_pan_avg;num_packets_equal_src_pan_max;num_packets_equal_src_pan_min;/"
            "num_packets_equal_dest_avg;num_packets_equal_dest_max;num_packets_equal_dest_min;/"
            "num_packets_equal_dest_pan_avg;num_packets_equal_dest_pan_max;num_packets_equal_dest_pan_min;/"
            "num_frames_out_avg;num_frames_out_max;num_frames_out_min;/"
            "num_frames_in_avg;num_frames_in_max;num_frames_out_avg;/"
            "weighted_num_frames_in_avg;weighted_num_frames_in_max;weighted_num_frames_in_min;/"
            "num_route_msgs;/"
            "num_forwarded_packets;num_forwarded_packets_avg;num_forwarded_packets_max;num_forwarded_packets_min;/"
            "num_packets_created_avg;num_packets_created_max;num_packets_created_min;/"
            "frac_packets_created_acquired_avg;frac_packets_created_acquired_max;frac_packets_created_acquired_min\n");
     */
    //=======================================================================

    num_packets = 0;
    num_frames = 0;

    //=======================================================================

    num_packets_out.resize(getParentModule()->par("numNodes").longValue());
    for(int i=0; i<num_packets_out.size(); i++){
        std::map<int,int>* tmp = new std::map<int, int>();
        num_packets_out[i] = tmp;

        for(int j=0; j<MAX_NODES_IN_PAN; j++){
            (*tmp)[j]=-1;
        }
    }
    num_nodes_in_transfer = 0;

    //=======================================================================

    num_packets_in.resize(getParentModule()->par("numNodes").longValue());
    for(int i=0; i<num_packets_in.size(); i++){
        std::map<int,int>* tmp = new std::map<int, int>();
        num_packets_in[i] = tmp;

        for(int j=0; j<MAX_NODES_IN_PAN; j++){
            (*tmp)[j]=-1;
        }
    }

    num_nodes_in_receipt = 0;

    numPANNeighbours.resize(getParentModule()->par("numNodes").longValue());
    for(int i=0; i<numPANNeighbours.size(); i++){
        numPANNeighbours[i] = 1;
    }

    //=======================================================================

    num_packets_created.resize(getParentModule()->par("numNodes").longValue());
    for(int i=0; i<num_packets_created.size(); i++){
        std::map<int,int>* tmp = new std::map<int, int>();
        num_packets_created[i] = tmp;

        for(int j=0; j<MAX_NODES_IN_PAN; j++){
            (*tmp)[j]=-1;
        }
    }

    num_nodes_creators = 0;

    //=======================================================================

    num_packets_equal_src.resize(getParentModule()->par("numNodes").longValue());
    for(int i=0; i<num_packets_equal_src.size(); i++){
        std::map<int,int>* tmp = new std::map<int, int>();
        num_packets_equal_src[i] = tmp;

        for(int j=0; j<MAX_NODES_IN_PAN; j++){
            (*tmp)[j]=-1;
        }
    }

    num_packets_equal_dest.resize(getParentModule()->par("numNodes").longValue());
    for(int i=0; i<num_packets_equal_dest.size(); i++){
        std::map<int,int>* tmp = new std::map<int, int>();
        num_packets_equal_dest[i] = tmp;

        for(int j=0; j<MAX_NODES_IN_PAN; j++){
            (*tmp)[j]=-1;
        }
    }

    num_src_nodes = 0;
    num_dest_nodes = 0;
    num_src_pans = 0;
    num_dest_pans = 0;

    //=======================================================================

    num_frames_out.resize(getParentModule()->par("numNodes").longValue());
    for(int i=0; i<num_frames_out.size(); i++){
        std::map<int,int>* tmp = new std::map<int, int>();
        num_frames_out[i] = tmp;

        for(int j=0; j<MAX_NODES_IN_PAN; j++){
            (*tmp)[j]=-1;
        }
    }
    num_nodes_in_transfer_frames = 0;

    //=======================================================================

    num_frames_in.resize(getParentModule()->par("numNodes").longValue());
    for(int i=0; i<num_frames_in.size(); i++){
        std::map<int,int>* tmp = new std::map<int, int>();
        num_frames_in[i] = tmp;

        for(int j=0; j<MAX_NODES_IN_PAN; j++){
            (*tmp)[j]=-1;
        }
    }

    num_nodes_in_receipt_frames = 0;

    //=======================================================================

    num_route_msgs = 0;

    //=======================================================================

    _num_forwarded_packets.resize(getParentModule()->par("numNodes"));
    for(int i=0; i<_num_forwarded_packets.size(); i++) _num_forwarded_packets[i]=0;

    scheduleAt(period, new cMessage("write"));
}

/*
 * Closing porocedure to fflush files.
 */
void collector::finish(){
    fclose(output_file);
    //fclose(output_headed);
}


/*
 * Procedure to handle incoming messages, the only message for collector is self-message "write".
 */
void collector::handleMessage(cMessage* msg){

    if(!strcmp(msg->getName(),"write")){

        /*
         * 1.   num_frames
         * 2.   num_frames_avg
         * 3.   num_packets
         * 4.   num_packets_avg
         */

        EV << "num_packets: " << num_packets <<std::endl;
        EV << "num_frames: " << num_frames <<std::endl;

        int num_frames_avg = (int)(round(num_frames/getParentModule()->par("numNodes").longValue()));
        int num_packets_avg = (int)(round(num_packets/getParentModule()->par("numNodes").longValue()));

        fprintf(output_file, "%d;%d;%d;%d;", num_frames, num_frames_avg, num_packets, num_packets_avg);
        //fprintf(output_headed, "%d;%d;%d;%d;", num_frames, num_frames_avg, num_packets, num_packets_avg);

        num_packets = 0;
        num_frames = 0;
//===================================================================================================

        /*
         * 5.   num_packets_out_avg
         * 6.   num_packets_out_max
         * 7.   num_packets_out_min
         */

        int num_packets_out_avg = 0;
        int num_packets_out_max = 0;
        int num_packets_out_min = INT_MAX;

        for(int i=0; i<num_packets_out.size(); i++){
            std::map<int,int>* tmp = num_packets_out[i];
            for(int j=0; j<MAX_NODES_IN_PAN; j++){
                if((*tmp)[j]>0){
                    if((*tmp)[j]>num_packets_out_max) num_packets_out_max = (*tmp)[j];
                    if((*tmp)[j]<num_packets_out_min) num_packets_out_min = (*tmp)[j];
                    num_packets_out_avg += (*tmp)[j];
                }
            }
        }
        if(num_nodes_in_transfer>0) num_packets_out_avg = (int)round(num_packets_out_avg/(double)(num_nodes_in_transfer));

        if(num_packets_out_min == INT_MAX) num_packets_out_min = 0;

        EV << "num_packets_out_avg: " << num_packets_out_avg << std::endl;
        EV << "num_packets_out_max: " << num_packets_out_max << std::endl;
        EV << "num_packets_out_min: " << num_packets_out_min << std::endl;


        fprintf(output_file, "%d;%d;%d;", num_packets_out_avg, num_packets_out_max, num_packets_out_min);
        //fprintf(output_headed, "%d;%d;%d;", num_packets_out_avg, num_packets_out_max, num_packets_out_min);

//=========================================================================================

        /*
         * 8.   num_packets_in_avg
         * 9.   num_packets_in_max
         * 10.  num_packets_in_min
         * 11.  weighted_num_packets_in_avg
         * 12.  weighted_num_packets_in_max
         * 13.  weighted_num_packets_in_min
         */

        int num_packets_in_avg = 0;
        int num_packets_in_max = 0;
        int num_packets_in_min = INT_MAX;
        double weighted_num_packets_in_avg = 0;
        double weighted_num_packets_in_max = 0;
        double weighted_num_packets_in_min = INT_MAX;
        double tmp_weighted_value = 0.0;

        for(int i=0; i<num_packets_in.size(); i++){
            std::map<int,int>* tmp = num_packets_in[i];
            for(int j=0; j<MAX_NODES_IN_PAN; j++){
                if((*tmp)[j]>0){
                    if((*tmp)[j]>num_packets_in_max) num_packets_in_max = (*tmp)[j];
                    if((*tmp)[j]<num_packets_in_min) num_packets_in_min = (*tmp)[j];
                    num_packets_in_avg += (*tmp)[j];
                }
            }
            tmp_weighted_value = (double)((*tmp)[0])/(double)(numPANNeighbours[i]);
            if(tmp_weighted_value > weighted_num_packets_in_max) weighted_num_packets_in_max = tmp_weighted_value;
            if((tmp_weighted_value < weighted_num_packets_in_min)&&(tmp_weighted_value>0)) weighted_num_packets_in_min = tmp_weighted_value;
            if(tmp_weighted_value>0) weighted_num_packets_in_avg += tmp_weighted_value;
        }

        if(num_nodes_in_receipt>0){
            num_packets_in_avg = (int)round(num_packets_in_avg/(double)(num_nodes_in_receipt));
            weighted_num_packets_in_avg = weighted_num_packets_in_avg / num_nodes_in_receipt;
        }

        if(num_packets_in_min == INT_MAX) num_packets_in_min = 0;
        if(weighted_num_packets_in_min == INT_MAX) weighted_num_packets_in_min = 0;

        EV << "num_packets_in_avg: " << num_packets_in_avg << std::endl;
        EV << "num_packets_in_max: " << num_packets_in_max << std::endl;
        EV << "num_packets_in_min: " << num_packets_in_min << std::endl;

        EV << "weighted_num_packets_in_avg: " << weighted_num_packets_in_avg << std::endl;
        EV << "weighted_num_packets_in_max: " << weighted_num_packets_in_max << std::endl;
        EV << "weighted_num_packets_in_min: " << weighted_num_packets_in_min << std::endl;

        fprintf(output_file,
        "%d;%d;%d;%.2f;%.2f;%.2f;",
        num_packets_in_avg, num_packets_in_max, num_packets_in_min,
        weighted_num_packets_in_avg, weighted_num_packets_in_max, weighted_num_packets_in_min
        );

        /*fprintf(output_headed,
        "%d;%d;%d;%.2f;%.2f;%.2f;",
        num_packets_in_avg, num_packets_in_max, num_packets_in_min,
        weighted_num_packets_in_avg, weighted_num_packets_in_max, weighted_num_packets_in_min
        );*/

//=========================================================================================

        /*
         * 14.  frac_packets_in_out_avg
         * 15.  frac_packets_in_out_max
         * 16.  frac_packets_in_out_min
         * 17.  frac_packets_in_out_pan_avg
         * 18.  frac_packets_in_out_pan_max
         * 19.  frac_packets_in_out_pan_min
         */

        double frac_packets_in_out_avg = 0;
        double frac_packets_in_out_max = 0;
        double frac_packets_in_out_min = INT_MAX;
        double frac_packets_in_out_pan_avg = 0;
        double frac_packets_in_out_pan_max = 0;
        double frac_packets_in_out_pan_min = INT_MAX;

        int frac_num_nodes = 0;

        for(int i=0; i<getParentModule()->par("numNodes").longValue(); i++){
            std::map<int,int>* tmp_in = num_packets_in[i];
            std::map<int,int>* tmp_out = num_packets_out[i];
            int pan_in = 0;
            int pan_out = 0;
            int tmp = 0;
            for(int j=0; j<MAX_NODES_IN_PAN; j++){
                if(((*tmp_in)[j]>0)&&((*tmp_out)[j]>0)){
                    tmp = (*tmp_in)[j]/(*tmp_out)[j];
                    pan_in += (*tmp_in)[j];
                    pan_out += (*tmp_out)[j];
                    if (tmp>frac_packets_in_out_max) frac_packets_in_out_max = tmp;
                    if (tmp<frac_packets_in_out_min) frac_packets_in_out_min = tmp;
                    frac_packets_in_out_avg += tmp;
                    frac_num_nodes++;
                }
            }
            if((pan_in>0)&&(pan_out>0)) tmp = pan_in/pan_out;
            else tmp = 0;
            if (tmp>frac_packets_in_out_pan_max) frac_packets_in_out_pan_max = tmp;
            if (tmp<frac_packets_in_out_pan_min) frac_packets_in_out_pan_min = tmp;
            frac_packets_in_out_pan_avg += tmp;
        }

        if(frac_num_nodes>0) frac_packets_in_out_avg = frac_packets_in_out_avg / frac_num_nodes;
        frac_packets_in_out_pan_avg = frac_packets_in_out_pan_avg / getParentModule()->par("numNodes").longValue();

        if(frac_packets_in_out_min == INT_MAX) frac_packets_in_out_min=0;
        if(frac_packets_in_out_pan_min == INT_MAX) frac_packets_in_out_pan_min=0;


        EV << "frac_packets_in_out_avg: " << frac_packets_in_out_avg << std::endl;
        EV << "frac_packets_in_out_max: " << frac_packets_in_out_max << std::endl;
        EV << "frac_packets_in_out_min: " << frac_packets_in_out_min << std::endl;

        EV << "frac_packets_in_out_pan_avg: " << frac_packets_in_out_pan_avg << std::endl;
        EV << "frac_packets_in_out_pan_max: " << frac_packets_in_out_pan_max << std::endl;
        EV << "frac_packets_in_out_pan_min: " << frac_packets_in_out_pan_min << std::endl;

        fprintf(output_file,
        "%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;",
        frac_packets_in_out_avg, frac_packets_in_out_max, frac_packets_in_out_min,
        frac_packets_in_out_pan_avg, frac_packets_in_out_pan_max, frac_packets_in_out_pan_min
        );
        /*fprintf(output_headed,
        "%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;",
        frac_packets_in_out_avg, frac_packets_in_out_max, frac_packets_in_out_min,
        frac_packets_in_out_pan_avg, frac_packets_in_out_pan_max, frac_packets_in_out_pan_min
        );*/


        num_nodes_in_transfer = 0;
        for(int i=0; i<num_packets_out.size(); i++){
            std::map<int,int>* tmp = num_packets_out[i];
            for(int j=0; j<MAX_NODES_IN_PAN; j++){
                (*tmp)[j]=-1;
            }
        }

        num_nodes_in_receipt = 0;
        for(int i=0; i<num_packets_in.size(); i++){
            std::map<int,int>* tmp = num_packets_in[i];
            for(int j=0; j<MAX_NODES_IN_PAN; j++){
                (*tmp)[j]=-1;
            }
        }

//========================================================================================

        /*
         * 20.  num_packets_equal_src_avg
         * 21.  num_packets_equal_src_max
         * 22.  num_packets_equal_src_min
         * 23.  num_packets_equal_src_pan_avg
         * 24.  num_packets_equal_src_pan_max
         * 25.  num_packets_equal_src_pan_min
         */

        int num_packets_equal_src_avg = 0;
        int num_packets_equal_src_max = 0;
        int num_packets_equal_src_min = INT_MAX;

        int num_packets_equal_src_pan_avg = 0;
        int num_packets_equal_src_pan_max = 0;
        int num_packets_equal_src_pan_min = INT_MAX;


        for(int i=0; i<num_packets_equal_src.size(); i++){
            std::map<int, int>* tmp = num_packets_equal_src[i];
            int total = 0;
            for(int j=0; j<MAX_NODES_IN_PAN; j++){
                if((*tmp)[j]>0){
                    total+=(*tmp)[j];
                    num_packets_equal_src_avg+=(*tmp)[j];
                }
                if((*tmp)[j]>num_packets_equal_src_max) num_packets_equal_src_max = (*tmp)[j];
                if(((*tmp)[j]<num_packets_equal_src_min)&&((*tmp)[j]>0)) num_packets_equal_src_min = (*tmp)[j];
            }
            if(total>num_packets_equal_src_pan_max) num_packets_equal_src_pan_max = total;
            if((total<num_packets_equal_src_pan_min)&&(total>0)) num_packets_equal_src_pan_min = total;
            num_packets_equal_src_pan_avg+=total;
            if(total>0) num_src_pans++;
        }
        if(num_src_pans>0) num_packets_equal_src_pan_avg = (int)(round((double)(num_packets_equal_src_pan_avg)/(double)(num_src_pans)));
        if(num_src_nodes>0) num_packets_equal_src_avg = (int)(round((double)(num_packets_equal_src_avg)/(double)(num_src_nodes)));

        if(num_packets_equal_src_min == INT_MAX) num_packets_equal_src_min=0;
        if(num_packets_equal_src_pan_min == INT_MAX) num_packets_equal_src_pan_min=0;

        EV << "num_packets_equal_src_avg: " << num_packets_equal_src_avg << std::endl;
        EV << "num_packets_equal_src_max: " << num_packets_equal_src_max << std::endl;
        EV << "num_packets_equal_src_min: " << num_packets_equal_src_min << std::endl;
        EV << "num_packets_equal_src_pan_avg: " << num_packets_equal_src_pan_avg << std::endl;
        EV << "num_packets_equal_src_pan_max: " << num_packets_equal_src_pan_max << std::endl;
        EV << "num_packets_equal_src_pan_min: " << num_packets_equal_src_pan_min << std::endl;

        fprintf(output_file,
        "%d;%d;%d;%d;%d;%d;",
        num_packets_equal_src_avg, num_packets_equal_src_max, num_packets_equal_src_min,
        num_packets_equal_src_pan_avg, num_packets_equal_src_pan_max, num_packets_equal_src_pan_min
        );

        /*fprintf(output_headed,
        "%d;%d;%d;%d;%d;%d;",
        num_packets_equal_src_avg, num_packets_equal_src_max, num_packets_equal_src_min,
        num_packets_equal_src_pan_avg, num_packets_equal_src_pan_max, num_packets_equal_src_pan_min
        );*/

        //clear - below!
//==================================================================================================

        /*
         * 26.  num_packets_equal_dest_avg
         * 27.  num_packets_equal_dest_max
         * 28.  num_packets_equal_dest_min
         * 29.  num_packets_equal_dest_pan_avg
         * 30.  num_packets_equal_dest_pan_max
         * 31.  num_packets_equal_dest_pan_min
         */

        int num_packets_equal_dest_avg = 0;
        int num_packets_equal_dest_max = 0;
        int num_packets_equal_dest_min = INT_MAX;

        int num_packets_equal_dest_pan_avg = 0;
        int num_packets_equal_dest_pan_max = 0;
        int num_packets_equal_dest_pan_min = INT_MAX;

        for(int i=0; i<num_packets_equal_dest.size(); i++){
            std::map<int, int>* tmp = num_packets_equal_dest[i];
            int total = 0;
            for(int j=0; j<MAX_NODES_IN_PAN; j++){
                if((*tmp)[j]>0){
                    total+=(*tmp)[j];
                    num_packets_equal_dest_avg+=(*tmp)[j];
                }
                if((*tmp)[j]>num_packets_equal_dest_max) num_packets_equal_dest_max = (*tmp)[j];
                if(((*tmp)[j]<num_packets_equal_dest_min)&&((*tmp)[j]>0)) num_packets_equal_dest_min = (*tmp)[j];
            }
            if(total>num_packets_equal_dest_pan_max) num_packets_equal_dest_pan_max = total;
            if((total<num_packets_equal_dest_pan_min)&&(total>0)) num_packets_equal_dest_pan_min = total;
            num_packets_equal_dest_pan_avg+=total;
            if(total>0) num_dest_pans++;
        }
        if(num_dest_pans>0) num_packets_equal_dest_pan_avg = (int)(round((double)(num_packets_equal_dest_pan_avg)/(double)(num_dest_pans)));
        if(num_dest_nodes>0) num_packets_equal_dest_avg = (int)(round((double)(num_packets_equal_dest_avg)/(double)(num_dest_nodes)));

        if(num_packets_equal_dest_min == INT_MAX) num_packets_equal_dest_min=0;
        if(num_packets_equal_dest_pan_min == INT_MAX) num_packets_equal_dest_pan_min=0;

        EV << "num_packets_equal_dest_avg: " << num_packets_equal_dest_avg << std::endl;
        EV << "num_packets_equal_dest_max: " << num_packets_equal_dest_max << std::endl;
        EV << "num_packets_equal_dest_min: " << num_packets_equal_dest_min << std::endl;
        EV << "num_packets_equal_dest_pan_avg: " << num_packets_equal_dest_pan_avg << std::endl;
        EV << "num_packets_equal_dest_pan_max: " << num_packets_equal_dest_pan_max << std::endl;
        EV << "num_packets_equal_dest_pan_min: " << num_packets_equal_dest_pan_min << std::endl;

        fprintf(output_file,
        "%d;%d;%d;%d;%d;%d;",
        num_packets_equal_dest_avg, num_packets_equal_dest_max, num_packets_equal_dest_min,
        num_packets_equal_dest_pan_avg, num_packets_equal_dest_pan_max, num_packets_equal_dest_pan_min
        );
        /*fprintf(output_headed,
        "%d;%d;%d;%d;%d;%d;",
        num_packets_equal_dest_avg, num_packets_equal_dest_max, num_packets_equal_dest_min,
        num_packets_equal_dest_pan_avg, num_packets_equal_dest_pan_max, num_packets_equal_dest_pan_min
        );*/

        for(int i=0; i<num_packets_equal_dest.size(); i++){
            std::map<int,int>* tmp = num_packets_equal_dest[i];
            for(int j=0; j<MAX_NODES_IN_PAN; j++){
                (*tmp)[j]=-1;
            }
        }
        num_dest_pans = 0;
        num_dest_nodes = 0;

//==========================================================================================

        /*
         * 32.  num_frames_out_avg
         * 33.  num_frames_out_max
         * 34.  num_frames_out_min
         */

        int num_frames_out_avg = 0;
        int num_frames_out_max = 0;
        int num_frames_out_min = INT_MAX;

        for(int i=0; i<num_frames_out.size(); i++){
            std::map<int,int>* tmp = num_frames_out[i];
            for(int j=0; j<MAX_NODES_IN_PAN; j++){
                if((*tmp)[j]>0){
                    if((*tmp)[j]>num_frames_out_max) num_frames_out_max = (*tmp)[j];
                    if((*tmp)[j]<num_frames_out_min) num_frames_out_min = (*tmp)[j];
                    num_frames_out_avg += (*tmp)[j];
                }
            }
        }
        if(num_nodes_in_transfer_frames>0) num_frames_out_avg = (int)round(num_frames_out_avg/(double)(num_nodes_in_transfer_frames));

        if(num_frames_out_min == INT_MAX) num_frames_out_min=0;

        EV << "num_frames_out_avg: " << num_frames_out_avg << std::endl;
        EV << "num_frames_out_max: " << num_frames_out_max << std::endl;
        EV << "num_frames_out_min: " << num_frames_out_min << std::endl;

        fprintf(output_file,
        "%d;%d;%d;",
        num_frames_out_avg, num_frames_out_max, num_frames_out_min
        );

        /*fprintf(output_headed,
        "%d;%d;%d;",
        num_frames_out_avg, num_frames_out_max, num_frames_out_min
        );*/


        num_nodes_in_transfer_frames = 0;
        for(int i=0; i<num_frames_out.size(); i++){
            std::map<int,int>* tmp = num_frames_out[i];
            for(int j=0; j<MAX_NODES_IN_PAN; j++){
                (*tmp)[j]=-1;
            }
        }
//===========================================================================================

        /*
         * 35.  num_frames_in_avg
         * 36.  num_frames_in_max
         * 37.  num_frames_in_min
         * 38.  weighted_num_frames_in_avg
         * 39.  weighted_num_frames_in_max
         * 40.  weighted_num_frames_in_min
         */

        int num_frames_in_avg = 0;
        int num_frames_in_max = 0;
        int num_frames_in_min = INT_MAX;

        double weighted_num_frames_in_avg = 0;
        double weighted_num_frames_in_max = 0;
        double weighted_num_frames_in_min = INT_MAX;
        double tmp_weighted_value_frames = 0.0;


        for(int i=0; i<num_frames_in.size(); i++){
            std::map<int,int>* tmp = num_frames_in[i];
            for(int j=0; j<MAX_NODES_IN_PAN; j++){
                if((*tmp)[j]>0){
                    if((*tmp)[j]>num_frames_in_max) num_frames_in_max = (*tmp)[j];
                    if((*tmp)[j]<num_frames_in_min) num_frames_in_min = (*tmp)[j];
                    num_frames_in_avg += (*tmp)[j];
                }
            }
            tmp_weighted_value_frames = (double)((*tmp)[0])/(double)(numPANNeighbours[i]);
            if(tmp_weighted_value_frames > weighted_num_frames_in_max) weighted_num_frames_in_max = tmp_weighted_value_frames;
            if((tmp_weighted_value_frames < weighted_num_frames_in_min)&&(tmp_weighted_value_frames>0)) weighted_num_frames_in_min = tmp_weighted_value_frames;
            if(tmp_weighted_value_frames>0) weighted_num_frames_in_avg += tmp_weighted_value_frames;
        }
        if(num_nodes_in_receipt_frames>0){
            num_frames_in_avg = (int)round(num_frames_in_avg/(double)(num_nodes_in_receipt_frames));
            weighted_num_frames_in_avg = weighted_num_frames_in_avg / num_nodes_in_receipt_frames;
        }

        if(num_frames_in_min == INT_MAX) num_frames_in_min = 0;
        if(weighted_num_frames_in_min == INT_MAX) weighted_num_frames_in_min=0;

        EV << "num_frames_in_avg: " << num_frames_in_avg << std::endl;
        EV << "num_frames_in_max: " << num_frames_in_max << std::endl;
        EV << "num_frames_in_min: " << num_frames_in_min << std::endl;
        EV << "weighted_num_frames_in_avg: " << weighted_num_frames_in_avg << std::endl;
        EV << "weighted_num_frames_in_max: " << weighted_num_frames_in_max << std::endl;
        EV << "weighted_num_frames_in_min: " << weighted_num_frames_in_min << std::endl;

        fprintf(output_file,
        "%d;%d;%d;%.2f;%.2f;%.2f;",
        num_frames_in_avg, num_frames_in_max, num_frames_in_min,
        weighted_num_frames_in_avg, weighted_num_frames_in_max, weighted_num_frames_in_min
        );

        /*fprintf(output_headed,
        "%d;%d;%d;%.2f;%.2f;%.2f;",
        num_frames_in_avg, num_frames_in_max, num_frames_in_min,
        weighted_num_frames_in_avg, weighted_num_frames_in_max, weighted_num_frames_in_min
        );*/


        num_nodes_in_receipt_frames = 0;
        for(int i=0; i<num_frames_in.size(); i++){
            std::map<int,int>* tmp = num_frames_in[i];
            for(int j=0; j<MAX_NODES_IN_PAN; j++){
                (*tmp)[j]=-1;
            }
        }
//============================================================================================

        /*
         * 41.  num_route_msgs
         */

        EV << "num_route_msgs: " << num_route_msgs << std::endl;
        fprintf(output_file, "%d;", num_route_msgs);
        //fprintf(output_headed, "%d;", num_route_msgs);

        num_route_msgs = 0;

//===============================================================================================

        /*
         * 42.  num_forwarded_packets
         * 43.  num_forwarded_packets_avg
         * 44.  num_forwarded_packets_max
         * 45.  num_forwarded_packets_min
         */

        int num_forwarded_packets = 0;
        int num_forwarded_packets_max = 0;
        int num_forwarded_packets_min = INT_MAX;
        int num_forwarded_packets_avg = 0;

        for(int i=0; i<_num_forwarded_packets.size(); i++){
            num_forwarded_packets += _num_forwarded_packets[i];
            if(_num_forwarded_packets[i]>num_forwarded_packets_max) num_forwarded_packets_max = _num_forwarded_packets[i];
            if(_num_forwarded_packets[i]<num_forwarded_packets_min) num_forwarded_packets_min = _num_forwarded_packets[i];
            num_forwarded_packets_avg += _num_forwarded_packets[i];
        }
        num_forwarded_packets_avg = (int)(round((double)(num_forwarded_packets)/(double)(getParentModule()->par("numNodes").longValue())));
        EV << "num_forwarded_packets: " << num_forwarded_packets << std::endl;
        EV << "num_forwarded_packets_avg: " << num_forwarded_packets_avg << std::endl;
        EV << "num_forwarded_packets_max: " << num_forwarded_packets_max << std::endl;
        EV << "num_forwarded_packets_min: " << num_forwarded_packets_min << std::endl;

        fprintf(output_file,
        "%d;%d;%d;%d;",
        num_forwarded_packets, num_forwarded_packets_avg, num_forwarded_packets_max, num_forwarded_packets_min
        );
        /*fprintf(output_headed,
        "%d;%d;%d;%d;",
        num_forwarded_packets, num_forwarded_packets_avg, num_forwarded_packets_max, num_forwarded_packets_min
        );*/

        for(int i=0; i<_num_forwarded_packets.size(); i++) _num_forwarded_packets[i]=0;

        //===================================================================================================
        /*
         * 46.   num_packets_created_avg
         * 47.   num_packets_created_max
         * 48.   num_packets_created_min
         */
        int num_packets_created_avg = 0;
        int num_packets_created_max = 0;
        int num_packets_created_min = INT_MAX;

        for(int i=0; i<num_packets_created.size(); i++){
            std::map<int,int>* tmp = num_packets_created[i];
            for(int j=0; j<MAX_NODES_IN_PAN; j++){
                if((*tmp)[j]>0){
                    if((*tmp)[j]>num_packets_created_max) num_packets_created_max = (*tmp)[j];
                    if((*tmp)[j]<num_packets_created_min) num_packets_created_min = (*tmp)[j];
                    num_packets_created_avg += (*tmp)[j];
                }
            }
        }
        if(num_nodes_creators>0) num_packets_created_avg = (int)round(num_packets_created_avg/(double)(num_nodes_creators));

        if(num_packets_created_min == INT_MAX) num_packets_created_min=0;

        EV << "num_packets_created_avg: " << num_packets_created_avg << std::endl;
        EV << "num_packets_created_max: " << num_packets_created_max << std::endl;
        EV << "num_packets_created_min: " << num_packets_created_min << std::endl;

        fprintf(output_file, "%d;%d;%d;", num_packets_created_avg, num_packets_created_max, num_packets_created_min);
        //fprintf(output_headed, "%d;%d;%d;", num_packets_created_avg, num_packets_created_max, num_packets_created_min);

 //=========================================================================================

        /*
         * 49. frac_packets_created_acquired_avg
         * 50. frac_packets_created_acquired_max
         * 51. frac_packets_created_acquired_min
         */

        double frac_packets_created_acquired_avg = 0;
        double frac_packets_created_acquired_max = 0;
        double frac_packets_created_acquired_min = INT_MAX;

        int frac_num_nodes_1 = 0;

        for(int i=0; i<getParentModule()->par("numNodes").longValue(); i++){
            std::map<int,int>* tmp_created = num_packets_created[i];
            std::map<int,int>* tmp_acquired = num_packets_equal_src[i];

            int tmp = 0;
            for(int j=0; j<MAX_NODES_IN_PAN; j++){
                if(((*tmp_created)[j]>0)&&((*tmp_acquired)[j]>0)){
                    tmp = (*tmp_created)[j]/(*tmp_acquired)[j];
                    if (tmp>frac_packets_created_acquired_max) frac_packets_created_acquired_max = tmp;
                    if (tmp<frac_packets_created_acquired_min) frac_packets_created_acquired_min = tmp;
                    frac_packets_created_acquired_avg += tmp;
                    frac_num_nodes_1++;
                }
            }
        }

        if(frac_num_nodes_1>0) frac_packets_created_acquired_avg = frac_packets_created_acquired_avg / frac_num_nodes_1;

        if(frac_packets_created_acquired_min == INT_MAX) frac_packets_created_acquired_min=0;

        EV << "frac_packets_created_acquired_avg: " << frac_packets_created_acquired_avg << std::endl;
        EV << "frac_packets_created_acquired_max: " << frac_packets_created_acquired_max << std::endl;
        EV << "frac_packets_created_acquired_min: " << frac_packets_created_acquired_min << std::endl;

        fprintf(output_file,
        "%.2f;%.2f;%.2f\n",
        frac_packets_created_acquired_avg, frac_packets_created_acquired_max, frac_packets_created_acquired_min
        );

        /*fprintf(output_headed,
        "%.2f;%.2f;%.2f\n",
        frac_packets_created_acquired_avg, frac_packets_created_acquired_max, frac_packets_created_acquired_min
        );*/

        //drop down vectors

        num_nodes_in_transfer = 0;
        for(int i=0; i<num_packets_out.size(); i++){
            std::map<int,int>* tmp = num_packets_out[i];
            for(int j=0; j<MAX_NODES_IN_PAN; j++){
                (*tmp)[j]=-1;
            }
        }

        num_nodes_in_receipt = 0;
        for(int i=0; i<num_packets_in.size(); i++){
            std::map<int,int>* tmp = num_packets_in[i];
            for(int j=0; j<MAX_NODES_IN_PAN; j++){
                (*tmp)[j]=-1;
            }
        }

        for(int i=0; i<num_packets_equal_src.size(); i++){
            std::map<int,int>* tmp = num_packets_equal_src[i];
            for(int j=0; j<MAX_NODES_IN_PAN; j++){
                (*tmp)[j]=-1;
            }
        }
        num_src_pans = 0;
        num_src_nodes = 0;

        for(int i=0; i<num_packets_created.size(); i++){
            std::map<int,int>* tmp = num_packets_created[i];
            for(int j=0; j<MAX_NODES_IN_PAN; j++){
                (*tmp)[j]=-1;
            }
        }

        scheduleAt(simTime() + period, new cMessage("write"));
    }
}

void collector::incNumPackets(){
    this->num_packets++;
}

void collector::addNumFrames(int num){
    this->num_frames+=num;
}

void collector::incNumPacketsOut(int PANAddress, int address){
    if((*(num_packets_out[PANAddress]))[address]==-1){
        (*(num_packets_out[PANAddress]))[address] = 0;
        num_nodes_in_transfer++;
    }
    (*(num_packets_out[PANAddress]))[address]++;
}

void collector::incNumPacketsCreated(int PANAddress, int address){
    if((*(num_packets_created[PANAddress]))[address]==-1){
        (*(num_packets_created[PANAddress]))[address] = 0;
        num_nodes_creators++;
    }
    (*(num_packets_created[PANAddress]))[address]++;
}

void collector::incNumPacketsIn(int PANAddress, int address, int numNeighbours){
    if((*(num_packets_in[PANAddress]))[address]==-1){
        (*(num_packets_in[PANAddress]))[address] = 0;
        num_nodes_in_receipt++;
    }
    (*(num_packets_in[PANAddress]))[address]++;
    if(numNeighbours>0) numPANNeighbours[PANAddress] = numNeighbours;
}

void collector::incNumPacketsEqualSrc(int PANAddress, int address){
    if((*(num_packets_equal_src[PANAddress]))[address]==-1){
        (*(num_packets_equal_src[PANAddress]))[address] = 0;
        num_src_nodes++;
    }
    (*(num_packets_equal_src[PANAddress]))[address]++;
}

void collector::incNumPacketsEqualDest(int PANAddress, int address){
    if((*(num_packets_equal_dest[PANAddress]))[address]==-1){
        (*(num_packets_equal_dest[PANAddress]))[address] = 0;
        num_dest_nodes++;
    }
    (*(num_packets_equal_dest[PANAddress]))[address]++;
}

void collector::addNumFramesOut(int num, int PANAddress, int address){
    if((*(num_frames_out[PANAddress]))[address]==-1){
        (*(num_frames_out[PANAddress]))[address] = 0;
        num_nodes_in_transfer_frames++;
    }
    (*(num_frames_out[PANAddress]))[address]+=num;;
}

void collector::addNumFramesIn(int num, int PANAddress, int address, int numNeighbours){
    if((*(num_frames_in[PANAddress]))[address]==-1){
        (*(num_frames_in[PANAddress]))[address] = 0;
        num_nodes_in_receipt_frames++;
    }
    (*(num_frames_in[PANAddress]))[address] +=num;
    if(numNeighbours>0) numPANNeighbours[PANAddress] = numNeighbours;
}

void collector::incNumRouteMsgs(){
    this->num_route_msgs++;
}


void collector::addForwardedPackets(int PANAddress){
    this->_num_forwarded_packets[PANAddress]++;
}
