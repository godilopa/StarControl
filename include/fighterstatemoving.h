#ifndef FIGHTER_STATE_MOVING_H
#define FIGHTER_STATE_MOVING_H

#include "istate.h"
#include "entitiesid.h"
class CStateMachine;
class CEntity;
class Sprite;

class CFighterStateMoving : public IState {
public:
	CFighterStateMoving(CStateMachine * stateMachine, CEntity * entity) { m_stateMachine = stateMachine;  m_entity = entity; m_sprite = nullptr; m_launcherSprite = nullptr; }
	virtual void Enter();
	virtual void Update(double elapsed);
	virtual void ManageEvent(int32 nEvent);
	virtual void Exit();
	virtual int32 GetId() { return ESTATE_FIGHTER_MOVING; }
private:
	CStateMachine * m_stateMachine;
	CEntity * m_entity;
	Sprite * m_sprite;
	Sprite * m_launcherSprite;
	double m_timeTochase;
};

#endif