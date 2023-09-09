//
// Generated file, do not edit! Created by nedtool 5.7 from myMessage.msg.
//

#ifndef __MYMESSAGE_M_H
#define __MYMESSAGE_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0507
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Class generated from <tt>myMessage.msg:19</tt> by nedtool.
 * <pre>
 * //
 * // TODO generated message class
 * //
 * message MyMessage
 * {
 *     int priority;
 *     simtime_t timestamp;
 *     bool hastimestamp;
 * }
 * </pre>
 */
class MyMessage : public ::omnetpp::cMessage
{
  protected:
    int priority;
    ::omnetpp::simtime_t timestamp;
    bool hastimestamp;

  private:
    void copy(const MyMessage& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const MyMessage&);

  public:
    MyMessage(const char *name=nullptr, short kind=0);
    MyMessage(const MyMessage& other);
    virtual ~MyMessage();
    MyMessage& operator=(const MyMessage& other);
    virtual MyMessage *dup() const override {return new MyMessage(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getPriority() const;
    virtual void setPriority(int priority);
    virtual ::omnetpp::simtime_t getTimestamp() const;
    virtual void setTimestamp(::omnetpp::simtime_t timestamp);
    virtual bool getHastimestamp() const;
    virtual void setHastimestamp(bool hastimestamp);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const MyMessage& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, MyMessage& obj) {obj.parsimUnpack(b);}


#endif // ifndef __MYMESSAGE_M_H

