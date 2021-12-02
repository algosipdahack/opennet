#pragma once
#include "buf.h"
struct ArpHdr
{
  // hardware type (hrd_)
  enum : uint8_t
  {
    ETHER = 0x0001
  };

  // operation (op_)
  enum : uint8_t
  {
    Request = 0x0001,
    Reply = 0x0002
  };
  
  uint8_t hrd_;
  uint16_t pro_;
  uint8_t hln_;
  uint8_t pln_;
  uint8_t op_;
  Mac smac_;
  Mac tmac_;
  Ip sip_;
  Ip tip_;
};
typedef ArpHdr *PArpHdr;
