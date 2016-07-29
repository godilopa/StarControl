#include "../include/EnemyStateMoving.h"
#include "../include/statemachine.h"
#include "../include/message.h"
#include "../include/math.h"
#include "../include/entity.h"
#include "../include/globales.h"
#include "../include/sprite.h"
#include <math.h>

void CEnemyStateMoving::Enter(){
	if (!m_sprite){ //Condicion para entrar una sola vez
		MGetSprite gsmsg;
		m_entity->SendMessage(&gsmsg);
		m_sprite = gsmsg.sprite;
		m_timeToShoot = 0;
		//Sprite del player
		g_pGame->GetWorld()->SendMessageToEntity(g_pGame->GetWorld()->GetPlayerEntity(), &gsmsg);
		m_spritePlayer = gsmsg.sprite;
	}
}

void CEnemyStateMoving::Update(double elapsed){
	m_timeToShoot += elapsed;
	double playerX = m_spritePlayer->GetX();
	double playerY = m_spritePlayer->GetY();
	double enemyX = m_sprite->GetX();
	double enemyY = m_sprite->GetY();
	double angle = m_sprite->GetAngle();
	double distance = Distance(playerX, playerY, enemyX, enemyY);
	//Giramos al sprite en direccion al contrincante 
	double ux = (playerX - enemyX) / distance;
	double uy = (playerY - enemyY) / distance;
	double dot = - ux *DegSin(angle) - uy * DegCos(angle);
	double angBetweenSprites = DegACos(ux *DegCos(angle) - uy * DegSin(angle));
	//Pedimos la velocidad
	MGetSpeeds gsmsg;
	m_entity->SendMessage(&gsmsg);
	//Calculamos hacia donde debe rotar
	if (!m_sprite->IsRotating()){
		if (dot >= 0){
			m_sprite->RotateTo((int32)(angle + angBetweenSprites), gsmsg.rotationSpeed);
		}
		else{
			m_sprite->RotateTo((int32)(angle - angBetweenSprites), gsmsg.rotationSpeed);
		}
	}
	//Avanzamos o retrocedemos manteniendo una distancia de seguridad
	if (distance < 210){
		if (!m_sprite->IsMoving()){
			m_sprite->MoveDown(210 - distance, gsmsg.linearSpeed);
		}
	}
	else if (distance > 250) {
		if (!m_sprite->IsMoving()){
			m_sprite->MoveUp(distance - 250, gsmsg.linearSpeed);
		}
	}
	//Cada cierto tiempo dispara una bala
	if (m_timeToShoot > 2){
		m_stateMachine->ChangeState(ESTATE_ENEMY_SHOOTING);
		m_sprite->SetIsMoving(false);
	}
}

void CEnemyStateMoving::ManageEvent(int32 nEvent){
	//Si el contrincante dispara este recibe evento y pasa a esquivar
	if (nEvent == m_stateMachine->EVENT_SHOT){
		m_stateMachine->ChangeState(ESTATE_ENEMY_DODGING);
	}
}

void CEnemyStateMoving::Exit(){
	m_timeToShoot = 0;
	m_sprite->SetIsMoving(false);
}