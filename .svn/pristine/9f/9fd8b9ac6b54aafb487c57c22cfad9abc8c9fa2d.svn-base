/*
 * ModelFisic.cc
 *
 *  Created on: 18/11/2011
 *      Author: Chutaos team
 */

#include "ModelPhisic.h"

ModelPhisic::ModelPhisic(int type, Polygon *p){
	switch(type){
	case Core::Entities::e_captain:
		bodyData = new BodyData(*p, b2_dynamicBody);
		bodyData->setDensity(1.0);
		bodyData->setMasa(50);
		bodyData->setFriction(0.0);
		bodyData->setLinearDamping(5);
		bodyData->setAngularDamping(5);
		bodyData->setGoodPerson();
		break;
	case Core::Entities::e_tecnic:
		bodyData = new BodyData(*p, b2_dynamicBody);
		bodyData->setDensity(1.0);
		bodyData->setMasa(50);
		bodyData->setFriction(0.0);
		bodyData->setLinearDamping(5);
		bodyData->setAngularDamping(5);
		bodyData->setGoodPerson();
		break;
	case Core::Entities::e_explosive:
		bodyData = new BodyData(*p, b2_dynamicBody);
		bodyData->setDensity(1.0);
		bodyData->setMasa(50);
		bodyData->setFriction(0.0);
		bodyData->setLinearDamping(5);
		bodyData->setAngularDamping(5);
		bodyData->setGoodPerson();
		break;
	case Core::Entities::e_especialist:
		bodyData = new BodyData(*p, b2_dynamicBody);
		bodyData->setDensity(1.0);
		bodyData->setMasa(50);
		bodyData->setFriction(0.0);
		bodyData->setLinearDamping(5);
		bodyData->setAngularDamping(5);
		bodyData->setGoodPerson();
		break;
	case Core::Entities::e_enemy1:
		bodyData = new BodyData(*p, b2_dynamicBody);
		bodyData->setDensity(1.0);
		bodyData->setMasa(70);
		bodyData->setFriction(1.0);
		bodyData->setLinearDamping(5);
		bodyData->setAngularDamping(5);
		bodyData->setBadPerson();
		break;
	case Core::Entities::e_enemy2:
		bodyData = new BodyData(*p, b2_dynamicBody);
		bodyData->setDensity(1.0);
		bodyData->setMasa(80);
		bodyData->setFriction(1.0);
		bodyData->setLinearDamping(5);
		bodyData->setAngularDamping(5);
		bodyData->setBadPerson();
		break;
	case Core::Entities::e_enemy3:
		bodyData = new BodyData(*p, b2_dynamicBody);
		bodyData->setDensity(1.0);
		bodyData->setMasa(90);
		bodyData->setFriction(1.0);
		bodyData->setLinearDamping(5);
		bodyData->setAngularDamping(5);
		bodyData->setBadPerson();
		break;
	case Core::Entities::e_miniboss:
		bodyData = new BodyData(*p, b2_dynamicBody);
		bodyData->setDensity(1.0);
		bodyData->setMasa(110);
		bodyData->setFriction(0.0);
		bodyData->setLinearDamping(5);
		bodyData->setAngularDamping(5);
		bodyData->setBadPerson();
		break;
	case Core::Entities::e_megaboss:
		bodyData = new BodyData(*p, b2_dynamicBody);
		bodyData->setDensity(1.0);
		bodyData->setMasa(150);
		bodyData->setFriction(0.0);
		bodyData->setLinearDamping(5);
		bodyData->setAngularDamping(5);
		bodyData->setBadPerson();
		break;
	case Core::Entities::e_wall:
		bodyData = new BodyData(*p, b2_staticBody);
		bodyData->setDensity(1.0);
		bodyData->setMasa(1);
		bodyData->setLinearDamping(5);
		bodyData->setAngularDamping(5);
		bodyData->setNeutral();
		break;
	case Core::Entities::e_pointer:
		bodyData = new BodyData(*p, b2_dynamicBody);
		bodyData->getBodyDef()->active = false;
		break;
	default:
		bodyData = NULL;
		break;
	}

}

ModelPhisic::ModelPhisic(Core::Obstacles::Type type, Polygon p){

	switch(type){
	case Core::Obstacles::obs_table:
		bodyData = new BodyData(p, b2_staticBody);
		bodyData->setDensity(1.0);
		bodyData->setMasa(50);
		bodyData->setFriction(0.0);
		bodyData->setLinearDamping(5);
		bodyData->setAngularDamping(5);
		bodyData->setNeutral();
		break;
	default:
		break;
	}

}
ModelPhisic::~ModelPhisic(){
	if (bodyData != NULL){
		delete bodyData;
		bodyData = NULL;
	}
}
void ModelPhisic::setBodyData(BodyData *b){
	bodyData = b;
}
ModelPhisic::ModelPhisic(const ModelPhisic & m)
{
	Copiar(m);
}

ModelPhisic & ModelPhisic::operator =(const ModelPhisic & m)
{
	if(this != &m)
	{
		Destructor();
		Copiar(m);
	}

	return *this;
}

BodyData* ModelPhisic::getBodyData(){
	return bodyData;
}

void ModelPhisic::Copiar(const ModelPhisic & m)
{
	if(m.bodyData != NULL)
	{
		bodyData = new BodyData(*m.bodyData);
	}
	else
	{
		bodyData = NULL;
	}
}

void ModelPhisic::Destructor() {
	if(bodyData != NULL)
	{
		delete bodyData;
		bodyData = NULL;
	}
}

