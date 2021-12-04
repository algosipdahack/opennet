#pragma once

#include "ip.h"
#include "mac.h"

struct Buf
{
    Buf();
    Buf(pbyte data, size_t size);

    pbyte data_;
    size_t size_;

    bool valid();
    void clear();
};
