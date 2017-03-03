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

package zigbee02.determinedMesh;
import zigbee02.collector;
import zigbee02.nwkMesh.nwkMeshNormal;
import zigbee02.nwkMesh.nwkMeshDenialOfSleep;

network nwk_mesh_sinkhole_determined_15
{
    parameters:
        int numNodes;
        @display("bgb=500,500");
    submodules:
        node0: nwkMeshNormal {
            @display("p=100,100");
        }
        node1: nwkMeshDenialOfSleep {
            @display("p=50,150");
        }
        node2: nwkMeshDenialOfSleep {
            @display("p=150,150");
        }
        node3: nwkMeshDenialOfSleep {
            @display("p=50,250");
        }
        node4: nwkMeshDenialOfSleep {
            @display("p=150,250");
        }
        node5: nwkMeshDenialOfSleep {
            @display("p=100,300");
        }
        node6: nwkMeshDenialOfSleep {
            @display("p=250,100");
        }
        node7: nwkMeshDenialOfSleep {
            @display("p=250,300");
        }
        node8: nwkMeshDenialOfSleep {
            @display("p=250,200");
        }
        node9: nwkMeshDenialOfSleep {
            @display("p=200,350");
        }
        node10: nwkMeshDenialOfSleep {
            @display("p=300,150");
        }
        node11: nwkMeshDenialOfSleep {
            @display("p=300,250");
        }
        node12: nwkMeshDenialOfSleep {
            @display("p=50,350");
        }
        node13: nwkMeshDenialOfSleep {
            @display("p=300,350");
        }
        node14: nwkMeshDenialOfSleep {
            @display("p=200,400");
        }
        collector: collector {
            @display("p=400,50");
        }
    connections:
        node0.port++ <--> node1.port++;
        node0.port++ <--> node2.port++;
        node2.port++ <--> node4.port++;
        node2.port++ <--> node6.port++;
        node3.port++ <--> node5.port++;
        node3.port++ <--> node12.port++;
        node4.port++ <--> node5.port++;
        node4.port++ <--> node7.port++;
        node5.port++ <--> node9.port++;
        node7.port++ <--> node8.port++;
        node7.port++ <--> node9.port++;
        node7.port++ <--> node11.port++;
        node8.port++ <--> node10.port++;
        node9.port++ <--> node12.port++;
        node9.port++ <--> node13.port++;
        node9.port++ <--> node14.port++;
        node10.port++ <--> node11.port++;
        node11.port++ <--> node13.port++;
        node12.port++ <--> node14.port++;
        node13.port++ <--> node14.port++;
}
