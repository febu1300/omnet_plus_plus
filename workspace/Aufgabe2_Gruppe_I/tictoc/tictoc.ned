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

//
// TODO auto-generated type
//
simple Knoten
{
    parameters:
        bool isMaster = default(false);


    gates:
        input in[];
        output out[];
}

simple TimeStampLayer
{
    parameters:
        bool isMaster = default(false);
    gates:
        input port_in;
        output port_out;
}

network Net1
{
    @display("bgb=715,408");
    submodules:
        k1: Knoten {
            @display("p=277,111;b=60,56,oval");
        }


        k2: Knoten {
            @display("p=374,236");
        }


        k3: Knoten {
            @display("p=206,236");
        }
    connections:
        k1.out++ --> k2.in++;
        k2.out++ --> k1.in++;

        k1.out++ --> k3.in++;
        k3.out++ --> k1.in++;

        k2.out++ --> k3.in++;
        k3.out++ --> k2.in++;
}
