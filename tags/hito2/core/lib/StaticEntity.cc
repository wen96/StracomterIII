/*
 * StaticEntity.cc
 *
 *  Created on: 12/11/2011
 *      Author: Chutaos Team
 */

#include "StaticEntity.h"

StaticEntity::StaticEntity() {
	setMovable(false);

}

StaticEntity::~StaticEntity() {
	setMovable(false);
}

void StaticEntity::generateCollision(){
	BodyData *aux = getResource()->getModelPhisics(getType())->getBodyData();
	World *auxWorld = getResource()->getWorld();

	body = new Body(*auxWorld,*aux);

	body->setPosition(center);
	body->setAngle(angle);
}
