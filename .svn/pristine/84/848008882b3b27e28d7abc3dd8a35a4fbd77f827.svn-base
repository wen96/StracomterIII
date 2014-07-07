#include "Point.h"
#include <cmath>

ostream&
operator<<(ostream &os, const Point &p) {

	os << "(" << p.x << "," << p.y << ")";

	return os;
}

double Point::distance(Point p1, Point p2) {

	double ssX = p1.x - p2.x;
	ssX *= ssX;

	double ssY = p1.y - p2.y;
	ssY *= ssY;

	double ssZ = p1.z - p2.z;
	ssZ *= ssZ;

	double distancia = sqrt(ssX + ssY + ssZ);

	return distancia;
}


bool Point::operator==(const Point &p) {
	bool iguales = true;

	if (abs(x - p.x) >= 0.001)
		iguales = false;
	else if (abs(y - p.y) >= 0.001)
		iguales = false;
	else if (abs(z - p.z) >= 0.001)
		iguales = false;

	return iguales;
}
/*
bool Point::operator==(const Point &p) {
	bool iguales = true;

	if (x != p.x)
		iguales = false;
	else if (y != p.y)
		iguales = false;
	else if (z != p.z)
		iguales = false;

	return iguales;
}*/

Point Point::interP(const Point &p1, const Point &p2){
	double x = abs(p1.x -p2.x);
	double y = abs(p1.y -p2.y);
	Point p(x, y);
	return p;
}

bool Point::isInRadius(const Point &p, double radius){
	return (distance(*this, p) <= radius);
}

bool Point::operator!=(const Point &p) {
	bool dif = false;

	if (abs(x - p.x) >= 0.001){
		dif = true;
	}else if (abs(y - p.y) >= 0.001)
		dif = true;
	else if (abs(z - p.z) >= 0.001)
		dif = true;

	return dif;
}
