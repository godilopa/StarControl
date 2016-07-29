
#include "../include/SA_Playing.h"
#include "../include/globales.h"
#include "../include/entityFactory.h"

void SA_Playing::ProcessInput() {
	g_pGame->ProcessInput();
}

void SA_Playing::Run() {
	g_pGame->Run();
}

void SA_Playing::Draw() {
	g_pGame->Draw();
}

void SA_Playing::Activate() {
	//Load info to use entityfactory and
	CEntityFactory::Instance().LoadFileInfo("data/config.xml");
	g_pGame->GetWorld()->Init(g_pGame->GetNavePlayer(), g_pGame->GetNaveEnemy());
}

void SA_Playing::Deactivate() {
	
}
