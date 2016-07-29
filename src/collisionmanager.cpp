#include "../include/collisionmanager.h"
#include "../include/math.h"
#include "../include/collisionpixeldata.h"

CollisionManager* CollisionManager::manager= nullptr;

const CollisionManager& CollisionManager::Instance() {
	if (!manager){
		manager = new CollisionManager();
	}
		return *manager;
}

bool CollisionManager::CircleToCircle(double x1, double y1, double r1,
	double x2, double y2, double r2) const{

	if (Distance(x1 + r1, y1 + r1, x2 + r2, y2 + r2) < r1 + r2){
		return true;
	}

	return false;
}

bool CollisionManager::CircleToPixels(double cx, double cy, double cr,
	const CollisionPixelData* pixels, double px, double py) const{

	//Si chocan sus rectangulos
	if (RectsOverlap(px, py, pixels->GetWidth(), pixels->GetHeight(), cx, cy, 2 * cr, 2 * cr)){
		//Calculamos el rectangulo de colision
		double outx, outy, outwidth, outheight;
		OverlappingRect(px, py, pixels->GetWidth(), pixels->GetHeight(), cx, cy, 2*cr, 2*cr, &outx, &outy, &outwidth, &outheight);

		uint32 px1 = outx - px;
		uint32 py1 = outy - py; //1º pixel relativo a p1
		for (int32 pyy = 0; pyy < outheight; pyy++){
			for (int32 pxx = 0; pxx < outwidth; pxx++){
				//if one pixel is visible and inside the circle
				if (pixels->GetData(px1 + pxx, py1 + pyy) == true && Distance(cx + cr, cy + cr, outx + pxx, outy + pyy) < cr) return true;
			}
		}

	}
	return false;
}

bool CollisionManager::CircleToRect(double cx, double cy, double cr,
	double rx, double ry, double rw, double rh) const{
	double outx, outy;
	ClosestPointToRect(cx + cr, cy + cr, rx, ry, rw, rh, &outx, &outy);
	return Distance(cx + cr, cy + cr, outx, outy) < cr;
}

bool CollisionManager::PixelsToPixels(const CollisionPixelData* p1,
	double x1, double y1, const CollisionPixelData* p2, double x2, double y2) const{

	if (RectsOverlap(x1, y1, p1->GetWidth(), p1->GetHeight(), x2, y2, p2->GetWidth(), p2->GetHeight())){
		double outx, outy, outwidth, outheight;
		OverlappingRect(x1, y1, p1->GetWidth(), p1->GetHeight(), x2, y2, p2->GetWidth(), p2->GetHeight(), &outx, &outy, &outwidth, &outheight);
		uint32 px1 = outx - x1;
		uint32 py1 = outy - y1; //1º pixel relativo a p1
		uint32 px2 = outx - x2;
		uint32 py2 = outy - y2; //1º pixel relativo a p2
		for (int32 py = 0; py < outheight; py++){
			for (int32 px = 0; px < outwidth; px++){
				if (p1->GetData(px1 + px, py1 + py) == true && p2->GetData(px2 + px, py2 + py) == true) return true;
			}
		}
	}

	return false;
}

bool CollisionManager::PixelsToRect(const CollisionPixelData* pixels,
	double px, double py, double rx, double ry, double rw, double rh) const{

	if (RectsOverlap(px, py, pixels->GetWidth(), pixels->GetHeight(), rx, ry, rw, rh)){
		double outx, outy, outwidth, outheight;
		OverlappingRect(px, py, pixels->GetWidth(), pixels->GetHeight(), rx, ry, rw, rh, &outx, &outy, &outwidth, &outheight);
		uint32 px1 = outx - px;
		uint32 py1 = outy - py; //1º pixel relativo a p1
		for (int32 pyy = 0; pyy < outheight; pyy++){
			for (int32 pxx = 0; pxx < outwidth; pxx++){
				if (pixels->GetData(px1 + pxx, py1 + pyy) == true) return true;
			}
		}
	}


	return false;
}

bool CollisionManager::RectToRect(double x1, double y1, double w1, double h1,
	double x2, double y2, double w2, double h2) const{
	return PointInRect(x1, y1, x2, y2, w2, h2) || PointInRect(x1 + w1, y1, x2, y2, w2, h2) || PointInRect(x1, y1 + h1, x2, y2, w2, h2) ||
		   PointInRect(x1 + w1, y1 + h1, x2, y2, w2, h2);

}