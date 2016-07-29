#include "../include/EnemyStateShooting.h"
#include "../include/statemachine.h"
#include "../include/globales.h"
#include "../include/entityfactory.h"
#include "../include/message.h"
#include "../include/entity.h"
#include "../include/sprite.h"
#include <math.h>

void CEnemyStateShooting::Enter(){
	if (!m_sprite){ //Condicion para entrar una sola vez
		MGetSprite gsmsg;
		m_entity->SendMessage(&gsmsg);
		m_sprite = gsmsg.sprite;
		//Sprite del player
		g_pGame->GetWorld()->SendMessageToEntity(g_pGame->GetWorld()->GetPlayerEntity(), &gsmsg);
		m_spritePlayer = gsmsg.sprite;
		//Velocidad del player
		MGetSpeeds gsdmsg;
		g_pGame->GetWorld()->SendMessageToEntity(g_pGame->GetWorld()->GetPlayerEntity(), &gsdmsg);
		m_velPlayer = gsdmsg.linearSpeed;
	}
}

void CEnemyStateShooting::Update(double elapsed){
	//Aleatoriament usa alguna de las 2 armas disponibles
	if (rand() % 2 == 1){
		MGetWeapon1Info gwmsg;
		m_entity->SendMessage(&gwmsg);
		Shot(gwmsg.energy, gwmsg.id, gwmsg.vel);
	}else{
		MGetWeapon2Info gwmsg;
		m_entity->SendMessage(&gwmsg);
		Shot(gwmsg.energy, gwmsg.id, gwmsg.vel);
	}

	m_stateMachine->ChangeState(ESTATE_ENEMY_MOVING);
}

void CEnemyStateShooting::ManageEvent(int32 nEvent){
	//Si el contrincante dispara este recibe evento y pasa a esquivar
	if (nEvent == m_stateMachine->EVENT_SHOT){
		m_stateMachine->ChangeState(ESTATE_ENEMY_DODGING);
	}
}

void CEnemyStateShooting::Exit(){

}

void CEnemyStateShooting::Shot(int32 energy, EntityId id, double vel){
	//Manda mensaje de coger energia
	MGetEnergy gemsg;
	m_entity->SendMessage(&gemsg);
	//Dispara si hay suficiente energia
	if (gemsg.energy > energy){
		//Manda mensaje de reducir energia
		MReduceEnergy remsg; remsg.amount = energy;
		m_entity->SendMessage(&remsg);
		//Get sprite de la nave
		MGetSprite gsmsg;
		m_entity->SendMessage(&gsmsg);
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
			g_pGame->GetWorld()->GetPlayerEntity()->SendMessage(&gesmsg);
			MTract tmsg; tmsg.ownerSprite = gsmsg.sprite; tmsg.targetSprite = gesmsg.sprite;
			weapon->SendMessage(&tmsg);
		}
		//Si el arma es la segunda del dreadnought disparara dos entidades
		if (id == EDREADNOUGHTSHOT2){
			weapon = CEntityFactory::Instance().CreateEntity(id);
			g_pGame->GetWorld()->GetEntities().Add(weapon);
			MInitFighter ifmsg;
			//Rellenamos el mensaje con el sprite que lo ha lanzado y el objetivo
			MGetSprite gsmsg;
			g_pGame->GetWorld()->GetEnemyEntity()->SendMessage(&gsmsg);
			ifmsg.launcherSprite = gsmsg.sprite;
			g_pGame->GetWorld()->GetPlayerEntity()->SendMessage(&gsmsg);
			ifmsg.targetSprite = gsmsg.sprite;
			weapon->SendMessage(&ifmsg);
			weapon2 = CEntityFactory::Instance().CreateEntity(id);
			g_pGame->GetWorld()->GetEntities().Add(weapon2);
			weapon2->SendMessage(&ifmsg);
		}
		//Sonido para el disparo que escuchara weapons y lo reproducira
		MPlayShot psmsg; psmsg.weapon = id;
		m_entity->SendMessage(&psmsg);
	}
}