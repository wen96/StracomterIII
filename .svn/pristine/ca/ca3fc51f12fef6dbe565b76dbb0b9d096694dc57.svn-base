/*
 * ActionControl.cc
 *
 *  Created on: 04/11/2011
 *      Author: Chutaos team
 */

#include "GameAction.h"
#include "Aplication.h"

GameAction::GameAction(TWindow *w, HIDControl *hid_, TConsole *cons,
		Map *map_) {
	srand(time(NULL));
	window = w;
	world = new World();
	event = new EventControl();

	resources = ResourceManager::getInstance(world, event);

	manager = new EntityManager(resources);
	hid = hid_;
	scene = new Scene(manager, resources, 800.0, 600.0);

	event->setEntities(manager);
	status = Core::GameActionStatus::Normal;
	gameOver = false;
	mapa = map_;
	opti = new Optimization();

	menuPause = new TForm(800, 600, Point(400, 300));
	menuGameOver = new TForm(800, 600, Point(400, 300));
	loadingScreen = new TForm(800, 600, Point(400, 300));

	ia = new AI();

	features = CharacterFeature::getInstance();

	sManager = SceneManager::getInstance();
	//sManager->makeStracomterTree();

	consola = cons;

	ap = NULL;

	loadMap = 0;
}

GameAction::~GameAction() {
	this->Clear();
	if (manager != NULL) {
		delete manager;
	}
	if (world != NULL) {
		delete world;
	}
	if (scene != NULL) {
		delete scene;
	}
	if (event != NULL) {
		delete event;
	}

	menuPause->removeWorld();
	menuGameOver->removeWorld();
	loadingScreen->removeWorld();

	if (menuPause != NULL) {
		delete menuPause;
	}
	if (menuGameOver != NULL) {
		delete menuGameOver;
	}
	if (loadingScreen != NULL) {
		delete loadingScreen;
	}

	event = NULL;
	resources = NULL;
	manager = NULL;
	world = NULL;
	scene = NULL;
	status = Core::GameActionStatus::Normal;
	gameOver = false;
}

void GameAction::resetAction() {
	if (world != NULL) {
		delete world;
	}
	if (opti != NULL) {
		delete opti;
	}

	if (manager != NULL) {
		delete manager;
		manager = NULL;
	}

	if (scene != NULL) {
		delete scene;
		scene = NULL;
	}

	opti = new Optimization();
	world = new World();
	resources = ResourceManager::getInstance(world, event);
	manager = new EntityManager(resources);
	scene = new Scene(manager, resources, 800.0, 600.0);
	status = Core::GameActionStatus::Normal;
	loadMap = 0;
	gameOver = false;
	//sManager->makeStracomterTree();
	event->setEntities(manager);
	ia->Reset();
}

void GameAction::Clear() {
	manager->freeAllEntities();
	sManager->removeStracomterTree();
	//sManager->makeStracomterTree();
	resetAction();
}

void GameAction::StartUp() {

	debugMode = false;

	window->showMouseCursos(true);

	sManager->makeStracomterTree();

	ap = Aplication::getInstance();

	gMenu = ap->getMenuGame();

	sManager->addElement(gMenu,
			sManager->getNode(Graphics::DirectNodes::t_menu));
	//sManager->makeStracomterTree();

	resources->loadTextures();

	///////////////////////////// ----- //////////////////////////////////////////////////

	features->loadData("testFiles/features/f1.xml");

	consola->setScene(scene);
	consola->Init();

	mapa->setManager(manager);
	mapa->loadData();

	opti->CargarFuncionObjetivo(4773784, 1);
	opti->CalcularEnemigos();
	opti->CargarEnemigos(mapa);

	manager->addPointer();
	Point playerPos = mapa->getPlayerPos();
	//	manager->addSmartEntity(Point(300,300),0.0,Core::Entities::e_enemy1,NULL);
	manager->addSmartEntity(playerPos, 0.0, Core::Entities::e_explosive, NULL);
	manager->addSmartEntity(playerPos, 0.0, Core::Entities::e_especialist,
			NULL);
	manager->addSmartEntity(playerPos, 0.0, Core::Entities::e_tecnic, NULL);

	/*
	 *	Estas tres lineas hacen:
	 *		Inicializa la escena
	 *		Pinta la pantalla de carga
	 *		Actualiza el frame
	 */

	scene->Init(ia);
	//	scene->DrawMenu(loadingScreen); //TODO Aqui porque hace falta el player (que se carga en loadData) para poder pintarlo PROVISIONAL
	gMenu->setVisible(Graphics::Menus::m_loading);
	window->display();

	scene->setDebugOn(true);

	ia->setMap(mapa);
	ia->setManager(manager);
	ia->setControler(event);
	ia->Init(); //Pone el pathfinder de todas las entidades bot

	//TODO esto no va aquí.
	GLfloat luzAmbiente[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat luzDifusa[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat luzEspecular[] = { 0.9, 0.9, 0.9, 1.0 };
	GLfloat luzExponente[] = { 64.0, 64.0, 64.0, 1.0 };
	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT, GL_AMBIENT, luzAmbiente);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, luzDifusa);
	glMaterialfv(GL_FRONT, GL_SPECULAR, luzEspecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, luzExponente);

	glEnable(GL_DEPTH_TEST);
	sManager->InitializeScene();
	ap->setMode3D(false);
	ap->setZoomAction(-680);
	ap->setAngleAction(0);
	ap->setAngleCamera(-30);

	status = Core::GameActionStatus::Normal;

	gameTime.Start();
}

