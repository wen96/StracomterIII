/*
 * ActionControl.cc
 *
 *  Created on: 04/11/2011
 *      Author: ruben
 */

#include "GameAction.h"

GameAction::GameAction(TWindow *w) {
	srand(time(NULL));
	window = w;
	world = new World();
	resources = new ResourceManager(world);
	manager = new EntityManager(resources);
	hid = NULL;
	scene = new Scene(manager, resources, 0.0, 0.0);
	paused = false;
}

GameAction::~GameAction() {
	if (resources != NULL){
		delete resources;
		resources = NULL;
	}
	if (manager != NULL){
		delete manager;
		manager = NULL;
	}
	if (world != NULL){
		delete world;
		world = NULL;
	}
	paused = false;
}

void GameAction::StartUp() {
	window->showMouseCursos(false);
	//ioEvents = new IOControl(window->getInputs());
	//hid = new HIDControl(ioEvents);

	Color<float> c_wall(1.0f, 1.0f, 1.0f);
	int rad = 30;
	manager->addPlayer(Point(200,200), 10, Color<float>(0.0,0.6,0.8, 0.5));
	for(int i = 0; i < 10; i++)
	{

		float a = rand()%100/(double)75 + 0.25;
		Color<float> c_enemy(1,0,0,a);
		int x, y;
		x = rand()%(window->getWidth()- 2*rad) + rad;
		y = rand()%(window->getHeight()- 2*rad) + rad;

		manager->addEnemy(Point(x,y), rad, c_enemy);

	}

	manager->addWall(Point(0,0), 0, c_wall);
	manager->addWall(Point(0,0), -90, c_wall);
	manager->addWall(Point(220,300), 180, c_wall);
	manager->addWall(Point(500,200), 0, c_wall);
	manager->addWall(Point(600,400), 00, c_wall);
	manager->addWall(Point(300,300), 90, c_wall);
	manager->addWall(Point(600,400), -90, c_wall);
	manager->addWall(Point(400,400), 180, c_wall);

	manager->addWall(Point(window->getWidth(),window->getHeight()), 90, c_wall);
	manager->addWall(Point(window->getWidth(),window->getHeight()), 180, c_wall);


}

void GameAction::Update() {
	hid->actionControl(manager);
	world->setFrame(window->getFrameTime());
	world->UpdateWorld();

	vector<Entity *> en = manager->getEntitiesbyType(Core::Entities::e_enemy2);

	int vel = 5;
		for(unsigned i = 0; i < en.size(); i++)
		{
			int prob = rand()%100;
			if(prob == 4)
			{
				int x,y, sx, sy;
				x = rand()%vel + 20;
				y = rand()%vel + 20;

				sx = rand()%2;
				sy = rand()%2;

				x *= pow(-1, sx);
				y *= pow(-1, sy);
				en[i]->setForce(Force(x,y));
			}
			en[i]->applyForce();
		}

	//FUNCION ACTUALIZADOR DE CENTROS - YA LE BUSCAREMOS SITIO
	vector<Entity*> ent = manager->getEntities();
	for(unsigned int i = 0; i < ent.size(); i++)
	{
		ent[i]->setCenter(ent[i]->body->getPosition());
		ent[i]->setAngle(ent[i]->body->getAngle());
		//ent[i]->body->body->SetTransform(ent[i]->body->body->GetPosition(), ent[i]->body->body->GetAngle()+ (0.1 * b2_pi));
	}
}

void GameAction::Render() {
	scene->Draw();
	scene->Reshape(window->getWidth() ,window->getHeight());
}

void GameAction::Start(HIDControl *hid_){
	//MAIN LOOP
	hid = hid_;
	this->StartUp();
	while (window->isOpen()){
		if (!paused){

			glClearColor(0.0, 0.0, 0.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT);
			this->Render();
			this->Update();

		}

		paused = window->display(paused);
	}
}


bool GameAction::getPaused() {
	return paused;
}

void GameAction::setPaused(bool pause_) {
	paused = pause_;
}
