/*
 * Captain.cc
 *
 *  Created on: 12/11/2011
 *      Author: Chutaos Team
 */

#include "Entity.h"

Entity::Entity() {
	angle = 0.0;
	resource = NULL;
	body = NULL;
	idDisplay = 0;
	element = Core::Element::e_entity;
	clock = new Clock();
	clock->Start();
}

Entity::Entity(const Entity &ent) {

	body = new Body(*ent.body);
	type = ent.type;
	id = ent.id;
	center = ent.center;
	angle = ent.angle;
	resource = ent.resource;
	color = ent.color;
	force = ent.force;
	visible = ent.visible;
	movable = ent.movable;
	small = ent.small;
	dirtyBit = ent.dirtyBit;
	element = ent.element;
	idDisplay = ent.idDisplay;
}
Entity& Entity::operator=(const Entity &ent) {

	if (this != &ent) {
		this->~Entity();
		body = new Body(*ent.body);
		type = ent.type;
		id = ent.id;
		center = ent.center;
		angle = ent.angle;
		resource = ent.resource;
		color = ent.color;
		force = ent.force;
		visible = ent.visible;
		movable = ent.movable;
		small = ent.small;
		dirtyBit = ent.dirtyBit;
		element = ent.element;
		idDisplay = ent.idDisplay;
	}
	return *this;
}

Entity::~Entity() {
	visible = false;
	if (body != NULL) {
		delete body;
		body = NULL;
	}

	if(clock != NULL)
	{
		delete clock;
		clock = NULL;
	}
	dirtyBit = false;
	id = 0;
	idDisplay = 0;
	movable = true;
	visible = true;
	angle = 0;
	resource = NULL;
	element = Core::Element::e_none;
}

void Entity::generateCollision() {

	BodyData *aux = getResource()->getModelPhisics(getType())->getBodyData();
	World *auxWorld = getResource()->getWorld();

	if (aux != NULL && auxWorld != NULL) {

		body = new Body(*auxWorld, *aux);
		body->setPosition(center);
		body->setAngle(angle);

	}

}

Point Entity::getCenter() const {

	double auxZ = center.getZ();
	Point aux = center;
	if (body != NULL) {
		aux = body->getPosition();
	}

	aux.setZ(auxZ);
	return aux;
}
float Entity::getAngle() const {
	if (body != NULL) {
		return body->getAngle();
	}
	return angle;
}

int Entity::getId() const {
	return id;
}
bool Entity::getMovable() const {
	return movable;
}
bool Entity::getSmall() const {
	return small;
}
bool Entity::getVisible() const {
	return visible;
}
Core::Entities::Type Entity::getType() const {
	return type;
}
ResourceManager *Entity::getResource() const {
	return resource;
}
Color<float> Entity::getColor() const {
	return color;
}

Force Entity::getForce() const {
	return force;
}
void Entity::setCenter(Point cen) {
	if (body != NULL) {
		body->setPosition(cen);
	}
	center = cen;
}

void Entity::setAngle(float angle_) {
	if (body != NULL) {
		body->setAngle(angle_);
	}
	angle = angle_;
}
void Entity::setId(unsigned int ide) {
	id = ide;
}
void Entity::setMovable(bool m) {
	movable = m;
}
void Entity::setSmall(bool s) {
	small = s;
}
void Entity::setVisible(bool v) {
	visible = v;
}
void Entity::setType(Core::Entities::Type type_) {
	type = type_;
}
void Entity::setResource(ResourceManager *resource) {
	this->resource = resource;
}
void Entity::setColor(Color<float> color) {
	this->color = color;
}
void Entity::setForce(Force f) {
	force = f;
}

void Entity::applyForce() {
	body->addLinearVelocity(force);
}

void Entity::applyForce(Force f) {
	force = f;
	body->addLinearVelocity(force);
}

void Entity::addLinearVelocity(Force f) {
	body->addLinearVelocity(f);
}

void Entity::setLinearVelocity(Force f) {
	body->setLinearVelocity(f);
}

void Entity::applyImpulse(Vector2D f, Point p) {
	body->applyImpulse(f, p);
}

void Entity::addAngle(float a) {
	body->addAngle(a);
}

Body* Entity::getBody() {
	return body;
}

int Entity::getIdDisplay() {
	return idDisplay;
}

bool Entity::isDirtyBit() const {
	return dirtyBit;
}

bool Entity::isMovable() const {
	return movable;
}

bool Entity::isSmall() const {
	return small;
}

bool Entity::isVisible() const {
	return visible;
}

void Entity::setBody(Body *body) {
	this->body = body;
}

void Entity::setDirtyBit(bool dirtyBit) {
	this->dirtyBit = dirtyBit;
}

