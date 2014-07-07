/*
 * SteeringBehavior.h
 *
 *  Created on: Feb 26, 2012
 *      Author: Chutaos Team
 */

#ifndef STEERINGBEHAVIOR_H_
#define STEERINGBEHAVIOR_H_

#include "Vector2D.h"
#include "MovementComp.h"
#include "Path.h"

class MovementComp;

class SteeringBehavior{
public:
	SteeringBehavior();
	SteeringBehavior(MovementComp *mov, MovementComp *lead=NULL);
	~SteeringBehavior();
	SteeringBehavior(const SteeringBehavior &sBeh);
	SteeringBehavior & operator=(const SteeringBehavior &sBeh);

	Vector2D Calculate();
	void setPath(vector<Point> vp, bool loop = false);
	void setOwner(MovementComp *mov);
	void setMode(int modo);
	void setLeader(MovementComp *mov);
private:
	MovementComp *owner;
	Path camino;
	int mode;
	MovementComp *leader;

	Vector2D Seek(Vector2D TargetPos);
	Vector2D Arrive(Vector2D TargetPos, int deceleration);
	Vector2D FollowPath();
	Vector2D OffsetPursuit(Vector2D offset);
};


#endif /* STEERINGBEHAVIOR_H_ */
