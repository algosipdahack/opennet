#include "obj.h"

Obj::~Obj() {
  if (state_ != Closed) {
    std::cout << "[X] State is " << state_ << std::endl;
  }
}

bool Obj::active() {
	return state_ == Opened;
}

// signal slot
/*bool Obj::open() {
	if (state_ != Closed) {
    // not closed
    std::cout << "State is " << state << std::endl;
		return false;
	}

	state_ = Opening;
	bool res = doOpen();
	if (!res) {
		state_ = Closing;
		doClose();
		state_ = Closed;
		return false;
	}

	state_ = Opened;
	// emit opened();
	return true;
}

bool Obj::close() {
	if (state_ == Closed)
		return true;

	if (!active()) {
    // not opened
		std::cout << "State is " << state_ << std::endl;
		return false;
	}

	state_ = Closing;
	doClose();
	state_ = Closed;
	// emit closed();
	return true;
}*/

bool Obj::doOpen() {
  // virtual function call
  std::cout << "[X] virtual function call" << std::endl;
	return false;
}

bool Obj::doClose() {
  // virtual function call
	std::cout << "[X] virtual function call" << std::endl;
	return false;
}
