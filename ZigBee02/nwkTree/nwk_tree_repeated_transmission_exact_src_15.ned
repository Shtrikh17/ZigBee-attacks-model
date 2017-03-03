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
import zigbee02.collector;

network nwk_tree_repeated_transmission_exact_src_15
{
    parameters:
        int numNodes;
        @display("bgb=538.27203,499.96802");
    submodules:
        node0: nwkTreeNormal {
            @display("p=250,50");
        }
        node1: nwkTreeRepeatedTransmissionExactSrc {
            @display("p=150,100");
        }
        node2: nwkTreeNormal {
            @display("p=350,100");
        }
        node3: nwkTreeNormal {
            @display("p=50,200");
        }
        node4: nwkTreeNormal {
            @display("p=125,200");
        }
        node5: nwkTreeNormal {
            @display("p=200,200");
        }
        node6: nwkTreeNormal {
            @display("p=300,200");
        }
        node7: nwkTreeNormal {
            @display("p=400,200");
        }
        node8: nwkTreeNormal {
            @display("p=75,300");
        }
        node9: nwkTreeNormal {
            @display("p=150,300");
        }
        node10: nwkTreeNormal {
            @display("p=250,300");
        }
        node11: nwkTreeNormal {
            @display("p=350,300");
        }
        node12: nwkTreeNormal {
            @display("p=200,400");
        }
        node13: nwkTreeNormal {
            @display("p=300,400");
        }
        node14: nwkTreeNormal {
            @display("p=400,400");
        }
        address_helper: address_helper {
            @display("p=450,50");
        }
        collector: collector{
         	@display("p=450,125");   
        }
    connections:
        node0.children++ <--> node1.parent;
        node0.children++ <--> node2.parent;
        node1.children++ <--> node3.parent;
        node1.children++ <--> node4.parent;
        node1.children++ <--> node5.parent;
        node2.children++ <--> node6.parent;
        node2.children++ <--> node7.parent;
        node4.children++ <--> node8.parent;
        node4.children++ <--> node9.parent;
        node6.children++ <--> node10.parent;
        node6.children++ <--> node11.parent;
        node10.children++ <--> node12.parent;
        node10.children++ <--> node13.parent;
        node11.children++ <--> node14.parent;
}