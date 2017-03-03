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


package zigbee02.nwkTree;

simple nwkTreeNormal{
	parameters:
	    @display("i=device/accesspoint");
	    bool coordinator;
	    int numAddresses;
	    int numRFDs;	//max - 10
	    double packet_size_parametr_geometric;
	    double packet_generation_period;
	    double dev_packet_generation_period;
	    double delay;
	gates:
	    inout parent @loose;
	    inout children[]; 
}


simple nwkTreeDenialOfSleep extends nwkTreeNormal{
	parameters:
	    int attack_address;
	    int attack_pan;
	    @display("i=block/control");   
		@class(nwkTreeDenialOfSleep);
}

simple nwkTreeSelectiveForward extends nwkTreeNormal{
	parameters:
	    int select_period;
	    @display("i=block/tunnel");
	    @class(nwkTreeSelectiveForward);    
}

simple nwkTreeSelectiveForwardExactSrc extends nwkTreeNormal{
	parameters:
	    int select_period;
	    int select_address;
	    int select_pan;
	    @display("i=block/tunnel");
	    @class(nwkTreeSelectiveForwardExactSrc);    
}

simple nwkTreeSelectiveForwardExactDest extends nwkTreeNormal{
	parameters:
	    int select_period;
	    int select_address;
	    int select_pan;
	    @display("i=block/tunnel");
	    @class(nwkTreeSelectiveForwardExactDest);    
}

simple nwkTreeRepeatedTransmission extends nwkTreeNormal{
	parameters:
	    int repeat_period;
	    int select_period;
	    @display("i=block/dispatch");
	    @class(nwkTreeRepeatedTransmission);    
}

simple nwkTreeRepeatedTransmissionExactSrc extends nwkTreeNormal{
	parameters:
	    int repeat_period;
	    int select_period;
	    int select_address;
	    int select_pan;
	    @display("i=block/dispatch");
	    @class(nwkTreeRepeatedTransmissionExactSrc);    
}

simple nwkTreeRepeatedTransmissionExactDest extends nwkTreeNormal{
	parameters:
	    int repeat_period;
	    int select_period;
	    int select_address;
	    int select_pan;
	    @display("i=block/dispatch");
	    @class(nwkTreeRepeatedTransmissionExactDest);    
}

simple nwkTreeSpoofing extends nwkTreeNormal{
    parameters:
        int spoof_period;
        @display("i=block/departure");
        @class(nwkTreeSpoofing);
}

simple nwkTreeSpoofingExactSrc extends nwkTreeNormal{
    parameters:
        int spoof_period;
        int spoof_address;
        int spoof_pan;
        @display("i=block/departure");
        @class(nwkTreeSpoofingExactSrc);
}

simple nwkTreeSpoofingExactDest extends nwkTreeNormal{
    parameters:
        int spoof_period;
        int spoof_address;
        int spoof_pan;
        @display("i=block/departure");
        @class(nwkTreeSpoofingExactDest);
}

simple nwkTreeWormhole extends nwkTreeNormal{
	parameters:
	    int my_num;
	    int wormhole_period;
    	@display("i=block/rxtx");
    	@class(nwkTreeWormhole);
	gates:
		input wormhole @directIn;
}
