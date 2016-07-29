#ifndef STATS_H
#define STATS_H

#include "component.h"
class Sprite;
class String;

class CStats : public Component{
public:
	CStats(CEntity * entity);
	void Init(const String& file, const String& entityName);
	virtual ~CStats();
	virtual void Update(double elapsed);
	virtual void ReceiveMessage(Message * msg);
private:
	int32 m_life;
	double m_rotationSpeed;
	double m_linearSpeed;
	int32 m_energy;
	double m_inicialEnergy;
};

#endif