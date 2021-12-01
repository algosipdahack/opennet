#pragma once
#include "opennet.h"
struct Mac
{
    Mac() {}
    Mac(const Mac& r) { memcpy(this->mac_, r.mac_, SIZE); }
    Mac(const byte* r) { memcpy(this->mac_, r, SIZE); }
    Mac(const string& str);
    static Mac& nullMac();
    static Mac& broadcastMac();
    const static int SIZE = 6;
private:
    byte mac_[SIZE];
};
typedef Mac *PMac;
