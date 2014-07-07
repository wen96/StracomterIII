/*
 * GameStrategy.cc
 *
 *  Created on: 26/12/2011
 *      Author: Chutaos Team
 */

#include "GameStrategy.h"

GameStrategy::GameStrategy(HIDControl *hid_,TForm* menu_) {
	menu = menu_;
	hid = hid_;

}

GameStrategy::~GameStrategy() {

	if(menu != NULL)
		delete menu;
	menu = NULL;
	if(hid != NULL)
		delete hid;
	hid = NULL;
}

int GameStrategy::Start(){
	return 0;
}


int GameStrategy::Update() {
	return hid->formMenuControl(menu);
}

void GameStrategy::Render() {
	menu->Draw();
}
