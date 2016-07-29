#ifndef AFFECTOR_H
#define AFFECTOR_H

#include "types.h"

class Affector {

public:
	friend class Emitter;
	Affector(){};
	Affector(Region region):region(region){}
	virtual void SetVelocityX(double minvelx, double maxvelx){ newminvelx = minvelx; newmaxvelx = maxvelx; }
	virtual void SetVelocityY(double minvely, double maxvely){ newminvely = minvely; newmaxvely = maxvely; }
	virtual void SetAngularVelocity(double minangvel, double maxangvel){ newminangvel = minangvel; newmaxangvel = maxangvel; }
	virtual void SetMinColor(uint8 r, uint8 g, uint8 b){ newminr = r; newming = g; newminb = b; }
	virtual void SetMaxColor(uint8 r, uint8 g, uint8 b) { newmaxr = r; newmaxg = g; newmaxb = b; }

private:
	Region region;
	uint8 newminr, newming, newminb;
	uint8 newmaxr, newmaxg, newmaxb;
	double newminvelx, newmaxvelx;
	double newminvely, newmaxvely;
	double newminangvel, newmaxangvel;
};




#endif