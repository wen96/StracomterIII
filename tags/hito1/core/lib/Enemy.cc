/*
 * Enemy.cc
 *
 *  Created on: 12/11/2011
 *      Author: alex
 */

#include "Enemy.h"

Enemy::Enemy(ResourceManager *r) {
	setId(0);
	setType(Core::Entities::e_enemy2);
	setVisible(true);
	setSmall(false);
	setResource(r);
	//Variables especificas del eneitan
	hp=80;
	speed=100;
	rate=0.2;
	damage=10;
	MAXhp=80;
}

Enemy::Enemy(const unsigned int idG, const Point pos, float angle, ResourceManager *res, Color<float> color_) {
	setId(idG);
	setType(Core::Entities::e_enemy2);
	setVisible(true);
	setSmall(true);
	setCenter(pos);
	setResource(res);
	setColor(color_);
	BodyData *aux = getResource()->getModelPhisics(getType())->getBodyData();
	World *auxWorld = getResource()->getWorld();
	body = new Body(*auxWorld,*aux);
	body->setPosition(pos);
	body->setAngle(angle);
	//Variables especificas del eneitan
	hp=80;
	speed=100;
	rate=0.2;
	damage=10;
	MAXhp=80;
}

Enemy::Enemy(const Enemy &ene) {

	setId(ene.getId());
	setType(ene.getType());
	setVisible(ene.getVisible());
	setSmall(ene.getSmall());
	setCenter(ene.getCenter());
	setResource(ene.getResource());
	setColor(ene.getColor());
	//Variables especificas del eneitan
	hp=ene.hp;
	speed=ene.speed;
	rate=ene.rate;
	damage=ene.damage;
}

Enemy::~Enemy() {
	hp=0;
	speed=0;
	rate=0;
	damage=0;
	MAXhp=0;
}

Enemy&
Enemy::operator =(const Enemy & ene)
{
	if(&ene != this)
	{
		this->~Enemy();
		setId(ene.getId());
		setType(ene.getType());
		setVisible(ene.getVisible());
		setSmall(ene.getSmall());
		setCenter(ene.getCenter());
		setResource(ene.getResource());
		//Variables especificas del eneitan
		hp=ene.hp;
		speed=ene.speed;
		rate=ene.rate;
		damage=ene.damage;
	}
	return *this;
}

int Enemy::getDamage() const
{
    return damage;
}

int Enemy::getHp() const
{
    return hp;
}

float Enemy::getRate() const
{
    return rate;
}

int Enemy::getSpeed() const
{
    return speed;
}

unsigned int Enemy::getMAXhp() const
{
    return MAXhp;
}

void Enemy::setDamage(int damage)
{
    this->damage = damage;
}

void Enemy::setHp(int hp)
{
    this->hp = hp;
}

void Enemy::setRate(float rate)
{
    this->rate = rate;
}

void Enemy::setSpeed(int speed)
{
    this->speed = speed;
}
