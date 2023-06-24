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

package aufgabe2gruppei.CompoundedModule;

//
// TODO auto-generated type
//
simple ApplicationLayer
{
    parameters:

    gates:
        input appIn[];
        output appOut[];
}
simple TimestampLayer
{
    parameters:

    gates:
        input tstampIn[];
        output tstampOut[];

}

channel Channel1 extends ned.DelayChannel
{
    delay = 0ms;
}
channel Channel2 extends ned.DelayChannel
{
    delay = 0ms;
}


module CompoundedModule
{
    parameters:
        bool isMaster = default(false);
        @display("bgb=718,387");
    gates:
        input in[];
        output out[];

    submodules:
        app_l: ApplicationLayer {

            @display("p=139,195");
        }
        tstamp_l: TimestampLayer {
            @display("p=476,193");
        }
    connections:
        app_l.appOut++ --> Channel1 --> tstamp_l.tstampIn++;
        app_l.appIn++ <-- Channel1 <-- tstamp_l.tstampOut++;

        app_l.appOut++ --> Channel2 --> tstamp_l.tstampIn++;
        app_l.appIn++ <-- Channel2 <-- tstamp_l.tstampOut++;

        tstamp_l.tstampOut++ --> Channel1 --> out++;
        tstamp_l.tstampIn++ <-- Channel1 <-- in++;

        tstamp_l.tstampOut++ --> Channel2 --> out++;
        tstamp_l.tstampIn++ <-- Channel2 <-- in++;
}
network Network
{
    @display("bgb=499,229");
    submodules:
        cmodule[3]: CompoundedModule {
            @display("p=148,145");
        }
    connections:
        cmodule[1].out++ --> cmodule[2].in++;
        cmodule[1].in++ <-- cmodule[2].out++;

        cmodule[0].out++ --> cmodule[1].in++;
        cmodule[0].in++ <-- cmodule[1].out++;

        cmodule[0].out++ --> cmodule[2].in++;
        cmodule[0].in++ <-- cmodule[2].out++;

}
