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
	ModelPhisic(int type, Polygon *p);
	ModelPhisic(Core::Obstacles::Type, Polygon);
	ModelPhisic(const ModelPhisic &);
	ModelPhisic & operator=(const ModelPhisic &);

	/** Destructor
	 */
	virtual ~ModelPhisic();

	/** Set del body data
	 * La propia clase se encarga de borrar el puntero
	 * @param b puntero BodyData de la forma a setear
	 */
	void setBodyData(BodyData *b);

	/** Devuelve la forma fisica de la entidad creada a partir de la forma real
	 * Devuelve un puntero a BodyData que contiene la forma para poner generar la fisica de la misma
	 * @return puntero a BodyData con al forma
	 */
	BodyData* getBodyData();
private:
	void Copiar(const ModelPhisic &);
	void Destructor();
	/** Puntero a bodyData con la forma fisica del elemento
	 */
	BodyData *bodyData;
};

#endif /* MODELFISIC_H_ */
