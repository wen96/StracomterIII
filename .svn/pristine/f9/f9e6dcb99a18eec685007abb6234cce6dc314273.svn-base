/*
 * ActionEvents.h
 *
 *  Created on: 04/11/2011
 *      Author: ruben
 */

#ifndef ACTIONEVENTS_H_
#define ACTIONEVENTS_H_
#include <ctime>
#include <cstdlib>
#include <cmath>
#include "EntityManager.h"
#include "TWindow.h"
#include "ResourceManager.h"
#include "HIDControl.h"
#include "IOControl.h"
#include "World.h"
#include "Body.h"
#include "Scene.h"

class GameAction {
public:
	GameAction(TWindow *w);
	virtual ~GameAction();
	void Start(HIDControl *hid_);
	void StartUp();
	void Update();
	void Render();
	bool getPaused();
	void setPaused(bool pause_);

private:
	EntityManager *manager;
	ResourceManager *resources;
	TWindow *window;
	HIDControl *hid;
	World *world;
	Scene *scene;
	bool paused;
};




#endif /* ACTIONEVENTS_H_ */