int GameAction::Update() {

	UpdateGraphics();
	int gameStatus = Core::GameMode::Action;
	int auxStatus = -1;
	switch (status) {
	case Core::GameActionStatus::Normal:
		gameTime.Unpause();
		//Cambiamos el menu a mostrar
		gMenu->setVisible(Graphics::Menus::m_none);

		//Actualizacion de eventos automaticos
		event->Update();

		// Player
		auxStatus = hid->actionControl(manager, event);
		if (auxStatus == Core::signalExit) {
			gameStatus = Core::GameMode::Salir;
		} else {
			status = (Core::GameActionStatus::Mode) auxStatus;
		}

		// NPCs
		ia->Update();

		// Mundo
		world->setFrame(window->getFrameTime());
		world->UpdateWorld();

		//Entity manager
		if (manager->Update()) {
			status = Core::GameActionStatus::GameOver;
		}
		if (manager->getBadPersons().size() == 0 && !debugMode) {
			status = Core::GameActionStatus::Win;
		}
		break;

	case Core::GameActionStatus::Paused:
		gameTime.Pause();
		gMenu->setVisible(Graphics::Menus::m_pause);
		auxStatus = gMenu->Update();
		if (auxStatus > -1) {
			if (auxStatus == 0) {
				status = (Core::GameActionStatus::Mode) auxStatus;
			} else {
				gameStatus = (Core::GameMode::Mode) auxStatus;
				this->Clear();
			}

		} else {
			if (auxStatus == Core::signalExit) {
				gameStatus = Core::GameMode::Salir;
			}
		}
		break;

	case Core::GameActionStatus::Console:
		gameTime.Pause();
		consola->Open();

		status = (Core::GameActionStatus::Mode) consola->getInput();

		parseCommand(consola->getCommand());

		if (status != 2) {
			consola->Close();
			gameTime.Unpause();
		}
		break;
	case Core::GameActionStatus::GameOver:
		gameTime.Pause();
		gMenu->setVisible(Graphics::Menus::m_gameover);
		auxStatus = (Core::GameMode::Mode) gMenu->Update();
		//Si se ha pulsado algun boton
		if (auxStatus > -1) {
			gameStatus = (Core::GameMode::Mode) auxStatus;
			this->Clear();
			//Si vamos a volver a lanzar el gameAction
			if (gameStatus == Core::GameMode::Action) {
				this->StartUp(); //Relanzamos el juego
			}

		} else {
			if (auxStatus == Core::signalExit) {
				gameStatus = Core::GameMode::Salir;
			}
		}
		break;

	case Core::GameActionStatus::Win:
		gameTime.Pause();

		gMenu->setVisible(Graphics::Menus::m_win);
		auxStatus = (Core::GameMode::Mode) gMenu->Update();
		//Si se ha pulsado algun boton
		if (auxStatus > -1) {
			gameStatus = (Core::GameMode::Mode) auxStatus;
			this->Clear();
			//Si vamos a volver a lanzar el gameAction
			if (gameStatus == Core::GameMode::Action) {
				this->StartUp(); //Relanzamos el juego
			}

		} else {
			if (auxStatus == Core::signalExit) {
				gameStatus = Core::GameMode::Salir;
			}
		}
		break;

	}

	return gameStatus;
}

void GameAction::Render() {
	if (!ap->isMode3D()) {
		glEnable(GL_LIGHTING);
		sManager->DrawScene();
	} else {
		glEnable(GL_BLEND);
		scene->Draw();
		if (gameOver) {
			scene->DrawMenu(menuGameOver);
		} else if (status == 1) {
			scene->DrawMenu(menuPause);
		} else if (status == 2) {
			consola->Render();
		}
	}

	//window->display();
}

int GameAction::Start() {
	//MAIN LOOP
	this->StartUp();

	while (window->isOpen() && loadMap != 1) {
		this->Render();

		this->Update();
	}

	this->Clear();

	return 0;
}

bool GameAction::getPaused() {
	return status == 1;
}

void GameAction::setPaused(bool pause_) {

}

