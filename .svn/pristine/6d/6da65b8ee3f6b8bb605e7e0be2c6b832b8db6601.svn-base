/*
 * DynamicEntity.h
 *
 *  Created on: 12/11/2011
 *      Author: Chutaos Team
 */

#ifndef DYNAMICENTITY_H_
#define DYNAMICENTITY_H_

#include "Entity.h"

/**
 * Clase para definir una entidad dinamica y contiene la funcion para generar forma fisica como tal
 */
class DynamicEntity: public Entity {
public:
	DynamicEntity();
	virtual ~DynamicEntity();
    Transform *getTrans() const;
    void setTrans(Transform *trans);
	void generateCollision();

};
/*Atributos que Hereda en la parte privada:
 * 	Type type;
 *	int id;
 *	Box colision;
 *	Point center;
 *	bool visible;
 *	bool muvible = true;
 *	bool small;
 */

#endif /* DYNAMICENTITY_H_ */
