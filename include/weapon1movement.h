#ifndef WEAPON1_MOVEMENT_H
#define WEAPON1_MOVEMENT_H

#include "component.h"

class CWeapon1Movement : public Component{
public:
	CWeapon1Movement(CEntity * entity);
	void Init(Sprite * sprite, double vel);
	virtual ~CWeapon1Movement();
	virtual void Update(double elapsed);
	virtual void ReceiveMessage(Message * msg);
private:
	double m_initX, m_initY;
	double m_dirX, m_dirY;
	double m_velocity;
};

#endif