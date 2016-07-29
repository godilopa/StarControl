#include "../include/collisioncomponent.h"
#include "../include/sprite.h"
#include "../include/globales.h"
#include "../include/image.h"
#include "../include/message.h"

CColisionComponent::CColisionComponent(CEntity * entity){
	m_owner = entity;
}

CColisionComponent::~CColisionComponent(){

}

void CColisionComponent::Init(){
	//Obtenemos el sprite para setear su colision
	MGetSprite gsmsg;
	m_owner->SendMessage(&gsmsg);
	gsmsg.sprite->SetRadius(gsmsg.sprite->GetImage()->GetWidth() * gsmsg.sprite->GetScaleX() / 3);
	gsmsg.sprite->SetCollision(Sprite::COLLISION_CIRCLE);
}

void CColisionComponent::Update(double elapsed){
	MGetSprite gsmsg;
	m_owner->SendMessage(&gsmsg);

	if (gsmsg.sprite->DidCollide()){
		//Entidad con la que colisiona segun el sprite
		MGetEntityBySprite gemsg; gemsg.sprite = gsmsg.sprite->CollisionSprite();
		g_pGame->GetWorld()->SendMessageToAllEntities(&gemsg);
		ResultOfCollision(gemsg.entity);
	}
}

void CColisionComponent::ReceiveMessage(Message * msg){

}

/* La colision con el arma 2 del dreadnought la maneja su maquina de estados */
void CColisionComponent::ResultOfCollision(CEntity * entity){
	switch (m_owner->GetId()){
		case EAVATAR:
		{
			switch (entity->GetId()){
			case EAVATARSHOT1:
			{
				//Reducimos la vida y apuntamos la bala para que se destruya
				MReduceLife rlmsg; rlmsg.amount = 10;
				m_owner->SendMessage(&rlmsg);
				g_pGame->GetWorld()->AddEntityToDestroy(entity);
				return;
			}

			case EDREADNOUGHTSHOT1:
			{
				//Reducimos la vida y apuntamos la bala para que se destruya
				MReduceLife rlmsg; rlmsg.amount = 10;
				m_owner->SendMessage(&rlmsg);
				g_pGame->GetWorld()->AddEntityToDestroy(entity);
				return;
			}

			case EDREADNOUGHT:
			{
				MSetLife slmsg; slmsg.life = 0;
				m_owner->SendMessage(&slmsg);
				entity->SendMessage(&slmsg);
				return;
			}
			case EAVATAR:
			{
				MSetLife slmsg; slmsg.life = 0;
				m_owner->SendMessage(&slmsg);
				entity->SendMessage(&slmsg);
				return;
			}
		}
	}

	case EDREADNOUGHT:
	{
		switch (entity->GetId()){
			case EAVATARSHOT1:
			{
				//Reducimos la vida y apuntamos la bala para que se destruya
				MReduceLife rlmsg; rlmsg.amount = 10;
				m_owner->SendMessage(&rlmsg);
				g_pGame->GetWorld()->AddEntityToDestroy(entity);
				return;
			}

			case EDREADNOUGHTSHOT1:
			{
				//Reducimos la vida y apuntamos la bala para que se destruya
				MReduceLife rlmsg; rlmsg.amount = 10;
				m_owner->SendMessage(&rlmsg);
				g_pGame->GetWorld()->AddEntityToDestroy(entity);
				return;
			}

			case EDREADNOUGHT:
			{
				MSetLife slmsg; slmsg.life = 0;
				m_owner->SendMessage(&slmsg);
				entity->SendMessage(&slmsg);
				return;
			}
			case EAVATAR:
			{
				MSetLife slmsg; slmsg.life = 0;
				m_owner->SendMessage(&slmsg);
				entity->SendMessage(&slmsg);
				return;
			}
		}
	}
	}
}
