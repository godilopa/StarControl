#include "../include/traction.h"
#include "../include/globales.h"
#include "../include/sprite.h"
#include "../include/math.h"

CTraction::CTraction(CEntity * entity){
	m_owner = entity;
}

CTraction::~CTraction(){

}

/* Controla el tiempo traccionando*/
void CTraction::Update(double elapsed){
	if (m_tractActive){
		m_timer += elapsed;
	}

	if (m_timer > 0.5){
		m_tractActive = false;
		m_timer = 0;
		m_spriteTarget->SetIsMoving(false);
	}
}

void CTraction::ReceiveMessage(Message * msg){
	MTract * tmsg = dynamic_cast<MTract*>(msg);

	if (tmsg){
		m_spriteOwner = tmsg->ownerSprite;
		m_spriteTarget = tmsg->targetSprite;
		m_tractActive = true;
		Tract();
	}
}

void CTraction::Tract(){
	//Direccion en la que traccionar
	double dirX = m_spriteOwner->GetX() - m_spriteTarget->GetX();
	double dirY = m_spriteOwner->GetY() - m_spriteTarget->GetY();
	//Si el target se estaba moviendo paramos su movimiento
	m_spriteTarget->SetIsMoving(false);
	//Traccionamos la target
	m_spriteTarget->MoveTo(m_spriteTarget->GetX() + dirX, m_spriteTarget->GetY() + dirY, 100);
}