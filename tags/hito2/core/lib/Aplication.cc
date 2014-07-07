/*
 * Aplication.cc
 *
 *  Created on: 04/11/2011
 *      Author: Chuatos Team
 */

#include "Aplication.h"
#include <iostream>

Aplication * Aplication::_app = NULL;

Aplication* Aplication::getInstance() {
	if(_app == NULL){
		_app = new Aplication();
	}
	return _app;
}

Aplication* Aplication::getInstance(string nombreMapa) {
	if(_app == NULL){
		_app = new Aplication(nombreMapa);
	}
	return _app;
}

Aplication::Aplication() {
	defaultMap = "testFiles/maps/mapRuben.xml";
	mapa = new Map(defaultMap);

	resManager = ResourceManager::getInstance();

	window = new TWindow;
	ioEvents = new IOControl(window);
	hid = new HIDControl(ioEvents);
	consola = new TConsole(15, ioEvents);
	actionGame = new GameAction(window,hid,consola, mapa);

	menuGame = new GameMenu(hid);//todo
	strategyGame = NULL;//todo

	currentMode = Core::GameMode::Menu; //TODO cambiarlo para cuando tengamos el menú principal
	startNewMode = true;
	sm = SceneManager::getInstance();
	sm->makeMenuTree();
	sm->addElement(menuGame,sm->getNode(Graphics::DirectNodesMenu::t_menu));
}

Aplication::Aplication(string nombreMapa) {
	mapa = new Map(nombreMapa);

	resManager = ResourceManager::getInstance();

	window = new TWindow;
	ioEvents = new IOControl(window);
	hid = new HIDControl(ioEvents);
	consola = new TConsole(10, ioEvents);
	actionGame = new GameAction(window,hid,consola, mapa);

	menuGame = new GameMenu(hid);//todo
	strategyGame = NULL;//todo

	currentMode = Core::GameMode::Action; //TODO cambiarlo para cuando tengamos el menú principal
	startNewMode = true;
	sm = SceneManager::getInstance();
	sm->makeMenuTree();
	sm->addElement(menuGame,sm->getNode(Graphics::DirectNodesMenu::t_menu));
}

void Aplication::setMap(string map_){
	if (mapa!=NULL){
		mapa->setMap(map_);
	}
}

Aplication::~Aplication() {
	if (actionGame!=NULL){
		delete actionGame;
	}
	if (strategyGame!=NULL){
		delete strategyGame;
	}
	if (ioEvents != NULL){
		delete ioEvents;
	}
	if (menuGame!=NULL){
		delete menuGame;
	}


	if (hid!=NULL){
		delete hid;
	}
	if (consola!=NULL){
		delete consola;
	}
	if (mapa!=NULL){
		delete mapa;
	}
	if (resManager!=NULL){
		delete resManager;
	}


	actionGame = NULL;
	hid = NULL;
	menuGame = NULL;
	strategyGame = NULL;

	//Cerramos la ventana al final para que el usuario sepa que hace
	window->close();

	if (window!=NULL){
		delete window;
	}
	window = NULL;
}

void Aplication::StartUp(){

	window->openSFML(800,600,false);
	window->setFrameLimit(60);
	window->Init();
	menuGame->StartUp();
	menuGame->setVisible(Graphics::Menus::m_inicio);
	currentMode = Core::GameMode::Menu;
}

void Aplication::Launch(){
	StartUp();

	/*while(window->isOpen()){
		switch(currentMode)
		{
			case Core::GameMode::Menu:
				sm->DrawScene();
				break;
			case Core::GameMode::Strategy:
				//TODO
				break;

			case Core::GameMode::Action:
				sm->removeMenuTree();
				actionGame->Start();
				break;
		}

		window->display();
	}*/


	GameLoop();
}

void Aplication::Update(){
	int aux = -1;
	switch(currentMode){
	case Core::GameMode::Action:
		currentMode = (Core::GameMode::Mode)actionGame->Update();
		switch(currentMode){
		case Core::GameMode::Menu:
			sm->makeMenuTree();
			sm->addElement(menuGame,sm->getNode(Graphics::DirectNodesMenu::t_menu));
			break;
		default:
			break;
		}


		break;
	case Core::GameMode::Menu:
		menuGame->setVisible(Graphics::Menus::m_inicio);
		aux = menuGame->Update();
		if (aux > -1){
			currentMode = (Core::GameMode::Mode)aux;
			switch(currentMode){
			case Core::GameMode::Strategy:
				cerr << "Modo estrategia" << endl;
				break;
			case Core::GameMode::Action:
				//Pantalla cargando
				menuGame->setVisible(Graphics::Menus::m_loading);
				sm->DrawScene();
				window->display();
				//Destruimos e inicializamos
				sm->removeMenuTree();
				actionGame->StartUp();
				break;
			default:
				break;
			}
		}else{
			if (aux == Core::signalExit){
				currentMode = Core::GameMode::Salir;
			}
		}
		break;
	case Core::GameMode::Strategy:
		//TODO
		break;
	default:
		break;
	}
}

void Aplication::Render(){

	switch(currentMode){
	case Core::GameMode::Action:
		actionGame->Render();
		break;
	case Core::GameMode::Menu:
		sm->DrawScene();
		break;
	case Core::GameMode::Strategy:
		//TODO
		cerr << "Modo estrategia Renderizando" << endl;
		break;
	default:
		break;
	}


	window->display();//cosas de la sfml para la actualizacion de la ventana
}

void Aplication::GameLoop(){
	sf::Clock frameRate;

	while(Core::GameMode::Salir  != currentMode){

		this->Update();

		this->Render();

		fps = 1.0 / (frameRate.GetElapsedTime() / 1000.0);
		frameRate.Reset();
	}

	menuGame->setVisible(Graphics::Menus::m_closing);
	sm->DrawScene();
	window->display();

}

float Aplication::getZoomAction() const
{
    return zoomAction;
}

bool Aplication::isMode3D() const
{
    return mode3D;
}

void Aplication::setMode3D(bool mode3D)
{
    this->mode3D = mode3D;
}

void Aplication::setZoomAction(float zoomAction)
{
    this->zoomAction = zoomAction;
}


float Aplication::getAngleAction() const
{
    return angleAction;
}

void Aplication::setAngleAction(float angleAction)
{
    this->angleAction = angleAction;
}

float Aplication::getAngleCamera() {
	return angleCamera;
}

void Aplication::setAngleCamera(float angle_) {
	angleCamera = angle_;
}

GameAction *Aplication::getActionGame() const
{
    return actionGame;
}

GameMenu *Aplication::getMenuGame() const
{
    return menuGame;
}

void Aplication::setActionGame(GameAction *actionGame)
{
    this->actionGame = actionGame;
}

void Aplication::setMenuGame(GameMenu *menuGame)
{
    this->menuGame = menuGame;
}

float Aplication::getFps() const
{
    return fps;
}

void Aplication::setFps(float fps)
{
    this->fps = fps;
}





