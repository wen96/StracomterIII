/*
 * Model.h
 *
 *  Created on: 15/11/2011
 *      Author: Chutaos Team
 */

#ifndef MODEL_H_
#define MODEL_H_

#include <iostream>
#include "Polygon.h"
#include "CoreNamespace.h"

/** Clase Model2D encargada de crear un modelo 2D para su dibujado o para la creacion de un modelo fisico
 *  Nota: Todavia en fase de creacion, no es estable.
 */
class Model2D {
public:
	/**\brief Contructor con parametro de tipo
	 * Para crear un Model se debe indicar el tipo de modelo que se quiere crear
	 * \param type int con el tipo que se desea crear
	 */
	Model2D(int type);

	Model2D(Core::Obstacles::Type);

	Model2D(Core::Objects::Class);

	/** Destructor
	 */
	virtual ~Model2D();

	/** Set de la forma con puntero
	 * La propia clase hace el delete del puntero
	 * \param p Polygon puntero a alamacenar
	 */
	void setShape(Polygon *p);

	/** Devuelve un puntero a un polygono con la forma en 2D del elemento
	 */
	Polygon* getShape();
private:
	/** Polygono con la forma en 2D del tipo especificado
	 */
	Polygon *shape;
};

#endif /* MODEL_H_ */
