#include "../include/entity.h"
#include "../include/component.h"

CEntity::~CEntity(){
	for (uint32 i = 0; i < m_components.Size(); i++){
		delete m_components[i];
	}
}

void CEntity::Update(double elapsed){
	for (uint32 i = 0; i < m_components.Size(); i++){
		m_components[i]->Update(elapsed);
	}
}

void CEntity::AddComponent(Component * component){
	m_components.Add(component);
}

void CEntity::DeleteComponent(Component * component){
	delete component;
	m_components.Remove(component);
}

void CEntity::SendMessage(Message * msg){
	for (uint32 i = 0; i < m_components.Size(); i++){
		m_components[i]->ReceiveMessage(msg);
	}
}