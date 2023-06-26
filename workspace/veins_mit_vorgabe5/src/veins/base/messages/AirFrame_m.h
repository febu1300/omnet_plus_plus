//
// Generated file, do not edit! Created by nedtool 5.6 from veins/base/messages/AirFrame.msg.
//

#ifndef __VEINS_AIRFRAME_M_H
#define __VEINS_AIRFRAME_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
//#define MSGC_VERSION 0x0506
//#if (MSGC_VERSION!=OMNETPP_VERSION)
//#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
//#endif

// cplusplus {{
#include "veins/base/toolbox/Signal.h"
#include "veins/base/utils/POA.h"
// }}


namespace Veins {

/**
 * Class generated from <tt>veins/base/messages/AirFrame.msg:32</tt> by nedtool.
 * <pre>
 * //
 * // Format of the packets that are sent to the channel
 * //
 * // subclass if you want to create your own AirFrame packet class
 * // (see Omnet manual, chapter Messages - Inheritance among packet
 * // classes).
 * //
 * // This packet format is used to send a packet from the physical
 * // layer to the channel. All other physical layers that can 'hear'
 * // this packet can evaluate noise, interference etc. from the
 * // information contained in this packet (especially the signal):
 * //
 * // Note: BasePhy layer creates AirFrames with a slightly higher
 * // priority than normal to ensure channel consistency. This means that before anything else happens
 * // at a time point t every AirFrame which ended at t has been removed and
 * // every AirFrame started at t has been added to the channel.
 * //
 * // If you need more fields for whatever reason, please do NOT create
 * // your own packet! Just extend (subclass) this packet format
 * //
 * packet AirFrame
 * {
 *     Signal signal;        // Contains the physical data of this AirFrame
 * 
 *     POA poa;            // contains a POA object with the position, orientation and antenna (pointer)
 *                             // of the sender
 * 
 *     simtime_t duration;    // time the AirFrames takes to be transmited (without propagation delay)
 * 
 *     int state = 1;         // state of the AirFrames, used by the physical layer
 *                             // as state machine for delay and transmission duration
 *                             // simulation
 * 
 *     int type = 0;        // If type isn't null then this is a control-AirFrame
 *                             // and type specifies the control type.
 * 
 *     long id;            // Unique ID of the AirFrame used as identifier for
 *                             // related control-AirFrames
 * 
 *     int protocolId;        //the id of the phy protocol of this airframe
 * 
 *     int channel;        //the channel of the radio used for this transmission
 *     int mcs; // Modulation and conding scheme of the packet
 * }
 * </pre>
 */
class AirFrame : public ::omnetpp::cPacket
{
  protected:
    Signal signal;
    POA poa;
    ::omnetpp::simtime_t duration;
    int state;
    int type;
    long id;
    int protocolId;
    int channel;
    int mcs;

  private:
    void copy(const AirFrame& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const AirFrame&);

  public:
    AirFrame(const char *name=nullptr, short kind=0);
    AirFrame(const AirFrame& other);
    virtual ~AirFrame();
    AirFrame& operator=(const AirFrame& other);
    virtual AirFrame *dup() const override {return new AirFrame(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual Signal& getSignal();
    virtual const Signal& getSignal() const {return const_cast<AirFrame*>(this)->getSignal();}
    virtual void setSignal(const Signal& signal);
    virtual POA& getPoa();
    virtual const POA& getPoa() const {return const_cast<AirFrame*>(this)->getPoa();}
    virtual void setPoa(const POA& poa);
    virtual ::omnetpp::simtime_t getDuration() const;
    virtual void setDuration(::omnetpp::simtime_t duration);
    virtual int getState() const;
    virtual void setState(int state);
    virtual int getType() const;
    virtual void setType(int type);
    virtual long getId() const;
    virtual void setId(long id);
    virtual int getProtocolId() const;
    virtual void setProtocolId(int protocolId);
    virtual int getChannel() const;
    virtual void setChannel(int channel);
    virtual int getMcs() const;
    virtual void setMcs(int mcs);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const AirFrame& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, AirFrame& obj) {obj.parsimUnpack(b);}

} // namespace Veins

#endif // ifndef __VEINS_AIRFRAME_M_H

