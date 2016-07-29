#include "../include/fighterstatemoving.h"
#include "../include/message.h"
#include "../include/entity.h"
#include "../include/math.h"
#include "../include/screen.h"
#include "../include/statemachine.h"

void CFighterStateMoving::Enter(){
	if (!m_sprite){ //Guardamos el sprite de la entidad
		MGetSprite gsmsg;
		m_entity->SendMessage(&gsmsg);
		m_sprite = gsmsg.sprite;
	}

	m_timeTochase = 0;
}

void CFighterStateMoving::Update(double elapsed){
	//Guardamos el sprite que lanza la bala para setear su origen
	if (!m_launcherSprite){
		MGetFighterSprites sfmsg;
		m_entity->SendMessage(&sfmsg);
		m_launcherSprite = sfmsg.launcherSprite;
		m_sprite->SetX(m_launcherSprite->GetX());
		m_sprite->SetY(m_launcherSprite->GetY());
	}

	m_timeTochase += Screen::Instance().ElapsedTime();
	double ang = rand() % 360; //para que la direccion donde se lanza sea aleatoria

	if (!m_sprite->IsMoving()){
		m_sprite->MoveTo(m_sprite->GetX() + DegCos(ang) * 500, m_sprite->GetY() + DegSin(ang) * 500, 200);
	}

	if (m_timeTochase > 0.5){
		m_stateMachine->ChangeState(ESTATE_FIGHTER_CHASING);
	}
}

void CFighterStateMoving::ManageEvent(int32 nEvent){

}

void CFighterStateMoving::Exit(){

}