#ifndef ENTITY_H
#define ENTITY_H

#include "array.h"
#include "message.h"
#include "entitiesid.h"
class Component;

class CEntity {
public:
	CEntity(EntityId id){ m_id = id; }
	~CEntity();
	EntityId GetId(){ return m_id; }
	virtual void Update(double elapsed);
	void AddComponent(Component * component);
	void DeleteComponent(Component * component);
	void SendMessage(Message * msg);
private:
	Array<Component*> m_components;
	EntityId m_id;
};

#endif