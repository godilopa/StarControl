#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "component.h"
#include "eventsconstants.h"
#include "entitiesid.h"
#include "iobserver.h"

class CController : public Component, public IEventObserver{
public:
	CController(CEntity * entity);
	virtual ~CController();
	void Init(const String& file, const String& entityName);
	virtual void Update(double elapsed);
	virtual void ReceiveMessage(Message * msg);
	virtual bool OnEvent(Event e);
private:
	void AssignStringToEvent(int key);
	void RotRight();
	void MoveDown();
	void RotLeft();
	void MoveUp();
	void Shot(int32 energy, EntityId id, double vel);
	double m_shootDelay;
};

#endif