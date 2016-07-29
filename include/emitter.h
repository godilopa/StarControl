#ifndef EMITTER_H
#define EMITTER_H

#include "image.h"
#include "affector.h"
#include "particle.h"


class Emitter {
public:
	Emitter(Image* image, bool autofade);
	virtual void SetPosition(double x, double y){ Emitter::x = x; Emitter::y = y; }
	virtual void SetX(double x){ Emitter::x = x; }
	virtual void SetY(double y){ Emitter::y = y; }
	virtual double GetX() const{ return x; }
	virtual double GetY() const{ return y; }
	virtual void SetRate(double minrate, double maxrate){ Emitter::minrate = minrate; Emitter::maxrate = maxrate; }
	virtual void SetVelocityX(double minvelx, double maxvelx){ Emitter::minvelx = minvelx; Emitter::maxvelx = maxvelx; }
	virtual void SetVelocityY(double minvely, double maxvely){ Emitter::minvely = minvely; Emitter::maxvely = maxvely; }
	virtual void SetAngularVelocity(double minangvel, double maxangvel){ Emitter::minangvel = minangvel; Emitter::maxangvel = maxangvel; }
	virtual void SetLifetime(double minlifetime, double maxlifetime){ Emitter::minlifetime = minlifetime; Emitter::maxlifetime = maxlifetime; }
	virtual void SetMinColor(uint8 r, uint8 g, uint8 b){ minr = r; ming = g; minb = b; }
	virtual void SetMaxColor(uint8 r, uint8 g, uint8 b) { maxr = r; maxg = g; maxb = b; }
	virtual void SetBlendMode(Renderer::BlendMode mode = Renderer::ADDITIVE){ blendMode = mode; }
	virtual void AddAffector(Affector affector){ affectors.Add(affector); }
	virtual void Start();
	virtual void Stop();
	virtual bool IsEmitting() const{ return emitting; }
	virtual bool ParticleAffected(Particle& particle, const Affector& affector);
	virtual void Update(double elapsed);
	virtual void Render() const;
private:
	Image* image;
	bool autofade;
	double x, y;
	double minrate, maxrate;
	double minvelx, maxvelx;
	double minvely, maxvely;
	double minangvel, maxangvel;
	double minlifetime, maxlifetime;
	uint8 minr, ming, minb;
	uint8 maxr, maxg, maxb;
	Renderer::BlendMode blendMode;
	bool emitting;
	Array<Particle> particles;
	Array<Affector> affectors;
};

#endif