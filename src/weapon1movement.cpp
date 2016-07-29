#include "../include/weapon1movement.h"
#include "../include/globales.h"
#include "../include/sprite.h"
#include "../include/image.h"
#include "../include/math.h"

CWeapon1Movement::CWeapon1Movement(CEntity * entity){
	m_owner = entity;
}

CWeapon1Movement::~CWeapon1Movement(){

}

//Sprite es de la entidad de donde sale la bala
void CWeapon1Movement::Init(Sprite* sprite, double vel){
	double centerX = sprite->GetX();
	double centerY = sprite->GetY();
	double angle = sprite->GetAngle();
	double width = sprite->GetImage()->GetWidth(); //por la scala si queda grande la bala a su escala original
	double height = sprite->GetImage()->GetHeight();
	//Calculamos el punto desde donde sale el disparo y la direccion 0.4 como offset
	double initX = centerX + (0 * DegCos(360 - angle + 90) + width * 0.4 * DegSin(360 - angle + 90));
	double initY = centerY - (0 * DegSin(angle - 360 - 90) + height * 0.4 * DegCos(360 - angle + 90));
	//Cambiamos el punto donde se pintara la bala al iniciarse
	MGetSprite gsmsg;
	m_owner->SendMessage(&gsmsg);
	gsmsg.sprite->SetX(initX);
	gsmsg.sprite->SetY(initY);
	gsmsg.sprite->SetAngle(angle);
	//Inicializamos el movimiento de la bala
	m_initX = initX;
	m_initY = initY;
	m_velocity = vel;
	m_dirX = initX - centerX;
	m_dirY = initY - centerY;
}

void CWeapon1Movement::Update(double elapsed){
	MGetSprite spriteMsg;
	m_owner->SendMessage(&spriteMsg);

	if (!spriteMsg.sprite->IsMoving()){
		spriteMsg.sprite->MoveTo(m_initX + m_dirX * 500, m_initY + m_dirY * 500, m_velocity);
	}
}

void CWeapon1Movement::ReceiveMessage(Message * msg){
	MInitWeapon * iwmsg = dynamic_cast<MInitWeapon*>(msg);

	if (iwmsg){
		Init(iwmsg->sprite, iwmsg->vel);
	}
}