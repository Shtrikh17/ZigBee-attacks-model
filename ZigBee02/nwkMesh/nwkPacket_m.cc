//
// Generated file, do not edit! Created by nedtool 5.0 from nwkMesh/nwkPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "nwkPacket_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: no doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: no doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(nwkPacket);

nwkPacket::nwkPacket(const char *name, int kind) : ::omnetpp::cPacket(name,kind)
{
    this->spoofed = false;
    this->srcAddress = 0;
    this->destAddress = 0;
    this->srcPANAddress = 0;
    this->destPANAddress = 0;
    this->type = 0;
}

nwkPacket::nwkPacket(const nwkPacket& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

nwkPacket::~nwkPacket()
{
}

nwkPacket& nwkPacket::operator=(const nwkPacket& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void nwkPacket::copy(const nwkPacket& other)
{
    this->spoofed = other.spoofed;
    this->srcAddress = other.srcAddress;
    this->destAddress = other.destAddress;
    this->srcPANAddress = other.srcPANAddress;
    this->destPANAddress = other.destPANAddress;
    this->type = other.type;
}

void nwkPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->spoofed);
    doParsimPacking(b,this->srcAddress);
    doParsimPacking(b,this->destAddress);
    doParsimPacking(b,this->srcPANAddress);
    doParsimPacking(b,this->destPANAddress);
    doParsimPacking(b,this->type);
}

void nwkPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->spoofed);
    doParsimUnpacking(b,this->srcAddress);
    doParsimUnpacking(b,this->destAddress);
    doParsimUnpacking(b,this->srcPANAddress);
    doParsimUnpacking(b,this->destPANAddress);
    doParsimUnpacking(b,this->type);
}

bool nwkPacket::getSpoofed() const
{
    return this->spoofed;
}

void nwkPacket::setSpoofed(bool spoofed)
{
    this->spoofed = spoofed;
}

int nwkPacket::getSrcAddress() const
{
    return this->srcAddress;
}

void nwkPacket::setSrcAddress(int srcAddress)
{
    this->srcAddress = srcAddress;
}

int nwkPacket::getDestAddress() const
{
    return this->destAddress;
}

void nwkPacket::setDestAddress(int destAddress)
{
    this->destAddress = destAddress;
}

int nwkPacket::getSrcPANAddress() const
{
    return this->srcPANAddress;
}

void nwkPacket::setSrcPANAddress(int srcPANAddress)
{
    this->srcPANAddress = srcPANAddress;
}

int nwkPacket::getDestPANAddress() const
{
    return this->destPANAddress;
}

void nwkPacket::setDestPANAddress(int destPANAddress)
{
    this->destPANAddress = destPANAddress;
}

int nwkPacket::getType() const
{
    return this->type;
}

void nwkPacket::setType(int type)
{
    this->type = type;
}

class nwkPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    nwkPacketDescriptor();
    virtual ~nwkPacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(nwkPacketDescriptor);

nwkPacketDescriptor::nwkPacketDescriptor() : omnetpp::cClassDescriptor("nwkPacket", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

nwkPacketDescriptor::~nwkPacketDescriptor()
{
    delete[] propertynames;
}

bool nwkPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<nwkPacket *>(obj)!=nullptr;
}

const char **nwkPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *nwkPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int nwkPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount() : 6;
}

unsigned int nwkPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<6) ? fieldTypeFlags[field] : 0;
}

const char *nwkPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "spoofed",
        "srcAddress",
        "destAddress",
        "srcPANAddress",
        "destPANAddress",
        "type",
    };
    return (field>=0 && field<6) ? fieldNames[field] : nullptr;
}

int nwkPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "spoofed")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcAddress")==0) return base+1;
    if (fieldName[0]=='d' && strcmp(fieldName, "destAddress")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcPANAddress")==0) return base+3;
    if (fieldName[0]=='d' && strcmp(fieldName, "destPANAddress")==0) return base+4;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+5;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *nwkPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",
        "int",
        "int",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<6) ? fieldTypeStrings[field] : nullptr;
}

const char **nwkPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *nwkPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int nwkPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    nwkPacket *pp = (nwkPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string nwkPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    nwkPacket *pp = (nwkPacket *)object; (void)pp;
    switch (field) {
        case 0: return bool2string(pp->getSpoofed());
        case 1: return long2string(pp->getSrcAddress());
        case 2: return long2string(pp->getDestAddress());
        case 3: return long2string(pp->getSrcPANAddress());
        case 4: return long2string(pp->getDestPANAddress());
        case 5: return long2string(pp->getType());
        default: return "";
    }
}

