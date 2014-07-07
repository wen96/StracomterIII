/*
 * Wall.cc
 *
 *  Created on: 12/11/2011
 *      Author: alex
 */

#include "Wall.h"

Wall::Wall(ResourceManager *r) {
	setId(0);
	setType(Core::Entities::e_wall);
	setVisible(true);
	setSmall(false);
	setResource(r);
}

Wall::Wall(const unsigned int idG, const Point pos, float angle, ResourceManager *r, Color<float> color_) {
	setId(idG);
	setType(Core::Entities::e_wall);
	setVisible(true);
	setSmall(false);
	setResource(r);
	setColor(color_);
	BodyData *aux = getResource()->getModelPhisics(getType())->getBodyData();
	World *auxWorld = getResource()->getWorld();
	body = new Body(*auxWorld,*aux);
	body->setPosition(pos);
	body->setAngle(angle);
}

Wall::Wall(const Wall &pare) {
	setId(pare.getId());
	setType(pare.getType());
	setVisible(pare.getVisible());
	setSmall(pare.getSmall());
	setResource(pare.getResource());
	setColor(pare.getColor());
}

Wall::~Wall() {
	// TODO Auto-generated destructor stub
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
		colision=pare.colision;*/
	}
	return *this;
}
