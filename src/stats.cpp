#include "../include/stats.h"
#include "../include/globales.h"
#include "../lib/rapidxml.hpp"

using namespace rapidxml;

CStats::CStats(CEntity * entity){
	m_owner = entity;
}

void CStats::Init(const String& file, const String& entityName){
	String buffer = String::Read(file);
	//Analizamos el XML
	xml_document<> doc;
	doc.parse<0>((char*)buffer.ToCString());
	//Accedemos al nodo de la entidad
	xml_node<>* entityNode = doc.first_node()->first_node(entityName.ToCString());
	//Accedemos al nodo stats
	xml_node<>* componentNode = entityNode->first_node("components")->first_node("stats");
	//Buscamos todos los valores que inicializar en el componente
	String life = componentNode->first_attribute("life")->value();
	m_life = life.ToInt();
	String linearSpeed = componentNode->first_attribute("linearspeed")->value();
	m_linearSpeed = linearSpeed.ToFloat();
	String rotationSpeed = componentNode->first_attribute("rotationspeed")->value();
	m_rotationSpeed = rotationSpeed.ToFloat();
	String energy = componentNode->first_attribute("energy")->value();
	m_energy= energy.ToInt();
	m_inicialEnergy = m_energy;
}

CStats::~CStats(){

}

void CStats::Update(double elapsed){
	//Se va rellenando la energía automáticamente
	if (m_energy < m_inicialEnergy){
		m_energy += 10 * (int32)elapsed;
	}
}

void CStats::ReceiveMessage(Message * msg){
	MReduceLife * rlmsg = dynamic_cast<MReduceLife*>(msg);

	if (rlmsg){
		m_life -= rlmsg->amount;
	}

	MGetLife * glmsg = dynamic_cast<MGetLife*>(msg);

	if (glmsg){
		glmsg->life = m_life;
	}

	MSetLife * slmsg = dynamic_cast<MSetLife*>(msg);

	if (slmsg){
		m_life = slmsg->life;
	}

	MGetSpeeds * gsmsg = dynamic_cast<MGetSpeeds*>(msg);

	if (gsmsg){
		gsmsg->linearSpeed = m_linearSpeed;
		gsmsg->rotationSpeed = m_rotationSpeed;
	}

	MGetEnergy * gemsg = dynamic_cast<MGetEnergy*>(msg);

	if (gemsg){
		gemsg->energy = m_energy;
	}

	MReduceEnergy * remsg = dynamic_cast<MReduceEnergy*>(msg);

	if (remsg){
		m_energy -= remsg->amount;
	}
}