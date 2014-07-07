/*
 * IOControl.cc
 *
 *  Created on: 19/11/2011
 *      Author: Chutaos Team
 */

#include "IOControl.h"

IOControl::IOControl(TWindow *w) {
	window =w;
}

IOControl::~IOControl() {
	window = NULL;
}

bool IOControl::isMouseButtonDown(Core::Mouse::Button b){
	sf::Mouse::Button bsf = (sf::Mouse::Button)b;
	return sf::Mouse::IsButtonPressed(bsf);
}


bool IOControl::IsKeyDown(Core::Key::Code key_) {
	sf::Keyboard::Key k = (sf::Keyboard::Key)key_;
	return sf::Keyboard::IsKeyPressed(k);
}

int IOControl::GetMouseX() {
	if (window->getWindow()!=NULL){
		return sf::Mouse::GetPosition(*window->getWindow()).x;
	}else{
		return 0;
	}
}

int IOControl::GetMouseY() {
	if (window->getWindow()!=NULL){
		return sf::Mouse::GetPosition(*window->getWindow()).y;
	}else{
		return 0;
	}
}

bool IOControl::isKeyPressed(sf::Event event,Core::Key::Code key_){
	sf::Keyboard::Key k = (sf::Keyboard::Key)key_;
	return (event.Type == sf::Event::KeyPressed && event.Key.Code == k);
}

bool IOControl::isPressClose(sf::Event event){
	return (event.Type == sf::Event::Closed);
}







