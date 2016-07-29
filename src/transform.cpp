#include "../include/transform.h"
#include "../lib/rapidxml.hpp"

using namespace rapidxml;

CTransform::CTransform(CEntity * entity){
	m_owner = entity;
}

CTransform::~CTransform(){

}

void CTransform::Init(const String& file, const String& entityName){
	String buffer = String::Read(file);
	//Analizamos el XML
	xml_document<> doc;
	doc.parse<0>((char*)buffer.ToCString());
	//Accedemos al nodo de la entidad
	xml_node<>* entityNode = doc.first_node()->first_node(entityName.ToCString());
	//Accedemos al nodo del componente
	xml_node<>* componentNode = entityNode->first_node("components")->first_node("transform");
	//Buscamos todos los valores que inicializar en el componente
	String posx = componentNode->first_attribute("posx")->value();
	String posy = componentNode->first_attribute("posy")->value();
	String angle = componentNode->first_attribute("angle")->value();
	String scale = componentNode->first_attribute("scale")->value();
	m_x = posx.ToFloat();
	m_y = posy.ToFloat();
	m_scalex = scale.ToFloat();
	m_scaley = scale.ToFloat();
	m_angle = angle.ToFloat();
}

void CTransform::Update(double elapsed){

}

void CTransform::ReceiveMessage(Message * msg){
	//Recibir mensaje de cambiar posicion
	MChangePosition * cpmsg = dynamic_cast<MChangePosition*>(msg);

	if (cpmsg){
		m_x = cpmsg->x;
		m_y = cpmsg->y;
	}
	//Recibir mensaje de dar posicion
	MGetPosition * spmsg = dynamic_cast<MGetPosition*>(msg);

	if (spmsg){
		spmsg->x = m_x;
		spmsg->y = m_y;
	}
	//Recibir mensaje de cambiar rotacion
	MChangeRotation * crmsg = dynamic_cast<MChangeRotation*>(msg);

	if (crmsg){
		m_angle = crmsg->angle;
	}
	//Recibir mensaje de dar rotacion
	MGetRotation * srmsg = dynamic_cast<MGetRotation*>(msg);

	if (srmsg){
		srmsg->angle = m_angle;
	}
	//Recibir mensaje de cambiar escala
	MChangeScale * csmsg = dynamic_cast<MChangeScale*>(msg);

	if (csmsg){
		m_scalex = csmsg->scalex;
		m_scaley = csmsg->scaley;
	}
	//Recibir mensaje de dar escala
	MGetScale * ssmsg = dynamic_cast<MGetScale*>(msg);

	if (ssmsg){
		ssmsg->scalex = m_scalex;
		ssmsg->scaley = m_scaley;
	}
}