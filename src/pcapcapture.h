#pragma once

#include <pcap.h>
#include "capture.h"

struct PcapCapture : Capture
{
	PcapCapture() : Capture() {}
	~PcapCapture() override { /* close(); */ /* signal function */ }

	std::string filter_{""};
	int mtu_{0};

	Packet::Result read(Packet* packet) override;
	Packet::Result write(Buf buf) override;
	Packet::Result write(Packet* packet) override;
	Packet::Result relay(Packet* packet) override;

	Packet::Dlt dlt() override { return dlt_; }
	PathType pathType() override { return OutOfPath; }

protected:
	bool doOpen() override;
	bool doClose() override;

	bool pcapProcessFilter(pcap_if_t* dev);
	pcap_t* pcap_{nullptr};
	Packet::Dlt dlt_{Packet::Null};
};
