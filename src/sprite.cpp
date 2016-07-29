#include "../include/sprite.h"
#include "../include/rectcollision.h"
#include "../include/image.h"
#include "../include/map.h"
#include "../include/math.h"
#include "../include/pixelcollision.h"
#include "../include/renderer.h"
#include "../include/circlecollision.h"
#include <math.h>

Sprite::Sprite(){}

Sprite::Sprite(Image* image) : image(image) {
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->colx = 0;
	this->coly = 0;
	this->colwidth = 0;
	this->colheight = 0;
	this->angle = 0;
	this->scalex = 1;
	this->scaley = 1;
	this->radius = 0;
	this->animFPS = 0;
	this->firstFrame = 0;
	this->lastFrame = image->GetNumFrames() - 1;
	this->currentFrame = 0;
	this->blendMode = Renderer::ALPHA;
	this->r = 255;
	this->g = 255;
	this->b = 255;
	this->a = 255;
	this->collision = nullptr;
	this->colPixelData = nullptr;
	this->colSprite = nullptr;
	this->collided = false;
	rotating = false;
	moving = false;

	this->userData = nullptr;
}


Sprite::~Sprite() {
    // TAREA: Implementar
	if (collision) delete collision;

}

void Sprite::SetCollision(CollisionMode mode) {
	if (mode == COLLISION_NONE){
		delete collision;
		collision = nullptr;
	}

	if (mode == COLLISION_CIRCLE){
		delete collision;
		collision = new CircleCollision(&colx, &coly, &radius);
	}
	
	if (mode == COLLISION_PIXEL){
		delete collision;
		collision = new PixelCollision(colPixelData, &colx, &coly);
	}

	if (mode == COLLISION_RECT){
		delete collision;
		collision = new RectCollision(&colx, &coly, &colwidth, &colheight);
	}
}

bool Sprite::CheckCollision(Sprite* sprite) {
	// TAREA: Implementar
	if (this->collision != nullptr && sprite->collision != nullptr) {
		bool col = collision->DoesCollide(sprite->collision);
		if (col){
			this->colSprite = sprite;
			this->collided = true;
			sprite->colSprite = this;
			sprite->collided = true;
			return true;
		}
		else{
			return col;
		}
	}
	else{
		return false;
	}
}

bool Sprite::CheckCollision(const Map* map) {
	// TAREA: Implementar
	if (map){
		return map->CheckCollision(GetCollision());
	}
	else{
		return false;
	}
}


void Sprite::RotateTo(int32 angle, double speed) {
	if (WrapValue(angle, 360) == WrapValue(this->angle, 360) || speed == 0) {
		rotating = false;
	}
	else {
		rotating = true;
		toAngle = (uint16)WrapValue(angle, 360);

		uint16 wrapAngle = (uint16)WrapValue(this->angle, 360);
		if (min(WrapValue(toAngle - wrapAngle, 360), WrapValue(wrapAngle - toAngle, 360)) == WrapValue(toAngle - wrapAngle, 360)) {
			rotatingSpeed = fabs(speed);
			degreesToRotate = WrapValue(toAngle - wrapAngle, 360);
		}
		else {
			rotatingSpeed = -fabs(speed);
			degreesToRotate = WrapValue(wrapAngle - toAngle, 360);
		}
	}
}

void Sprite::MoveTo(double x, double y, double speed) {
	if (x == GetX() && y == GetY() || speed == 0){
		moving = false;
	}
	else{
		moving = true;
		endX = x;
		endY = y;
		vector.x = x - GetX();
		vector.y = y - GetY();
		distancia = sqrt((vector.x * vector.x) + (vector.y * vector.y));
		vectorNormalizado.x = vector.x / distancia;
		vectorNormalizado.y = vector.y / distancia;
		movingSpeedX = vectorNormalizado.x * speed;
		movingSpeedY = vectorNormalizado.y * speed;
	}
}

