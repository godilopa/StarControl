#ifndef ISTATE_H
#define ISTATE_H

#include "types.h"

enum EEnemyStates { ESTATE_ENEMY_NULL, ESTATE_ENEMY_MOVING, ESTATE_ENEMY_SHOOTING, ESTATE_ENEMY_DODGING };
enum EFighterStates { ESTATE_FIGHTER_NULL, ESTATE_FIGHTER_MOVING, ESTATE_FIGHTER_SHOOTING, ESTATE_FIGHTER_CHASING };

class IState{
public:
	virtual void Enter() = 0;
	virtual void Update(double elased) = 0;
	virtual void ManageEvent(int32 nEvent) = 0;
	virtual void Exit() = 0;
	virtual int32 GetId() = 0;
};

#endif