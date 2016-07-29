#include "../include/enemystatedodging.h"
#include "../include/statemachine.h"
#include "../include/message.h"
#include "../include/entity.h"
#include "../include/sprite.h"
#include "../include/message.h"

void CEnemyStateDodging::Enter(){
	if (!m_sprite){ //Condicion para entrar una sola vez
		MGetSprite gsmsg;
		m_entity->SendMessage(&gsmsg);
		m_sprite = gsmsg.sprite;
		m_timer = 0;
	}
}

void CEnemyStateDodging::Update(double elapsed){
	m_timer += elapsed;
	//Pedimos la velocidad
	MGetSpeeds gsmsg;
	m_entity->SendMessage(&gsmsg);
	if (!m_sprite->IsMoving()){
		m_sprite->MoveTo(rand() % 800, rand() % 600, gsmsg.linearSpeed);
	}

	if (m_timer > 1){
		m_stateMachine->ChangeState(ESTATE_ENEMY_MOVING);
		m_sprite->SetIsMoving(false);
	}
}

void CEnemyStateDodging::ManageEvent(int32 nEvent){

}

void CEnemyStateDodging::Exit(){
	m_timer = 0;
}