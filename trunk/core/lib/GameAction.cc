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

	gameOptions = GameOptions::getInstance();

	manager = new EntityManager(resources);
	hid = hid_;
	scene = new Scene(manager, resources, gameOptions->getWindowWidth(), gameOptions->getWindowHeight());

	event->setEntities(manager);
	status = Core::GameActionStatus::Normal;
	gameOver = false;
	mapa = map_;
	mapa->setWorld(world);

	opti = new Optimization();

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
	scene = new Scene(manager, resources, gameOptions->getWindowWidth(), gameOptions->getWindowHeight());
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

	AnimationControl::getInstance()->freeAllAnimations();

	GameStatus *gs = GameStatus::getInstance();
	debugMode = false;

	manager->setPlayerType(gs->getTypePlayer());
	window->showMouseCursos(true);

	sManager->makeStracomterTree();

	sManager->setShaderActive(GameOptions::getInstance()->isUseShaders());

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

	//cout << Aplication::getInstance()->defaultMap << endl;


	/*switch(gs->getZona())
	{
	case 1:
		mapa->setMap("testFiles/maps/map6.xml");
		break;
	case 2:
		mapa->setMap("testFiles/maps/map4.xml");;
		break;
	case 3:
		mapa->setMap("testFiles/maps/map5.xml");
		break;
	case 4:
		mapa->setMap("testFiles/maps/map6.xml");
		break;
	case 5:
		mapa->setMap("testFiles/maps/map4.xml");
		break;
	case 6:
		mapa->setMap("testFiles/maps/map5.xml");
		break;
	case 7:
		mapa->setMap("testFiles/maps/map6.xml");
		break;
	case 8:
		mapa->setMap("testFiles/maps/finalMap.xml");
		break;
	default:
		mapa->setMap(Aplication::getInstance()->defaultMap);
		break;
	}*/

	mapa->setMap(selectionMap());

	mapa->setManager(manager);
	mapa->loadData();
	mapa->generateTriangulation();

	manager->setMap(mapa);

	ia->initMap(mapa, manager->getEntitiesbyType(Core::Entities::e_door));
	ia->setManager(manager);
	ia->setControler(event);
	ia->Init(); //Pone el pathfinder de todas las entidades bot

	//
	float dif;
	if(GameStatus::getInstance()->getNivelPlanta() != -1)
	{
		dif = GameStatus::getInstance()->getNivelPlanta()*gameOptions->getDificultad();
	}
	else
	{
		dif = gameOptions->getDificultad()*gameOptions->getDificultad();
	}
	opti->CargarFuncionObjetivo(mapa->getArea(), dif);
	opti->CalcularEnemigos();
	opti->CargarEnemigos(mapa, ia->getPf());

	//Cargar miniboss y megaboss
	if (GameStatus::getInstance()->getNivelPlanta()<8){//Si estamos en las plantas normales
		manager->addSmartEntity(mapa->miniBoss,0.0,Core::Entities::e_miniboss,ia->getPf());
	}else{
		manager->addSmartEntity(mapa->megaBoss,0.0,Core::Entities::e_megaboss,ia->getPf());
	}

	manager->addPointer();
	Point playerPos = mapa->getPlayerPos();

	Player * player = (Player *) manager->getPlayer();
	Vector2D f0 = player->getFormation()[0];
	Vector2D f1 = player->getFormation()[1];
	Vector2D f2 = player->getFormation()[2];

	switch(player->getType())
	{
	case Core::Entities::e_tecnic:
		manager->addSmartEntity(playerPos, 0.0, Core::Entities::e_explosive, ia->getPf(), f0);
		manager->addSmartEntity(playerPos, 0.0, Core::Entities::e_especialist, ia->getPf(), f1);
		manager->addSmartEntity(playerPos, 0.0, Core::Entities::e_captain, ia->getPf(), f2);
		break;
	case Core::Entities::e_especialist:
		manager->addSmartEntity(playerPos, 0.0, Core::Entities::e_explosive, ia->getPf(), f0);
		manager->addSmartEntity(playerPos, 0.0, Core::Entities::e_captain, ia->getPf(), f2);
		manager->addSmartEntity(playerPos, 0.0, Core::Entities::e_tecnic, ia->getPf(), f1);
		break;
	case Core::Entities::e_explosive:
		manager->addSmartEntity(playerPos, 0.0, Core::Entities::e_captain, ia->getPf(), f0);
		manager->addSmartEntity(playerPos, 0.0, Core::Entities::e_especialist, ia->getPf(), f2);
		manager->addSmartEntity(playerPos, 0.0, Core::Entities::e_tecnic, ia->getPf(), f1);
		break;
	default:
		manager->addSmartEntity(playerPos, 0.0, Core::Entities::e_explosive, ia->getPf(), f0);
		manager->addSmartEntity(playerPos, 0.0, Core::Entities::e_especialist, ia->getPf(), f2);
		manager->addSmartEntity(playerPos, 0.0, Core::Entities::e_tecnic, ia->getPf(), f1);
		break;
	}

	GameStatus::getInstance()->applyCharacterStatus(manager);

	string ruta = RESOURCESROOT;
	ruta += "texturas/van.jpg";

	/*
	 *	Estas tres lineas hacen:
	 *		Inicializa la escena
	 *		Pinta la pantalla de carga
	 *		Actualiza el frame
	 */

	scene->Init(ia);

	scene->setDebugOn(true);

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
	//	((Character*)player)->addObject(new Object(Core::Objects::ammo_pack_1));
	//	((Character*)player)->addObject(new Object(Core::Objects::ammo_pack_2));
	//	((Character*)player)->addObject(new Object(Core::Objects::health_pack_1));
	//	((Character*)player)->addObject(new Object(Core::Objects::health_pack_2));
	//	((Character*)player)->addObject(new Object(Core::Objects::health_pack_3));


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

		ParticleManager::getInstance()->Update();

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

			if(GameStatus::getInstance()->getNivelPlanta() == -1)
			{
				GameStatus::getInstance()->initializeVectorPlayers();
				GameStatus::getInstance()->setNivelPlanta(-1);
				GameStatus::getInstance()->setZona(3);
				GameStatus::getInstance()->setPuntuacionPlayer(0);
				GameStatus::getInstance()->setTypePlayer(Core::Entities::e_captain);

				gameStatus = (Core::GameMode::Mode) auxStatus;
				this->Clear();
				//Si vamos a volver a lanzar el gameAction
				if (gameStatus == Core::GameMode::Action) {
					this->StartUp(); //Relanzamos el juego
				}
			}
			else
			{
				//AÑADIMOS LAS RECOMPENSAS DE ESE NIVEL
				vector<Entity*> ent = manager->getGoodPersons();
				for(unsigned int i = 0; i< ent.size(); i++)
					((Character*)ent[i])->addObject(new Object(ap->getGameSelections()->getRecompensa()));
				//cout<<"PLANTA ANTES DE INCREMENTAR: "<<GameStatus::getInstance()->getNivelPlanta()<<endl;
				if(GameStatus::getInstance()->getNivelPlanta() != -1)
					GameStatus::getInstance()->incrementLevel();
				//cout<<"PLANTA DESPUES DE INCREMENTAR: "<<GameStatus::getInstance()->getNivelPlanta()<<endl;
				GameStatus::getInstance()->getCharacters(manager);
				GameStatus::getInstance()->saveData();
				gameStatus = (Core::GameMode::Mode) auxStatus;
				this->Clear();
				//Si vamos a volver a lanzar el gameAction
				if (gameStatus == Core::GameMode::Action) {
					this->StartUp(); //Relanzamos el juego
				}
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
			scene->DrawMenu(gMenu->getMenu(Graphics::Menus::m_gameover));
		} else if (status == 1) {
			scene->DrawMenu(gMenu->getMenu(Graphics::Menus::m_pause));
		} else if (status == 2) {
			consola->Render();
		}
	}
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

				}else if(parameters[0] == "bad"){
					vector<Entity *> enty = manager->getBadPersons();
					vector<Entity *>::iterator eIter;
					for(eIter = enty.begin(); eIter != enty.end(); eIter++){
						manager->addDead((*eIter)->getType(), (*eIter)->getId());
					}
				}else if (parameters[0] == "me") {
					int id = manager->getPlayer()->getId();
					int tipo = manager->getPlayer()->getType();

					manager->addDead((Core::Entities::Type) tipo, id);
				} else {
					int id = atoi(parameters[0].c_str());

					if(id >= 0){
						int tipo = manager->getIdPos(id);
						if (tipo != -1)
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

				if(entidad != -1)
					for(int i = 0; i < 10; i++)
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
		} else if (command == "shader"){
			SceneManager *sm = SceneManager::getInstance();
			int nParam = parameters.size();

			if (nParam == 1){

				if(parameters[0] == "true"){
					sm->setShaderActive(true);
				}else if(parameters[0] == "false"){
					sm->setShaderActive(false);
				}

			}else if(nParam == 2){

				if(parameters[0] == "use"){

					string sh = parameters[1];
					if(sh == "Phong"){
						sm->setCurrentShader(Graphics::Shader::Phong);
					}else if (sh == "CellShading"){
						sm->setCurrentShader(Graphics::Shader::CellShading);
					}else if( sh == "Pruebas"){
						sm->setCurrentShader(Graphics::Shader::Pruebas);
					}else if( sh == "None"){
						sm->setCurrentShader(Graphics::Shader::None);
					}
				}
			}
		}else if(command == "isVisible"){

			int nParam = parameters.size();
			string vis = "";
			Entity *ent = NULL;
			if (nParam == 1){
				ent = manager->getPlayer();
				vis = parameters[0];
			}else if(nParam == 2){
				int id = atoi(parameters[0].c_str());
				vis = parameters[1];
				if(id > 0)
					ent = manager->getEntity(id);
			}

			if(ent != NULL){
				if(vis == "1" || vis == "true"){
					ent->setVisible(true);
				}else if (vis == "0" || vis == "false"){
					ent->setVisible(false);
				}
			}
		}else if(command == "info"){
			int nParam = parameters.size();
			if (nParam == 1){
				int id = atoi(parameters[0].c_str());
				Character *ent = (Character *) manager->getEntity(id);

				if(ent != NULL){
					cout << "Posicion: " << ent->getCenter() << endl;
					cout << "Angulo: " << ent->getAngle() << endl;
					cout << "Vida: " << ent->getHp() << "/" << ent->getMaXhp() << endl;
					cout << "Municion: " << ent->getAmmunition() << endl;
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
	TListener::setPosition(player);//POSICION DE ESCUCHA DEL JUEGO

	AnimationControl::getInstance()->Update();

	//float w = window->getWidth();
	//float h = window->getHeight();

	Element *escenario = sManager->getNode(Graphics::DirectNodes::t_escena)->getItem();
	((Transform*) escenario)->setIdentity();
	((Transform*) escenario)->addTranslation(0, 0, ap->getZoomAction());
	((Transform*) escenario)->addRotationX(ap->getAngleCamera());
	((Transform*) escenario)->addRotationZ(ap->getAngleAction());
	//	((Transform*) escenario)->addRotationZ(manager->getPlayer()->getAngle() + 90);
	((Transform*) escenario)->addTranslation(-1.0 * x, y, -100);
	((Transform*) escenario)->addScale(1, -1, 1);
	//((Transform*)escenario)->addScale(ap->getZoomAction(), ap->getZoomAction(), ap->getZoomAction());

	escenario = sManager->getNode(Graphics::DirectNodes::t_mapa)->getItem();
	((Transform*) escenario)->setIdentity();
	((Transform*) escenario)->addTranslation(0, 0, -600);
	((Transform*) escenario)->addTranslation(-1.0 * x, y, 0);
	((Transform*) escenario)->addScale(1, -1, 1);

	Element *luz = sManager->getNode(Graphics::DirectNodes::t_light2)->getItem();
	player.setZ(700);
	player.setY(player.getY() - 400);

	((Light*) luz)->setPosicion(player);

	string tmp = "";
	char aux[50];
	int enemigos = (manager->getBadPersons()).size();

	sprintf(aux, "%d", enemigos);
	tmp = aux;

	Text *txt;
	txt = ((Text*) sManager->getNode(Graphics::DirectNodes::t_enemigos)->getItem());
	txt->setText(tmp);

	if (clkUpdateFPS.getElapsedMiliseconds() > 500) {
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


string GameAction::selectionMap() {

	GameStatus *gs = GameStatus::getInstance();
	string mapa = Aplication::getInstance()->defaultMap;

	int num_mapa = gs->getNivelPlanta()*10 + gs->getZona();

	if(gs->getNivelPlanta() == -1)
	{
		ifstream f("editorMap.xml",ios::in);
		if (f){
			mapa = "editorMap.xml";
			f.close();
		}
	}
	else if(gs->getNivelPlanta() == 8)
	{
		mapa = "testFiles/maps/finalMap.xml";
	}
	else
	{
		switch(gs->getZona())
		{
		case 1:
		case 2:

			switch(gs->getNivelPlanta())
			{
			case 1:
			case 5:
				mapa = "testFiles/maps/mapP1.xml";
				break;
			case 2:
			case 6:
				mapa = "testFiles/maps/mapP2.xml";
				break;
			case 3:
			case 7:
				mapa = "testFiles/maps/mapP3.xml";
				break;
			case 4:
				mapa = "testFiles/maps/mapP4.xml";
				break;
			}
			break;
		case 3:
		case 4:

			switch(gs->getNivelPlanta())
			{
			case 1:
				mapa = "testFiles/maps/mapM1.xml";
				break;
			case 5:
				mapa = "testFiles/maps/mapG1.xml";
				break;
			case 2:
				mapa = "testFiles/maps/mapM1.xml";
				break;
			case 6:
				mapa = "testFiles/maps/mapG2.xml";
				break;
			case 3:
				mapa = "testFiles/maps/mapG3.xml";
				break;
			case 7:
				mapa = "testFiles/maps/mapM3.xml";
				break;
			case 4:
				mapa = "testFiles/maps/mapM4.xml";
				break;
			}
			break;

		case 5:
		case 6:

			switch(gs->getNivelPlanta())
			{
			case 1:
			case 5:
				mapa = "testFiles/maps/mapG1.xml";
				break;
			case 2:
			case 6:
				mapa = "testFiles/maps/mapG2.xml";
				break;
			case 3:
			case 7:
				mapa = "testFiles/maps/mapG3.xml";
				break;
			case 4:
				mapa = "testFiles/maps/mapG4.xml";
				break;
			}
			break;
		}
	}

	return mapa;

}
