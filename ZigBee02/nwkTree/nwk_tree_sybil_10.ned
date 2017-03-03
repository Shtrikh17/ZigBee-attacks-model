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

network nwk_tree_sybil_10
{
    parameters:
        int numNodes;
        @display("bgb=725.326,498.976");
    submodules:
        node0: nwkTreeNormal {
            @display("p=298.188,49.196");
        }
        node1: nwkTreeNormal {
            @display("p=150,100");
        }
        node2: nwkTreeNormal {
            @display("p=438.748,99.395996");
        }
        node3: nwkTreeNormal {
            @display("p=70.28,204.816");
        }
        node4: nwkTreeNormal {
            @display("p=198.79199,204.816");
        }
        node5: nwkTreeNormal {
            @display("p=102.408,285.136");
        }
        node6: nwkTreeNormal {
            @display("p=253.008,285.136");
        }
        node7: nwkTreeNormal {
            @display("p=337.344,204.816");
        }
        node8: nwkTreeNormal {
            @display("p=438.748,204.816");
        }
        node9: nwkTreeNormal {
            @display("p=539.148,204.816");
        }
        address_helper: address_helper {
            @display("p=655.912,50.3");
        }
        collector: collector {
            @display("p=655.912,119.714");
        }
        node10: nwkTreeNormal {
            @display("p=149.596,49.196");
        }
        node11: nwkTreeNormal {
            @display("p=83.332,49.196");
        }
        node12: nwkTreeNormal {
            @display("p=31.123999,49.196");
        }
        node13: nwkTreeNormal {
            @display("p=31.123999,99.395996");
        }
        node14: nwkTreeNormal {
            @display("p=83.332,99.395996");
        }
    connections:
        node0.children++ <--> node10.parent;
        node0.children++ <--> node2.parent;
        node1.children++ <--> node4.parent;
        node4.children++ <--> node5.parent;
        node4.children++ <--> node6.parent;
        node2.children++ <--> node7.parent;
        node2.children++ <--> node8.parent;
        node2.children++ <--> node9.parent;
        node1.children++ <--> node3.parent;
        node10.children++ <--> node11.parent;
        node11.children++ <--> node12.parent;
        node12.children++ <--> node13.parent;
        node13.children++ <--> node14.parent;
        node14.children++ <--> node1.parent;
}
