#ifndef MESSAGE_H
#define MESSAGE_H

#include "sprite.h"
#include "entitiesid.h"
class CBulletMovement;
class CEntity;
class Component;

struct Message{
	virtual ~Message(){} //Para que los mensajes sean polymorficos y poder usar dynamic_cast
};

struct MGetPosition : Message {
	float x;
	float y;
};

struct MChangePosition : Message {
	float x;
	float y;
};

struct MGetRotation : Message {
	float angle;
};

struct MChangeRotation : Message {
	float angle;
};

struct MGetScale : Message {
	float scalex;
	float scaley;
};

struct MChangeScale : Message {
	float scalex;
	float scaley;
};

struct MReduceLife : Message {
	int32 amount;
};

struct MGetLife : Message {
	int32 life;
};

struct MSetLife : Message {
	int32 life;
};

struct MGetRadius : Message {
	int32 radius;
};

struct MGetSprite : Message {
	Sprite * sprite;
};

struct MGetSpeeds : Message {
	double rotationSpeed;
	double linearSpeed;
};

struct MGetEnergy : Message {
	int32 energy;
};

struct MReduceEnergy : Message {
	int32 amount;
};

struct MGetWeapon1Info : Message {
	double delay;
	int32 energy;
	double vel;
	EntityId id;
};

struct MGetWeapon2Info : Message {
	double delay;
	int32 energy;
	double vel;
	EntityId id;
};

struct MInitWeapon : Message {
	Sprite * sprite;
	double vel;
};

struct MTract : Message {
	Sprite * ownerSprite;
	Sprite * targetSprite;
};

struct MEventShot : Message { //Mensaje que recibe la ia para saber que tiene que lanzar un evento shot a su maquina de estados

};

struct MGetEntityBySprite : Message {
	Sprite * sprite;
	CEntity * entity;
};

struct MActivateExplosion : Message {
	bool activate;
};

struct MPlayShot : Message {
	EntityId weapon;
};

struct MInitFighter : Message {
	Sprite * launcherSprite;
	Sprite * targetSprite;
};

struct MGetFighterSprites : Message {
	Sprite * launcherSprite;
	Sprite * targetSprite;
};

struct MDeleteController : Message {

};

struct MDeleteIA : Message {

};

#endif