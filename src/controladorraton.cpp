#include "../include/controladorraton.h"
#include "../include/eventsconstants.h"
#include "../include/inputManager.h"
#include "../lib/glfw.h"

CMouseController* CMouseController::m_mouseController = nullptr;

void GLFWCALL MouseCallback(int button, int action);
void GLFWCALL MouseCallback2(int posX, int posY);

CMouseController& CMouseController::Instance(){

	if (!m_mouseController){
		m_mouseController = new CMouseController();
		glfwSetMouseButtonCallback(&MouseCallback); //asocia la funcion de callback al glfw
		glfwSetMousePosCallback(&MouseCallback2);
	}

	return *m_mouseController;
}

void GLFWCALL MouseCallback(int button, int action){
	Event eventToProcess = EVENT_NULL;
	Array<IGestor*> gestors = CMouseController::Instance().GetIGestor();

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		eventToProcess = MOUSE_PRESS_LEFT;

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		eventToProcess = MOUSE_PRESS_RIGHT;

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		eventToProcess = MOUSE_RELEASE_LEFT;

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
		eventToProcess = MOUSE_RELEASE_RIGHT;

	for (uint32 i = 0; i < gestors.Size(); i++) gestors[i]->ManageEvent(eventToProcess);
}

//Este callback actualiza constantemente las coordendas del raton del input
void GLFWCALL MouseCallback2(int mouseX, int mouseY){
	CInputManager::Instance().SetMouseX(mouseX);
	CInputManager::Instance().SetMouseY(mouseY);
}
