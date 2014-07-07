/*
 * Force.cpp
 *
 *  Created on: 18/11/2011
 *      Author: sergio
 */

#include "Force.h"

Force::Force() {
	forceX = 0.0;
	forceY = 0.0;
}

Force::Force(float forceX_, float forceY_)
{
	forceX = forceX_;
	forceY = forceY_;
}

Force::Force(const Force &force)
{
	forceX = force.forceX;
	forceY = force.forceY;
}

Force &
Force::operator =(const Force &force) {
	if(this != &force)
	{
		this->~Force();
		forceX = force.forceX;
		forceY = force.forceY;
	}
	return *this;
}

b2Vec2
Force::getForce() const{
	b2Vec2 force;
	force.Set(forceX, forceY);
	return force;
}

Force::~Force() {
	forceX = 0.0;
	forceY = 0.0;
}

