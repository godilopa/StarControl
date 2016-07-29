#ifndef UGINE_PIXELCOLLISION_H
#define UGINE_PIXELCOLLISION_H

#include "collision.h"
#include "../include/collisionmanager.h"

class PixelCollision : public Collision {
public:
	PixelCollision(const CollisionPixelData* pixels, double* px, double* py) : px(px), py(py), pixels(pixels) {}

	virtual bool DoesCollide(const Collision* other) const { return other->DoesCollide(pixels, *px, *py); }
	virtual bool DoesCollide(double cx, double cy, double cradius) const { return CollisionManager::Instance().CircleToPixels(cx, cy, cradius, pixels, *px, *py); }
	virtual bool DoesCollide(double rx, double ry, double rwidth, double rheight) const { return CollisionManager::Instance().PixelsToRect(pixels, *px, *py, rx, ry, rwidth, rheight); }
	virtual bool DoesCollide(const CollisionPixelData* pixels, double px, double py) const { return CollisionManager::Instance().PixelsToPixels(pixels, px, py, this->pixels, *this->px, *this->py); }
private:
	double* px;
	double* py;
	const CollisionPixelData* pixels;
};

#endif
