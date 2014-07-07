/*
 * SteringBehavior.cc
 *
 *  Created on: Feb 26, 2012
 *      Author: Chutaos Team
 */

#include "SteeringBehavior.h"
#include "MovementComp.h"
#include "CoreNamespace.h"

SteeringBehavior::SteeringBehavior() {
	owner = NULL;
	leader = NULL;
	mode = 0;
}

SteeringBehavior::SteeringBehavior(MovementComp *mov, MovementComp *lead) {
	owner = mov;
	leader = lead;
	if(leader != NULL)
		mode = 1;
	else
		mode = 0;
}

SteeringBehavior::~SteeringBehavior() {
	owner = NULL;
	leader = NULL;
	mode = 0;
}

SteeringBehavior::SteeringBehavior(const SteeringBehavior & sBeh) {
	owner = sBeh.owner;
	camino = sBeh.camino;
	leader = sBeh.leader;
	mode = sBeh.mode;
}

SteeringBehavior & SteeringBehavior::operator =(const SteeringBehavior & sBeh) {
	if (this != &sBeh) {
		owner = sBeh.owner;
		camino = sBeh.camino;
		leader = sBeh.leader;
		mode = sBeh.mode;
	}
	return *this;
}

Vector2D SteeringBehavior::Calculate() {
	// Habra que cambiarlo si queremos diferentes comportamientos
	switch (mode) {
	case 0:
		return FollowPath();
		break;
	case 1:
		return OffsetPursuit(owner->getOffset());
		break;
	}
	return Vector2D();
}

void SteeringBehavior::setPath(vector<Point> vp, bool loop) {
	camino.setWaypoints(vp, loop);
}

Vector2D SteeringBehavior::Seek(Vector2D TargetPos) {
	Vector2D desiredVel = Normalize(TargetPos - owner->getPos())
			* owner->getMaxSpeed();

	return (desiredVel - (owner->getVelocity() * owner->getMaxForce()));
}

Vector2D SteeringBehavior::Arrive(Vector2D TargetPos, int deceleration) {
	Vector2D toTarget = TargetPos - owner->getPos();

	double dist = toTarget.Length();
	if (dist > 0) {
		double decelTweaker = 0.3;

		double speed = dist / ((double) deceleration * decelTweaker);

		speed = min(speed, owner->getMaxSpeed());

		Vector2D desiredVel = toTarget * speed / dist;

		return (desiredVel - (owner->getVelocity() * owner->getMaxForce()));
	}
	return Vector2D();
}

void SteeringBehavior::setMode(int modo) {
	if(modo == 1 || modo == 0)
		mode = modo;
}

void SteeringBehavior::setLeader(MovementComp *mov) {
	leader = mov;
}

Vector2D SteeringBehavior::FollowPath() {
	Vector2D force;
	if (!camino.isFinished()) {

		force = Seek(camino.getCurrentWaypointV());

//		if(!camino.lastWaypoint()){
//			force = Seek(camino.getCurrentWaypointV());
//
//		}else{
//			force = Arrive(camino.getCurrentWaypointV(), 1);
//		}

		if (Distance(camino.getCurrentWaypointV(), owner->getPos()) < 5) {
			camino.setNextWaypoint();
		}
	} else {
		force = owner->getVelocity() * -2;
	}

	return force;
}

void SteeringBehavior::setOwner(MovementComp *mov) {
	owner = mov;
}

Vector2D SteeringBehavior::OffsetPursuit(Vector2D offset) {

	Vector2D worldOffset = offset;
	worldOffset.localToWorld(leader->getPos(), leader->getHeading());

	Vector2D toOffset = worldOffset - owner->getPos();

	if(toOffset.Length() >= 1){
		double lookAheadTime = toOffset.Length() / (owner->getMaxSpeed() + leader->getVelocity()).Length();

		Vector2D arrivingForce = Arrive(worldOffset + leader->getVelocity() * lookAheadTime, 1);

		return arrivingForce;
	}else{
		return owner->getVelocity() * -1;
	}
}

