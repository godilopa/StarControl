#ifndef IGESTOR_H
#define IGESTOR_H

#include "eventsconstants.h"
	
class IGestor{
public:
	virtual void ManageEvent(Event e) = 0;
};


#endif