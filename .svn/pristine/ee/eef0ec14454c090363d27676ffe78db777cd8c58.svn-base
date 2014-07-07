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
	if (_app == NULL) {
		_app = new Aplication();
	}
	return _app;
}

GameStatus *Aplication::getGameSelections() const
{
	return gameSelections;
}

void Aplication::setGameSelections(GameStatus *gameSelections)
{
	this->gameSelections = gameSelections;
}

Aplication::Aplication() {

	gameOptions = GameOptions::getInstance();
	if (!gameOptions->loadData("testFiles/settings.txt")){
		gameOptions->saveData("testFiles/settings.txt");
	}

	defaultMap = "testFiles/maps/mapG4.xml";
	mapa = new Map(defaultMap);

	resManager = ResourceManager::getInstance();
	window = new TWindow;
	ioEvents = new IOControl(window);
	hid = new HIDControl(ioEvents);
	consola = new TConsole(15, ioEvents);
	actionGame = new GameAction(window, hid, consola, mapa);

	menuGame = new GameMenu(hid);
	strategyGame = NULL;

	currentMode = Core::GameMode::Menu;
	startNewMode = true;
	sm = SceneManager::getInstance();
	sm->makeMenuTree();
	sm->addElement(menuGame, sm->getNode(Graphics::DirectNodesMenu::t_menu));

	animationMenu = AnimationControl::getInstance(window,menuGame);
	animationMenu->setTime(500);

	gameSelections = GameStatus::getInstance();
	ac = AudioControl::getInstance();

	ac->loadData();//Leo la configuracion de gameoptions
	if (!gameSelections->loadData()){
		gameSelections->setNivelPlanta(1);
		gameSelections->setZona(3);
		gameSelections->saveData();
	}


}

void Aplication::setMap(string map_) {
	if (mapa != NULL) {
		defaultMap = map_;
	}
}

Aplication::~Aplication() {
	if (actionGame != NULL) {
		delete actionGame;
	}
	if (strategyGame != NULL) {
		delete strategyGame;
	}
	if (ioEvents != NULL) {
		delete ioEvents;
	}
	if (menuGame != NULL) {
		delete menuGame;
	}

	if (hid != NULL) {
		delete hid;
	}
	if (consola != NULL) {
		delete consola;
	}
	if (mapa != NULL) {
		delete mapa;
	}
	if (resManager != NULL) {
		delete resManager;
	}

	if (ac != NULL){
		delete ac;
	}
	ac = NULL;

	if (gameSelections != NULL){
		delete gameSelections;
	}
	gameSelections = NULL;

	if (gameOptions != NULL){
		delete gameOptions;
	}
	gameOptions = NULL;

	actionGame = NULL;
	hid = NULL;
	menuGame = NULL;
	strategyGame = NULL;

	//Cerramos la ventana al final para que el usuario sepa que hace
	window->close();

	if (window != NULL) {
		delete window;
	}
	window = NULL;

}

void Aplication::StartUp() {
	window->openSFML(gameOptions->getWindowWidth(), gameOptions->getWindowHeight(), gameOptions->isFullScreen());
	window->setFrameLimit(60);
	window->Init();
	menuGame->StartUp();
	menuGame->setVisible(Graphics::Menus::m_inicio);
	currentMode = Core::GameMode::Menu;
	ac->switchSong(Audio::Music::s_menu);
	ac->playMusic();
}

void Aplication::Launch() {
	StartUp();
	GameLoop();
}

