/*
 * StaticEntity.h
 *
 *  Created on: 12/11/2011
 *      Author: Chutaos Team
 */

#ifndef STATICENTITY_H_
#define STATICENTITY_H_

#include "Entity.h"

class StaticEntity: public Entity {
public:
	StaticEntity();
	virtual ~StaticEntity();
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