void Sprite::Update(double elapsed, const Map* map) {
	// Informacion inicial de colision
	colSprite = NULL;
	collided = false;

	// TAREA: Actualizar animacion
	currentFrame += animFPS * elapsed;
	if (currentFrame > lastFrame) {
		currentFrame -= (lastFrame - firstFrame); //o = firstFrame (pero velocidad no lineal);
	}
	if (currentFrame < firstFrame){
		currentFrame += (firstFrame - lastFrame); // o = lastFrame(pero velocidad no lineal);
	}

	// TAREA: Actualizar rotacion animada
	if (rotating) {
		angle += rotatingSpeed * elapsed;
		degreesToRotate -= fabs(rotatingSpeed * elapsed);

		if (degreesToRotate <= 0) {
			angle = toAngle;
			rotating = false;
		}
	}

	if (moving){
		double eX = movingSpeedX * elapsed;
		double eY = movingSpeedY * elapsed;
		prevx = GetX();
		prevy = GetY();
		if (eX > 0){
			if (GetX() + eX > endX){
				moving = false;
				SetX(endX);
				SetY(endY);
			}
			else{
				SetPosition(GetX() + eX, GetY() + eY);
			}
			UpdateCollisionBox();
			if (CheckCollision(map)){
				SetX(prevx);
				//Si choca por arriba o por la derecha poner eX = 0 o eY = 0
				eX = 0;
			}
		}

		if (eX < 0){
			if (GetX() + eX < endX){
				moving = false;
				SetX(endX);
				SetY(endY);
			}
			else{
				SetPosition(GetX() + eX, GetY() + eY);
			}
			UpdateCollisionBox();
			if (CheckCollision(map)){
				SetX(prevx);
				eX = 0;
			}
		}

		if (eX == 0){
			if (eY > 0){
				if (GetY() + eY > endY){
					moving = false;
					SetY(endY);
				}
				else{
					SetPosition(GetX() + eX, GetY() + eY);
				}
				UpdateCollisionBox();
				if (CheckCollision(map)){
					SetY(prevy);
				}
			}

			if (eY < 0){
				if (GetY() + eY < endY){
					moving = false;
					SetY(endY);
				}
				else{
					SetPosition(GetX() + eX, GetY() + eY);
				}
				UpdateCollisionBox();
				if (CheckCollision(map)){
					SetY(prevy);
				}
			}
		}
	}
	//Informacion final de colision
	UpdateCollisionBox();
}

void Sprite::MoveDown(double c, double speed)  {
	double newx =  0* DegCos(- angle + 90) + c * DegSin(- angle + 90);
	double newy = 0 * DegSin(angle - 90) + c * DegCos(- angle + 90);
	MoveTo(x - newx, y + newy, speed);
}

void Sprite::MoveUp(double c, double speed)  {
	double newx = 0 * DegCos(- angle + 90) + c * DegSin(- angle + 90);
	double newy = 0 * DegSin(angle - 90) + c * DegCos(- angle + 90);
	MoveTo(x + newx, y - newy, speed);
}

void Sprite::Render() const {
	Renderer::Instance().SetBlendMode(blendMode);
	Renderer::Instance().SetColor(r, g, b, a);
	Renderer::Instance().DrawImage(image, x, y, currentFrame, image->GetWidth()*scalex, image->GetHeight()*scaley, GetAngle());
}

void Sprite::UpdateCollisionBox() {
	// TAREA: Implementar
	colx = x - image->GetHandleX() * fabs(scalex);
	coly = y - image->GetHandleY() * fabs(scaley);
	colwidth = image->GetWidth() * fabs(scalex);
	colheight = image->GetHeight() * fabs(scaley);
	UpdateCollisionBox(colx, coly, colwidth, colheight);
}

void Sprite::UpdateCollisionBox(double x, double y, double w, double h) { // Este no es necesario
	// TAREA: Implementar
	colx = x;
	coly = y;
	colwidth = w;
	colheight = h;
}
