#include "../include/render.h"
#include "../include/sprite.h"
#include "../include/globales.h"
#include "../include/string.h"
#include "../include/audiosource.h"
#include "../include/audiobuffer.h"
#include "../include/entityfactory.h"
#include "../lib/rapidxml.hpp"

#define SCREENWIDTH Screen::Instance().GetWidth()
#define SCREENHEIGHT Screen::Instance().GetHeight()
#define LIMITTODESTROY 900

using namespace rapidxml;

CRender::CRender(CEntity * entity){
	m_owner = entity;
	m_audioExplosion = nullptr;
	m_audioBufferExplosion = nullptr;
}

void CRender::Init(const String& file, const String& entityName){
	String buffer = String::Read(file);
	//Analizamos el XML
	xml_document<> doc;
	doc.parse<0>((char*)buffer.ToCString());
	//Accedemos al nodo de la entidad
	xml_node<>* entityNode = doc.first_node()->first_node(entityName.ToCString());
	//Accedemos al nodo render
	xml_node<>* componentNode = entityNode->first_node("components")->first_node("render");
	//Buscamos todos los valores que inicializar en el componente
	String dir = componentNode->first_attribute("imagedir")->value();
	Image* image = ResourceManager::Instance().LoadImage(dir);
	image->SetMidHandle();

	if (componentNode->first_attribute("explosiondir")){
		String dir = componentNode->first_attribute("explosiondir")->value();
		m_explosionImage = ResourceManager::Instance().LoadImage(dir, 20, 1);
		m_explosionImage->SetMidHandle();
	}

	if (componentNode->first_attribute("explosionsound")){
		String audioDir = componentNode->first_attribute("explosionsound")->value();
		m_audioBufferExplosion = new AudioBuffer(audioDir);
		m_audioExplosion = new AudioSource(m_audioBufferExplosion);
	}

	m_sprite = g_pGame->GetWorld()->GetScene()->CreateSprite(image);
	String posx = componentNode->first_attribute("posx")->value();
	String posy = componentNode->first_attribute("posy")->value();
	String angle = componentNode->first_attribute("angle")->value();
	String scale = componentNode->first_attribute("scale")->value();
	m_sprite->SetX(posx.ToFloat());
	m_sprite->SetY(posy.ToFloat());
	m_sprite->SetScale(scale.ToFloat(), scale.ToFloat());
	m_sprite->SetAngle(angle.ToFloat());
}

CRender::~CRender(){
	if (m_audioBufferExplosion) delete m_audioBufferExplosion;
	if (m_audioExplosion) delete m_audioExplosion;
	g_pGame->GetWorld()->GetScene()->DeleteSprite(m_sprite);
}

/*Si el sprite sale de los limites de la pantalla dependiendo de cual sea cambia su posicion o borra la entidad (caso de las armas)*/
void CRender::Update(double elapsed){
	switch (m_owner->GetId()){
	case EAVATAR:
		TrasladarEntidad();
	case EDREADNOUGHT:
		TrasladarEntidad();
	default:
		DestruirEntidad();
	}
	//Condicion para salir del juego cuando explota una nave y llegue el ultimo frame de la explosion
	if (m_sprite->GetImage() == m_explosionImage){
		if (m_sprite->GetCurrentFrame() == 19){
			g_wantedState = SA_GAMEOVER;
		}
	}
}

void CRender::ReceiveMessage(Message * msg){
	MGetSprite * rbmsg = dynamic_cast<MGetSprite*>(msg);

	if (rbmsg){
		rbmsg->sprite = m_sprite;
	}

	MGetEntityBySprite * gemsg = dynamic_cast<MGetEntityBySprite*>(msg);

	if (gemsg){
		if (gemsg->sprite == m_sprite){
			gemsg->entity = m_owner;
		}
	}

	MActivateExplosion * axmsg = dynamic_cast<MActivateExplosion*>(msg);

	if (axmsg && axmsg->activate){
		m_sprite->SetImage(m_explosionImage);
		m_sprite->SetFPS(10);
		m_sprite->SetFrameRange(0, m_sprite->GetImage()->GetNumFrames());
		m_audioExplosion->Play();
	}
}

void CRender::TrasladarEntidad(){
	if (m_sprite->GetX()< -m_sprite->GetImage()->GetWidth() * m_sprite->GetScaleX() / 2){
		m_sprite->SetX(SCREENWIDTH + m_sprite->GetImage()->GetWidth() * m_sprite->GetScaleX() / 2);
	}

	if (m_sprite->GetX() > SCREENWIDTH + m_sprite->GetImage()->GetWidth()  * m_sprite->GetScaleX() / 2) {
		m_sprite->SetX(-m_sprite->GetImage()->GetWidth()  * m_sprite->GetScaleX() / 2);
	}

	if (m_sprite->GetY() > SCREENHEIGHT + m_sprite->GetImage()->GetHeight()  * m_sprite->GetScaleY() / 2) {
		m_sprite->SetY(-m_sprite->GetImage()->GetHeight()  * m_sprite->GetScaleY() / 2);
	}

	if (m_sprite->GetY() < -m_sprite->GetImage()->GetHeight()  * m_sprite->GetScaleY() / 2) {
		m_sprite->SetY(SCREENHEIGHT + m_sprite->GetImage()->GetHeight()  * m_sprite->GetScaleY() / 2);
	}
}

void CRender::DestruirEntidad(){
	if (m_sprite->GetX() > LIMITTODESTROY){
		g_pGame->GetWorld()->AddEntityToDestroy(m_owner);
	}
}