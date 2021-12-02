#pragma once

#include "opennet.h"

struct Obj {
public:
	enum State {
		Closed, // 0
    Closing, // 1
		Opening, // 2
		Opened, // 3
	};

  Obj();
  ~Obj();

	bool active();

// public -> slot
/*public slots:
	virtual bool open();
	virtual bool close();

signals:
	void opened();
	void closed();*/

protected:
	virtual bool doOpen();
	virtual bool doClose();

protected:
	State state_{Closed};
};
