/*
 * Wall.cc
 *
 *  Created on: 12/11/2011
 *      Author: Chutaos Team
 */

#include "Wall.h"

Wall::Wall(){

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

Wall::Wall(const unsigned int idG, const Point pos, float angle, ResourceManager *r, Color<float> color_, vector<Point> vP) {
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
	calculate8Points();
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
	calculate8Points();
}

Wall::~Wall() {
	// TODO Auto-generated destructor stub
}

void Wall::calculate8Points(){
	if (puntos.size() == 8){


		for (int i = 0; i < 4; i++){
			Point aux = puntos[i];
			//Pongo los 4 con la z mas alta
			aux.setZ(90);
			puntos[i+4]=aux;
		}
	}
}

Wall&
Wall::operator=(const Wall &pare) {
	if(this != &pare)
	{
		/*this->~Wall();
		id=pare.id;
		type=e_wall;
		visible=pare.visible;
		small=pare.small;
		center=pare.center;
		colision=pare.colision;
		idDisplay = pare.idDisplay;*/
	}
	return *this;
}

void Wall::generateCollision(){

	vector<Point> vaux = getPoints();
	for(int i = 0; i < 4; i++) vaux.pop_back();
	Polygon pol(Point(),vaux);
	pol.Reverse();

	BodyData *aux = new BodyData(pol);
	aux->setNeutral();

	World *auxWorld = getResource()->getWorld();
	body = new Body(*auxWorld,*aux);
	body->setPosition(center);
	body->setAngle(angle);
}

void Wall::setPoints(vector<Point> vP){

	if(vP.size() == 8){
		puntos = vP;
	}
}

vector<Point> Wall::getPoints(){
	return puntos;
}

ostream& operator<<(ostream &os, const Wall& obj)
{
	os<<"Entity(e_wall)";
	return os;
}


