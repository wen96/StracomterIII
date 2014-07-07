/*
 * IOControl.cc
 *
 *  Created on: 19/11/2011
 *      Author: Chutaos Team
 */

#include "IOControl.h"

IOControl::IOControl(const sf::Input &inputs_):inputs(inputs_) {

}

IOControl::~IOControl() {

}

bool IOControl::isMouseButtonDown(sf::Mouse::Button b){
	return inputs.IsMouseButtonDown(b);
}


bool IOControl::IsKeyDown(Core::Key::Code key_) {
	sf::Key::Code k = (sf::Key::Code)key_;
	return inputs.IsKeyDown(k);
}

int IOControl::GetMouseX() {
	return inputs.GetMouseX();
}

int IOControl::GetMouseY() {
	return inputs.GetMouseY();
}







