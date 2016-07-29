
#include "../include/world.h"
#include "../include/resourcemanager.h"
#include "../include/guimanager.h"
#include "../include/image.h"
#include "../include/sprite.h"
#include "../include/entityfactory.h"
#include "../include/entity.h"
#include "../include/globales.h"
#include "../include/audioengine.h"

#define PLAYER1LIFEX 30
#define PLAYER1LIFEY 20
#define PLAYER1ENERGYX 30
#define PLAYER1ENERGYY 50
#define PLAYER2LIFEX 600
#define PLAYER2LIFEY 20
#define PLAYER2ENERGYX 600
#define PLAYER2ENERGYY 50

CWorld::CWorld() {
	Image * bg = ResourceManager::Instance().LoadImage("data/background.jpg");
	m_scene = new Scene(bg);
	m_font = ResourceManager::Instance().LoadFont("data/arial16.png");
	AudioEngine::Instance().Init();
}

CWorld::~CWorld() {
	AudioEngine::Instance().Finish();
	ResourceManager::Instance().FreeResources();
	delete m_scene;
}

void CWorld::Init(EntityId player, EntityId enemy){
	m_scene->GetCamera().SetBounds(0, 0, 0, 0);
	m_scene->GetCamera().SetPosition(0, 0);
	//Cargamos la info del player, creara el tipo de nave que llegue segun el parametro player
	//y luego le añadira el componente controller
	m_playerEntity = CEntityFactory::Instance().CreateEntity(player);
	m_playerEntity->AddComponent(CEntityFactory::Instance().NewComponent("controller", m_playerEntity, "player1"));
	m_entities.Add(m_playerEntity);
	//Cargamos la info del enemy, creara el tipo de nave que llegue segun el parametro enemy
	//y luego le añadira que esta manejada por la ia (si son dos jugadores otro controller2)
	if (g_pGame->GetTwoPlayers()){
		m_enemyEntity = CEntityFactory::Instance().CreateEntity(enemy);
		m_enemyEntity->AddComponent(CEntityFactory::Instance().NewComponent("controller", m_enemyEntity, "player2"));
		m_entities.Add(m_enemyEntity);
	}
	else{
		m_enemyEntity = CEntityFactory::Instance().CreateEntity(enemy);
		m_enemyEntity->AddComponent(CEntityFactory::Instance().NewComponent("ia", m_enemyEntity, "enemy"));
		m_entities.Add(m_enemyEntity);
	}
	//Strings para la info en el hud
	m_player1Life = "Player1 Life ";
	m_player1Energy = "Player1 Energy ";
	m_player2Life = "Player2 Life ";
	m_player2Energy = "Player2 Energy ";
	//Rellenamos la vida y energia totales
	MGetEnergy gemsg;
	MGetLife glmsg;
	//Del player
	m_playerEntity->SendMessage(&gemsg);
	m_playerEntity->SendMessage(&glmsg);
	m_player1TotalLife = String::FromInt(glmsg.life);
	m_player1TotalEnergy = String::FromInt(gemsg.energy);
	//Del enemigo
	m_enemyEntity->SendMessage(&gemsg);
	m_enemyEntity->SendMessage(&glmsg);
	m_player2TotalLife = String::FromInt(glmsg.life);
	m_player2TotalEnergy = String::FromInt(gemsg.energy);

}

void CWorld::Run() {
	//Actualizamos los sprites
	m_scene->Update(Screen::Instance().ElapsedTime(), nullptr);
	//Actualizamos las entidades
	for (uint32 i = 0; i < m_entities.Size(); i++){
		m_entities[i]->Update(Screen::Instance().ElapsedTime());
	}

	DestroyEntities();
	CheckEndOfGame();
}

void CWorld::DestroyEntities(){
	for (uint32 i = 0; i < m_entitiesToDestroy.Size(); i++){
		CEntityFactory::Instance().DeleteEntity(m_entitiesToDestroy[i]);
		m_entities.Remove(m_entitiesToDestroy[i]);
	}

	m_entitiesToDestroy.Clear();
}

void CWorld::CheckEndOfGame(){
	//Para entrar una unica vez
	if (!g_pGame->GetEndOfGame()){
		MGetLife glmsg1, glmsg2;
		m_playerEntity->SendMessage(&glmsg1);
		m_enemyEntity->SendMessage(&glmsg2);

		if (glmsg1.life <= 0 && glmsg2.life <= 0){
			MActivateExplosion axmsg;
			MDeleteController dcmsg;
			MDeleteIA diamsg;
			m_playerEntity->SendMessage(&axmsg);
			m_enemyEntity->SendMessage(&axmsg);
			m_playerEntity->SendMessage(&dcmsg);
			m_enemyEntity->SendMessage(&diamsg);
			g_pGame->SetWinner("deuce");
			g_pGame->SetEndOfGame(true);
		}

		if (glmsg1.life <= 0 && glmsg2.life > 0){
			MDeleteController dcmsg;
			MActivateExplosion axmsg;
			MDeleteIA diamsg;
			m_playerEntity->SendMessage(&axmsg);
			m_playerEntity->SendMessage(&dcmsg);
			m_enemyEntity->SendMessage(&diamsg);
			g_pGame->SetWinner("enemy");
			g_pGame->SetEndOfGame(true);
		}

		if (glmsg1.life > 0 && glmsg2.life <= 0){
			MDeleteController dcmsg;
			MActivateExplosion axmsg;
			MDeleteIA diamsg;
			m_enemyEntity->SendMessage(&axmsg);
			m_playerEntity->SendMessage(&dcmsg);
			m_enemyEntity->SendMessage(&diamsg);
			g_pGame->SetWinner("player");
			g_pGame->SetEndOfGame(true);
		}
	}

}

void CWorld::Draw() {
	m_scene->Render();
	CGuiManager::Instance().Render();
	//Obtenemos la informacion de los stats de ambos jugadores para renderearlos
	MGetEnergy gemsg;
	MGetLife glmsg;
	//Del player
	m_playerEntity->SendMessage(&gemsg);
	m_playerEntity->SendMessage(&glmsg);
	m_font->Render(m_player1Life + String::FromInt(glmsg.life) + "/" + m_player1TotalLife, PLAYER1LIFEX, PLAYER1LIFEY);
	m_font->Render(m_player1Energy + String::FromInt(gemsg.energy) + "/" + m_player1TotalEnergy, PLAYER1ENERGYX, PLAYER1ENERGYY);
	//Del enemigo
	m_enemyEntity->SendMessage(&gemsg);
	m_enemyEntity->SendMessage(&glmsg);
	m_font->Render(m_player2Life + String::FromInt(glmsg.life) + "/" + m_player2TotalLife, PLAYER2LIFEX, PLAYER2LIFEY);
	m_font->Render(m_player2Energy + String::FromInt(gemsg.energy) + "/" + m_player2TotalEnergy, PLAYER2ENERGYX, PLAYER2ENERGYY);
	Screen::Instance().Refresh();
	Renderer::Instance().Clear();
}

void CWorld::SendMessageToEntity(CEntity * entity, Message * msg){
	entity->SendMessage(msg);
}

void  CWorld::SendMessageToAllEntities(Message * msg){
	for (uint32 i = 0; i < m_entities.Size(); i++){
		m_entities[i]->SendMessage(msg);
	}
}