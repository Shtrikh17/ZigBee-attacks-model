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

network nwk_mesh_normal_20
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
            @display("p=238.89601,149.184");
        }
        node4: nwkMeshNormal {
            @display("p=188.496,219.744");
        }
        node5: nwkMeshNormal {
            @display("p=286.272,219.744");
        }
        node6: nwkMeshNormal {
            @display("p=49.392002,219.744");
        }
        node7: nwkMeshNormal {
            @display("p=109.872,219.744");
        }
        node8: nwkMeshNormal {
            @display("p=188.496,288.288");
        }
        node9: nwkMeshNormal {
            @display("p=259.056,318.528");
        }
        node10: nwkMeshNormal {
            @display("p=49.392002,294.336");
        }
        node11: nwkMeshNormal {
            @display("p=60.480003,399.168");
        }
        node12: nwkMeshNormal {
            @display("p=188.496,399.168");
        }
        node13: nwkMeshNormal {
            @display("p=131.04001,337.68002");
        }
        node14: nwkMeshNormal {
            @display("p=325.584,348.768");
        }
        node15: nwkMeshNormal {
            @display("p=342.72,149.184");
        }
        node16: nwkMeshNormal {
            @display("p=406.224,219.744");
        }
        node17: nwkMeshNormal {
            @display("p=399.168,288.288");
        }
        node18: nwkMeshNormal {
            @display("p=319.536,440.496");
        }
        node19: nwkMeshNormal {
            @display("p=406.224,399.168");
        }
        collector: collector {
            @display("p=400,50");
        }
    connections:
        node0.port++ <--> node1.port++;
        node0.port++ <--> node2.port++;
        node2.port++ <--> node3.port++;
        node1.port++ <--> node6.port++;
        node6.port++ <--> node7.port++;
        node7.port++ <--> node2.port++;
        node6.port++ <--> node10.port++;
        node10.port++ <--> node13.port++;
        node13.port++ <--> node8.port++;
        node8.port++ <--> node7.port++;
        node8.port++ <--> node4.port++;
        node4.port++ <--> node3.port++;
        node3.port++ <--> node15.port++;
        node15.port++ <--> node16.port++;
        node3.port++ <--> node5.port++;
        node5.port++ <--> node16.port++;
        node16.port++ <--> node17.port++;
        node5.port++ <--> node9.port++;
        node8.port++ <--> node9.port++;
        node9.port++ <--> node14.port++;
        node13.port++ <--> node11.port++;
        node10.port++ <--> node11.port++;
        node11.port++ <--> node12.port++;
        node12.port++ <--> node9.port++;
        node12.port++ <--> node14.port++;
        node18.port++ <--> node12.port++;
        node18.port++ <--> node19.port++;
        node14.port++ <--> node19.port++;
        node14.port++ <--> node17.port++;
}
