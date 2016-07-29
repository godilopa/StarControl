#include "../include/controladorteclado.h"
#include "../include/eventsconstants.h"
#include "../lib/glfw.h"

CKeyController* CKeyController::m_keyController = nullptr;

void GLFWCALL KeyCallback(int button, int action);

CKeyController& CKeyController::Instance(){
	if (!m_keyController){
		m_keyController = new CKeyController();
		glfwSetKeyCallback(&KeyCallback); //asocia la funcion de callback al glfw
	}

	return *m_keyController;
}

void GLFWCALL KeyCallback(int button, int action){
	Event eventToProcess = EVENT_NULL;
	Array<IGestor*> gestors = CKeyController::Instance().GetIGestor();
	
	if (button == 32 && action == GLFW_PRESS)
		eventToProcess = KEY_PRESS_SPACE;
	if (button == 87 && action == GLFW_PRESS)
		eventToProcess = KEY_PRESS_W;
	if (button == 83 && action == GLFW_PRESS)
		eventToProcess = KEY_PRESS_S;
	if (button == 65 && action == GLFW_PRESS)
		eventToProcess = KEY_PRESS_A;
	if (button == 68 && action == GLFW_PRESS)
		eventToProcess = KEY_PRESS_D;
	if (button == 87 && action == GLFW_RELEASE)
		eventToProcess = KEY_RELEASE_W;
	if (button == 83 && action == GLFW_RELEASE)
		eventToProcess = KEY_RELEASE_S;
	if (button == 65 && action == GLFW_RELEASE)
		eventToProcess = KEY_RELEASE_A;
	if (button == 68 && action == GLFW_RELEASE)
		eventToProcess = KEY_RELEASE_D;
	if (button == 81 && action == GLFW_PRESS)
		eventToProcess = KEY_PRESS_Q;
	if (button == 50 && action == GLFW_PRESS)
		eventToProcess = KEY_PRESS_2;
	if (button == 294 && action == GLFW_PRESS)
		eventToProcess = KEY_PRESS_ENTER;
	if (button == 288 && action == GLFW_PRESS)
		eventToProcess = KEY_PRESS_SHIFT;
	if (button == 286 && action == GLFW_PRESS)
		eventToProcess = KEY_PRESS_RIGHT;
	if (button == 285 && action == GLFW_PRESS)
		eventToProcess = KEY_PRESS_LEFT;
	if (button == 284 && action == GLFW_PRESS)
		eventToProcess = KEY_PRESS_DOWN;
	if (button == 283 && action == GLFW_PRESS)
		eventToProcess = KEY_PRESS_UP;
	if (button == 286 && action == GLFW_RELEASE)
		eventToProcess = KEY_RELEASE_RIGHT;
	if (button == 285 && action == GLFW_RELEASE)
		eventToProcess = KEY_RELEASE_LEFT;
	if (button == 284 && action == GLFW_RELEASE)
		eventToProcess = KEY_RELEASE_DOWN;
	if (button == 283 && action == GLFW_RELEASE)
		eventToProcess = KEY_RELEASE_UP;

	for (uint32 i = 0; i < gestors.Size(); i++) gestors[i]->ManageEvent(eventToProcess);
}