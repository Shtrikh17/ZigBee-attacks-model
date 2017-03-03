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

network nwk_tree_denial_of_sleep_20
{
    parameters:
        int numNodes;
        @display("bgb=725.326,498.976");
    submodules:
        node0: nwkTreeNormal {
            @display("p=349.082,49.294");
        }
        node1: nwkTreeNormal {
            @display("p=150,100");
        }
        node2: nwkTreeNormal {
            @display("p=309.848,99.594");
        }
        node3: nwkTreeNormal {
            @display("p=471.814,99.594");
        }
        node4: nwkTreeNormal {
            @display("p=60.36,199.188");
        }
        node5: nwkTreeDenialOfSleep {
            @display("p=149.894,199.188");
        }
        node6: nwkTreeNormal {
            @display("p=300,200");
        }
        node7: nwkTreeNormal {
            @display("p=400,200");
        }
        node8: nwkTreeNormal {
            @display("p=511.048,205.224");
        }
        node9: nwkTreeNormal {
            @display("p=45.27,305.824");
        }
        node10: nwkTreeNormal {
            @display("p=116.696,305.824");
        }
        node11: nwkTreeNormal {
            @display("p=199.188,305.824");
        }
        node12: nwkTreeNormal {
            @display("p=289.728,305.824");
        }
        node13: nwkTreeNormal {
            @display("p=360.148,305.824");
        }
        node14: nwkTreeNormal {
            @display("p=438.616,305.824");
        }
        node15: nwkTreeNormal {
            @display("p=511.048,305.824");
        }
        node16: nwkTreeNormal {
            @display("p=178.062,399.382");
        }
        node17: nwkTreeNormal {
            @display("p=250.494,399.382");
        }
        node18: nwkTreeNormal {
            @display("p=349.082,399.382");
        }
        node19: nwkTreeNormal {
            @display("p=416.484,399.382");
        }
        address_helper: address_helper {
            @display("p=655.912,50.3");
        }
        collector: collector {
            @display("p=655.912,119.714");
        }
    connections:
        node0.children++ <--> node1.parent;
        node0.children++ <--> node2.parent;
        node1.children++ <--> node4.parent;
        node1.children++ <--> node5.parent;
        node2.children++ <--> node6.parent;
        node3.children++ <--> node7.parent;
        node3.children++ <--> node8.parent;
        node4.children++ <--> node9.parent;
        node4.children++ <--> node10.parent;
        node4.children++ <--> node11.parent;
        node6.children++ <--> node12.parent;
        node6.children++ <--> node13.parent;
        node7.children++ <--> node14.parent;
        node0.children++ <--> node3.parent;
        node11.children++ <--> node16.parent;
        node11.children++ <--> node17.parent;
        node13.children++ <--> node18.parent;
        node13.children++ <--> node19.parent;
}
