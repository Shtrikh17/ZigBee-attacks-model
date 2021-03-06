//
// Generated file, do not edit! Created by nedtool 5.0 from nwkTree/nwkPacketTree.msg.
//

#ifndef __NWKPACKETTREE_M_H
#define __NWKPACKETTREE_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0500
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Class generated from <tt>nwkTree/nwkPacketTree.msg:16</tt> by nedtool.
 * <pre>
 * packet nwkPacketTree
 * {
 *     int srcAddress;
 *     int destAddress;
 *     int srcPANAddress;
 *     int destPANAddress;
 * }
 * </pre>
 */
class nwkPacketTree : public ::omnetpp::cPacket
{
  protected:
    int srcAddress;
    int destAddress;
    int srcPANAddress;
    int destPANAddress;

  private:
    void copy(const nwkPacketTree& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const nwkPacketTree&);

  public:
    nwkPacketTree(const char *name=nullptr, int kind=0);
    nwkPacketTree(const nwkPacketTree& other);
    virtual ~nwkPacketTree();
    nwkPacketTree& operator=(const nwkPacketTree& other);
    virtual nwkPacketTree *dup() const {return new nwkPacketTree(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b);

    // field getter/setter methods
    virtual int getSrcAddress() const;
    virtual void setSrcAddress(int srcAddress);
    virtual int getDestAddress() const;
    virtual void setDestAddress(int destAddress);
    virtual int getSrcPANAddress() const;
    virtual void setSrcPANAddress(int srcPANAddress);
    virtual int getDestPANAddress() const;
    virtual void setDestPANAddress(int destPANAddress);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const nwkPacketTree& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, nwkPacketTree& obj) {obj.parsimUnpack(b);}


#endif // ifndef __NWKPACKETTREE_M_H

