#ifndef GESTURE_MANAGER_H
#define GESTURE_MANAGER_H

#include "igestor.h"
class CMouseController;
class CKeyController;

class CGestureManager : public IGestor{

public:
	static CGestureManager& Instance();
	virtual void ManageEvent(Event e);
	void Update();
protected:
	CGestureManager(){ Init(); }
	virtual ~CGestureManager() {};
private:
	static CGestureManager* m_gestureManager;
	void Init();
	bool MousePressed();
	bool KeyPressed();
	void Click();
	void Drag();
	bool eventProcessed; //Controla si se ha producido algun evento para actualizar el timer entre eventos
	bool m_mouseleft_is_pressed, m_mouseright_is_pressed, m_mouseleft_is_released;
	bool m_press_up, m_press_down, m_press_right, m_press_left, m_press_w, m_press_s, m_press_a, m_press_d, m_press_space;
	double timer, prevTime, timeBetweenEvents;
	int mouseX, mouseY;
};



#endif