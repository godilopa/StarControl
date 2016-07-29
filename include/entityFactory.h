#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include "array.h"
#include "string.h"
#include "entitiesid.h"
class CEntity;
class Component;

class CEntityFactory{
public:
	static CEntityFactory& Instance();
	void LoadFileInfo(const String& file);
	CEntity* CreateEntity(EntityId id);
	Component * NewComponent(const String& name, CEntity * entity, const String& entityName);
	void DeleteEntity(CEntity * entity);
	void DeleteAllEntities();
protected:
	CEntityFactory();
	virtual ~CEntityFactory();
private:
	static CEntityFactory * m_entityFactory;
	String m_entitiesInfo;
	Array<CEntity*> m_entities;
};

#endif