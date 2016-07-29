#include "../include/particle.h"

Particle::Particle(){}

Particle::Particle(Image* image, double velx, double vely, double angularVel,
	double lifetime, bool autofade) :Sprite(image),velocityx(velx),
	velocityy(vely), angularVelocity(angularVel), initialLifetime(lifetime),
	lifetime(lifetime), autofade(autofade), default(false), affector(nullptr){

}

void Particle::Update(double elapsed){
	if (autofade == true){
		SetAlpha(255 * lifetime / initialLifetime);
	}
	SetX(GetX() + velocityx*elapsed);
	SetY(GetY() + velocityy*elapsed);
	SetAngle(GetAngle()+angularVelocity*elapsed);
	lifetime -= elapsed;
}