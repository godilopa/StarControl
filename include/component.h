#ifndef COMPONENT_H
#define COMPONENT_H

#include "message.h"
#include "entity.h"

class Component{
public:
	virtual ~Component() {}
	virtual void Update(double elapsed) = 0;
	virtual void ReceiveMessage(Message * msg) = 0;
protected:
	CEntity * m_owner;
};

#endif