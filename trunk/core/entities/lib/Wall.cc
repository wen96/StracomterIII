/*
 * Wall.cc
 *
 *  Created on: 12/11/2011
 *      Author: Chutaos Team
 */

#include "Wall.h"

Wall::Wall() {

}

Wall::Wall(ResourceManager *r) {
	setId(0);
	setType(Core::Entities::e_wall);
	setVisible(true);
	setSmall(false);
	setResource(r);
	generateCollision();
	idDisplay = 0;
}

Wall::Wall(const unsigned int idG, const Point pos, float angle,
		ResourceManager *r, Color<float> color_, vector<Point> vP) {
	setId(idG);
	setType(Core::Entities::e_wall);
	setAngle(angle);
	setCenter(pos);
	setVisible(true);
	setSmall(false);
	setResource(r);
	setColor(color_);
	puntos = vP;
	generateCollision();
	idDisplay = r->generateWall(puntos);

}

Wall::Wall(const Wall &pare) {
	setId(pare.getId());
	setType(pare.getType());
	setVisible(pare.getVisible());
	setSmall(pare.getSmall());
	setResource(pare.getResource());
	setColor(pare.getColor());
	generateCollision();
	idDisplay = pare.idDisplay;
}

Wall::~Wall() {
	// TODO Auto-generated destructor stub
}

Wall&
Wall::operator=(const Wall &pare) {
	if (this != &pare) {

	}
	return *this;
}

void Wall::generateCollision() {

	Polygon pol(Point(), puntos);
	pol.Reverse();

	BodyData *aux = new BodyData(pol);
	aux->setNeutral();

	World *auxWorld = getResource()->getWorld();
	body = new Body(*auxWorld, *aux);
	body->setPosition(center);
	body->setAngle(angle);
}

void Wall::setPoints(vector<Point> vP) {

	if (vP.size() == 4) {
		puntos = vP;
	}
}

vector<Point> Wall::getPoints() {
	return puntos;
}

ostream& operator<<(ostream &os, const Wall& obj) {
	os << "Entity(e_wall)";
	return os;
}

void Wall::Move(Point p) {

	setCenter(p);

	double xDesp = max(abs(puntos[0].getX() - puntos[1].getX()),
					   abs(puntos[0].getX() - puntos[2].getX())) / 2.0;
	double yDesp = max(abs(puntos[0].getY() - puntos[1].getY()),
					   abs(puntos[0].getY() - puntos[2].getY())) / 2.0;

	double x = p.getX();
	double y = p.getY();

	Point a(x - xDesp, y - yDesp);
	Point b(x - xDesp, y + yDesp);
	Point c(x + xDesp, y + yDesp);
	Point d(x + xDesp, y - yDesp);

	puntos.clear();
	puntos.push_back(a);
	puntos.push_back(b);
	puntos.push_back(c);
	puntos.push_back(d);

	if(body != NULL)
		delete body;
	generateCollision();

	idDisplay = ResourceManager::getInstance()->generateWall(puntos, idDisplay);
}

bool Wall::isInside(Point p){
	double x = p.getX(),
		   y = p.getY(),
		   mx = min(puntos[0].getX(), min(puntos[1].getX(), puntos[2].getX())),
		   Mx = max(puntos[0].getX(), max(puntos[1].getX(), puntos[2].getX())),
		   my = min(puntos[0].getY(), min(puntos[1].getY(), puntos[2].getY())),
		   My = max(puntos[0].getY(), max(puntos[1].getY(), puntos[2].getY()));

	return (mx <= x && x <= Mx) && (my <= y && y <= My);
}

void Wall::Expand(double x){

	if((int) angle % 180 == 0){ // Horizontal
		if(abs(puntos[2].getX() - puntos[1].getX()) + x > 0){
			puntos[2].setX(puntos[2].getX() + x);
			puntos[3].setX(puntos[3].getX() + x);
		}
	}else{	// Vertical
		if(abs(puntos[1].getY() - puntos[0].getY()) + x > 0){
			puntos[1].setY(puntos[1].getY() + x);
			puntos[2].setY(puntos[2].getY() + x);
		}
	}

	if(body != NULL)
		delete body;
	generateCollision();

	idDisplay = ResourceManager::getInstance()->generateWall(puntos, idDisplay);
}

void Wall::Rotate(double a){
	setAngle(this->getAngle() + a);

	double despX = abs(puntos[2].getX() - puntos[1].getX()) / 2,
		   despY = abs(puntos[1].getY() - puntos[0].getY()) / 2,
		   x = puntos[0].getX() + despX,
		   y = puntos[0].getY() + despY;

	puntos[0] = Point(x - despY, y - despX);
	puntos[1] = Point(x - despY, y + despX);
	puntos[2] = Point(x + despY, y + despX);
	puntos[3] = Point(x + despY, y - despX);

	if(body != NULL)
		delete body;
	generateCollision();

	idDisplay = ResourceManager::getInstance()->generateWall(puntos, idDisplay);
}

double Wall::Width(){
	return abs(puntos[2].getX() - puntos[1].getX());
}

double Wall::Height(){
	return abs(puntos[1].getY() - puntos[0].getY());
}
