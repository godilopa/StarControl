
#include "../include/SA_Options.h"
#include "../include/checkbutton.h"
#include "../include/font.h"
#include "../include/gesturemanager.h"
#include "../include/guimanager.h"
#include "../include/globales.h"

#define SCREENCENTERX Screen::Instance().GetWidth() / 2
#define SCREENCENTERY Screen::Instance().GetHeight() / 2

void SA_Options::Run() {
	CGuiManager::Instance().Update();
}

void SA_Options::Draw() {
	CGuiManager::Instance().Render();
	m_font->Render("PLAYER", 100, 100);
	m_font->Render("Press 2 for second player", 180, 450);

	if (g_pGame->GetTwoPlayers()){
		m_font->Render("PLAYER2", 500, 100);
	}
	else{
		m_font->Render("ENEMY", 500, 100);
	}

	m_font->Render("Press space to start", 225, 500);
	Screen::Instance().Refresh();
	Renderer::Instance().Clear();
}

void SA_Options::ProcessInput() {
	CGestureManager::Instance().Update();
}

void SA_Options::Activate() {
	CInputManager::Instance().AddObserver(KEY_PRESS_SPACE, this, 2); //2 para que consuma el evento
	CInputManager::Instance().AddObserver(KEY_PRESS_2, this);
	m_enemyAvatarCheckButton = new CCheckButton();
	m_enemyAvatarCheckButton->Init("Avatar", 500, 200, "data/checkbuttonenabled.png", "data/checkbuttondisabled.png");
	m_enemyDreadnoughtCheckButton = new CCheckButton();
	m_enemyDreadnoughtCheckButton->Init("Dreadnought", 500, 300, "data/checkbuttonenabled.png", "data/checkbuttondisabled.png");
	m_playerAvatarCheckButton = new CCheckButton();
	m_playerAvatarCheckButton->Init("Avatar", 100, 200, "data/checkbuttonenabled.png", "data/checkbuttondisabled.png");
	m_playerDreadnoughtCheckButton = new CCheckButton();
	m_playerDreadnoughtCheckButton->Init("Dreadnought", 100, 300, "data/checkbuttonenabled.png", "data/checkbuttondisabled.png");
	m_font = new Font("data/monospaced.png");
}

void SA_Options::Deactivate() {
	delete m_enemyAvatarCheckButton;
	delete m_enemyDreadnoughtCheckButton;
	delete m_playerAvatarCheckButton;
	delete m_playerDreadnoughtCheckButton;
	delete m_font;
	CInputManager::Instance().DeleteObserver(KEY_PRESS_SPACE, this);
	CInputManager::Instance().DeleteObserver(KEY_PRESS_2, this);
}

bool SA_Options::OnEvent(Event e){
	if (e == KEY_PRESS_SPACE){
		if (ToGame()){
			g_wantedState = SA_PLAYING;
			return true;
		}
	} 

	if (e == KEY_PRESS_2){
		g_pGame->SetTwoPlayers(true);
	}

	return false;
}

/* Comprueba si todas las opciones han sido elegidas correctamente */
bool SA_Options::ToGame(){
	if (m_playerAvatarCheckButton->GetEnabled() != m_playerDreadnoughtCheckButton->GetEnabled()
		&& m_enemyAvatarCheckButton->GetEnabled() != m_enemyDreadnoughtCheckButton->GetEnabled()
		&& m_enemyAvatarCheckButton->GetEnabled() != m_playerAvatarCheckButton->GetEnabled()
		&& m_enemyDreadnoughtCheckButton->GetEnabled() != m_playerDreadnoughtCheckButton->GetEnabled()){
		//Según la que esté activada guardamos la nave correspondiente al player y a la IA en game
		if (m_playerAvatarCheckButton->GetEnabled()){
			g_pGame->SetNavePlayer(EAVATAR);
		}
		else{
			g_pGame->SetNavePlayer(EDREADNOUGHT);
		}

		if (m_enemyAvatarCheckButton->GetEnabled()){
			g_pGame->SetNaveEnemy(EAVATAR);
		}
		else{
			g_pGame->SetNaveEnemy(EDREADNOUGHT);
		}

		Screen::Instance().SetTitle("");
		return true;
	}
	else{
		Screen::Instance().SetTitle("Opciones incorrectas");
	}
	
	return false;
}
