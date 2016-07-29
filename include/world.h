#ifndef WORLD_H
#define WORLD_H

#include "scene.h"
#include "entitiesid.h"
#include "message.h"
class CEntity;
class Sprite;
class Image;

class CWorld {

public:
	CWorld();
	~CWorld();
	void Init(EntityId player, EntityId enemy);
	void Run();
	void Draw();
	void SendMessageToEntity(CEntity * entity, Message * msg);
	void SendMessageToAllEntities(Message * msg);
	void AddEntityToDestroy(CEntity* entity){ m_entitiesToDestroy.Add(entity); }
	CEntity * GetPlayerEntity(){ return m_playerEntity; }
	CEntity * GetEnemyEntity(){ return m_enemyEntity; }
	Scene * GetScene () { return m_scene; }
	Array<CEntity*>& GetEntities() { return m_entities; }
private:
	void DestroyEntities();
	void CheckEndOfGame();
	Font * m_font;
	Array<CEntity*> m_entities;
	Array<CEntity*> m_entitiesToDestroy;
	Scene * m_scene;
	CEntity * m_playerEntity;
	CEntity * m_enemyEntity;
	String m_player1Life, m_player1Energy, m_player2Life, m_player2Energy;
	String m_player1TotalLife, m_player1TotalEnergy, m_player2TotalLife, m_player2TotalEnergy;
};

#endif