void Aplication::Update() {
	int aux = -1;
	switch (currentMode) {
	case Core::GameMode::Action:
		//		//cout<<"¡¡¡ENTRO EN EL MODO ACCION!!!"<<endl;
		currentMode = (Core::GameMode::Mode) actionGame->Update();
		switch (currentMode) {
		case Core::GameMode::Menu:
			ac->switchSong(Audio::Music::s_menu);
			ac->playMusic();
			sm->makeMenuTree();
			sm->addElement(menuGame,
					sm->getNode(Graphics::DirectNodesMenu::t_menu));
			menuGame->setVisible(Graphics::Menus::m_inicio);
			break;
		case Core::GameMode::Strategy:
			menuGame->loadStrategyStatus();
			ac->switchSong(Audio::Music::s_menu);
			ac->playMusic();
			sm->makeMenuTree();
			sm->addElement(menuGame,
					sm->getNode(Graphics::DirectNodesMenu::t_menu));
			menuGame->setVisible(Graphics::Menus::m_strategy);
			break;
		default:
			break;
		}

		break;
		case Core::GameMode::Menu:
			aux = menuGame->Update();
			if (aux > -1) {
				if (aux == Core::GameMode::Free){//si se ha pulsado en partida rápida
					//Reinicializo el fichero
					gameSelections->initializeVectorPlayers();
					gameSelections->setNivelPlanta(-1);
					gameSelections->setZona(3);
					gameSelections->setPuntuacionPlayer(0);
					gameSelections->setTypePlayer(Core::Entities::e_captain);
					//gameSelections->saveData();
					aux = Core::GameMode::Strategy;
				}
				else if (aux == Core::GameMode::Strategy + 100){//si se ha pulsado en nueva partida
					//Reinicializo el fichero
					gameSelections->initializeVectorPlayers();
					gameSelections->setNivelPlanta(1);
					gameSelections->setZona(3);
					gameSelections->setPuntuacionPlayer(0);
					gameSelections->setTypePlayer(Core::Entities::e_captain);
					gameSelections->saveData();
					aux = Core::GameMode::Strategy;
				}
				else
				{
					if (!gameSelections->loadData()){
						gameSelections->setNivelPlanta(1);
						gameSelections->setZona(3);
						gameSelections->saveData();
					}

				}
				if (aux > Core::GameMode::size){//Si estamos en el menu de opciones
					switch (aux){
					case Core::GameMode::size + 1:
					animationMenu->slideDown(Graphics::Menus::m_inicio,Graphics::Menus::m_options,Graphics::DirectNodesMenu::t_menu);
					menuGame->setVisible(Graphics::Menus::m_options);
					menuGame->loadOptionsMenu();
					break;
					default://Para que quede mas limpio
						this->controlOption(aux);//funcion que hace lo que tenga que hacer con las opciones al pulsar en uno de sus botones
						break;
					}
				}else{//si estamos en el menu principial
					currentMode = (Core::GameMode::Mode) aux;
					switch (currentMode) {
					case Core::GameMode::Strategy:
						menuGame->loadStrategyStatus();
						if (gameSelections->getNivelPlanta()<9){
							animationMenu->slideLeft(Graphics::Menus::m_inicio,Graphics::Menus::m_strategy,Graphics::DirectNodesMenu::t_menu);
						}else{
							animationMenu->slideLeft(Graphics::Menus::m_inicio,Graphics::Menus::m_theend,Graphics::DirectNodesMenu::t_menu);
						}
						sm->makeMenuTree();
						sm->addElement(menuGame,
								sm->getNode(Graphics::DirectNodesMenu::t_menu));

						if (gameSelections->getNivelPlanta()<9){
							menuGame->setVisible(Graphics::Menus::m_strategy);
						}else{
							menuGame->setVisible(Graphics::Menus::m_theend);
						}
						break;
					case Core::GameMode::Action:
						//Pantalla cargando
						animationMenu->slideUp(Graphics::Menus::m_inicio,Graphics::Menus::m_loading,Graphics::DirectNodesMenu::t_menu);
						sm->DrawScene();
						window->display();
						//Destruimos e inicializamos
						sm->removeMenuTree();
						actionGame->StartUp();
						break;
					case Core::GameMode::Menu:
						//Animacion

						animationMenu->slideUp(Graphics::Menus::m_options,Graphics::Menus::m_inicio,Graphics::DirectNodesMenu::t_menu);
						menuGame->setVisible(Graphics::Menus::m_inicio);
						//window->create(gameOptions->getWindowWidth(),gameOptions->getWindowHeight(),gameOptions->isFullScreen());

						break;
					case Core::GameMode::Credits:
						animationMenu->slideUp(Graphics::Menus::m_inicio,Graphics::Menus::m_credits,Graphics::DirectNodesMenu::t_menu);
						menuGame->setVisible(Graphics::Menus::m_credits);
						ac->switchSong(Audio::Music::s_credits);
						ac->playMusic();
						break;
					default:
						if (menuGame->getVisible() == Graphics::Menus::m_options){//Pulsar escape en el menu de opciones
							animationMenu->slideUp(Graphics::Menus::m_options,Graphics::Menus::m_inicio,Graphics::DirectNodesMenu::t_menu);
							menuGame->setVisible(Graphics::Menus::m_inicio);
							currentMode = Core::GameMode::Menu;
						}else {//Pulsar escape en el menu de inicio
							animationMenu->slideRight(Graphics::Menus::m_inicio,Graphics::Menus::m_closing,Graphics::DirectNodesMenu::t_menu);
						}
						break;
					}
				}
			} else {
				if (aux == Core::signalExit) {
					animationMenu->slideRight(Graphics::Menus::m_inicio,Graphics::Menus::m_closing,Graphics::DirectNodesMenu::t_menu);
					currentMode = Core::GameMode::Salir;
				}
			}
			break;
		case Core::GameMode::Strategy:
			if (gameSelections->getNivelPlanta()<9){
				menuGame->setVisible(Graphics::Menus::m_strategy);
			}else{
				menuGame->setVisible(Graphics::Menus::m_theend);
			}
			aux = menuGame->Update();
			if (aux > -1) {
				switch(aux)
				{
				case 20:
					currentMode = Core::GameMode::Menu;
					break;
				case 30:
					currentMode = Core::GameMode::Action;
					break;
				case 40:
					currentMode = Core::GameMode::Credits;
					break;
				default:
					currentMode = Core::GameMode::Strategy;
					break;
				}
				switch (currentMode) {
				case Core::GameMode::Strategy:
					if(aux<10)
					{
						gameSelections->selectZona(aux);
						menuGame->cambiaRecompensa(aux);
					}else{
						menuGame->efectoVisible(aux%10);//nos quedamos con la parte baja para ver que nos pide del modo estrategia.
						gameSelections->setTypePlayer((Core::Entities::Type)(aux%10));
					}
					sm->makeMenuTree();
					sm->addElement(menuGame,
							sm->getNode(Graphics::DirectNodesMenu::t_menu));
					menuGame->setVisible(Graphics::Menus::m_strategy);
					break;
				case Core::GameMode::Menu:
					if (menuGame->getVisible()==Graphics::Menus::m_strategy){
						animationMenu->slideRight(Graphics::Menus::m_strategy,Graphics::Menus::m_inicio,Graphics::DirectNodesMenu::t_menu);
					}else{
						animationMenu->slideRight(Graphics::Menus::m_theend,Graphics::Menus::m_inicio,Graphics::DirectNodesMenu::t_menu);
					}
					sm->makeMenuTree();
					sm->addElement(menuGame,
							sm->getNode(Graphics::DirectNodesMenu::t_menu));
					menuGame->setVisible(Graphics::Menus::m_inicio);
					break;
				case Core::GameMode::Action:
					ac->switchSong(Audio::Music::s_action);
					ac->playMusic();
					//Pantalla cargando
					animationMenu->slideLeft(Graphics::Menus::m_strategy,Graphics::Menus::m_loading,Graphics::DirectNodesMenu::t_menu);
					menuGame->setVisible(Graphics::Menus::m_loading);
					sm->DrawScene();
					window->display();
					//Destruimos e inicializamos
					sm->removeMenuTree();
					actionGame->StartUp();
					break;
				case Core::GameMode::Credits:
					animationMenu->slideUp(Graphics::Menus::m_theend,Graphics::Menus::m_credits,Graphics::DirectNodesMenu::t_menu);
					menuGame->setVisible(Graphics::Menus::m_credits);
					ac->switchSong(Audio::Music::s_credits);
					ac->playMusic();
					break;
				default:
					break;
				}
			} else {
				if (aux == Core::signalExit) {
					animationMenu->slideRight(Graphics::Menus::m_inicio,Graphics::Menus::m_closing,Graphics::DirectNodesMenu::t_menu);
					currentMode = Core::GameMode::Salir;
				}
			}
			break;
		case Core::GameMode::Credits:
			menuGame->setVisible(Graphics::Menus::m_credits);
			aux = menuGame->Update();
			if (aux > -1) {
				currentMode = (Core::GameMode::Mode) aux;
				animationMenu->slideDown(Graphics::Menus::m_credits,Graphics::Menus::m_inicio,Graphics::DirectNodesMenu::t_menu);
				menuGame->setVisible(Graphics::Menus::m_inicio);
				ac->switchSong(Audio::Music::s_menu);
				ac->playMusic();
			}else{
				if (aux == Core::signalExit) {
					animationMenu->slideRight(Graphics::Menus::m_credits,Graphics::Menus::m_closing,Graphics::DirectNodesMenu::t_menu);
					currentMode = Core::GameMode::Salir;
				}
			}
			break;

		default:
			break;
	}
}

