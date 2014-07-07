/*
 * Player.cc
 *
 *  Created on: 12/11/2011
 *      Author: alex
 */

#include "Player.h"

Player::Player(ResourceManager *r) {
	setId(0);
	setType(Core::Entities::e_captain);
	setVisible(true);
	setSmall(false);
	setResource(r);
	//Variables especificas del player
	hp=100;
	speed=100;
	rate=0.2;
	damage=10;
	MAXhp=100;
}

Player::Player(const unsigned int idG, const Point pos, float angle, ResourceManager *col, Color<float> color_) {
	setId(idG);
	setType(Core::Entities::e_captain);
	setVisible(true);
	setSmall(false);
	setCenter(pos);
	setResource(col);
	setColor(color_);
	BodyData *aux = getResource()->getModelPhisics(getType())->getBodyData();
	World *auxWorld = getResource()->getWorld();

	body = new Body(*auxWorld,*aux);
	//TODO PODER PONER EL BODY EN UNA POSICION INICIAL (principialmente por los objetos statics
	//cout << "Player:\n";
	//cout << body->getLinearVelocity().getForceX() << endl;

	body->setPosition(pos);
	body->setAngle(angle);
	//Variables especificas del plaitan
	hp=100;
	speed=100;
	rate=0.2;
	damage=10;
	MAXhp=100;
}

Player::Player(const Player &pla) {

	setId(pla.getId());
	setType(pla.getType());
	setVisible(pla.getVisible());
	setSmall(pla.getSmall());
	setCenter(pla.getCenter());
	setResource(pla.getResource());
	setColor(pla.getColor());
	//Variables especificas del plaitan
	hp=pla.hp;
	speed=pla.speed;
	rate=pla.rate;
	damage=pla.damage;
}

Player::~Player() {
	hp=0;
	speed=0;
	rate=0;
	damage=0;
	MAXhp=0;
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
		//Variables especificas del plaitan
		hp=pla.hp;
		speed=pla.speed;
		rate=pla.rate;
		damage=pla.damage;
	}
	return *this;
}

void
Player::generateVisionRotation(Point mouse) {

	float x, y, mx, my, ry, rx;
	x = getCenter().getX();
	y = getCenter().getY();

	mx = mouse.getX();
	my = mouse.getY();

	rx = mx - x;
	ry = my - y;

	float angulo = atan(ry/rx);
	angulo = angulo * 180/M_PI * -1;

	if(mx >= x)
		body->setAngle(angulo);
	else
		body->setAngle(180+angulo);

}

/*void
Player::shoot(Point mouse, EntityManager *em) {

	vector<Entity*> entities = em->getEntities();
	bool impact = false;

	for(int i = 0; i < entities.size() && !impact; i++)
	{

	}

}*/

int Player::getDamage() const
{
    return damage;
}

int Player::getHp() const
{
    return hp;
}

float Player::getRate() const
{
    return rate;
}

int Player::getSpeed() const
{
    return speed;
}

unsigned int Player::getMAXhp() const
{
    return MAXhp;
}

void Player::setDamage(int damage)
{
    this->damage = damage;
}

void Player::setHp(int hp)
{
    this->hp = hp;
}

void Player::setRate(float rate)
{
    this->rate = rate;
}

void Player::setSpeed(int speed)
{
    this->speed = speed;
}
