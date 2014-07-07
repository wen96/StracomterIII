/*
 * StaticEntity.h
 *
 *  Created on: 12/11/2011
 *      Author: Chutaos Team
 */

#ifndef STATICENTITY_H_
#define STATICENTITY_H_

#include "Entity.h"

/**
 * Clase para definir una entidad estatica y contiene la funcion para generar forma fisica como tal
 */
class StaticEntity: public Entity {
public:
	StaticEntity();
	virtual ~StaticEntity();
	void generateCollision();
};
/*Atributos que Hereda en la parte privada:
 * 	Type type;
 *	int id;
 *	Box colision;
 *	Point center;
 *	bool visible;
 *	bool muvible = false;
 *	bool small;
 */

#endif /* STATICENTITY_H_ */
