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
// Generic LIN request frame
//
packet LinRequestFrame {
    //LIN identifier, which encodes the expected
    //response message and the message type
    int messageId;
}

packet LinResponseFrame extends LinRequestFrame {
    //The response from a slave actually contains several (up to 8) 
    //data bytes plus a checksum. For simplicity, we assume that a 
    //slave will simply reply with a random yes/no value
    int response;
}
