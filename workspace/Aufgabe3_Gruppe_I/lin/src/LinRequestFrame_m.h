//
// Generated file, do not edit! Created by nedtool 5.6 from LinRequestFrame.msg.
//

#ifndef __LINREQUESTFRAME_M_H
#define __LINREQUESTFRAME_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0506
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Class generated from <tt>LinRequestFrame.msg:19</tt> by nedtool.
 * <pre>
 * //
 * // Generic LIN request frame
 * //
 * packet LinRequestFrame
 * {
 *     //LIN identifier, which encodes the expected
 *     //response message and the message type
 *     int messageId;
 * }
 * </pre>
 */
class LinRequestFrame : public ::omnetpp::cPacket
{
  protected:
    int messageId;

  private:
    void copy(const LinRequestFrame& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const LinRequestFrame&);

  public:
    LinRequestFrame(const char *name=nullptr, short kind=0);
    LinRequestFrame(const LinRequestFrame& other);
    virtual ~LinRequestFrame();
    LinRequestFrame& operator=(const LinRequestFrame& other);
    virtual LinRequestFrame *dup() const override {return new LinRequestFrame(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getMessageId() const;
    virtual void setMessageId(int messageId);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const LinRequestFrame& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, LinRequestFrame& obj) {obj.parsimUnpack(b);}


#endif // ifndef __LINREQUESTFRAME_M_H

