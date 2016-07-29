#include "../include/camera.h"

void Camera::Update(){

	if (followingSprite){

		SetPosition(followingSprite->GetX() - Screen::Instance().GetWidth() / 2, followingSprite->GetY() - Screen::Instance().GetHeight() / 2);

	}
}

void Camera::SetPosition(double x, double y){

	if (x < boundx0 && HasBounds()){
		Camera::x= GetMinX();
	}
	else if (x > boundx1 - Screen::Instance().GetWidth() && HasBounds()){
		Camera::x = GetMaxX();
	}
	else{
		Camera::x = x;
	}

	if (y < boundy0 && HasBounds()){
		Camera::y = GetMinY();
	}
	else if (y > boundy1 - Screen::Instance().GetHeight() && HasBounds()){
		Camera::y = GetMaxY();
	}
	else{
		Camera::y = y;
	}
}
