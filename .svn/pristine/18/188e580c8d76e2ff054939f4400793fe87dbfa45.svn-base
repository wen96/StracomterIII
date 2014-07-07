/*
 * Object.cpp
 *
 *  Created on: 03/04/2012
 *      Author: gallardo
 */

#include "Object.h"

Object::Object() {
	Destructor();
	type = Core::Entities::e_objects;
	objectClass = Core::Objects::none_class;
	myAnimation = NULL;
}

Object::Object(const Object& o) {

	Copiar(o);
}

Object& Object::operator =(const Object& o) {

	if(this != &o)
	{
		Destructor();
		Copiar(o);
	}

	return *this;
}

Object::~Object() {
	Destructor();
}

void Object::Copiar(const Object& o) {

	objectClass = o.objectClass;
	objectType = o.objectType;
}

void Object::Apply(Character* ent) {

	if(ent != NULL)
	{
		switch(objectClass)
		{
		case Core::Objects::health_pack_1:
			ent->setHp(ent->getHp()+ 20);
			break;
		case Core::Objects::health_pack_2:
			ent->setHp(ent->getHp()+ 50);
			break;
		case Core::Objects::health_pack_3:
			ent->setHp(ent->getHp()+ 100);
			break;
		case Core::Objects::ammo_pack_1:
			ent->setAmmunition(ent->getAmmunition() + 20);
			break;
		case Core::Objects::ammo_pack_2:
			ent->setAmmunition(ent->getAmmunition() + 50);
			break;
		case Core::Objects::ammo_pack_3:
			ent->setAmmunition(ent->getAmmunition() + 100);
			break;
		case Core::Objects::sniper:
			cout << "Próximamente" << endl;
			break;
		default:
			break;
		}
	}
}

void Object::Apply() {
}

Object::Object(Core::Objects::Type type_, Core::Objects::Class classO, ResourceManager *r, Point pos, float angle_) {

	objectClass = classO;
	objectType = type_;
	setResource(r);
	setCenter(pos);
	setAngle(angle_);
	idDisplay = classO + 500;
	type = Core::Entities::e_objects;
	color = Color<float>(0,1,0);

	generateObjectsCollision(classO, pos);

	setAngle(angle_);
	setCenter(pos);
}



Object::Object(Core::Objects::Class _class)
{
	objectClass = _class;
	objectType = Core::Objects::obj_dynamics;
	type = Core::Entities::e_objects;
}

void Object::Destructor() {

	objectClass = Core::Objects::none_class;
	objectType = Core::Objects::obj_none;
}

void Object::generateObjectsCollision(Core::Objects::Class type_, Point p) {

		Model2D model = Model2D(type_);

		BodyData *bodyData;

		//switch(type){
			//case Core::Obstacles::obs_table:
			bodyData = new BodyData((*model.getShape()), b2_staticBody);
			bodyData->setDensity(1.0);
			bodyData->setMasa(50);
			bodyData->setFriction(0.0);
			bodyData->setLinearDamping(5);
			bodyData->setAngularDamping(5);
			bodyData->setSensor(true);
			bodyData->setObstacle();


			setColor(Color<float>(0,1,0));
				/*break;
			default:
				break;
		}*/


		World *auxWorld = getResource()->getWorld();
		body = new Body(*auxWorld,*bodyData);

		//body->setPosition(p);

		puntos = model.getShape()->getPuntos();
		if(bodyData != NULL)
		{
			delete bodyData;
			bodyData = NULL;
		}

}