void Aplication::Render() {

	switch (currentMode) {
	case Core::GameMode::Action:
		actionGame->Render();
		break;
	case Core::GameMode::Menu:
	case Core::GameMode::Strategy:
	case Core::GameMode::Credits:
		sm->DrawScene();
		break;
	default:
		break;
	}

	window->display(); //cosas de la sfml para la actualizacion de la ventana
}

void Aplication::GameLoop() {
	Clock frameRate;

	while (Core::GameMode::Salir != currentMode) {

		this->Update();

		this->Render();

		fps = 1000.0 / (float) frameRate.getElapsedMiliseconds();
		frameRate.Reset();
	}

	menuGame->setVisible(Graphics::Menus::m_closing);
	sm->DrawScene();
	window->display();

}


void Aplication::controlOption(int event){
	switch (event){
	case Core::GameMode::size+2://Volume music up
	gameOptions->upMusicVolume();
	break;
	case Core::GameMode::size+3://Volume music down
	gameOptions->downMusicVolume();
	break;
	case Core::GameMode::size+4://Volume efect up
	gameOptions->upEffectsVolume();
	ac->loadData();
	ac->playSound(Audio::Sound::e_machineGun);
	break;
	case Core::GameMode::size+5://Volume efect down
	gameOptions->downEffectsVolume();
	ac->loadData();
	ac->playSound(Audio::Sound::e_machineGun);
	break;
	case Core::GameMode::size+6:
	gameOptions->downDificult();
	break;
	case Core::GameMode::size+7:
	gameOptions->upDificult();
	break;
	case Core::GameMode::size+8:
	gameOptions->upResolution();
	break;
	case Core::GameMode::size+9:
	gameOptions->downResolution();
	break;
	case Core::GameMode::size+10:
	gameOptions->switchFullScreen();
	break;
	case Core::GameMode::size+11:
	gameOptions->switchShaders();
	break;
	case Core::GameMode::size+12:
	gameOptions->switchParticles();
	break;
	default:
		break;
	}
	menuGame->loadOptionsMenu();
	ac->loadData();
	gameOptions->saveData("testFiles/settings.txt");
}

float Aplication::getZoomAction() const {
	return zoomAction;
}

bool Aplication::isMode3D() const {
	return mode3D;
}

void Aplication::setMode3D(bool mode3D) {
	this->mode3D = mode3D;
}

void Aplication::setZoomAction(float zoomAction) {
	this->zoomAction = zoomAction;
}

float Aplication::getAngleAction() const {
	return angleAction;
}

void Aplication::setAngleAction(float angleAction) {
	this->angleAction = angleAction;
}

float Aplication::getAngleCamera() {
	return angleCamera;
}

void Aplication::setAngleCamera(float angle_) {
	angleCamera = angle_;
}

GameAction *Aplication::getActionGame() const {
	return actionGame;
}

GameMenu *Aplication::getMenuGame() const {
	return menuGame;
}

void Aplication::setActionGame(GameAction *actionGame) {
	this->actionGame = actionGame;
}

void Aplication::setMenuGame(GameMenu *menuGame) {
	this->menuGame = menuGame;
}

float Aplication::getFps() const {
	return fps;
}

void Aplication::setFps(float fps) {
	this->fps = fps;
}

