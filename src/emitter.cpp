#include "../include/emitter.h"
#include "../include/screen.h"
#include <cstdlib>
#include <ctime>

double random(double max, double min){
	return min + (rand() / (float)RAND_MAX) * (max - min);
}

Emitter::Emitter(Image* image, bool autofade): image(image), autofade(autofade){
	srand(static_cast<unsigned int>(time(0)));
}

void Emitter::Start(){
	emitting = true;
}

void Emitter::Update(double elapsed){
	double rate;
	rate = random(maxrate, minrate);

	if (emitting){
		//generador de particulas
		for (int32 i = 0; i < rate*elapsed; i++){
			double velx = random(maxvelx, minvelx);
			double vely = random(maxvely, minvely);
			double angvel = random(maxangvel, minangvel);
			double lifetime = random(maxlifetime, minlifetime);
			Particle particle(image, velx, vely, angvel, lifetime, autofade);
			particle.SetBlendMode(Renderer::ADDITIVE);
			particle.SetColor(rand() % 255, rand() % 255, rand() % 255);
			particle.SetPosition(GetX(), GetY());
			particles.Add(particle);
		}
	}

	for (int32 i = 0; i < particles.Size(); i++){ //Para cada particula
		for (int32 j = 0; j < affectors.Size(); j++){ //Comprobamos para cada afector
			if (particles[i].GetAffector() != &affectors[j]){ //Si el afector es distinto al ultimo que afecto a la particula
				if (ParticleAffected(particles[i], affectors[j])){ //Y entra en su region, cambia sus estados
					//Calculamos el random de cada atributo que se va a cambiar
					int8 newr, newg, newb;
					double newangvel = random(affectors[j].newmaxangvel, affectors[j].newminangvel);
					newr = random(affectors[j].newmaxr, affectors[j].newminr);
					newg = random(affectors[j].newmaxg, affectors[j].newming);
					newb = random(affectors[j].newmaxb, affectors[j].newminb);

					particles[i].SetColor(newr, newg, newb);
					particles[i].SetAngularVelocity(newangvel);
				}
			}
			else if (!ParticleAffected(particles[i], affectors[j]) && !particles[i].GetDefault()){ // si no esta siendo afectada y no esta ya por defecto
				double angvel = random(maxangvel, minangvel);
				particles[i].SetAngularVelocity(angvel);
				particles[i].SetColor(rand() % 255, rand() % 255, rand() % 255);
				particles[i].SetDefault(true);
			}
		}
		//Se actualizan las particulas
		particles[i].Update(elapsed);
		if (particles[i].GetLifetime() <= 0) particles.RemoveAt(i); //la particula se elimina
	}
}

void Emitter::Stop(){
	emitting = false;
}

void Emitter::Render() const{
	for (int32 i = 0; i < particles.Size(); i++){
		particles[i].Render();
	}
}

bool Emitter::ParticleAffected(Particle& particle, const Affector& affector) {
	double x = particle.GetX();
	double y = particle.GetY();
	Vector2 vector = { x, y };
	//Recta p1-p2
	double v1 = affector.region.p2.x - affector.region.p1.x;
	double v2 = affector.region.p2.y - affector.region.p1.y;
	double c1 = v2 * x - v1 * y + v1 * affector.region.p1.y - v2 * affector.region.p1.x;
	//Recta p2-p3
	v1 = affector.region.p3.x - affector.region.p2.x;
	v2 = affector.region.p3.y - affector.region.p2.y;
	double c2 = v2 * x - v1 * y + v1 * affector.region.p2.y - v2 * affector.region.p2.x;
	//Recta p4-p3
	v1 = affector.region.p3.x - affector.region.p4.x;
	v2 = affector.region.p3.y - affector.region.p4.y;
	double c3 = v2 * x - v1 * y + v1 * affector.region.p4.y - v2 * affector.region.p4.x;
	//Recta p1-p4
	v1 = affector.region.p4.x - affector.region.p1.x;
	v2 = affector.region.p4.y - affector.region.p1.y;
	double c4 = v2 * x - v1 * y + v1 * affector.region.p1.y - v2 * affector.region.p1.x;
	if (c1 < 0 && c2 < 0 && c3 > 0 && c4 > 0){
		particle.SetAffector(&affector);
		return true;
		
	}
	else{
		return false;
	}


}