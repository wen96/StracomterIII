/*
 * MovementComp.h
 *
 *  Created on: Feb 26, 2012
 *      Author: rellik
 */

#ifndef MOVEMENTCOMP_H_
#define MOVEMENTCOMP_H_

#include "Vector2D.h"
#include "Path.h"
#include <SFML/Graphics.hpp>
#include "SteeringBehavior.h"

class SteeringBehavior;

class MovementComp {
public:
	MovementComp();
	MovementComp(SteeringBehavior *steer);
	MovementComp(MovementComp *leader);
	~MovementComp();
	MovementComp(const MovementComp &mov);
	MovementComp & operator=(const MovementComp &mov);

	void Update();
	void setPath(vector<Point> vPuntos, bool loop = false);

	void addVelocity(Vector2D force);

	void setPos(Point p);
	Vector2D getPos();
	Point getPosP();
    Vector2D getHeading() const;
    double getMass() const;
    double getMaxForce() const;
    double getMaxSpeed() const;
    double getMaxTurnRate() const;
    Vector2D getSide() const;
    Vector2D getVelocity() const;
    void setHeading(Vector2D heading);
    void setMass(double mass);
    void setMaxForce(double maxForce);
    void setMaxSpeed(double maxSpeed);
    void setMaxTurnRate(double maxTurnRate);
    void setVelocity(Vector2D velocity);
    void setOffset(Vector2D offs);
    Vector2D getOffset();
    void setMode(int modo);
    void setLeader(MovementComp *mov);

private:
    Vector2D pos;
	Vector2D mVelocity;
	Vector2D mHeading;
	Vector2D mSide;
	double mMass;
	double mMaxSpeed;
	double mMaxForce;
	double mMaxTurnRate;
	sf::Clock time;
	SteeringBehavior *steering;
	Vector2D offset;
};


#endif /* MOVEMENTCOMP_H_ */
