#include "capture.h"

Capture::~Capture() {
	close();
}

// required check
/*bool GCapture::doOpen() {
	if (!enabled_) return true;

	if (autoRead_) {
		thread_.start();
	}
	return true;
}

bool GCapture::doClose() {
	if (!enabled_) return true;

	bool res = true;
	if (autoRead_) {
		thread_.quit();
		res = thread_.wait();
	}
	return res;
}*/

void Capture::run() {
	EthPacket ethPacket;
	IpPacket ipPacket;

	// data link type
	Packet* packet;
	switch(dlt()) {
		case Packet::Eth:
      packet = &ethPacket;
      break;
		case Packet::Ip:
      packet = &ipPacket;
      break;
	}

	PathType pt = pathType();
	while (active()) {
		Packet::Result res = read(packet);
		if (res == Packet::None) continue;
		if (res == Packet::Eof || res == Packet::Fail) break;
		// emit captured(packet);
		
    if (pt == InPath) {
			if (packet->ctrl.block_)
				res = drop(packet);
			else
				res = relay(packet);
			if (res != Packet::Ok) {
        std::cout << "[!] relay - return " << res << std::endl;
			}
    }
	}
}
	// emit closed();
