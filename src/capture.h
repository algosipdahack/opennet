#include "obj.h";
#include "ethpacket.h";

struct Capture : Obj {
public:
	Capture() : Obj() {}
	~Capture() override;

bool autoParse_{true};

protected:
	bool autoRead_{true};

protected:
	bool doOpen() override { /* close(); */ /* signal function */ };
	bool doClose() override;

public:
	enum PathType {
		InPath,
		OutOfPath
	};

public:
	virtual Packet::Result read(Packet* packet);
	virtual Packet::Result write(Buf buf);
	virtual Packet::Result write(Packet* packet);
	virtual Packet::Result writeMtuSplit(Packet* packet, size_t mtu, Packet::Dlt dlt, Duration msleepTime = 1);
	virtual Packet::Result relay(Packet* packet);
	virtual Packet::Result drop(Packet* packet);

	virtual Packet::Dlt dlt() { return Packet::Null; }
	virtual PathType pathType() { return OutOfPath; }

// required check (about thread)
/*protected:
	struct Thread : GThread {
		Thread(GCapture* capture) : GThread(capture) {}
	protected:
		void run() override {
			GCapture* capture = dynamic_cast<GCapture*>(parent());
			Q_ASSERT(capture != nullptr);
			capture->run();
		}
	} thread_{this};*/

	virtual void run();

// signal function
// signals:
// 	void captured(GPacket* packet);
};
