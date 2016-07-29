
#include "../include/controller.h"
#include "../include/globales.h"
#include "../include/inputmanager.h"
#include "../include/entityfactory.h"
#include "../include/screen.h"
#include "../include/math.h"
#include "../lib/rapidxml.hpp"

using namespace rapidxml;

CController::CController(CEntity * entity){
	m_owner = entity;
	m_shootDelay = 0;
}

CController::~CController(){
	CInputManager::Instance().DeleteObserver(G_KEY_IS_PRESSED_W, this);
	CInputManager::Instance().DeleteObserver(G_KEY_IS_PRESSED_S, this);
	CInputManager::Instance().DeleteObserver(G_KEY_IS_PRESSED_A, this);
	CInputManager::Instance().DeleteObserver(G_KEY_IS_PRESSED_D, this);
	CInputManager::Instance().DeleteObserver(G_KEY_IS_PRESSED_UP, this);
	CInputManager::Instance().DeleteObserver(G_KEY_IS_PRESSED_DOWN, this);
	CInputManager::Instance().DeleteObserver(G_KEY_IS_PRESSED_LEFT, this);
	CInputManager::Instance().DeleteObserver(G_KEY_IS_PRESSED_RIGHT, this);
	CInputManager::Instance().DeleteObserver(KEY_PRESS_ENTER, this);
	CInputManager::Instance().DeleteObserver(KEY_PRESS_SHIFT, this);
	CInputManager::Instance().DeleteObserver(KEY_PRESS_SPACE, this);
	CInputManager::Instance().DeleteObserver(KEY_PRESS_Q, this);
}

void CController::Init(const String& file, const String& entityName){
	String buffer = String::Read(file);
	//Analizamos el XML
	xml_document<> doc;
	doc.parse<0>((char*)buffer.ToCString());
	//Accedemos al nodo de la entidad
	xml_node<>* entityNode = doc.first_node()->first_node(entityName.ToCString());
	//Accedemos al nodo controller
	xml_node<>* controllerNode = entityNode->first_node("controller");
	//Buscamos las teclas asignadas
	String down = controllerNode->first_attribute("down")->value();
	AssignStringToEvent(down.ToInt());
	String up = controllerNode->first_attribute("up")->value();
	AssignStringToEvent(up.ToInt());
	String rotleft = controllerNode->first_attribute("rotleft")->value();
	AssignStringToEvent(rotleft.ToInt());
	String rotright = controllerNode->first_attribute("rotright")->value();
	AssignStringToEvent(rotright.ToInt());
	String fire1 = controllerNode->first_attribute("fire1")->value();
	AssignStringToEvent(fire1.ToInt());
	String fire2 = controllerNode->first_attribute("fire2")->value();
	AssignStringToEvent(fire2.ToInt());
}

void CController::Update(double elapsed){
	if (m_shootDelay > 0){
		m_shootDelay -= Screen::Instance().ElapsedTime();
	} else{
		m_shootDelay = 0;
	}
}

void CController::ReceiveMessage(Message * msg){
	MDeleteController * dcmsg = dynamic_cast<MDeleteController*>(msg);
	//Borrar el controller para cuando muere el jugador
	if (dcmsg){
		m_owner->DeleteComponent(this);
	}
}

void  CController::AssignStringToEvent(int key){
	switch(key){
		case 87:
			CInputManager::Instance().AddObserver(G_KEY_IS_PRESSED_W, this);
			break;
		case 83:
			CInputManager::Instance().AddObserver(G_KEY_IS_PRESSED_S, this);
			break;
		case 65:
			CInputManager::Instance().AddObserver(G_KEY_IS_PRESSED_A, this);
			break;
		case 68:
			CInputManager::Instance().AddObserver(G_KEY_IS_PRESSED_D, this);
			break;
		case 32:
			CInputManager::Instance().AddObserver(KEY_PRESS_SPACE, this);
			break;
		case 81:
			CInputManager::Instance().AddObserver(KEY_PRESS_Q, this);
			break;
		case 28:
			CInputManager::Instance().AddObserver(G_KEY_IS_PRESSED_LEFT, this);
			break;
		case 29:
			CInputManager::Instance().AddObserver(G_KEY_IS_PRESSED_RIGHT, this);
			break;
		case 30:
			CInputManager::Instance().AddObserver(G_KEY_IS_PRESSED_UP, this);
			break;
		case 31:
			CInputManager::Instance().AddObserver(G_KEY_IS_PRESSED_DOWN, this);
			break;
		case 13:
			CInputManager::Instance().AddObserver(KEY_PRESS_ENTER, this);
			break;
		case 15:
			CInputManager::Instance().AddObserver(KEY_PRESS_SHIFT, this);
			break;
	}
}

