#ifndef PARALLAX_SCENE_H
#define PARALLAX_SCENE_H

#include "scene.h"

class ParallaxScene : public Scene {
public:
	ParallaxScene(Image* imageBack, Image* imageFront = 0);
	virtual const Image* GetBackLayer() const { return backLayer; }
	virtual const Image* GetFrontLayer() const { return frontLayer; }
	virtual void SetRelativeBackSpeed(double x, double y) { relBackSpeedX = x; relBackSpeedY = y; }
	virtual void SetRelativeFrontSpeed(double x, double y) { relFrontSpeedX = x; relFrontSpeedY = y; }
	virtual void SetAutoBackSpeed(double x, double y) { autoBackSpeedX = x; autoBackSpeedY = y; }
	virtual void SetAutoFrontSpeed(double x, double y) { autoFrontSpeedX = x; autoFrontSpeedY = y; }
	virtual void Update(double elapsed, Map* map = 0);
protected:
	virtual void RenderBackground() const;
private:
	Image* backLayer;
	Image* frontLayer;
	double backX, backY;
	double frontX, frontY;
	double relBackSpeedX, relBackSpeedY;
	double relFrontSpeedX, relFrontSpeedY;
	double autoBackSpeedX, autoBackSpeedY;
	double autoFrontSpeedX, autoFrontSpeedY;
};

#endif