int GameAction::parseCommand(vector<string> input) {
	int status = 0;
	if (input.size() > 0) {
		string command = input.front();
		input.erase(input.begin());
		vector<string> parameters = input;

		if (command == "spawn" || command == "add") {
			if (parameters.size() == 3) {
				int entidad = getEnum(parameters[0]);
				int x = atoi(parameters[1].c_str());
				int y = atoi(parameters[2].c_str());

				manager->addSmartEntity(Point(x, y), 0.0,
						(Core::Entities::Type) entidad, ia->getPf());
			}

		} else if (command == "kill") {

			if (parameters.size() == 1) {
				if (parameters[0] == "all") {

					vector<Entity *> enty = manager->getBadPersons();
					vector<Entity *>::iterator eIter;
					for(eIter = enty.begin(); eIter != enty.end(); eIter++){
						manager->addDead((*eIter)->getType(), (*eIter)->getId());
					}

					enty = manager->getIACompains();
					for(eIter = enty.begin(); eIter != enty.end(); eIter++){
						manager->addDead((*eIter)->getType(), (*eIter)->getId());
					}

				} else if (parameters[0] == "me") {
					int id = manager->getPlayer()->getId();
					int tipo = manager->getPlayer()->getType();

					manager->addDead((Core::Entities::Type) tipo, id);
				} else {
					int id = atoi(parameters[0].c_str());

					int tipo = manager->getIdPos(id);
					if (tipo != -1) {

						manager->addDead((Core::Entities::Type) tipo, id);
					}
				}
			}
		} else if (command == "move") {

			if (parameters.size() == 3) {
				int id = atoi(parameters[0].c_str());

				int x = atoi(parameters[1].c_str());
				int y = atoi(parameters[2].c_str());

				// Mover la entidad id a Point(x,y)
				Entity *entP = manager->getEntity(id);

				if (entP != NULL) {
					entP->setCenter(Point(x, y));
				} else {
					cout << "La entidad " << id << " no existe" << endl;
				}
			}
		} else if (command == "pos") {
			if (parameters.size() == 1) {
				int id = atoi(parameters[0].c_str());

				Entity *entP = manager->getEntity(id);

				if (entP != NULL) {
					cout << "La entidad " << id << " esta en la posición " << entP->getCenter() << endl;
				} else {
					cout << "La entidad " << id << " no existe" << endl;
				}
			} else if (parameters.size() == 0) {
				Entity *entP = manager->getPlayer();
				if (entP != NULL) {
					cout << "El player esta en: " << entP->getCenter() << endl;
				}
			}
		} else if (command == "setVision") {
			if (parameters.size() == 2) {

				int id = atoi(parameters[0].c_str());
				Entity *entP = manager->getEntity(id);

				string param = parameters[1];

				if (param == "1" || param == "true") {
					((Bot *) entP)->setBlindness(false);
				} else if (param == "0" || param == "false") {
					((Bot *) entP)->setBlindness(true);
				}
			}
		} else if (command == ":") {
			if (parameters.size() == 1) {
				if (parameters.front() == "god") {
					((Character *) (manager->getPlayer()))->setDead(
							!((Character *) (manager->getPlayer()))->isDead());
				} else if (parameters.front() == "ammo") {
					((Character *) (manager->getPlayer()))->setAmmunition(999);
				} else if (parameters.front() == "health") {
					((Character *) (manager->getPlayer()))->setHp(999);
				}
			}
		} else if (command == "tp") {

			if (parameters.size() == 2) {
				int x = atoi(parameters[0].c_str());
				int y = atoi(parameters[1].c_str());

				// Mover la entidad player a Point(x,y)
				Entity *entP = manager->getPlayer();

				if (entP != NULL) {
					entP->setCenter(Point(x, y));
				} else {
					cout << "El player no existe" << endl;
				}
			}
		} else if (command == "feature") {

			if (parameters.size() == 1) {
				string fich = parameters[0];

				if (features->loadData(fich)) {
					manager->setAllCharacterFeatures(features);
				}
			}
		} else if (command == "load") {
			if (parameters.size() == 1) {
				string fich = parameters[0];
				mapa->setMap(fich);
				if (mapa->loadData() == 1) {
					//cout << "Se ha podido cargar" << endl;
					this->Clear();
					this->StartUp();
				}
			}
		} else if (command == "team") {
			if (parameters.size() == 3) {
				int entidad = getEnum(parameters[0]);
				int x = atoi(parameters[1].c_str());
				int y = atoi(parameters[2].c_str());

				manager->addSmartEntity(Point(x, y), 0.0,
						(Core::Entities::Type) entidad, ia->getPf());
				manager->addSmartEntity(Point(x, y), 0.0,
						(Core::Entities::Type) entidad, ia->getPf());
				manager->addSmartEntity(Point(x, y), 0.0,
						(Core::Entities::Type) entidad, ia->getPf());
				manager->addSmartEntity(Point(x, y), 0.0,
						(Core::Entities::Type) entidad, ia->getPf());
				manager->addSmartEntity(Point(x, y), 0.0,
						(Core::Entities::Type) entidad, ia->getPf());
				manager->addSmartEntity(Point(x, y), 0.0,
						(Core::Entities::Type) entidad, ia->getPf());
				manager->addSmartEntity(Point(x, y), 0.0,
						(Core::Entities::Type) entidad, ia->getPf());
				manager->addSmartEntity(Point(x, y), 0.0,
						(Core::Entities::Type) entidad, ia->getPf());
				manager->addSmartEntity(Point(x, y), 0.0,
						(Core::Entities::Type) entidad, ia->getPf());
				manager->addSmartEntity(Point(x, y), 0.0,
						(Core::Entities::Type) entidad, ia->getPf());
			}
		} else if (command == "goto") {
			if (parameters.size() == 3) {
				int id = atoi(parameters[0].c_str());

				int x = atoi(parameters[1].c_str());
				int y = atoi(parameters[2].c_str());

				Entity *entP = manager->getEntity(id);

				if (entP != NULL) {
					if (manager->isDynamic(entP) && !manager->isPlayer(entP)) {
						Bot * bot = (Bot *) entP;

						bot->calculatePath(Point(x, y));
						bot->setDebug();
					}
				} else {
					cout << "La entidad " << id << " no existe" << endl;
				}
			}
		} else if (command == "restart") {
			this->Clear();
			this->StartUp();
		} else if (command == "mode") {
			if (parameters.size() == 1) {
				if (parameters[0] == "debug") {
					debugMode = true;
				} else if (parameters[0] == "normal") {
					debugMode = false;
				}
			}
		}
	}
	return status;
}

