#include "../include/weapons.h"
#include "../include/audiosource.h"
#include "../include/audiobuffer.h"
#include "../lib/rapidxml.hpp"

using namespace rapidxml;

CWeapons::CWeapons(CEntity * entity){
	m_owner = entity;
}

CWeapons::~CWeapons(){
	delete m_audioBufferShot1;
	delete m_audioBufferShot2;
	delete m_audioShot1;
	delete m_audioShot2;
}

void CWeapons::Init(const String& file, const String& entityName){
	String buffer = String::Read(file);
	//Analizamos el XML
	xml_document<> doc;
	doc.parse<0>((char*)buffer.ToCString());
	//Accedemos al nodo del componente
	xml_node<>* entityNode = doc.first_node()->first_node(entityName.ToCString());
	//Accedemos al nodo weapons
	xml_node<>* weaponNode = entityNode->first_node("components")->first_node("weapons");
	//Accedemos a la primera arma
	xml_node<>* weapon = weaponNode->first_node("weapon1");
	String weapon1 = weapon->first_attribute("name")->value();
	m_weapon1 = AssignWeapon(weapon1);
	String energy = weapon->first_attribute("energy")->value();
	m_shot1Energy = energy.ToInt();
	String vel = weapon->first_attribute("vel")->value();
	m_vel1 = vel.ToFloat();
	String delay = weapon->first_attribute("delay")->value();
	m_delay1 = delay.ToFloat();
	String audioDir = weapon->first_attribute("sound")->value();
	m_audioBufferShot1 = new AudioBuffer(audioDir);
	m_audioShot1 = new AudioSource(m_audioBufferShot1);
	//Accedemos a la segunda arma
	weapon = weaponNode->first_node("weapon2");
	String weapon2 = weapon->first_attribute("name")->value();
	m_weapon2 = AssignWeapon(weapon2);
	energy = weapon->first_attribute("energy")->value();
	m_shot2Energy = energy.ToInt();
	vel = weapon->first_attribute("vel")->value();
	m_vel2 = vel.ToFloat();
	delay = weapon->first_attribute("delay")->value();
	m_delay2 = delay.ToFloat();
	audioDir = weapon->first_attribute("sound")->value();
	m_audioBufferShot2 = new AudioBuffer(audioDir);
	m_audioShot2 = new AudioSource(m_audioBufferShot2);
}

//Asocia el string del xml a un id
EntityId CWeapons::AssignWeapon(const String& name){
	if (name == "dreadnoughtshot1"){
		return EDREADNOUGHTSHOT1;
	}
	else if (name == "dreadnoughtshot2"){
		return EDREADNOUGHTSHOT2;
	}
	else if (name == "avatarshot1"){
		return EAVATARSHOT1;
	}
	else if (name == "avatartractor"){
		return EAVATARTRACTOR;
	}

	return ENULL;
}

void CWeapons::Update(double elapsed){

}

void CWeapons::PlaySound(EntityId weapon){
	if (weapon == m_weapon1){
		m_audioShot1->Play();
	}

	if (weapon == m_weapon2){
		m_audioShot2->Play();
	}
}

void CWeapons::ReceiveMessage(Message * msg){
	MGetWeapon1Info  * gw1msg = dynamic_cast<MGetWeapon1Info*>(msg);

	if (gw1msg){
		gw1msg->energy = m_shot1Energy;
		gw1msg->vel = m_vel1;
		gw1msg->delay = m_delay1;
		gw1msg->id= m_weapon1;
	}

	MGetWeapon2Info  * gw2msg = dynamic_cast<MGetWeapon2Info*>(msg);

	if (gw2msg){
		gw2msg->energy = m_shot2Energy;
		gw2msg->vel = m_vel2;
		gw2msg->delay = m_delay2;
		gw2msg->id = m_weapon2;
	}

	MPlayShot  * psmsg = dynamic_cast<MPlayShot*>(msg);

	if (psmsg){
		PlaySound(psmsg->weapon);
	}
}