/*
 * Character.cc
 *
 *  Created on: 27/12/2011
 *      Author: Chutaos Team
 */

#include "Character.h"
#include "GraphicTree.h"

Character::Character() {
	hp = 0;
	speed = 0;
	force = 0;
	rate = 0;
	damage = 0;
	MAXhp = 0;
	moral = 0;
	score = 0;
	expKill = 0;
	goodPerson = false;
	shooting = false;
	dead = false;
	lastShoot.Reset();
	features = NULL;
	ammunition = 0;
}

Character::~Character() {
	hp = 0;
	speed = 0;
	force = 0;
	rate = 0;
	damage = 0;
	MAXhp = 0;
	moral = 0;
	score = 0;
	expKill = 0;
	shooting = false;
	goodPerson = false;
	dead = false;
	features = NULL;
	ammunition = 0;
	/*if (ray!=NULL){TODO Hacer el destructor de esto
		delete ray;
		ray = NULL;
	}*/
	/*if (mov!=NULL){
		delete mov;
		mov = NULL;
	}*/
}

int Character::getDamage() const {
	return damage;
}

int Character::getHp() const {
	return hp;
}

float Character::getRate() const {
	return rate;
}

float Character::getSpeed() const {
	return speed;
}

void Character::setDamage(int damage) {
	this->damage = damage;
}

void Character::setHp(int hp) {
	this->hp = hp;
}

void Character::setRate(float rate) {
	this->rate = rate;
}

void Character::setSpeed(float speed) {
	this->speed = speed;
}

int Character::getMaXhp() const {
	return MAXhp;
}

unsigned int Character::getMoral() const {
	return moral;
}

void Character::setMaXhp(int maXhp) {
	MAXhp = maXhp;
}

void Character::setMoral(unsigned int moral) {
	this->moral = moral;
}

void Character::setMaxForce(float f_) {
	force = f_;
}

float Character::getMaxForce() {
	return force;
}

void Character::UpdateSanar() {
	if (moral == 3) {
		if (hp < MAXhp) {
			if (clkSanar.GetElapsedTime() > 2000) {
				hp++;
				clkSanar.Reset();
			}
		}
	}
}

int Character::getAmmunition() const {
	return ammunition;
}

void Character::setAmmunition(int ammunition) {
	this->ammunition = ammunition;
}

void Character::returnMoral() {
	if (features != NULL) {
		moral = features->featuresContainer[type].Moral;
	}
}

void Character::addBullets(int num) {
	ammunition += num;
}

void Character::updateAmmunition() {
	if (ammunition != -1) {
		if (clkAmmu.GetElapsedTime() > 4000) {
			//TODO Hacerlo bonito
			ammunition += 10;
			if (ammunition > 999)
				ammunition = 999;
			clkAmmu.Reset();
		}
	}
}

