#include "pcapcapture.h"

bool PcapCapture::doOpen()
{
	int dataLink = pcap_datalink(pcap_);
	dlt_ = Packet::intToDlt(dataLink);

	if (filter_ != "" && !pcapProcessFilter(nullptr))
		return false;

	return Capture::doOpen();
}

bool PcapCapture::doClose()
{
	Capture::doClose();

	if (pcap_ != nullptr)
	{
		pcap_close(pcap_);
		pcap_ = nullptr;
	}

	return true;
}

Packet::Result PcapCapture::read(Packet *packet)
{
	packet->clear();

	pcap_pkthdr *pktHdr;
	int i = pcap_next_ex(pcap_, &pktHdr, const_cast<const u_char **>(&(packet->buf_.data_)));
	if (state_ != Opened)
		return Packet::Fail;

	Packet::Result res;
	switch (i)
	{
	case PCAP_ERROR:
		pchar err = pcap_geterr(pcap_);
		if (err != nullptr && strlen(err) > 0)
		{
			// error: read failed
			std::cout << "[X] pcap_next_ex return -1 error=" << err << std::endl;
		}
		res = Packet::Eof;
		break;
	case PCAP_ERROR_BREAK:
	{
		pchar err = pcap_geterr(pcap_);
		if (err != nullptr && strlen(err) > 0)
		{
			// error: read failed
			std::cout << "[X] pcap_next_ex return -2 error=" << err << std::endl;
		}
		res = Packet::Eof;
		break;
	}
	case 0: // timeout
		res = Packet::None;
		break;
	default: // packet captured (success)
		packet->ts_ = pktHdr->ts;
		packet->buf_.size_ = pktHdr->caplen;
		if (autoParse_)
			packet->parse();
		res = Packet::Ok;
		break;
	}
	return res;
}

Packet::Result PcapCapture::write(Buf buf)
{
	int i = pcap_sendpacket(pcap_, buf.data_, int(buf.size_));
	if (i == 0)
		return Packet::Ok;
	pchar err = pcap_geterr(pcap_);
	if (err == nullptr)
		err = pchar("unknown");
	std::cout << "[X] pcap_sendpacket return " << i << "(" << err << ") length=" << buf.size_ << std::endl;
	return Packet::Fail;
}

Packet::Result PcapCapture::write(Packet *packet)
{
	Packet::Result res;
    if (mtu_ != 0 && packet->ipHdr_ != nullptr && packet->ipHdr_->tlen() > uint16_t(mtu_) && packet->tcpHdr_ != nullptr)
        res = writeMtuSplit(packet, mtu_);
	else
		res = write(packet->buf_);
	return res;
}

Packet::Result PcapCapture::relay(Packet *packet)
{
	(void)packet;
	std::cout << "[!] not supported" << std::endl;
	return Packet::Fail;
}

bool PcapCapture::pcapProcessFilter(pcap_if_t *dev)
{
	u_int uNetMask;
	bpf_program code;

	if (dev != nullptr && dev->addresses != nullptr && dev->addresses->netmask != nullptr)
		uNetMask = (reinterpret_cast<struct sockaddr_in *>(dev->addresses->netmask))->sin_addr.s_addr;
	else
		uNetMask = 0xFFFFFFFF;
	if (pcap_compile(pcap_, &code, filter_.c_str(), 1, uNetMask) < 0)
	{
		std::cout << "[X] pcap_compile error - " << pcap_geterr(pcap_) << " - " << filter_ << std::endl;
		return false;
	}
	if (pcap_setfilter(pcap_, &code) < 0)
	{
		// error: unknown
		std::cout << "[X] pcap_set_filter error - " << pcap_geterr(pcap_) << std::endl;
		return false;
	}
	return true;
}
