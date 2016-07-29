#include "math.h"
#include <math.h>

#define DEG2RAD 0.0174532925
#define RAD2DEG 57.2957795

double Log2(double x) {
	return log(x) / log(2.0);
}

double DegSin(double degrees) {
	return sin(DEG2RAD * degrees);
}

double DegCos(double degrees) {
	return cos(DEG2RAD * degrees);
}

double DegTan(double degrees) {
	return tan(DEG2RAD * degrees);
}

double DegASin(double sin) {
	return asin(sin) * RAD2DEG;
}

double DegACos(double cos) {
	return acos(cos) * RAD2DEG;
}

double DegATan(double tan) {
	return atan(tan) * RAD2DEG;
}

double DegATan2(double y, double x) {
	return atan2(y, x) * RAD2DEG;
}

double WrapValue(double val, double mod) {
    if (mod == 0) return val;
    return val - mod*floor(val/mod);
}

double Angle(double x1, double y1, double x2, double y2) {
	if (x1 != x2){
		return WrapValue(DegATan2(y2 - y1, x1 - x2), 360);
	}
	else{
		return 180;
	}
}

double Distance(double x1, double y1, double x2, double y2) {
	return sqrt((x1 - x2)*(x1-x2)+ (y1-y2)*(y1-y2));
}

bool ValueInRange(double value, double min, double max) {
	return (value >= min) && (value <= max);
}

bool PointInRect(double x, double y, double rectx, double recty, double width, double height) {
	if (x >= rectx && x <= rectx + width && y >= recty && y <= recty + height) {
		return true;
	}

	return false;
}

void ClosestPointToRect(double x, double y, double rectx, double recty, double width, double height, double* outx, double* outy) {
	*outx = (x < rectx) ? rectx : (x > rectx+width) ? rectx+width : x;
	*outy = (y < recty) ? recty : (y > recty+height) ? recty+height : y;
}

bool RectsOverlap(double x1, double y1, double width1, double height1, double x2, double y2, double width2, double height2) {
	//If points R1 over R2
	if (PointInRect(x1, y1, x2, y2, width2, height2) || PointInRect(x1 + width1, y1, x2, y2, width2, height2) 
		|| PointInRect(x1, y1 + height1, x2, y2, width2, height2) || PointInRect(x1 + width1, y1 + height1, x2, y2, width2, height2)) {
		return true;
	}
	//If points R2 over R1
	if (PointInRect(x2, y2, x1, y1, width1, height1) || PointInRect(x2 + width2, y2, x1, y1, width1, height1)
		|| PointInRect(x2, y2 + height2, x1, y1, width1, height1) || PointInRect(x2 + width2, y2 + height2, x1, y1, width1, height1)) {
		return true;
	}

	return false;
}

void OverlappingRect(double x1, double y1, double width1, double height1, double x2, double y2, double width2, double height2, double* outx, double* outy, double* outwidth, double* outheight) {
	*outx = ValueInRange(x1, x2, x2 + width2) ? x1 : x2;
	*outy = ValueInRange(y1, y2, y2 + height2) ? y1 : y2;
	*outwidth = ValueInRange(x1 + width1, x2, x2 + width2) ? x1 + width1 - *outx : x2 + width2 - *outx;
	*outheight = ValueInRange(y1 + height1, y2, y2 + height2) ? y1 + height1 - *outy : y2 + height2 - *outy;
}

void TransformIsoCoords(double isoX, double isoY, double isoZ, double* screenX, double* screenY) {
	// TAREA: Implementar funcion
}
