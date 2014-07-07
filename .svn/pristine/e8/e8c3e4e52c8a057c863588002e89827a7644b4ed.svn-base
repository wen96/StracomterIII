/*
 * Pointer.h
 *
 *  Created on: 01/02/2012
 *      Author: Chutaos Team
 */

#ifndef POINTER_H_
#define POINTER_H_

#include "DynamicEntity.h"

class Pointer :public DynamicEntity {
public:
	Pointer(int,ResourceManager*);
	Pointer(const Pointer&);
	Pointer& operator=(const Pointer &);
	void setScreenCenter(Point);
	Point getScreeCenter();
	Point getAbsolutCenter(Point, Point, int, int);
	Point getAbsolutCenter(int,int);
	void setPlayerCenter(Point);
	Point getPlayerCenter();
	virtual ~Pointer();
	void Update(Point player, Point cursor);
private:
	Point screen;
	Point player;
};

#endif /* MOUSE_H_ */
