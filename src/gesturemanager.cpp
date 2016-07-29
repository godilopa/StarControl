#include "../include/gesturemanager.h"
#include "../include/inputmanager.h"
#include "../include/controladorraton.h"
#include "../include/controladorteclado.h"
#include "../include/screen.h"

CGestureManager* CGestureManager::m_gestureManager = nullptr;

CGestureManager& CGestureManager::Instance(){
	if (!m_gestureManager)
		m_gestureManager = new CGestureManager();
	return *m_gestureManager;
}

void CGestureManager::ManageEvent(Event e){
	eventProcessed = true;

	switch (e){
		case MOUSE_PRESS_LEFT:
			m_mouseleft_is_pressed = true;
			return;
		case MOUSE_RELEASE_LEFT:
			m_mouseleft_is_released = true;
			return;
		case MOUSE_PRESS_RIGHT:
			m_mouseright_is_pressed = true;
			return;
		case MOUSE_RELEASE_RIGHT:
			m_mouseright_is_pressed = false;
			return;
		case KEY_PRESS_SPACE:
			m_press_space = true;
			return;
		case KEY_PRESS_W:
			m_press_w = true;
			return;
		case KEY_PRESS_S:
			m_press_s = true;
			return;
		case KEY_PRESS_A:
			m_press_a = true;
			return;
		case KEY_PRESS_D:
			m_press_d = true;
			return;
		case KEY_RELEASE_W:
			m_press_w = false;
			return;
		case KEY_RELEASE_S:
			m_press_s = false;
			return;
		case KEY_RELEASE_A:
			m_press_a = false;
			return;
		case KEY_RELEASE_D:
			m_press_d = false;
			return;
		case KEY_PRESS_UP:
			m_press_up = true;
			return;
		case KEY_PRESS_DOWN:
			m_press_down = true;
			return;
		case KEY_PRESS_RIGHT:
			m_press_right = true;
			return;
		case KEY_PRESS_LEFT:
			m_press_left = true;
			return;
		case KEY_RELEASE_UP:
			m_press_up = false;
			return;
		case KEY_RELEASE_DOWN:
			m_press_down = false;
			return;
		case KEY_RELEASE_RIGHT:
			m_press_right = false;
			return;
		case KEY_RELEASE_LEFT:
			m_press_left = false;
			return;
	}
}

void CGestureManager::Init(){
	//Cargamos los controladores
	CMouseController::Instance().AddIGestor(this);
	CKeyController::Instance().AddIGestor(this);
	//Inicializamos variables miembros
	m_mouseleft_is_pressed = false; m_mouseright_is_pressed = false; timer = 0, timeBetweenEvents = 0;
	prevTime = 0; m_mouseleft_is_released = false; m_press_w = false; m_press_s = false;
	m_press_up = false; m_press_down = false; m_press_right = false; m_press_left = false;
	m_press_space = false; eventProcessed = false, m_press_a = false, m_press_d = false;
}

void CGestureManager::Update(){
	//Comprobamos si se ha producido algun evento para actualizar los timers
	if (eventProcessed) {
		timeBetweenEvents = timer - prevTime;
		prevTime = timer;
		eventProcessed = false;
	}

	timer += Screen::Instance().ElapsedTime();
	//Comprobamos si se ha producido algun gesto y actualizamos las coordenadas del raton
	MousePressed();
	KeyPressed();;
	Click();
	Drag();
	mouseX = CInputManager::Instance().GetMouseX();
	mouseY = CInputManager::Instance().GetMouseY();
}

bool CGestureManager::MousePressed(){
	if (m_mouseleft_is_pressed){
		CInputManager::Instance().ManageEvent(G_MOUSE_IS_PRESSED_LEFT);
		return true;
	}

	if (m_mouseright_is_pressed){
		CInputManager::Instance().ManageEvent(G_MOUSE_IS_PRESSED_RIGHT);
		return true;
	}

	return false;
}

bool CGestureManager::KeyPressed(){
	if (m_press_w){
		CInputManager::Instance().ManageEvent(G_KEY_IS_PRESSED_W);
	}

	if (m_press_s){
		CInputManager::Instance().ManageEvent(G_KEY_IS_PRESSED_S);
	}

	if (m_press_a){
		CInputManager::Instance().ManageEvent(G_KEY_IS_PRESSED_A);
	}

	if (m_press_d){
		CInputManager::Instance().ManageEvent(G_KEY_IS_PRESSED_D);
	}

	if (m_press_up){
		CInputManager::Instance().ManageEvent(G_KEY_IS_PRESSED_UP);
	}

	if (m_press_down){
		CInputManager::Instance().ManageEvent(G_KEY_IS_PRESSED_DOWN);
	}

	if (m_press_right){
		CInputManager::Instance().ManageEvent(G_KEY_IS_PRESSED_RIGHT);
	}

	if (m_press_left){
		CInputManager::Instance().ManageEvent(G_KEY_IS_PRESSED_LEFT);
	}
	return false;
}

void CGestureManager::Click(){
	if (m_mouseleft_is_pressed == true){
		if (m_mouseleft_is_released == true){
			//Si se ha pulsado y liberado el boton izquierdo reiniciamos a false sus valores
			m_mouseleft_is_pressed = false;
			m_mouseleft_is_released = false;
			//Comprobamos si se han producido en un intervalo de tiempo corto
			if (timeBetweenEvents < 0.3){
				CInputManager::Instance().ManageEvent(G_CLICK);
			}
		}
	}
}

void CGestureManager::Drag(){
	if (MousePressed()){
		//Si se ha pulsado el raton y alguna de las coordenadas que tenia guardadas son distintas de las actuales del raton es un drag
		if (mouseX != CInputManager::Instance().GetMouseX() ||
			mouseY != CInputManager::Instance().GetMouseY()){
				CInputManager::Instance().ManageEvent(G_DRAG);
		}
	}
}
