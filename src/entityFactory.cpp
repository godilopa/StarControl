#include "../include/entityFactory.h"
#include "../include/entitiesid.h"
#include "../include/entity.h"
#include "../include/component.h"
#include "../include/componenttypes.h"
#include "../lib/rapidxml.hpp"

using namespace rapidxml;

CEntityFactory* CEntityFactory::m_entityFactory = nullptr;

CEntityFactory& CEntityFactory::Instance(){
	if (!m_entityFactory){
		m_entityFactory = new CEntityFactory();
	}

	return *m_entityFactory;
}

CEntityFactory::CEntityFactory(){

}

CEntityFactory::~CEntityFactory(){

}

void CEntityFactory::LoadFileInfo(const String& file){
	m_entitiesInfo = file;
}

/*EntityName sirve para leer dentro del componente la informacion correcta segun el xml*/
Component * CEntityFactory::NewComponent(const String& name, CEntity * entity, const String& entityName){
	if (name == "render"){
		CRender * render = new CRender(entity);
		render->Init(m_entitiesInfo, entityName);
		return render;
	}
	else if (name == "stats"){
		CStats * stats = new CStats(entity);
		stats->Init(m_entitiesInfo, entityName);
		return stats;
	}
	else if (name == "collision"){
		CColisionComponent * collision = new CColisionComponent(entity);
		collision->Init();
		return collision;
	}
	else if (name == "controller"){
		CController * controller = new CController(entity);
		controller->Init(m_entitiesInfo, entityName);
		return controller;
	}
	else if (name == "ia"){
		CEnemyIA * ia = new CEnemyIA(entity);
		ia->Init();
		return ia;
	}
	else if (name == "weapons"){
		CWeapons * weapons = new CWeapons(entity);
		weapons->Init(m_entitiesInfo, entityName);
		return weapons;
	}
	else if (name == "iafighters"){
		CIAFighters * ia = new CIAFighters(entity);
		ia->Init();
		return ia;
	}
	else if (name == "traction"){
		CTraction * traction = new CTraction(entity);
		return traction;
	}
	else if (name == "weapon1movement"){
		CWeapon1Movement * weapon = new CWeapon1Movement(entity);
		return weapon;
	}
	else{
		return nullptr;
	}
}

CEntity * CEntityFactory::CreateEntity(EntityId id){
	String buffer = String::Read(m_entitiesInfo);
	//Analizamos el XML
	xml_document<> doc;
	doc.parse<0>((char*)buffer.ToCString());
	//Dependiendo del id buscamos la entidad adecuada
	String entityName;

	switch (id){
		case EDREADNOUGHT:
			entityName = "dreadnought";
			break;
		case EAVATAR:
			entityName = "avatar";
			break;
		case EDREADNOUGHTSHOT1:
			entityName = "dreadnoughtshot1";
			break;
		case EDREADNOUGHTSHOT2:
			entityName = "dreadnoughtshot2";
			break;
		case EAVATARSHOT1:
			entityName = "avatarshot1";
			break;
		case EAVATARTRACTOR:
			entityName = "avatartractor";
			break;
		case EFIGHTERSHOT:
			entityName = "fightershot";
			break;
	}

	//Accedemos al nodo de la entidad
	xml_node<>* entityNode = doc.first_node()->first_node(entityName.ToCString());
	CEntity * entity = new CEntity(id);
	//Accedemos al nodo componentes
	xml_node<>* componentsNode = entityNode->first_node("components");
	//Accedemos al primer componente
	xml_node<>* componentNode = componentsNode->first_node();
	//Buscamos todas las componentes
	while (componentNode != nullptr){
		String name = componentNode->name();
		//Creamos el nuevo componente
		Component * component = NewComponent(name, entity, entityName);
		//Lo añadimos a la entidad
		if (component){
			entity->AddComponent(component);
		}

		componentNode = componentNode->next_sibling();
	}

	m_entities.Add(entity);
	return entity;
}

void CEntityFactory::DeleteEntity(CEntity * entity){
	m_entities.Remove(entity);
	delete entity;
}

void CEntityFactory::DeleteAllEntities(){
	for (uint32 i = 0; i < m_entities.Size(); i++)
		delete m_entities[i];
	m_entities.Clear();
}