#include "../include/game.h"
#include "../include/globales.h"
#include "../include/gesturemanager.h"
#include "../include/entityfactory.h"
#include "../include/entity.h"

CGame::CGame() {
	m_endOfGame = false;
	m_World = new CWorld();
}

CGame::~CGame() {
	delete m_World;
}

void CGame::ProcessInput() {
	CGestureManager::Instance().Update();
}

void CGame::Run() {
	m_World->Run();
}

void CGame::Draw() {
	m_World->Draw();
}