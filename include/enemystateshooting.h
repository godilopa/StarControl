#ifndef ENEMY_STATE_SHOOTING_H
#define ENEMY_STATE_SHOOTING_H

#include "istate.h"
#include "entitiesid.h"
class CStateMachine;
class CEntity;
class Sprite;

class CEnemyStateShooting : public IState{
public:
	CEnemyStateShooting(CStateMachine * stateMachine, CEntity * entity) { m_stateMachine = stateMachine;  m_entity = entity; m_sprite = nullptr; }
	virtual void Enter();
	virtual void Update(double elapsed);
	virtual void ManageEvent(int32 nEvent);
	virtual void Exit();
	virtual int32 GetId() { return ESTATE_ENEMY_SHOOTING; }
private:
	void Shot(int32 energy, EntityId id, double vel);
	CStateMachine * m_stateMachine;
	CEntity * m_entity;
	Sprite * m_sprite; //el sprite de la entidad
	Sprite * m_spritePlayer;
	double m_velPlayer;
};

#endif