int GameAction::getEnum(string nombre) {
	int entidad = -1;

	if (nombre == "captain")
		entidad = 1;
	else if (nombre == "technic")
		entidad = 2;
	else if (nombre == "especialist")
		entidad = 3;
	else if (nombre == "explosives")
		entidad = 4;
	else if (nombre == "enemy1")
		entidad = 5;
	else if (nombre == "enemy2")
		entidad = 6;
	else if (nombre == "enemy3")
		entidad = 7;
	else if (nombre == "miniboss")
		entidad = 8;
	else if (nombre == "megaboss")
		entidad = 9;

	return entidad;

}

void GameAction::UpdateGraphics() {
	Point player = manager->getPlayer()->getCenter();
	int x = player.getX();
	int y = player.getY();
	//float w = window->getWidth();
	//float h = window->getHeight();

	Element *escenario =
			sManager->getNode(Graphics::DirectNodes::t_escena)->getItem();
	((Transform*) escenario)->setIdentity();
	((Transform*) escenario)->addTranslation(0, 0, ap->getZoomAction());
	((Transform*) escenario)->addRotationX(ap->getAngleCamera());
	((Transform*) escenario)->addRotationZ(ap->getAngleAction());
	((Transform*) escenario)->addTranslation(-1.0 * x, y, -100);
	((Transform*) escenario)->addScale(1, -1, 1);
	//((Transform*)escenario)->addScale(ap->getZoomAction(), ap->getZoomAction(), ap->getZoomAction());

	escenario = sManager->getNode(Graphics::DirectNodes::t_mapa)->getItem();
	((Transform*) escenario)->setIdentity();
	((Transform*) escenario)->addTranslation(0, 0, -600);
	((Transform*) escenario)->addTranslation(-1.0 * x, y, 0);
	((Transform*) escenario)->addScale(1, -1, 1);

	Element *luz =
			sManager->getNode(Graphics::DirectNodes::t_light0)->getItem();
	player.setZ(400);

	((Light*) luz)->setPosicion(player);

	string tmp = "";
	char aux[50];
	int enemigos = (manager->getBadPersons()).size();

	sprintf(aux, "%d", enemigos);
	tmp = aux;

	Text *txt;
	txt =
			((Text*) sManager->getNode(Graphics::DirectNodes::t_enemigos)->getItem());
	txt->setText(tmp);

	if (clkUpdateFPS.GetElapsedTime() > 500) {
		//Actualizacion de FPS
		int fps = (ap->getFps());
		sprintf(aux, "FPS:%d", fps);
		tmp = aux;
		txt =
				((Text*) sManager->getNode(Graphics::DirectNodes::t_fps)->getItem());
		txt->setText(tmp);
		clkUpdateFPS.Reset();

		txt =
				((Text*) sManager->getNode(Graphics::DirectNodes::t_time)->getItem());
		txt->setText(gameTime.toString());
	}
}
