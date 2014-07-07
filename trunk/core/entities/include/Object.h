/*
 * Object.h
 *
 *  Created on: 03/04/2012
 *      Author: gallardo
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include <iostream>
using namespace std;

#include "CoreNamespace.h"
#include "Point.h"
#include "Entity.h"
#include "Character.h"
#include "Animation.h"

class Object : public Entity {
public:
	Object();
	Object(Core::Objects::Type, Core::Objects::Class, ResourceManager*, Point, float);
	Object(Core::Objects::Class);
	Object(const Object &);
	Object& operator=(const Object &);
	virtual ~Object();
	void Apply(Character* ent);
	void Apply();

	Core::Objects::Class getObjectClass() const {
		return objectClass;
	}

	void setObjectClass(Core::Objects::Class objectClass) {
		this->objectClass = objectClass;
	}

	Core::Objects::Type getObjectType() const {
		return objectType;
	}

	void setObjectType(Core::Objects::Type objectType) {
		this->objectType = objectType;
	}

	void generateObjectsCollision(Core::Objects::Class type, Point p);
	bool isInside(Point p)
	{
		return body->TestPoint(p);
	}

	/**
	 * Puntero para borrar el vector de animaciones
	 */
	Animation *myAnimation;

private:
	void Copiar(const Object &);
	void Destructor();

	vector<Point> puntos;
	Core::Objects::Type objectType;
	Core::Objects::Class objectClass;
};

#endif /* OBJECT_H_ */
