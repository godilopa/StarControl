#ifndef ENEMY_STATE_MOVING_H
#define ENEMY_STATE_MOVING_H

#include "istate.h"
class CStateMachine;
class CEntity;
class Sprite;

class CEnemyStateMoving : public IState{
public:
	CEnemyStateMoving(CStateMachine * stateMachine, CEntity * entity) { m_stateMachine = stateMachine;  m_entity = entity; m_sprite = nullptr; }
	virtual void Enter();
	virtual void Update(double elapsed);
	virtual void ManageEvent(int32 nEvent);
	virtual void Exit();
	virtual int32 GetId() { return ESTATE_ENEMY_MOVING; }
private:
	CStateMachine * m_stateMachine;
	CEntity * m_entity;
	Sprite * m_sprite; //el sprite de la entidad lo rellena en enter
	Sprite * m_spritePlayer; //el sprite del player
	double m_timeToShoot;
};



#endif