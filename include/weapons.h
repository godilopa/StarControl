#ifndef WEAPONS_H
#define WEAPONS_H

#include "component.h"
class AudioSource;
class AudioBuffer;

class CWeapons : public Component{
public:
	CWeapons(CEntity * entity);
	void Init(const String& file, const String& entityName);
	virtual ~CWeapons();
	virtual void Update(double elapsed);
	virtual void ReceiveMessage(Message * msg);
private:
	void PlaySound(EntityId weapon);
	EntityId AssignWeapon(const String& name);
	int32 m_shot1Energy;
	int32 m_shot2Energy;
	AudioSource * m_audioShot1;
	AudioSource * m_audioShot2;
	AudioBuffer * m_audioBufferShot1;
	AudioBuffer * m_audioBufferShot2;
	EntityId m_weapon1;
	EntityId m_weapon2;
	double m_vel1;
	double m_vel2;
	double m_delay1;
	double m_delay2;
};

#endif