void Character::generateFeatures(Core::Entities::Type t) {
	setType(t);
	if (features == NULL) {
		features = CharacterFeature::getInstance();
	}
	if (features != NULL) {
		color = features->featuresContainer[t].color;
		hp = MAXhp = features->featuresContainer[t].HP;
		speed = features->featuresContainer[t].Speed;
		force = features->featuresContainer[t].Force;
		rate = features->featuresContainer[t].Cadence;
		damage = features->featuresContainer[t].Damage;
		moral = features->featuresContainer[t].Moral;
		expKill = features->featuresContainer[t].expKill;
		ammunition = 50;
	} else {

		switch (t) {
		case Core::Entities::e_captain:
			setColor(
					Color<float>(Core::Features::e_captain::Color::red,
							Core::Features::e_captain::Color::green,
							Core::Features::e_captain::Color::blue, 1));
			hp = Core::Features::e_captain::HP;
			speed = Core::Features::e_captain::Speed;
			force = Core::Features::e_captain::Force;
			rate = Core::Features::e_captain::Cadence;
			damage = Core::Features::e_captain::Damage;
			MAXhp = Core::Features::e_captain::HP;
			moral = Core::Features::e_captain::Moral;
			expKill = Core::Features::e_captain::expKill;
			break;
		case Core::Entities::e_tecnic:
			setColor(
					Color<float>(Core::Features::e_tecnic::Color::red,
							Core::Features::e_tecnic::Color::green,
							Core::Features::e_tecnic::Color::blue, 1));
			hp = Core::Features::e_tecnic::HP;
			speed = Core::Features::e_tecnic::Speed;
			force = Core::Features::e_tecnic::Force;
			rate = Core::Features::e_tecnic::Cadence;
			damage = Core::Features::e_tecnic::Damage;
			MAXhp = Core::Features::e_tecnic::HP;
			moral = Core::Features::e_tecnic::Moral;
			expKill = Core::Features::e_tecnic::expKill;
			break;
		case Core::Entities::e_especialist:
			setColor(
					Color<float>(Core::Features::e_especialist::Color::red,
							Core::Features::e_especialist::Color::green,
							Core::Features::e_especialist::Color::blue, 1));
			hp = Core::Features::e_especialist::HP;
			speed = Core::Features::e_especialist::Speed;
			force = Core::Features::e_especialist::Force;
			rate = Core::Features::e_especialist::Cadence;
			damage = Core::Features::e_especialist::Damage;
			MAXhp = Core::Features::e_especialist::HP;
			moral = Core::Features::e_especialist::Moral;
			expKill = Core::Features::e_especialist::expKill;
			break;
		case Core::Entities::e_explosive:
			setColor(
					Color<float>(Core::Features::e_explosive::Color::red,
							Core::Features::e_explosive::Color::green,
							Core::Features::e_explosive::Color::blue, 1));
			hp = Core::Features::e_explosive::HP;
			speed = Core::Features::e_explosive::Speed;
			force = Core::Features::e_explosive::Force;
			rate = Core::Features::e_explosive::Cadence;
			damage = Core::Features::e_explosive::Damage;
			MAXhp = Core::Features::e_explosive::HP;
			moral = Core::Features::e_explosive::Moral;
			expKill = Core::Features::e_explosive::expKill;
			break;
		case Core::Entities::e_enemy1:
			setColor(
					Color<float>(Core::Features::e_enemy1::Color::red,
							Core::Features::e_enemy1::Color::green,
							Core::Features::e_enemy1::Color::blue, 1));
			hp = Core::Features::e_enemy1::HP;
			speed = Core::Features::e_enemy1::Speed;
			rate = Core::Features::e_enemy1::Cadence;
			damage = Core::Features::e_enemy1::Damage;
			MAXhp = Core::Features::e_enemy1::HP;
			moral = Core::Features::e_enemy1::Moral;
			expKill = Core::Features::e_enemy1::expKill;
			break;
		case Core::Entities::e_enemy2:
			setColor(
					Color<float>(Core::Features::e_enemy2::Color::red,
							Core::Features::e_enemy2::Color::green,
							Core::Features::e_enemy2::Color::blue, 1));
			hp = Core::Features::e_enemy2::HP;
			speed = Core::Features::e_enemy2::Speed;
			force = Core::Features::e_enemy2::Force;
			rate = Core::Features::e_enemy2::Cadence;
			damage = Core::Features::e_enemy2::Damage;
			MAXhp = Core::Features::e_enemy2::HP;
			moral = Core::Features::e_enemy2::Moral;
			expKill = Core::Features::e_enemy2::expKill;
			break;
		case Core::Entities::e_enemy3:
			setColor(
					Color<float>(Core::Features::e_enemy3::Color::red,
							Core::Features::e_enemy3::Color::green,
							Core::Features::e_enemy3::Color::blue, 1));
			hp = Core::Features::e_enemy3::HP;
			speed = Core::Features::e_enemy3::Speed;
			force = Core::Features::e_enemy3::Force;
			rate = Core::Features::e_enemy3::Cadence;
			damage = Core::Features::e_enemy3::Damage;
			MAXhp = Core::Features::e_enemy3::HP;
			moral = Core::Features::e_enemy3::Moral;
			expKill = Core::Features::e_enemy3::expKill;
			break;
		default:
			break;
		}

	}

}
void Character::addScore(int sc) {
	score += sc;
}

void Character::setScore(int sc) {
	score = sc;
}

int Character::getScore() {
	return score;
}

float Character::shootDamage() {
	float dam = 0;
	if (ammunition != 0) {
		lastShoot.Reset();
		setShooting(true);
		if (ammunition > 0) {
			ammunition--;
		}
		dam = damage;
	}
	return dam;
}

bool Character::canShoot() {
	if (ammunition != 0 && lastShoot.GetElapsedTime() >= rate) {
		return true;
	}
	return false;
}

bool Character::hurt(int damage) {
	//TODO: Escudo
	bool muerto = false;
	hp -= damage;
	if (hp <= 0) {
		hp = 0;
		muerto = true;
	}
	return muerto;
}

void Character::generateVisionRotation(Point mouse) {

	float x, y, mx, my, ry, rx;
	x = getCenter().getX();
	y = getCenter().getY();
	Point centro(x, y);

	if (centro != mouse) {
		mx = mouse.getX();
		my = mouse.getY();

		rx = mx - x;
		ry = my - y;

		if (rx != 0) {
			float angulo = atan(ry / rx);
			angulo = angulo * 180 / M_PI * -1;

			if (mx >= x) {
				angle = angulo;
			} else {
				angle = 180 + angulo;
			}
			setAngle(angle);
		}
	}

}

RayData Character::generateRay(Point mouse) {

	mouse.setX(getCenter().getX() + 500*cos(getAngle()*M_PI/180));
	mouse.setY(getCenter().getY() + 500*sin(getAngle()*M_PI/180));

	laser = body->getWorld()->RayBody(getCenter(), mouse);

	if (!laser.hit) {
		laser.point = mouse;
	}

	return laser;
}

bool Character::isGoodPerson() const {
	return goodPerson;
}

void Character::setGoodPerson(bool goodPerson) {
	this->goodPerson = goodPerson;
}

bool Character::isShooting() const {
	return shooting;
}

void Character::setShooting(bool shooting) {
	this->shooting = shooting;
}

int Character::getExpKill() const {
	return expKill;
}

void Character::setExpKill(int expKill) {
	this->expKill = expKill;
}

bool Character::isDead() const {
	return dead;
}

void Character::setDead(bool dead) {
	this->dead = dead;
}

void Character::turnAround(float grados_) {
	float total = angle + grados_;
	if (total > 360) {
		total -= 360;
	}
	setAngle(total);
}

CharacterFeature *Character::getFeatures() {
	return features;
}

void Character::setFeatures(CharacterFeature *features_) {
	this->features = features_;
	generateFeatures(this->getType());
}

MovementComp * Character::getMovementComp() {
	return mov;
}

void Character::setMovementComp(MovementComp *mov) {
	if (this->mov != NULL)
		delete this->mov;

	this->mov = mov;
}

