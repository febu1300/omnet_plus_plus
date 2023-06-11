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
simple Knot
{

        
    gates:
        input in;


        output out;
    
}


network Net1
{
    @display("bgb=715,408");
    submodules:
        k1: Knot {
            @display("p=497,221");
        }


        k2: Knot {
            @display("p=334,95");
        }


        k3: Knot {
            @display("p=204,221");
        }


    connections:
        k1.out --> {  delay = 80ms; } --> k2.in;
        //k2.out --> {  delay = 100ms; } --> k1.in;
        k2.out --> {  delay = 80ms; } --> k3.in;
        //k3.out --> {  delay = 100ms; } --> k2.in;

        k3.out --> {  delay = 80ms; } --> k1.in;
        //k1.out --> {  delay = 100ms; } --> k3.in;



}
