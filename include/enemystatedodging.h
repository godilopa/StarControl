#ifndef ENEMY_STATE_DODGING_H
#define ENEMY_STATE_DODGING_H

#include "istate.h"
class CStateMachine;
class CEntity;
class Sprite;

class CEnemyStateDodging: public IState{
public:
	CEnemyStateDodging(CStateMachine * stateMachine, CEntity * entity) { m_stateMachine = stateMachine;  m_entity = entity; m_sprite = nullptr; }
	virtual void Enter();
	virtual void Update(double elapsed);
	virtual void ManageEvent(int32 nEvent);
	virtual void Exit();
	virtual int32 GetId() { return ESTATE_ENEMY_DODGING; }
private:
	CStateMachine * m_stateMachine;
	CEntity * m_entity;
	Sprite * m_sprite; //El sprite de la entidad
	double m_timer; //Controla cuanto esta esquivando
};

#endif