#ifndef COLLISION_COMPONENT_H
#define COLLISION_COMPONENT_H

#include "component.h"
class String;

class CColisionComponent : public Component{
public:
	CColisionComponent(CEntity * entity);
	virtual ~CColisionComponent();
	virtual void Init();
	virtual void Update(double elapsed);
	virtual void ReceiveMessage(Message * msg);
private:
	void ResultOfCollision (CEntity * entity);
};

#endif