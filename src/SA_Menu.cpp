
#include "../include/SA_Menu.h"
#include "../include/button.h"
#include "../include/gesturemanager.h"
#include "../include/guimanager.h"
#include "../include/globales.h"

#define SCREENCENTERX Screen::Instance().GetWidth() / 2
#define SCREENCENTERY Screen::Instance().GetHeight() / 2
#define TITLEX 170
#define TITLEY 0

void SA_Menu::Run() {
	CGuiManager::Instance().Update();
}

void SA_Menu::Draw() {
	Renderer::Instance().DrawImage(m_title, TITLEX, TITLEY);
	CGuiManager::Instance().Render();
	Screen::Instance().Refresh();
	Renderer::Instance().Clear();
}

void SA_Menu::ProcessInput() {
	CGestureManager::Instance().Update();
}

void SA_Menu::Activate() {
	m_title = ResourceManager::Instance().LoadImage("data/title.jpg");
	m_buttonPlay = new CButton();
	m_buttonPlay->Init("play", SCREENCENTERX, SCREENCENTERY, "data/normalbutton.png", "data/pressedbutton.png");
	m_buttonPlay->AddObserver(this);	
}

void SA_Menu::Deactivate() {
	delete m_buttonPlay;
}

bool SA_Menu::OnEvent(Event e){
	if (e == G_CLICK){
		g_wantedState = SA_OPTIONS;
		return false;
	}

	return false;
}