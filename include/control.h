#ifndef CONTROL_H
#define CONTROL_H

#include "eventsconstants.h"
#include "array.h"
class IEventObserver;

class AControl{
public:
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual bool OnEvent(Event e) = 0;
	void AddObserver(IEventObserver* observer) { m_observers.Add(observer); }
	void DeleteObserver(IEventObserver* observer) { m_observers.Remove(observer); }
protected:
	Array<IEventObserver *> m_observers; //Protegido para que sus hijos puedan acceder
};

#endif