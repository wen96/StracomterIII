/*
 * ModelFisic.h
 *
 *  Created on: 18/11/2011
 *      Author: Chutaos Team
 */

#ifndef MODELFISIC_H_
#define MODELFISIC_H_

#include <iostream>
#include "BodyData.h"
#include "CoreNamespace.h"

using namespace std;

/** class ModelPhisic encarga de crear un modelo fisico para la deteccion de colisiones
 *  Nota: Todavia en fase de creacion, no es estable.
 */
class ModelPhisic {
public:
	/** Constructor, crea un bodyData para la deteccion de colisiones.
	 * Crea un modelo fisico para que el motor de fisica pueda manejarse con el.
	 * @param type tipo de entidad que se desea crear.
	 * @param p poligono con la forma en 2D de la entidad.
	 */
	ModelPhisic(int type, Polygon *p){
		switch(type){
			case Core::Entities::e_captain:
				bodyData = new BodyData(*p, b2_dynamicBody);
				bodyData->setDensity(1.0);
				bodyData->setMasa(50);
				bodyData->setFriction(0.0);
				bodyData->setLinearDamping(5);
				bodyData->setAngularDamping(5);
				break;
			case Core::Entities::e_enemy2:
				bodyData = new BodyData(*p, b2_dynamicBody);
				bodyData->setDensity(1.0);
				bodyData->setMasa(80);
				bodyData->setFriction(1.0);
				bodyData->setLinearDamping(5);
				bodyData->setAngularDamping(5);
				break;
			case Core::Entities::e_wall:
				bodyData = new BodyData(*p, b2_staticBody);
				bodyData->setDensity(1.0);
				bodyData->setMasa(1);
				bodyData->setLinearDamping(5);
				bodyData->setAngularDamping(5);
				break;
			default:
				bodyData = NULL;
				break;
		}

	}
	virtual ~ModelPhisic(){
		if (bodyData != NULL){
			delete bodyData;
			bodyData = NULL;
		}
	}
	void setBodyData(BodyData *b){
		bodyData = b;
	}
	BodyData* getBodyData(){
		return bodyData;
	}
private:
	BodyData *bodyData;
};

#endif /* MODELFISIC_H_ */
