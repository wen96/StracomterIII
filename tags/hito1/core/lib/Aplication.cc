/*
 * Aplication.cc
 *
 *  Created on: 04/11/2011
 *      Author: Chuatos Team
 */

#include "Aplication.h"
#include <iostream>

/*Aplication*
Aplication::getInstance() {
	if(_app == NULL){
		_app = new Aplication;
	}
	return _app;

}*/
Aplication::Aplication() {
	window = new TWindow;
	actionGame = new GameAction(window);
	hid = NULL;
	ioEvents = NULL;
}
Aplication::~Aplication() {
	delete window;
	delete actionGame;
	if (hid==NULL){
		delete hid;
	}
}

void Aplication::StartUp(){
	window->openSFML(640,480,false);
	window->Init();
	ioEvents = new IOControl(window->getInputs());
	hid = new HIDControl(ioEvents);
}

void Aplication::Launch(){
	StartUp();

	actionGame->Start(hid);


}
