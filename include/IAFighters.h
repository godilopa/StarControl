#ifndef IA_FIGHTERS_H
#define IA_FIGHTERS_H

#include "component.h"
#include "statemachine.h"
class Sprite;

class CIAFighters : public Component{
public:
	CIAFighters(CEntity* entity);
	~CIAFighters();
	void Init();
	virtual void Update(double elapsed);
	virtual void ReceiveMessage(Message * msg);

private:
	Sprite * m_launcherSprite;
	Sprite * m_targetSprite;
	CStateMachine * m_stateMachine;
};

#endif