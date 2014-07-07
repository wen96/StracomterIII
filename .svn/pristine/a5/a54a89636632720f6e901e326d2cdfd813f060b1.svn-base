/*
 * BodyData.cpp
 *
 *  Created on: 18/11/2011
 *      Author: Chutaos Team
 */

#include "BodyData.h"

BodyData::BodyData() {

	box = NULL;
	bodyDef = new b2BodyDef();
	masa = new b2MassData();
	masa->mass = 1.0;
}
BodyData::BodyData(Polygon pol, b2BodyType type, float masa_) {

	box = new Box(pol);
	poligon = pol;

	bodyDef = new b2BodyDef();
	masa = new b2MassData();
	masa->mass = masa_;

	Point p_centro;
	p_centro = pol.getCentro();
	b2Vec2 centro;
	centro.x = p_centro.getX();
	centro.y = p_centro.getY();

	bodyDef->position = centro;
	bodyDef->type = type;
	bodyDef->fixedRotation = false;

	fixtureDef.shape = box->getShape();
	fixtureDef.density = 1.0f;

}

BodyData::BodyData(const BodyData &bd) {

	if(bd.bodyDef != NULL)
		bodyDef = new b2BodyDef(*bd.bodyDef);
	else
		bodyDef = NULL;

	fixtureDef = bd.fixtureDef;

	if(bd.masa != NULL)
		masa = new b2MassData(*bd.masa);
	else
		masa = NULL;
	if(bd.box != NULL)
		box = new Box(*bd.box);
	else
		box = NULL;
}

BodyData::~BodyData() {

	if(masa != NULL)
	{
		delete masa;
		masa = NULL;
	}

	if(bodyDef != NULL)
	{
		delete bodyDef;
		bodyDef = NULL;
	}

	if(box != NULL)
	{
		delete box;
		box = NULL;
	}

}

BodyData&
BodyData::operator=(const BodyData &bd){

	if(this != &bd)
	{
		this->~BodyData();

		if(bd.bodyDef != NULL)
			bodyDef = new b2BodyDef(*bd.bodyDef);
		else
			bodyDef = NULL;

		fixtureDef = bd.fixtureDef;

		if(bd.masa != NULL)
			masa = new b2MassData(*bd.masa);
		else
			masa = NULL;
		if(bd.box != NULL)
			box = new Box(*bd.box);
		else
			box = NULL;

	}
	return *this;
}

void
BodyData::setAngularVelocity(float vel) {
	bodyDef->angularVelocity = vel;
}

void
BodyData::setLinearVelocity(Force force) {
	bodyDef->linearVelocity = force.getForce();
}

void
BodyData::setPosition(Point p_centro) {

	b2Vec2 centro;
	centro.x = p_centro.getX();
	centro.y = p_centro.getY();
	bodyDef->position = centro;
}

void
BodyData::setAwake(bool awake_) {
	bodyDef->awake = awake_;
}

void
BodyData::setAngle(float angle_) {
	bodyDef->angle = angle_;
}

void
BodyData::fixedRotation(bool fix) {
	bodyDef->fixedRotation = fix;
}


void
BodyData::setDensity(float density_) {
	fixtureDef.density = density_;
}

void
BodyData::setFriction(float friction_) {
	if(friction_ >= 0.0 && friction_ <= 1.0)
		fixtureDef.friction = friction_;
	else
		fixtureDef.friction = 0.0;
}

void
BodyData::setRestitution(float restitution_) {
	if(restitution_ >= 0 && restitution_ <= 1)
		fixtureDef.restitution = restitution_;
	else
		fixtureDef.restitution = 1.0;
}

void
BodyData::setMasa(float masa_) {
	masa->mass = masa_;

}

void
BodyData::setLinearDamping(float damping) {
	if(damping >= 0)
		bodyDef->linearDamping = damping;
	else
		bodyDef->linearDamping = 0;
}

void
BodyData::setAngularDamping(float damping) {
	if(damping >= 0)
		bodyDef->angularDamping = damping;
	else
		bodyDef->angularDamping = damping;
}

void
BodyData::setSensor(bool sensor) {
	fixtureDef.isSensor = sensor;
}

void
BodyData::setBox(const Box &b) {

	*box = b;
}

void
BodyData::setGoodPerson() {

	fixtureDef.filter.categoryBits = 0x0002;
	fixtureDef.filter.maskBits = 0x000D;

}
void
BodyData::setBadPerson() {

	fixtureDef.filter.categoryBits = 0x0004;
	fixtureDef.filter.maskBits = 0x000B;
}

void
BodyData::setNeutral() {

	fixtureDef.filter.categoryBits = 0x0001;
	fixtureDef.filter.maskBits = 0x000E;
	//fixtureDef.friction = -1.0f;
}

void
BodyData::setObstacle() {

	fixtureDef.filter.categoryBits = 0x0008;
	fixtureDef.filter.maskBits = 0x0007;
}

Polygon BodyData::getPoligon() const
{
    return poligon;
}

void BodyData::setPoligon(Polygon poligon)
{
    this->poligon = poligon;
}


