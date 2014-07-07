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
#include "Box.h"

const int RM_PLAYER = 1;

class Model {
public:
	/**\brief Contructor con parametro de tipo
	 * Para crear un Model se debe indicar el tipo de modelo que se quiere crear
	 * \param type int con el tipo que se desea crear
	 */
	Model(int type){
		switch(type){
			case RM_PLAYER:
				shape = new Polygon(4,Point(0,0),5,90);
				//box = new Box(shape);
					//Circunstancial
					//box = new Box(shape->getPuntos(),4);
					box = NULL;
				break;
		}
	}

	virtual ~Model(){
		if (shape!=NULL){
			delete shape;
			shape = NULL;
		}
		if (box != NULL){
			delete box;
			box = NULL;
		}
	}

	void setShape(Polygon *p){
		shape = p;
	}
	Polygon* getShape(){
		return shape;
	}
	void setBox(Box *b){
		box = b;
	}
	Box* getBox(){
		return box;
	}
private:
	Polygon *shape;
	Box *box;
};

#endif /* MODEL_H_ */
