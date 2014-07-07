/*
 * Element.h
 *
 *  Created on: 04/11/2011
 *      Author: ruben
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include "Box.h"
#include "Point.h"
#include "ResourceManager.h"
#include "CoreNamespace.h"
#include "Color.h"
#include "Body.h"
#include "BodyData.h"
#include "World.h"

/**\brief Class Entity
 * Clase Entity, es una clase abstracta que se encargara de actuar de interfaz de todos los elementos que existan en el mapa
 */
class Entity {
public:
	/**\brief Constructor por defecto
	 * Vacio, es una clase abstracta.
	 */
	Entity(){
		angle = 0.0;
		resource = NULL;
		body = NULL;
	};

	/**\brief Destructor por defecto
	 * Declarado inline, tan solo pondra la propiedad visible a true.
	 */
	virtual ~Entity() {
		visible = false;
		if (body!= NULL){
			delete body;
			body = NULL;
		}

		//body = NULL;
		resource = NULL;
	}





	Point getCenter() const{
		return center;
	}

	float getAngle() const {
		return angle;
	}

	unsigned int getId() const{
		return id;
	}
	bool getMovable() const{
		return movable;
	}
	bool getSmall() const{
			return small;
	}
	bool getVisible() const{
			return visible;
		}
	Core::Entities::Type getType() const{
		return type;
	}
	ResourceManager *getResource() const {
		return resource;
	}
	Color<float> getColor() const {
		return color;
	}

	Force getForce() const {
		return force;
	}
	void setCenter(Point cen){
		center = cen;
	}

	void setAngle(float angle_){
		angle = angle_;
	}
	void setId(unsigned int ide){
		id = ide;
	}
	void setMovable(bool m){
		movable = m;
	}
	void setSmall(bool s){
		small = s;
	}
	void setVisible(bool v){
	    visible = v;
	}
	void setType(Core::Entities::Type type_){
		type = type_;
	}
	void setResource(ResourceManager *resource) {
		this->resource = resource;
	}
	void setColor(Color<float> color) {
		this->color = color;
	}
	void setForce(Force f) {
		force = f;
	}

	void applyForce() {
		body->setLinearVelocity(force);
	}

	void applyForce(Force f) {
		force = f;
		body->setLinearVelocity(force);
	}
	Body *body;

private:
	Core::Entities::Type type;
    unsigned int id;
    Point center;
    float angle;
    ResourceManager *resource;
    Color<float> color;
    Force force;
    bool visible;
    bool movable;
    bool small;
    bool dirtyBit;
    virtual void generateColision() = 0;
};





#endif /* ENTITY_H_ */
