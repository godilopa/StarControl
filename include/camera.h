#ifndef CAMERA_H
#define CAMERA_H

#include "sprite.h"
#include "screen.h"

class Camera {
public:
	Camera(){};
	virtual void SetPosition(double x, double y);
	virtual void SetX(double x){ this->x = x; }
	virtual void SetY(double y){ this->y = y; }
	virtual double GetX() const{ return x; }
	virtual double GetY() const{ return y; }
	virtual void SetBounds(double bx0, double by0, double bx1, double by1){ boundx0 = bx0; boundy0 = by0; boundx1 = bx1; boundy1 = by1; }
	virtual bool HasBounds() const { return !(boundx0 == boundx1); }
	virtual double GetMinX() const { return HasBounds() ? boundx0 : x; }
	virtual double GetMinY() const { return HasBounds() ? boundy0 : y; }
	virtual double GetMaxX() const { return HasBounds() ? boundx1 - Screen::Instance().GetWidth() : x; }
	virtual double GetMaxY() const { return HasBounds() ? boundy1 - Screen::Instance().GetHeight() : y; }

	virtual void FollowSprite(Sprite* sprite){ followingSprite = sprite; }
	virtual void Update();
private:
	double x, y;
	double boundx0, boundy0, boundx1, boundy1;
	Sprite* followingSprite = nullptr;
};

#endif







