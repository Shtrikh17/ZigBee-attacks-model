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

package zigbee02.nwkMesh;
import zigbee02.collector;

simple nwkMeshNormal{
    parameters:        
        int address;
        double packet_generation_period;
        double packet_size_parametr_geometric;
        double dev_packet_generation_period;
        
        int numRFDs;	//max - 10
        
        double delay;
        
        @display("i=device/accesspoint");
    gates:
        inout port[];    
}

simple nwkMeshDenialOfSleep extends nwkMeshNormal{
	parameters:
	    int attack_address;
	    int attack_pan;
	    @display("i=block/control");   
		@class(nwkMeshDenialOfSleep);
}

simple nwkMeshSelectiveForward extends nwkMeshNormal{
	parameters:
	    int select_period;
	    @display("i=block/tunnel");
	    @class(nwkMeshSelectiveForward);    
}

simple nwkMeshSelectiveForwardExactSrc extends nwkMeshNormal{
	parameters:
	    int select_period;
	    int select_address;
	    int select_pan;
	    @display("i=block/tunnel");
	    @class(nwkMeshSelectiveForwardExactSrc);    
}

simple nwkMeshSelectiveForwardExactDest extends nwkMeshNormal{
	parameters:
	    int select_period;
	    int select_address;
	    int select_pan;
	    @display("i=block/tunnel");
	    @class(nwkMeshSelectiveForwardExactDest);    
}

simple nwkMeshRepeatedTransmission extends nwkMeshNormal{
	parameters:
	    int repeat_period;
	    int select_period;
	    @display("i=block/dispatch");
	    @class(nwkMeshRepeatedTransmission);    
}

simple nwkMeshRepeatedTransmissionExactSrc extends nwkMeshNormal{
	parameters:
	    int repeat_period;
	    int select_period;
	    int select_address;
	    int select_pan;
	    @display("i=block/dispatch");
	    @class(nwkMeshRepeatedTransmissionExactSrc);    
}

simple nwkMeshRepeatedTransmissionExactDest extends nwkMeshNormal{
	parameters:
	    int repeat_period;
	    int select_period;
	    int select_address;
	    int select_pan;
	    @display("i=block/dispatch");
	    @class(nwkMeshRepeatedTransmissionExactDest);    
}

simple nwkMeshSpoofing extends nwkMeshNormal{
    parameters:
        int spoof_period;
        @display("i=block/departure");
        @class(nwkMeshSpoofing);
}

simple nwkMeshSpoofingExactSrc extends nwkMeshNormal{
    parameters:
        int spoof_period;
        int spoof_address;
        int spoof_pan;
        @display("i=block/departure");
        @class(nwkMeshSpoofingExactSrc);
}

simple nwkMeshSpoofingExactDest extends nwkMeshNormal{
    parameters:
        int spoof_period;
        int spoof_address;
        int spoof_pan;
        @display("i=block/departure");
        @class(nwkMeshSpoofingExactDest);
}

simple nwkMeshWormhole extends nwkMeshNormal{
	parameters:
	    int my_num;
	    int wormhole_period;
    	@display("i=block/rxtx");
    	@class(nwkMeshWormhole);
	gates:
		input wormhole @directIn;
}