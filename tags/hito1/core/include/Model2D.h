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
	Model2D(int type){

		vector<Point> aux;
		switch(type){
			case Core::Entities::e_captain:
				//aux.push_back(Point(0,35));
				//aux.push_back(Point(-25,20));
				//shape = new Polygon(Point(0,0), aux);
				shape = new Polygon(8,Point(0,0),30,45);
				//shape = new Polygon(4,Point(0,0),50,45);
				//shape = new Polygon(Point(0,0), 50);
				//shape = new Polygon(Point(-50,0), Point(-200, 60));
				//shape = new Polygon(Point(0,0), 30);
				break;
			case Core::Entities::e_enemy2:
				//shape = new Polygon(8,Point(0,0),0.05,45);
				//shape = new Polygon(4,Point(0,0),50,45);
				shape = new Polygon(Point(0,0), 30);
				break;
			case Core::Entities::e_wall:
				//shape = new Polygon(4,Point(0,0),40,45);
				//shape = new Polygon(Point(0,0), 30);
				aux.push_back(Point(0,0));
				aux.push_back(Point(640,0));
				aux.push_back(Point(640, 5));
				aux.push_back(Point(0,5));
				//shape = new Polygon(aux);
				//shape = new Polygon(Point(0,0), Point(640, 0));
				shape = new Polygon(Point(0,0), aux);
				break;
			default:
				shape = NULL;
				break;
		}
	}

	virtual ~Model2D(){
		if (shape!=NULL){
			delete shape;
			shape = NULL;
		}
	}

	void setShape(Polygon *p){
		shape = p;
	}
	Polygon* getShape(){
		return shape;
	}
private:
	Polygon *shape;
};

#endif /* MODEL_H_ */
