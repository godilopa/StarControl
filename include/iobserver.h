#ifndef IOBSERVER_H
#define IOBSERVER_H

#include "eventsconstants.h"

class IEventObserver {
public:
	virtual bool OnEvent(Event e) = 0;
private:
};


#endif