/*
 * MovementComp.cc
 *
 *  Created on: Feb 26, 2012
 *      Author: Chutaos Team
 */

#include "MovementComp.h"

MovementComp::MovementComp() {
	steering = new SteeringBehavior(this);
}

MovementComp::MovementComp(SteeringBehavior *steer) {
	steering = steer;
}

MovementComp::MovementComp(MovementComp *leader){
	steering = new SteeringBehavior(this, leader);
}

MovementComp::~MovementComp() {
	delete steering;
}

MovementComp::MovementComp(const MovementComp & mov) {
	mVelocity = mov.mVelocity;
	mHeading = mov.mHeading;
	mSide = mov.mSide;
	mMass = mov.mMass;
	mMaxSpeed = mov.mMaxSpeed;
	mMaxForce = mov.mMaxForce;
	mMaxTurnRate = mov.mMaxTurnRate;
	time = mov.time;
	steering = new SteeringBehavior(*mov.steering);
	steering->setOwner(this);
	offset = mov.offset;
}

MovementComp & MovementComp::operator =(const MovementComp & mov) {
	if (this != &mov) {
		mVelocity = mov.mVelocity;
		mHeading = mov.mHeading;
		mSide = mov.mSide;
		mMass = mov.mMass;
		mMaxSpeed = mov.mMaxSpeed;
		mMaxForce = mov.mMaxForce;
		mMaxTurnRate = mov.mMaxTurnRate;
		time = mov.time;
		if (steering != NULL)
			delete steering;
		steering = new SteeringBehavior(*mov.steering);
		steering->setOwner(this);
		offset = mov.offset;
	}
	return *this;
}
#include "MotorGrafico.h"
void MovementComp::Update() {
	double timeElapsed = time.GetElapsedTime() / 1000.0;
	time.Reset();

	if (timeElapsed <= 0.5) {

		Vector2D steeringForce = steering->Calculate();
		//steeringForce.Truncate(mMaxForce);

		Vector2D aceleration = steeringForce / mMass;

		mVelocity += aceleration * timeElapsed;

		mVelocity.Truncate(mMaxSpeed);

		pos += mVelocity * timeElapsed;

		if (mVelocity.LengthSqrd() > 0.00000001) {
			mHeading = Normalize(mVelocity);
			mSide = mHeading;
			mSide.perpCW();
		}

	}
}

void MovementComp::setPath(vector<Point> vPuntos, bool loop) {
	steering->setPath(vPuntos, loop);
}

void MovementComp::addVelocity(Vector2D force){
	mVelocity += force;
	mVelocity.Truncate(mMaxSpeed);
}

void MovementComp::setPos(Point p) {
	pos = Vector2D(p);
}

Vector2D MovementComp::getPos() {
	return pos;
}

Point MovementComp::getPosP() {
	return Point(pos.x, pos.y);
}

void MovementComp::setVelocity(Vector2D velocity) {
	mVelocity = velocity;

	if (mVelocity.LengthSqrd() > 0.00000001) {
		mHeading = Normalize(mVelocity);
		mSide = mHeading;
		mSide.perpCW();
	}
}

Vector2D MovementComp::getHeading() const {
	return mHeading;
}

double MovementComp::getMass() const {
	return mMass;
}

double MovementComp::getMaxForce() const {
	return mMaxForce;
}

double MovementComp::getMaxSpeed() const {
	return mMaxSpeed;
}

double MovementComp::getMaxTurnRate() const {
	return mMaxTurnRate;
}

Vector2D MovementComp::getSide() const {
	return mSide;
}

Vector2D MovementComp::getVelocity() const {
	return mVelocity;
}

void MovementComp::setHeading(Vector2D heading) {
	mHeading = heading;
	mSide = heading;
	mSide.perpCW();
}

void MovementComp::setMass(double mass) {
	mMass = mass;
}

void MovementComp::setMaxForce(double maxForce) {
	mMaxForce = maxForce;
}

void MovementComp::setMaxSpeed(double maxSpeed) {
	mMaxSpeed = maxSpeed;
}

void MovementComp::setMaxTurnRate(double maxTurnRate) {
	mMaxTurnRate = maxTurnRate;
}

void MovementComp::setOffset(Vector2D offs) {
	offset = offs;
}

Vector2D MovementComp::getOffset() {
	return offset;
}

void MovementComp::setMode(int modo) {
	steering->setMode(modo);
}

void MovementComp::setLeader(MovementComp *mov) {
	if(mov != this){
		steering->setLeader(mov);
	}
	if(mov == NULL){
		steering->setMode(0);
	}else{
		steering->setMode(1);
	}
}

