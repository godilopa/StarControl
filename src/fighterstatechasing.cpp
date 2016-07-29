#include "../include/fighterstatechasing.h"
#include "../include/message.h"
#include "../include/entity.h"
#include "../include/math.h"
#include "../include/statemachine.h"
#include "../include/globales.h"

void CFighterStateChasing::Enter(){
	if (!m_sprite){ //Guardamos el sprite de la entidad
		MGetSprite gsmsg;
		m_entity->SendMessage(&gsmsg);
		m_sprite = gsmsg.sprite;
	}
}

void CFighterStateChasing::Update(double elapsed){
	if (!m_targetSprite){
		MGetFighterSprites sfmsg;
		m_entity->SendMessage(&sfmsg);
		m_targetSprite = sfmsg.targetSprite;
	}

	m_sprite->MoveTo(m_targetSprite->GetX(), m_targetSprite->GetY(), 200);
	//Si hemos tocado la nave se reduce vida al objetivo y el arma se autodestruye
	if (Distance(m_targetSprite->GetX(), m_targetSprite->GetY(), m_sprite->GetX(), m_sprite->GetY()) < m_targetSprite->GetRadius() ){
		MReduceLife rlmsg; rlmsg.amount = 5;
		//Buscamos la entidad cuyo sprite es el que hemos golpeado y le reducimos la vida
		MGetEntityBySprite gemsg; gemsg.sprite = m_targetSprite;
		g_pGame->GetWorld()->SendMessageToAllEntities(&gemsg);
		gemsg.entity->SendMessage(&rlmsg);
		g_pGame->GetWorld()->AddEntityToDestroy(m_entity);
	}
}

void CFighterStateChasing::ManageEvent(int32 nEvent){

}

void CFighterStateChasing::Exit(){

}