bool nwkPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    nwkPacket *pp = (nwkPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setSpoofed(string2bool(value)); return true;
        case 1: pp->setSrcAddress(string2long(value)); return true;
        case 2: pp->setDestAddress(string2long(value)); return true;
        case 3: pp->setSrcPANAddress(string2long(value)); return true;
        case 4: pp->setDestPANAddress(string2long(value)); return true;
        case 5: pp->setType(string2long(value)); return true;
        default: return false;
    }
}

const char *nwkPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *nwkPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    nwkPacket *pp = (nwkPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(RREQ);

RREQ::RREQ(const char *name, int kind) : ::omnetpp::cPacket(name,kind)
{
    this->hopCount = 0;
    this->RREQID = 0;
    this->destPANAddress = 0;
    this->originatorPANAddress = 0;
    this->hopPANAddress = 0;
}

RREQ::RREQ(const RREQ& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

RREQ::~RREQ()
{
}

RREQ& RREQ::operator=(const RREQ& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void RREQ::copy(const RREQ& other)
{
    this->hopCount = other.hopCount;
    this->RREQID = other.RREQID;
    this->destPANAddress = other.destPANAddress;
    this->originatorPANAddress = other.originatorPANAddress;
    this->hopPANAddress = other.hopPANAddress;
}

void RREQ::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->hopCount);
    doParsimPacking(b,this->RREQID);
    doParsimPacking(b,this->destPANAddress);
    doParsimPacking(b,this->originatorPANAddress);
    doParsimPacking(b,this->hopPANAddress);
}

void RREQ::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->hopCount);
    doParsimUnpacking(b,this->RREQID);
    doParsimUnpacking(b,this->destPANAddress);
    doParsimUnpacking(b,this->originatorPANAddress);
    doParsimUnpacking(b,this->hopPANAddress);
}

int RREQ::getHopCount() const
{
    return this->hopCount;
}

void RREQ::setHopCount(int hopCount)
{
    this->hopCount = hopCount;
}

int RREQ::getRREQID() const
{
    return this->RREQID;
}

void RREQ::setRREQID(int RREQID)
{
    this->RREQID = RREQID;
}

int RREQ::getDestPANAddress() const
{
    return this->destPANAddress;
}

void RREQ::setDestPANAddress(int destPANAddress)
{
    this->destPANAddress = destPANAddress;
}

int RREQ::getOriginatorPANAddress() const
{
    return this->originatorPANAddress;
}

void RREQ::setOriginatorPANAddress(int originatorPANAddress)
{
    this->originatorPANAddress = originatorPANAddress;
}

int RREQ::getHopPANAddress() const
{
    return this->hopPANAddress;
}

void RREQ::setHopPANAddress(int hopPANAddress)
{
    this->hopPANAddress = hopPANAddress;
}

class RREQDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    RREQDescriptor();
    virtual ~RREQDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(RREQDescriptor);

RREQDescriptor::RREQDescriptor() : omnetpp::cClassDescriptor("RREQ", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

RREQDescriptor::~RREQDescriptor()
{
    delete[] propertynames;
}

bool RREQDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RREQ *>(obj)!=nullptr;
}

const char **RREQDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *RREQDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int RREQDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount() : 5;
}

unsigned int RREQDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *RREQDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "hopCount",
        "RREQID",
        "destPANAddress",
        "originatorPANAddress",
        "hopPANAddress",
    };
    return (field>=0 && field<5) ? fieldNames[field] : nullptr;
}

int RREQDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='h' && strcmp(fieldName, "hopCount")==0) return base+0;
    if (fieldName[0]=='R' && strcmp(fieldName, "RREQID")==0) return base+1;
    if (fieldName[0]=='d' && strcmp(fieldName, "destPANAddress")==0) return base+2;
    if (fieldName[0]=='o' && strcmp(fieldName, "originatorPANAddress")==0) return base+3;
    if (fieldName[0]=='h' && strcmp(fieldName, "hopPANAddress")==0) return base+4;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *RREQDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : nullptr;
}

const char **RREQDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *RREQDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int RREQDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    RREQ *pp = (RREQ *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string RREQDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    RREQ *pp = (RREQ *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getHopCount());
        case 1: return long2string(pp->getRREQID());
        case 2: return long2string(pp->getDestPANAddress());
        case 3: return long2string(pp->getOriginatorPANAddress());
        case 4: return long2string(pp->getHopPANAddress());
        default: return "";
    }
}

bool RREQDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    RREQ *pp = (RREQ *)object; (void)pp;
    switch (field) {
        case 0: pp->setHopCount(string2long(value)); return true;
        case 1: pp->setRREQID(string2long(value)); return true;
        case 2: pp->setDestPANAddress(string2long(value)); return true;
        case 3: pp->setOriginatorPANAddress(string2long(value)); return true;
        case 4: pp->setHopPANAddress(string2long(value)); return true;
        default: return false;
    }
}

