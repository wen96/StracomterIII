/*
 * Pointer.cc
 *
 *  Created on: 01/02/2012
 *      Author: Chutaos Team
 */

#include "Pointer.h"
#include "Aplication.h"

Pointer::Pointer(int id_, ResourceManager* res_) {

	setResource(res_);
	setId(id_);
	setColor(Color<float>(0,0,1));
	setCenter(Point());
	setType(Core::Entities::e_pointer);
	generateCollision();
	idDisplay = Core::Entities::e_pointer*5;


}

Pointer::~Pointer() {
	center = Point();
}

Pointer::Pointer(const Pointer &p) {

	center = p.center;
}

Pointer&
Pointer::operator=(const Pointer &p) {

	if(this != &p)
	{
		this->~Pointer();
		center = p.center;
	}
	return *this;
}

Point
Pointer::getAbsolutCenter(Point player_, Point screen_, int ancho, int alto) {
/*
	Point tmp  = player;

	Aplication *ap = Aplication::getInstance();

	tmp.setX(player.getX() + screen.getX() - ancho/2);
	tmp.setY(player.getY() + screen.getY() - alto/2);

	Point aux;
		aux.setX(player.getX() - tmp.getX());
		aux.setY(player.getY() - tmp.getY());

		Vector2D vect(aux.getX(), aux.getY());
		vect.Rotate(ap->getAngleAction());

		tmp.setX(vect.x + player.getX());
		tmp.setX(vect.y + player.getY());

	body->setPosition(tmp);

	return tmp;*/

	Aplication *ap = Aplication::getInstance();

	Vector2D worldPoint(screen_);

	Vector2D centro(ancho/2, alto/2);

	worldPoint -= centro;

	worldPoint.Rotate(ap->getAngleAction());

	worldPoint += player_;

	body->setPosition(worldPoint.toPoint());

	return worldPoint.toPoint();

}

Point
Pointer::getAbsolutCenter(int ancho, int alto) {
/*
	Aplication *ap = Aplication::getInstance();
	Point tmp  = player;

	tmp.setX(player.getX() + screen.getX() - ancho/2);
	tmp.setY(player.getY() + screen.getY() - alto/2);

	Point aux;
	aux.setX(player.getX() - tmp.getX());
	aux.setY(player.getY() - tmp.getY());

	Vector2D vect(aux.getX(), aux.getY());
	vect.Rotate(ap->getAngleAction());

	tmp.setX(vect.x + player.getX());
			tmp.setX(vect.y + player.getY());


	body->setPosition(tmp);

	return tmp;*/

	Vector2D worldPoint(screen);
	Vector2D centro(ancho/2, alto/2);

	worldPoint -= centro;

	worldPoint += player;

	body->setPosition(worldPoint.toPoint());

	return worldPoint.toPoint();

}
void
Pointer::setScreenCenter(Point screen_) {
	screen = screen_;
}

Point
Pointer::getScreeCenter() {
	return screen;
}

void
Pointer::setPlayerCenter(Point player_) {
	player = player_;
}

Point
Pointer::getPlayerCenter() {
	return player;
}

void Pointer::Update(Point player, Point cursor){
	this->setPlayerCenter(player);
	this->setScreenCenter(cursor);
}
