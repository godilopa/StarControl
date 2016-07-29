#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "igestor.h"
#include "eventsconstants.h"
#include <map>
#include "array.h"
#include "controladorraton.h"
#include "controladorteclado.h"

class IEventObserver;

class CInputManager: public IGestor{
public:
	static CInputManager& Instance();
	void AddObserver(Event e, IEventObserver* const observer, int priority = 1);
	void DeleteObserver(Event e, IEventObserver* observer);
	virtual void ManageEvent(Event e);
	int GetMouseX() const { return m_mouseX; }
	int GetMouseY() const { return m_mouseY; }
	void SetMouseX(int mouseX){ m_mouseX = mouseX; }
	void SetMouseY(int mouseY){ m_mouseY = mouseY; }
protected:
	CInputManager();
	virtual ~CInputManager() {}
private:
	//Estructura para guardar, asociado al evento, el array con el elemento que quiere observar y su prioridad
	struct Observer{
		int priority;
		IEventObserver * observer;
	};
	static bool Comparacion(Observer & observer1, Observer & observer2);
	static CInputManager* m_inputManager;
	int m_mouseX, m_mouseY;
	std::map<Event, Array<Observer>> m_mappingObservers;
	std::map<Event, Array<Observer>> ::iterator it;
};


#endif