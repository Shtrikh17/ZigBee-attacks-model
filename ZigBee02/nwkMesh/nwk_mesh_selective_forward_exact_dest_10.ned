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

network nwk_mesh_selective_forward_exact_dest_10
{
    parameters:
        int numNodes;
        @display("bgb=500,500");
    submodules:
        node0: nwkMeshNormal {
            @display("p=100,100");
        }
        node1: nwkMeshNormal {
            @display("p=50,150");
        }
        node2: nwkMeshNormal {
            @display("p=150,150");
        }
        node3: nwkMeshNormal {
            @display("p=50,250");
        }
        node4: nwkMeshSelectiveForwardExactDest {
            @display("p=150,250");
        }
        node5: nwkMeshNormal {
            @display("p=100,300");
        }
        node6: nwkMeshNormal {
            @display("p=265.104,99.792");
        }
        node7: nwkMeshNormal {
            @display("p=265.104,249.98401");
        }
        node8: nwkMeshNormal {
            @display("p=265.104,179.42401");
        }
        node9: nwkMeshNormal {
            @display("p=225.792,329.616");
        }
        collector: collector {
            @display("p=400,50");
        }
    connections:
        node0.port++ <--> node1.port++;
        node0.port++ <--> node2.port++;
        node1.port++ <--> node3.port++;
        node2.port++ <--> node4.port++;
        node2.port++ <--> node6.port++;
        node3.port++ <--> node5.port++;
        node4.port++ <--> node5.port++;
        node4.port++ <--> node7.port++;
        node5.port++ <--> node9.port++;
        node6.port++ <--> node8.port++;
        node7.port++ <--> node8.port++;
        node7.port++ <--> node9.port++;
}