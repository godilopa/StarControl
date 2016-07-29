#ifndef ENEMY_IA_H
#define ENEMY_IA_H

#include "component.h"
#include "statemachine.h"

class CEnemyIA : public Component{
public:
	CEnemyIA(CEntity* entity);
	~CEnemyIA();
	void Init();
	virtual void Update(double elapsed);
	virtual void ReceiveMessage(Message * msg);
private:
	CStateMachine * m_stateMachine;
};

#endif