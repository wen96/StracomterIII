/*
 * Pointer.cc
 *
 *  Created on: 01/02/2012
 *      Author: Chutaos Team
 */

#include "Pointer.h"

Pointer::Pointer(int id_, ResourceManager* res_) {

	setResource(res_);
	setId(id_);
	setColor(Color<float>(0,0,1));
	setCenter(Point());
	setType(Core::Entities::e_pointer);
	generateCollision();
	idDisplay = Core::Entities::e_pointer;


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

	Point tmp  = player;

	tmp.setX(player.getX() + screen.getX() - ancho/2);
	tmp.setY(player.getY() + screen.getY() - alto/2);

	body->setPosition(tmp);

	return tmp;
}

Point
Pointer::getAbsolutCenter(int ancho, int alto) {

	Point tmp  = player;

	tmp.setX(player.getX() + screen.getX() - ancho/2);
	tmp.setY(player.getY() + screen.getY() - alto/2);

	body->setPosition(tmp);

	return tmp;

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
