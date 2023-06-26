//
// Generated file, do not edit! Created by nedtool 5.6 from veins/modules/messages/DemoServiceAdvertisement.msg.
//

#ifndef __VEINS_DEMOSERVICEADVERTISEMENT_M_H
#define __VEINS_DEMOSERVICEADVERTISEMENT_M_H

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
#include "veins/base/utils/Coord.h"
#include "veins/modules/messages/BaseFrame1609_4_m.h"
// }}


namespace Veins {

/**
 * Class generated from <tt>veins/modules/messages/DemoServiceAdvertisement.msg:31</tt> by nedtool.
 * <pre>
 * packet DemoServiceAdvertisment extends BaseFrame1609_4
 * {
 *     int targetChannel;
 *     string serviceDescription;
 * }
 * </pre>
 */
class DemoServiceAdvertisment : public ::Veins::BaseFrame1609_4
{
  protected:
    int targetChannel;
    ::omnetpp::opp_string serviceDescription;

  private:
    void copy(const DemoServiceAdvertisment& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const DemoServiceAdvertisment&);

  public:
    DemoServiceAdvertisment(const char *name=nullptr, short kind=0);
    DemoServiceAdvertisment(const DemoServiceAdvertisment& other);
    virtual ~DemoServiceAdvertisment();
    DemoServiceAdvertisment& operator=(const DemoServiceAdvertisment& other);
    virtual DemoServiceAdvertisment *dup() const override {return new DemoServiceAdvertisment(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getTargetChannel() const;
    virtual void setTargetChannel(int targetChannel);
    virtual const char * getServiceDescription() const;
    virtual void setServiceDescription(const char * serviceDescription);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const DemoServiceAdvertisment& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, DemoServiceAdvertisment& obj) {obj.parsimUnpack(b);}

} // namespace Veins

#endif // ifndef __VEINS_DEMOSERVICEADVERTISEMENT_M_H

