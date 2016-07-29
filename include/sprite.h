#ifndef UGINE_SPRITE_H
#define UGINE_SPRITE_H

#include "renderer.h"
#include "types.h"

class Collision;
class CollisionPixelData;
class Image;
class Map;

class Sprite {
public:
	enum CollisionMode {
		COLLISION_NONE,
		COLLISION_CIRCLE,
		COLLISION_PIXEL,
		COLLISION_RECT
	};

	Sprite();
	Sprite(Image* image);
	virtual ~Sprite();

	virtual void SetImage(Image* image) { Sprite::image = image; }
	virtual const Image* GetImage() const { return image; }

	virtual void SetPosition(double x, double y, double z = 0) { Sprite::x = x; Sprite::y = y; }
	virtual void SetX(double x) { Sprite::x = x; }
	virtual void SetY(double y) { Sprite::y = y; }
	virtual void SetZ(double z) { Sprite::z = z; }
	virtual double GetX() const { return x; }
	virtual double GetY() const { return y; }
	virtual double GetZ() const { return z; }
	virtual double GetScreenX() const { return x; }
	virtual double GetScreenY() const { return y; }

	virtual void SetAngle(double angle) { Sprite::angle = angle; }
	virtual double GetAngle() const { return angle; }

	virtual void SetScale(double sx, double sy) { Sprite::scalex = sx; Sprite::scaley = sy; }
	virtual void SetScaleX(double sx) { Sprite::scalex = sx; }
	virtual void SetScaleY(double sy) { Sprite::scaley = sy; }
	virtual double GetScaleX() const { return scalex; }
	virtual double GetScaleY() const { return scaley; }

	virtual void SetFPS(int16 fps) { animFPS = fps; }
	virtual int16 GetFPS() const { return animFPS; }
	virtual void SetFrameRange(uint16 firstFrame, uint16 lastFrame) { Sprite::firstFrame = firstFrame;  Sprite::lastFrame = lastFrame; }
	virtual uint16 GetFirstFrame() const { return firstFrame; }
    virtual uint16 GetLastFrame() { return lastFrame; }
	virtual void SetCurrentFrame(uint16 frame) { currentFrame = frame; }
	virtual uint16 GetCurrentFrame() const { return currentFrame; }

	virtual void SetBlendMode(Renderer::BlendMode blend) { Sprite::blendMode = blend; }
	virtual Renderer::BlendMode GetBlendMode() const { return blendMode; }
	virtual void SetColor(uint8 r, uint8 g, uint8 b, uint8 alpha = 255) { Sprite::r = r; Sprite::g = g; Sprite::b = b; Sprite::a = a; }
	virtual uint8 GetRed() const { return r; }
	virtual uint8 GetGreen() const { return g; }
	virtual uint8 GetBlue() const { return b; }
	virtual uint8 GetAlpha() const { return a; }
	virtual void SetAlpha(uint8 a){ Sprite::a = a; }

	virtual void SetRadius(double radius) { Sprite::radius = radius; }
	virtual double GetRadius() const { return radius; }

 	virtual void SetCollision(CollisionMode mode);
	virtual void SetCollisionPixelData(const CollisionPixelData* colPixelData) { Sprite::colPixelData = colPixelData; }
	virtual const Collision* GetCollision() const { return collision; }
    virtual bool CheckCollision(Sprite* sprite);
    virtual bool CheckCollision(const Map* map);
	virtual Sprite* CollisionSprite() const { return colSprite; }
	virtual bool DidCollide() const { return collided; }

    virtual void RotateTo(int32 angle, double speed);
    virtual void MoveTo(double x, double y, double speed);
	virtual void MoveUp(double c, double speed);
	virtual void MoveDown(double c, double speed);
	virtual bool IsRotating() const { return rotating; }
	virtual bool IsMoving() const { return moving; }
	virtual void SetIsMoving(bool moving) { Sprite::moving = moving; }

    virtual void Update(double elapsed, const Map* map = NULL);
    virtual void Render() const;
	
	virtual void SetUserData(void* data) { userData = data; }
	virtual void* GetUserData() { return userData; }
	virtual const void* GetUserData() const { return userData; }
protected:
    virtual void UpdateCollisionBox();
    virtual void UpdateCollisionBox(double x, double y, double w, double h);
private:
    Image* image;
    double x, y, z;
    double colx, coly, colwidth, colheight;
    double angle;
    double scalex, scaley;
    double radius;
    int16 animFPS;
    uint16 firstFrame, lastFrame;
    double currentFrame;
    Renderer::BlendMode blendMode;
    uint8 r, g, b, a;
    Collision* collision;
    const CollisionPixelData* colPixelData;
    Sprite* colSprite;
    bool collided;

    bool rotating = false;
    uint16 toAngle;
    double rotatingSpeed;
	double degreesToRotate;

	Vector2 vector, vectorNormalizado;
    bool moving = false;
	double endX, endY;
	double movingSpeedX, movingSpeedY;
	double distancia;
	double prevx, prevy;
	
	void* userData;
};

#endif