bool CController::OnEvent(Event e){
	switch (e){
		case G_KEY_IS_PRESSED_S:
			MoveDown();
			return false;
		case G_KEY_IS_PRESSED_D:
			RotRight();
			return false;
		case G_KEY_IS_PRESSED_A:
			RotLeft();
			return false;
		case G_KEY_IS_PRESSED_W:
			MoveUp();
			return false;
		case G_KEY_IS_PRESSED_DOWN:
			MoveDown();
			return false;
		case G_KEY_IS_PRESSED_RIGHT:
			RotRight();
			return false;
		case G_KEY_IS_PRESSED_LEFT:
			RotLeft();
			return false;
		case G_KEY_IS_PRESSED_UP:
			MoveUp();
			return false;
		case KEY_PRESS_SPACE:
		{
			if (m_shootDelay == 0){
				//Manda un mensaje de coger la info del arma 1
				MGetWeapon1Info gwmsg;
				m_owner->SendMessage(&gwmsg);
				m_shootDelay = gwmsg.delay;
				Shot(gwmsg.energy, gwmsg.id, gwmsg.vel);
			}

			return false;
		}

		case KEY_PRESS_Q:
		{
			if (m_shootDelay == 0){
				//Manda un mensaje de coger la info del arma 2
				MGetWeapon2Info gwmsg;
				m_owner->SendMessage(&gwmsg);
				m_shootDelay = gwmsg.delay;
				Shot(gwmsg.energy, gwmsg.id, gwmsg.vel);
			}
		
			return false;
		}
		case KEY_PRESS_ENTER:
		{
			if (m_shootDelay == 0){
				//Manda un mensaje de coger la info del arma 1
				MGetWeapon1Info gwmsg;
				m_owner->SendMessage(&gwmsg);
				m_shootDelay = gwmsg.delay;
				Shot(gwmsg.energy, gwmsg.id, gwmsg.vel);
			}

			return false;
		}

		case KEY_PRESS_SHIFT:
		{
			if (m_shootDelay == 0){
				//Manda un mensaje de coger la info del arma 2
				MGetWeapon2Info gwmsg;
				m_owner->SendMessage(&gwmsg);
				m_shootDelay = gwmsg.delay;
				Shot(gwmsg.energy, gwmsg.id, gwmsg.vel);
			}

			return false;
		}
	}

	return false;
}

void CController::RotRight(){
	MGetSprite gsmsg;
	m_owner->SendMessage(&gsmsg);
	MGetSpeeds gspmsg;
	m_owner->SendMessage(&gspmsg);
	double a = gsmsg.sprite->GetAngle();
	gsmsg.sprite->RotateTo((int32)a - 10, gspmsg.rotationSpeed);
}

void CController::RotLeft(){
	MGetSprite gsmsg;
	m_owner->SendMessage(&gsmsg);
	MGetSpeeds gspmsg;
	m_owner->SendMessage(&gspmsg);
	double a = gsmsg.sprite->GetAngle();
	gsmsg.sprite->RotateTo((int32)a + 10, gspmsg.rotationSpeed);
}

void CController::MoveDown(){
	MGetSprite gsmsg;
	m_owner->SendMessage(&gsmsg);
	MGetSpeeds gspmsg;
	m_owner->SendMessage(&gspmsg);

	if (!gsmsg.sprite->IsMoving()){
		gsmsg.sprite->MoveDown(10, gspmsg.linearSpeed);
	}
}

void CController::MoveUp(){
	MGetSprite gsmsg;
	m_owner->SendMessage(&gsmsg);
	MGetSpeeds gspmsg;
	m_owner->SendMessage(&gspmsg);

	if (!gsmsg.sprite->IsMoving()){
		gsmsg.sprite->MoveUp(10, gspmsg.linearSpeed);
	}
}