const char *RREQDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *RREQDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    RREQ *pp = (RREQ *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(RREP);

RREP::RREP(const char *name, int kind) : ::omnetpp::cPacket(name,kind)
{
    this->RREQID = 0;
    this->originatorPANAddress = 0;
    this->hopsLeft = 0;
    this->destPANAddress = 0;
    this->hopPANAddress = 0;
}

RREP::RREP(const RREP& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

RREP::~RREP()
{
}

RREP& RREP::operator=(const RREP& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void RREP::copy(const RREP& other)
{
    this->RREQID = other.RREQID;
    this->originatorPANAddress = other.originatorPANAddress;
    this->hopsLeft = other.hopsLeft;
    this->destPANAddress = other.destPANAddress;
    this->hopPANAddress = other.hopPANAddress;
}

void RREP::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->RREQID);
    doParsimPacking(b,this->originatorPANAddress);
    doParsimPacking(b,this->hopsLeft);
    doParsimPacking(b,this->destPANAddress);
    doParsimPacking(b,this->hopPANAddress);
}

void RREP::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->RREQID);
    doParsimUnpacking(b,this->originatorPANAddress);
    doParsimUnpacking(b,this->hopsLeft);
    doParsimUnpacking(b,this->destPANAddress);
    doParsimUnpacking(b,this->hopPANAddress);
}

int RREP::getRREQID() const
{
    return this->RREQID;
}

void RREP::setRREQID(int RREQID)
{
    this->RREQID = RREQID;
}

int RREP::getOriginatorPANAddress() const
{
    return this->originatorPANAddress;
}

void RREP::setOriginatorPANAddress(int originatorPANAddress)
{
    this->originatorPANAddress = originatorPANAddress;
}

int RREP::getHopsLeft() const
{
    return this->hopsLeft;
}

void RREP::setHopsLeft(int hopsLeft)
{
    this->hopsLeft = hopsLeft;
}

int RREP::getDestPANAddress() const
{
    return this->destPANAddress;
}

void RREP::setDestPANAddress(int destPANAddress)
{
    this->destPANAddress = destPANAddress;
}

int RREP::getHopPANAddress() const
{
    return this->hopPANAddress;
}

void RREP::setHopPANAddress(int hopPANAddress)
{
    this->hopPANAddress = hopPANAddress;
}

class RREPDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    RREPDescriptor();
    virtual ~RREPDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(RREPDescriptor);

RREPDescriptor::RREPDescriptor() : omnetpp::cClassDescriptor("RREP", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

RREPDescriptor::~RREPDescriptor()
{
    delete[] propertynames;
}

bool RREPDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RREP *>(obj)!=nullptr;
}

const char **RREPDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *RREPDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int RREPDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount() : 5;
}

unsigned int RREPDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *RREPDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "RREQID",
        "originatorPANAddress",
        "hopsLeft",
        "destPANAddress",
        "hopPANAddress",
    };
    return (field>=0 && field<5) ? fieldNames[field] : nullptr;
}

int RREPDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='R' && strcmp(fieldName, "RREQID")==0) return base+0;
    if (fieldName[0]=='o' && strcmp(fieldName, "originatorPANAddress")==0) return base+1;
    if (fieldName[0]=='h' && strcmp(fieldName, "hopsLeft")==0) return base+2;
    if (fieldName[0]=='d' && strcmp(fieldName, "destPANAddress")==0) return base+3;
    if (fieldName[0]=='h' && strcmp(fieldName, "hopPANAddress")==0) return base+4;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *RREPDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : nullptr;
}

const char **RREPDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *RREPDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int RREPDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    RREP *pp = (RREP *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string RREPDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    RREP *pp = (RREP *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getRREQID());
        case 1: return long2string(pp->getOriginatorPANAddress());
        case 2: return long2string(pp->getHopsLeft());
        case 3: return long2string(pp->getDestPANAddress());
        case 4: return long2string(pp->getHopPANAddress());
        default: return "";
    }
}

bool RREPDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    RREP *pp = (RREP *)object; (void)pp;
    switch (field) {
        case 0: pp->setRREQID(string2long(value)); return true;
        case 1: pp->setOriginatorPANAddress(string2long(value)); return true;
        case 2: pp->setHopsLeft(string2long(value)); return true;
        case 3: pp->setDestPANAddress(string2long(value)); return true;
        case 4: pp->setHopPANAddress(string2long(value)); return true;
        default: return false;
    }
}

const char *RREPDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *RREPDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    RREP *pp = (RREP *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


