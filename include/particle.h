#ifndef PARTICLE_H
#define PARTICLE_H

#include "sprite.h"
#include "affector.h"

class Particle : public Sprite {
public:
	Particle();
	Particle(Image* image, double velx, double vely, double angularVel,
		double lifetime, bool autofade);
	virtual void SetVelocityx(double velocityx) { Particle::velocityx = velocityx; }
	virtual void SetVelocityy(double velocityy) { Particle::velocityy = velocityy; }
	virtual void SetAngularVelocity(double angularVelocity) { Particle::angularVelocity = angularVelocity; } //??porque si no pongo set no me deja hacer Particle::angularVelocity
	virtual double GetLifetime() const { return lifetime; }
	virtual bool GetDefault() const { return default; }
	virtual void SetDefault(bool default) { Particle::default = default; }
	virtual void SetAffector(const Affector* affector) { Particle::affector = affector; }
	virtual const Affector* GetAffector() const { return affector; }
	virtual void Update(double elapsed);
private:
	double velocityx, velocityy;
	double angularVelocity;
	double lifetime;
	double initialLifetime;
	bool autofade;
	bool default;
	const Affector* affector;
};

#endif