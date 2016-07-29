
#include "../include/enemyIA.h"
#include "../include/enemystates.h"

CEnemyIA::CEnemyIA(CEntity* entity){
	m_owner = entity;
}

CEnemyIA::~CEnemyIA(){
	delete m_stateMachine;
}

void CEnemyIA::Init(){
	m_stateMachine = new CStateMachine();
	m_stateMachine->AddState(new CEnemyStateMoving(m_stateMachine, m_owner)); //hace delete de los estados la propia maquina al destruirse
	m_stateMachine->AddState(new CEnemyStateShooting(m_stateMachine, m_owner)); 
	m_stateMachine->AddState(new CEnemyStateDodging(m_stateMachine, m_owner)); 
	//Inicializamos la maquina al estado moverse
	m_stateMachine->ChangeState(ESTATE_ENEMY_MOVING);
}

void CEnemyIA::Update(double elapsed){
	m_stateMachine->Update(elapsed);
}

void CEnemyIA::ReceiveMessage(Message * msg){
	//Recibira mensajes que se traduciran en eventos para la maquina de estados
	MEventShot * esmsg = dynamic_cast<MEventShot*>(msg);

	if (esmsg){
		m_stateMachine->ManageEvent(m_stateMachine->EVENT_SHOT);
	}

	MDeleteIA * diamsg = dynamic_cast<MDeleteIA*>(msg);

	if (diamsg){
		m_owner->DeleteComponent(this);
	}
}