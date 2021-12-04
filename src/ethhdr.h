#include "buf.h"
#pragma pack(push, 1)
struct EthHdr
{
    // ethertype (type_)
    enum : uint16_t
    {
        Arp = 0x806,
        Ip4 = 0x800,
    };

    Mac dmac_;
    Mac smac_;
    uint16_t type_;

    uint16_t type() { return ntohs(type_); }
    Mac smac() { return smac_; }
    Mac dmac() { return dmac_; }
};
typedef EthHdr *PEthHdr;
#pragma pack(pop)
