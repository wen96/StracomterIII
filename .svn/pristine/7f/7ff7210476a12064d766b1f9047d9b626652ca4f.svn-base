/*
 * TListener.cc
 *
 *  Created on: 10/04/2012
 *      Author: Chutaos Team
 */

#include "TListener.h"

void TListener::setPosition(Point p){
	sf::Listener::SetPosition(p.getX(),p.getY(),p.getZ());
}

void TListener::setPosition(double x, double y, double z){
	sf::Listener::SetPosition(x,y,z);
}

Point TListener::getPosition(){
	Point p;
	p.setX(sf::Listener::GetPosition().x);
	p.setY(sf::Listener::GetPosition().y);
	p.setZ(sf::Listener::GetPosition().z);
	return p;
}

void TListener::setVolumen(float vol){
	sf::Listener::SetGlobalVolume(vol);
}

float TListener::getVolumen(){
	return sf::Listener::GetGlobalVolume();
}
