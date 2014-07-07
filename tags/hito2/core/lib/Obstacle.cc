/*
 * Obstacle.cc
 *
 *  Created on: 12/11/2011
 *      Author: Chutaos Team
 */

#include "Obstacle.h"

Obstacle::Obstacle(){

}

Obstacle::Obstacle(Core::Entities::Type _type,ResourceManager *r) {
	setId(0);
	setType(_type);
	setVisible(true);
	setSmall(false);
	setResource(r);
	generateCollision();
	idDisplay = _type;
}

Obstacle::Obstacle(Core::Entities::Type _type, const unsigned int idG, const Point pos, float angle, ResourceManager *r, Color<float> color_, vector<Point> vP) {
	setId(idG);
	setType(_type);
	setAngle(angle);
	setCenter(pos);
	setVisible(true);
	setSmall(false);
	setResource(r);
	setColor(color_);
	puntos = vP;
	idDisplay = _type;
	generateCollision();
}

Obstacle::Obstacle(const Obstacle &pare) {
	setId(pare.getId());
	setType(pare.getType());
	setVisible(pare.getVisible());
	setSmall(pare.getSmall());
	setResource(pare.getResource());
	setColor(pare.getColor());
	generateCollision();
}

Obstacle::~Obstacle() {
}

Obstacle&
Obstacle::operator=(const Obstacle &pare) {
	if(this != &pare)
	{
		/*this->~Obstacle();
		id=pare.id;
		type=e_Obstacle;
		visible=pare.visible;
		small=pare.small;
		center=pare.center;
		colision=pare.colision;*/
	}
	return *this;
}

ostream& operator<<(ostream &os, const Obstacle& obj)
{
	os<<"Entity";
	switch(obj.type)
	{
	case 11:
		os<< "(e_columne)";
		break;
	case 12:
		os<< "(e_table)";
		break;
	default:
		os<< "(e_none)";
		break;
	}

	return os;
}
