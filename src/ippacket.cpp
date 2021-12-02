#include "ippacket.h"

void IpPacket::parse()
{
	pbyte p = buf_.data_;
	uint8_t proto;
	switch (*p & 0xF0)
	{					 // version field
	case 0x40: // version 4
		ipHdr_ = PIpHdr(p);
		proto = ipHdr_->p();
		p += ipHdr_->hl() * 4;
		break;
	default:
		proto = 0; // unknown
		break;
	}

	// protocol check
	switch (proto)
	{
	case IpHdr::TCP:
		tcpHdr_ = PTcpHdr(p);
		p += tcpHdr_->off() * 4;
		tcpData_ = TcpHdr::parseData(ipHdr_, tcpHdr_);
		break;
	case IpHdr::UDP:
		udpHdr_ = PUdpHdr(p);
		p += sizeof(UdpHdr);
		udpData_ = UdpHdr::parseData(udpHdr_);
		break;
	default:
		std::cout << "[!] unknown protocol - " << proto;
		break;
	}
}