void CController::Shot(int32 energy, EntityId id, double vel){
	//Manda mensaje de coger energia
	MGetEnergy gemsg;
	m_owner->SendMessage(&gemsg);
	//Dispara si hay suficiente energia
	if (gemsg.energy > energy){
		//Manda mensaje de reducir energia
		MReduceEnergy remsg; remsg.amount = energy;
		m_owner->SendMessage(&remsg);
		//Get sprite de la nave
		MGetSprite gsmsg;
		m_owner->SendMessage(&gsmsg);
		//Creamos la bala
		CEntity * weapon = nullptr;
		CEntity * weapon2 = nullptr; //para la segunda arma del dreadnought
		//Si el arma es la primera del dreadnought iniciamos su movimiento
		if (id == EDREADNOUGHTSHOT1){
			weapon = CEntityFactory::Instance().CreateEntity(id);
			g_pGame->GetWorld()->GetEntities().Add(weapon);
			MInitWeapon iwmsg; iwmsg.sprite = gsmsg.sprite; iwmsg.vel = vel;
			weapon->SendMessage(&iwmsg);
		}
		//Si el arma es la primera del avatar iniciamos su movimiento
		if (id == EAVATARSHOT1){
			weapon = CEntityFactory::Instance().CreateEntity(id);
			g_pGame->GetWorld()->GetEntities().Add(weapon);
			MInitWeapon iwmsg; iwmsg.sprite = gsmsg.sprite; iwmsg.vel = vel;
			weapon->SendMessage(&iwmsg);
		}
		//En el caso del tractor iniciamos la traccion
		if (id == EAVATARTRACTOR){
			weapon = CEntityFactory::Instance().CreateEntity(id);
			g_pGame->GetWorld()->GetEntities().Add(weapon);
			//Mandamos un mensaje para coger el sprite rival
			MGetSprite gesmsg;
			g_pGame->GetWorld()->GetEnemyEntity()->SendMessage(&gesmsg);
			MTract tmsg; tmsg.ownerSprite = gsmsg.sprite; tmsg.targetSprite = gesmsg.sprite;
			weapon->SendMessage(&tmsg);
		}
		//Si el arma es la segunda del dreadnought disparara dos entidades que tienen su propia maquina de estados
		if (id == EDREADNOUGHTSHOT2){
			weapon = CEntityFactory::Instance().CreateEntity(id);
			g_pGame->GetWorld()->GetEntities().Add(weapon);
			MInitFighter ifmsg;
			MGetSprite gsmsg;
			//Rellenamos el mensaje con el sprite que lo ha lanzado y el objetivo (si son 2 jugadores el 2º es el enemy)
			if (m_owner == g_pGame->GetWorld()->GetPlayerEntity()){
				g_pGame->GetWorld()->GetPlayerEntity()->SendMessage(&gsmsg);
				ifmsg.launcherSprite = gsmsg.sprite;
				g_pGame->GetWorld()->GetEnemyEntity()->SendMessage(&gsmsg);
				ifmsg.targetSprite = gsmsg.sprite;
			}
			else{
				g_pGame->GetWorld()->GetEnemyEntity()->SendMessage(&gsmsg);
				ifmsg.launcherSprite = gsmsg.sprite;
				g_pGame->GetWorld()->GetPlayerEntity()->SendMessage(&gsmsg);
				ifmsg.targetSprite = gsmsg.sprite;
			}
			//Inicimos el arma
			weapon->SendMessage(&ifmsg);
			weapon2 = CEntityFactory::Instance().CreateEntity(id);
			g_pGame->GetWorld()->GetEntities().Add(weapon2);
			weapon2->SendMessage(&ifmsg);
		}
		//Sonido para el disparo que escuchara weapons y lo reproducira
		MPlayShot psmsg; psmsg.weapon = id;
		m_owner->SendMessage(&psmsg);
		//Despues de crearse manda un mensaje a traves de mundo a la entidad enemigo cuya ia escuchara
		//y mandara el evento a su maquina de estados para intentar esquivar (en el caso de que haya sido un disparo)
		if (id == EDREADNOUGHTSHOT1 || id == EAVATARSHOT1){
			MEventShot esmsg;
			g_pGame->GetWorld()->SendMessageToEntity(g_pGame->GetWorld()->GetEnemyEntity(), &esmsg);
		}
	}
}