/*
 * Wall.h
 *
 *  Created on: 12/11/2011
 *      Author: alex
 */

#ifndef WALL_H_
#define WALL_H_

#include "StaticEntity.h"

class Wall: public StaticEntity {
public:
	Wall(ResourceManager *r);
	Wall(const unsigned int idG, const Point, float, ResourceManager *r, Color<float> color_);
	Wall(const Wall&);
	virtual ~Wall();
	Wall& operator=(const Wall&);
	void generateColision(){}
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
#endif /* WALL_H_ */
