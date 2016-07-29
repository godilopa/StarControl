
#include "../include/guimanager.h"
#include "../include/control.h"

CGuiManager* CGuiManager::m_guiManager = nullptr;

CGuiManager& CGuiManager::Instance(){
	if (!m_guiManager)
		m_guiManager = new CGuiManager();
	return *m_guiManager;
}

CGuiManager::CGuiManager(){
	CInputManager::Instance().AddObserver(G_CLICK, this, 2);
	CInputManager::Instance().AddObserver(G_DRAG, this, 2);
}

CGuiManager::~CGuiManager() { 
	CInputManager::Instance().DeleteObserver(G_CLICK, this);
	CInputManager::Instance().AddObserver(G_DRAG, this);
}

void CGuiManager::Update() const {
	for (uint32 i = 0; i < m_controls.Size(); i++){
		m_controls[i]->Update();
	}
}

void CGuiManager::Render() const{
	for (uint32 i = 0; i < m_controls.Size(); i++){
		m_controls[i]->Render();
	}
}

bool CGuiManager::OnEvent(Event e){
	it = m_mappingControls.find(e); //Buscamos si el evento ya está en el mapeado

	if (it != m_mappingControls.end()){ //Si lo está extraemos la lista de controles para iterar en ella, sino no hacemos nada
		Array<AControl*> controls = it->second;

		bool eventConsume = false;
		uint32 i = 0;
		while (!eventConsume && i < controls.Size()){ //Si el evento no esta consumido y quedan controles seguimos iterando
			eventConsume = controls[i]->OnEvent(e);
			i++;
		}
		return eventConsume;
	}
	return false;
}

void CGuiManager::AddControl(Event e, AControl* control){
	it = m_mappingControls.find(e); //Buscamos el evento en el mapeado

	if (it != m_mappingControls.end()) { //Si lo encontramos
		it->second.Add(control); //Añadimos el nuevo control al mapeado
		m_controls.Add(control); //Añadimos el nuevo control a la lista de controles para que sea actualizado y rendeado
	}
	else { //Si no lo encontramos añadimos el nuevo evento y el nuevo control
		Array<AControl*> controls;
		controls.Add(control); //Añadimos el nuevo control al mapeado
		m_controls.Add(control); //Añadimos el nuevo control a la lista de controles para que sea actualizado y rendeado
		m_mappingControls[e] = controls;
	}
}

void CGuiManager::DeleteControl(Event e, AControl* control){
	it = m_mappingControls.find(e); //Buscamos el evento en el mapeado

	if (it != m_mappingControls.end()) { //Si lo encontramos
		it->second.Remove(control); //Borramos el control del evento
		m_controls.Remove(control); //Borramos el controlr de la lista de controles a actualizar y renderear
	}
}