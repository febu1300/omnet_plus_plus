//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//
simple Node
{
    parameters:
        bool isMaster = default(false);

        @display("i=block/routing");
   gates:
        input in[];
        output out[];
}


network Network
{
    @display("bgb=375,300");
    submodules:
        node[3]: Node;
//        node1: Node {
//            parameters:
//                @display("i=,gold");
//        }
//        node2: Node {
//            @display("p=247,150");
//        }
//        node3: Node {
//            @display("p=104,150");
//        }
    connections:
        node[0].out++ --> node[1].in++;
        node[0].in++ <-- node[1].out++;
        
//        node[1].out++ --> node[2].in++;
//        node[1].in++ <-- node[2].out++;
        
        node[0].out++ --> node[2].in++;
        node[0].in++ <-- node[2].out++;     
//        node1.out --> {  delay = 100ms; } --> node2.in;
//        node1.in <-- {  delay = 100ms; } <-- node2.out;
//
//        node2.out --> {  delay = 100ms; } --> node3.in;
//        node2.in <-- {  delay = 100ms; } <-- node3.out;
//
//        node3.out --> {  delay = 100ms; } --> node1.in;
//        node3.in <-- {  delay = 100ms; } <-- node1.out;
}

