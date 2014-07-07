/*
 * Player.cc
 *
 *  Created on: 12/11/2011
 *      Author: Chutaos Team
 */

#include "Player.h"

Player::Player(ResourceManager *r, Core::Entities::Type t) {
	features = NULL;
	setId(0);
	setVisible(true);
	setSmall(false);
	setResource(r);
	setGoodPerson(true);
	dead = false;
	generateFeatures(t);
	generateCollision();
	idDisplay = t;

	mov = new MovementComp();
	mov->setPos(Point());
	mov->setVelocity(Vector2D());
	mov->setHeading(Vector2D(this->angle));
	mov->setMaxSpeed(400);
	mov->setMass(1);
	mov->setMaxForce(4);

	srand(time(NULL));

	double offsetX = Core::Radius * 4;
	double offsetY1 = Core::Radius * -2;
	double offsetY2 = Core::Radius * -4;

	// Calculamos los offset con un poco de aleatoriedad
	Vector2D v1(offsetX * -1 + ((rand()%100)/100.0 -50), offsetY1 + ((rand()%100)/100.0 -50));
	Vector2D v2(offsetX + ((rand()%100)/100.0 -50), offsetY1 + ((rand()%100)/100.0 -50));
	Vector2D v3(0 + ((rand()%100)/100.0 -50), offsetY2 + ((rand()%100)/100.0 -50));

	formation.push_back(v1);
	formation.push_back(v2);
	formation.push_back(v3);
	clkSanar.Reset();
	clkAmmu.Reset();
}

Player::Player(const unsigned int idG, const Point pos, float angle, ResourceManager *col, Core::Entities::Type t) {
	features = NULL;
	id = idG;
	visible = true;
	small = false;
	center = pos;
	resource = col;
	goodPerson = true;
	dead = false;
	//Genera caracteristicas para el personaje t
	generateFeatures(t);
	idDisplay = t;//esto no se

	generateCollision();

	mov = new MovementComp();
	mov->setPos(pos);
	mov->setVelocity(Vector2D());
	mov->setHeading(Vector2D(angle));
	mov->setMaxSpeed(400);
	mov->setMass(1);
	mov->setMaxForce(4);

	double offsetX = Core::Radius * 4;
	double offsetY1 = Core::Radius * -2;
	double offsetY2 = Core::Radius * -4;

	Vector2D v1(offsetX * -1 , offsetY1);
	Vector2D v2(offsetX, offsetY1);
	Vector2D v3(0, offsetY2);

	formation.push_back(v1);
	formation.push_back(v2);
	formation.push_back(v3);

	clkSanar.Reset();
	clkAmmu.Reset();
}

Player::Player(const Player &pla) {
	setId(pla.getId());
	setVisible(pla.getVisible());
	setSmall(pla.getSmall());
	setCenter(pla.getCenter());
	setResource(pla.getResource());
	setColor(pla.getColor());
	generateFeatures(pla.getType());
	generateCollision();
	features = pla.features;

	mov = new MovementComp(*pla.mov);
	formation = pla.formation;
}

Player::~Player() {
	if(mov != NULL)
		delete mov;
}

Player&
Player::operator =(const Player & pla)
{
	if(&pla != this)
	{
		this->~Player();
		setId(pla.getId());
		setType(pla.getType());
		setVisible(pla.getVisible());
		setSmall(pla.getSmall());
		setCenter(pla.getCenter());
		setResource(pla.getResource());
		features = pla.features;
		mov = new MovementComp(*pla.mov);
		formation = pla.formation;

	}
	return *this;
}

ostream& operator<<(ostream &os, const Player& obj)
{
	os<<"Entity";
	switch(obj.type)
	{
	case 1:
		os<< "(e_captain)";
		break;
	case 2:
		os<< "(e_tecnic)";
		break;
	case 3:
		os<< "(e_especialist)";
		break;
	case 4:
		os<< "(e_explosive)";
		break;
	default:
		os<< "(e_none)";
		break;
	}

	return os;
}

vector<Vector2D> Player::getFormation(){

	return formation;
}

void Player::Update(Vector2D force, Point p){
	this->generateVisionRotation(p);
	this->generateRay(p);

	if(force.isZero())
		this->mov->setVelocity(Vector2D());
	else
		this->UpdateMov(force,p);
	this->UpdateSanar();
}

void Player::UpdateMov(Vector2D force, Point p){
	this->setLinearVelocity(Force(force.x, force.y));
//	Vector2D nuevaVel(p - this->getCenter());
//	nuevaVel.Normalize();
//	nuevaVel *= force.Length();

	mov->setVelocity(force);
	mov->setPos(this->getCenter());

}
