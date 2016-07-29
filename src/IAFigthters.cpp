#include "../include/IAFighters.h"
#include "../include/enemystates.h"

CIAFighters::CIAFighters(CEntity* entity){
	m_owner = entity;
}

CIAFighters::~CIAFighters(){
	delete m_stateMachine;
}

void CIAFighters::Init(){
	m_stateMachine = new CStateMachine();
	m_stateMachine->AddState(new CFighterStateMoving(m_stateMachine, m_owner)); //hace delete de los estados la propia maquina al destruirse
	m_stateMachine->AddState(new CFighterStateChasing(m_stateMachine, m_owner));
	//Inicializamos la maquina al estado moverse
	m_stateMachine->ChangeState(ESTATE_FIGHTER_MOVING);
}

void CIAFighters::Update(double elapsed){
	m_stateMachine->Update(elapsed);
}

void CIAFighters::ReceiveMessage(Message * msg){
	//Al dispararse los fighters se recibe este mensaje (del controller o del shooting de la ia del enemigo)
	//y esta componente se guardara el sprite desde donde se ha lanzado y el objetivo de los fighters
	//que con un mensaje MGetFighterSprites a su owner los estados podran obtener
	MInitFighter * ifmsg = dynamic_cast<MInitFighter*>(msg);

	if (ifmsg){
		m_launcherSprite = ifmsg->launcherSprite;
		m_targetSprite = ifmsg->targetSprite;
	}

	MGetFighterSprites * fsmsg = dynamic_cast<MGetFighterSprites*>(msg);

	if (fsmsg){
		fsmsg->launcherSprite = m_launcherSprite;
		fsmsg->targetSprite = m_targetSprite;
	}
}