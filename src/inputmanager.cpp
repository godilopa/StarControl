#include "../include/inputmanager.h"
#include "../include/iobserver.h"

CInputManager* CInputManager::m_inputManager = nullptr;

CInputManager& CInputManager::Instance(){
	if (!m_inputManager)
		m_inputManager = new CInputManager();
	return *m_inputManager;
}

CInputManager::CInputManager(){
	CMouseController::Instance().AddIGestor(this);
	CKeyController::Instance().AddIGestor(this);
}

void CInputManager::ManageEvent(Event e){
	it = m_mappingObservers.find(e); //Buscamos si el evento ya está en el mapeado

	if (it != m_mappingObservers.end()){ //Si lo está extraemos la lista de observadores para iterar en ella, sino no hacemos nada
		Array<Observer> observers = it->second;
		
		bool eventConsume = false;
		uint32 i = 0;
		while (!eventConsume && i < observers.Size()){ //Si el evento no esta consumido y quedan observadores seguimos iterando
 				eventConsume = observers[i].observer->OnEvent(e);
				i++;
		}
	}
}

bool CInputManager::Comparacion(Observer & observer1, Observer & observer2){
	return (observer1.priority > observer2.priority);
}

void CInputManager::AddObserver(Event e, IEventObserver* const observer, int priority){
	it = m_mappingObservers.find(e); //Buscamos el evento en el mapeado

	if (it != m_mappingObservers.end()) { //Si lo encontramos
		Observer obs = { priority, observer }; //Definimos la prioridad con la que se va a guardar este evento en la lista
		it->second.Add(obs); //Añadimos el nuevo observer al evento
		it->second.Sort(Comparacion);
	}
	else { //Si no lo encontramos añadimos el nuevo evento y el nuevo observer
		Array<Observer> observers;
		Observer obs = { priority, observer };
		observers.Add(obs);
		m_mappingObservers[e] = observers;
	}
}

void CInputManager::DeleteObserver(Event e, IEventObserver* observer){
	it = m_mappingObservers.find(e); //Buscamos el evento en el mapeado

	if (it != m_mappingObservers.end()){ //Si lo encontramos
		for (uint32 i = 0; i < it->second.Size(); i++){ //Buscamos en el array si coinciden los observadores para borrar ese elemento
			if (it->second[i].observer == observer){
				it->second.RemoveAt(i);
			}
		}	
	}
}
