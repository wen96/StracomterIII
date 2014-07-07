/*
 * DynamicEntity.cpp
 *
 *  Created on: 12/11/2011
 *      Author: Team Chutaos
 */

#include "DynamicEntity.h"

DynamicEntity::DynamicEntity() {
	movable = true;
}


DynamicEntity::~DynamicEntity() {
	movable = true;
}


void DynamicEntity::generateCollision(){
	BodyData *aux = getResource()->getModelPhisics(getType())->getBodyData();
	World *auxWorld = getResource()->getWorld();

	if (aux!= NULL && auxWorld!=NULL){
		body = new Body(*auxWorld,*aux);

		body->setPosition(center);
		body->setAngle(angle);
	}
}

