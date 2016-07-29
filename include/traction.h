#ifndef TRACTION_H
#define TRACTION_H

#include "component.h"
class Sprite;

class CTraction : public Component{
public:
	CTraction(CEntity * entity);
	virtual ~CTraction();
	virtual void Update(double elapsed);
	virtual void ReceiveMessage(Message * msg);
	void Tract();
private:
	Sprite * m_spriteOwner;
	Sprite * m_spriteTarget;
	bool m_tractActive = false;
	double m_timer = 0;
};

#endif