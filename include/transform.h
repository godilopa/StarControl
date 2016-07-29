#ifndef POSICION_H
#define POSICION_H

#include "component.h"

class CTransform : public Component{
public:
	CTransform(CEntity * entity);
	void Init(const String& file, const String& entityName);
	virtual ~CTransform();
	virtual void Update(double elapsed);
	virtual void ReceiveMessage(Message * msg);
private:
	float m_x, m_y;
	float m_scalex, m_scaley;
	float m_angle;
};

#endif