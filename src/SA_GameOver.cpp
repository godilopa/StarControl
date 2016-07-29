
#include "../include/SA_GameOver.h"
#include "../include/entityFactory.h"
#include "../include/globales.h"
#include "../include/guimanager.h"
#include "../include/gesturemanager.h"
#include "../include/slider.h"

#define SLIDERX 250
#define SLIDERY 200
#define TEXTX 180
#define TEXTY 300
#define SLIDEROFFSET 20

void SA_GameOver::Run() {
	CGuiManager::Instance().Update();

	if (m_slider->GetValue() > m_slider->GetMaxVal() - SLIDEROFFSET){ //offset para que no haya que llegar justo al final de la barra
		g_wantedState = SA_MENU;
	}
}

void SA_GameOver::Draw() {
	if (g_pGame->GetWinner() != "deuce"){
		Screen::Instance().SetTitle(g_pGame->GetWinner() + " wins");
	}
	else{
		Screen::Instance().SetTitle(g_pGame->GetWinner());
	}
	
	CGuiManager::Instance().Render();
	m_font->Render("Drag till the end to restart", TEXTX, TEXTY);
	Screen::Instance().Refresh();
	Renderer::Instance().Clear();
}

void SA_GameOver::ProcessInput() {
	CGestureManager::Instance().Update();
}

void SA_GameOver::Activate() {
	m_font = new Font("data/monospaced.png");
	m_slider = new CSlider();
	m_slider->Init("Restart", SLIDERX, SLIDERY, "data/sliderbar.png", "data/sliderball.png");
	//Delete all entities
	CEntityFactory::Instance().DeleteAllEntities();
}

void SA_GameOver::Deactivate() {
	delete m_font;
	delete m_slider;
	Screen::Instance().SetTitle("");
	//Reset the game
	delete g_pGame;
	g_pGame = new CGame();
}

bool SA_GameOver::OnEvent(Event e){
	if (e == G_CLICK){
		g_wantedState = SA_OPTIONS;
		return false;
	}

	return false;
}
