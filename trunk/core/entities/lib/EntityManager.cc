/*
 * EntityManger.cc
 *
 *  Created on: 04/11/2011
 *      Author: Chutaos Team
 */

#include "EntityManager.h"
#include "SceneManager.h"
#include "AnimationControl.h"

EntityManager::EntityManager(ResourceManager *r) {
	numEntities = 0;
	nextId = 0;
	resources = r;
	//Preparado del vector
	vector<Entity*> aux;
	entidades = vector<vector<Entity*> >(Core::Entities::size, aux);
	sManager = SceneManager::getInstance();
	playerType = Core::Entities::e_captain;
}

EntityManager::~EntityManager() {
	numEntities = 0;
	nextId = 0; //TODO
	resources = NULL;
	sManager = NULL;
	vector<vector<Entity*> >::iterator iterPadre;
	vector<Entity*>::iterator iter;
	Entity *entidad = NULL;

	iterPadre = entidades.begin();
	while (!entidades.empty()) {
		iter = (*iterPadre).begin();
		while (!(*iterPadre).empty()) {
			entidad = *iter;
			if (entidad != NULL) {
				delete entidad;
			}
			iter = (*iterPadre).erase(iter);

		}
		(*iterPadre).clear();
		iterPadre = entidades.erase(iterPadre);
	}
	entidades.clear();
}

void EntityManager::freeAllEntities() {
	//Si es character pones: sManager->removeCharacter(entidad);
	vector<vector<Entity*> >::iterator iterPadre;
	vector<Entity*>::iterator iter;
	Entity *entidad = NULL;

	iterPadre = entidades.begin();
	while (!entidades.empty()) {
		iter = (*iterPadre).begin();
		while (!(*iterPadre).empty()) {
			entidad = *iter;
			if (isGood(entidad) || isBad(entidad)) {
				sManager->removeCharacter(entidad);
			} else {
				sManager->removeElement(entidad);
			}

			if (entidad != NULL) {
				delete entidad;
			}
			iter = (*iterPadre).erase(iter);

		}
		(*iterPadre).clear();
		iterPadre = entidades.erase(iterPadre);
	}
}

void EntityManager::setAllCharacterFeatures(CharacterFeature *f) {
	vector<Entity*> entitiesChar = getCharacters();
	vector<Entity*>::iterator iterChar;
	for (iterChar = entitiesChar.begin(); iterChar != entitiesChar.end(); iterChar++) {
		((Character*) (*iterChar))->setFeatures(f);
	}
}

Core::Entities::Type EntityManager::getPlayerType() const {
	return playerType;
}

void EntityManager::setPlayerType(Core::Entities::Type playerType) {
	this->playerType = playerType;
}

void EntityManager::copiar(const EntityManager &obj) {
	this->numEntities = obj.numEntities;
	this->nextId = obj.nextId;

	this->idPosition = obj.idPosition;

	//Preparado del vector
	vector<Entity*> aux;
	for (int i = 0; i < Core::Entities::size; i++) {
		entidades.push_back(aux);
	}
	Entity *pl = NULL;
	for (unsigned int i = 0; i < obj.entidades.size(); i++) {
		for (unsigned int j = 0; j < obj.entidades[i].size(); j++) {
			if (obj.entidades[i][j] != NULL) {
				switch (obj.entidades[i][j]->getType()) {
				case Core::Entities::e_captain:
				case Core::Entities::e_tecnic:
				case Core::Entities::e_especialist:
				case Core::Entities::e_explosive:
					pl = new Player(*((Player*) obj.entidades[i][j]));
					this->entidades[i].push_back(pl);
					break;

				case Core::Entities::e_enemy1:
				case Core::Entities::e_enemy2:
				case Core::Entities::e_enemy3:
				case Core::Entities::e_miniboss:
				case Core::Entities::e_megaboss:
					//TODO pl = new Bot(*((Bot*)obj.entidades[i][j]));
					this->entidades[i].push_back(pl);
					break;

				case Core::Entities::e_wall:
					pl = new Wall(*((Wall*) obj.entidades[i][j]));
					this->entidades[i].push_back(pl);
					break;

				default:
					cerr << "Warning: Se intenta copiar algo que no existe\n";
					break;

				}
			}
		}
	}

}

EntityManager::EntityManager(const EntityManager &obj) {
	copiar(obj);
}

EntityManager & EntityManager::operator =(const EntityManager & obj) {
	if (this != &obj) {
		this->~EntityManager();
		copiar(obj);
	}
	return *this;
}

vector<Entity*> EntityManager::getEntities() {

	vector<Entity*> en;
	for (unsigned int i = 0; i < entidades.size(); i++) {
		if (entidades[i].size() > 0)
			en.insert(en.end(), entidades[i].begin(), entidades[i].end());
	}
	return en;
}

vector<Entity*> EntityManager::getDynamicEntities() {

	vector<Entity*> en;
	en = getCharacters();
	return en;
}

int EntityManager::getNumEntities() {
	return numEntities;
}

void EntityManager::addPlayer(Point p, float angle) {
	Entity *ent = new Player(nextId, p, angle, resources, playerType);
	entidades[playerType].push_back(ent);

	while (nextId >= (int) idPosition.size())
		idPosition.push_back(-1);
	idPosition[nextId] = playerType;
	sManager->addCharacter(ent, sManager->getNode(Graphics::DirectNodes::t_escena));

	numEntities++;
	nextId++;
}

Entity * EntityManager::addObstacle(Core::Obstacles::Type t, Point center_, float angle_) {
	Entity *ent = new Obstacle(t, resources, center_, angle_);
	entidades[Core::Entities::e_obstacle].push_back(ent);

	while (nextId >= (int) idPosition.size())
		idPosition.push_back(-1);
	idPosition[nextId] = Core::Entities::e_obstacle;

	Transform *trans = new Transform();
	trans->addTranslation(center_);
	trans->addRotationZ(angle_);

	ent->setAngle(angle_);
	ent->setId(nextId);

	sManager->addElement(trans, sManager->getNode(Graphics::DirectNodes::t_escena));
	sManager->addElement(ent, trans->getNodo());
	ent->setPadre(trans->getNodo());

	numEntities++;
	nextId++;

	return ent;
}

void EntityManager::addObstacle(Core::Obstacles::Type t, Point center_, float angle_, string ruta_, int widht_, int height_, int alto_) {

	Entity *ent = new Obstacle(t, resources, center_, angle_, ruta_, widht_, height_, alto_);
	entidades[Core::Entities::e_obstacle].push_back(ent);

	while (nextId >= (int) idPosition.size())
		idPosition.push_back(-1);
	idPosition[nextId] = Core::Entities::e_obstacle;

	Transform *trans = new Transform();
	trans->addTranslation(center_);
	trans->addRotationZ(angle_);

	ent->setAngle(angle_);
	ent->setId(nextId);

	sManager->addElement(trans, sManager->getNode(Graphics::DirectNodes::t_escena));

	sManager->addElement(ent, trans->getNodo());
	numEntities++;

	nextId++;
}

Entity *  EntityManager::addObject(Core::Objects::Class c, Point center_, float angle_) {

	Entity *ent = new Object(Core::Objects::obj_dynamics, c, resources, center_, angle_);
	entidades[Core::Entities::e_objects].push_back(ent);


	while (nextId >= (int) idPosition.size())
		idPosition.push_back(-1);
	idPosition[nextId] = Core::Entities::e_objects;

	Transform *trans = new Transform();
	trans->addTranslation(center_);
	trans->addRotationZ(angle_);

	ent->setAngle(angle_);
	ent->setId(nextId);
	sManager->addElement(trans, sManager->getNode(Graphics::DirectNodes::t_escena));

	sManager->addElement(ent, trans->getNodo());
	ent->setPadre(trans->getNodo());
	numEntities++;

	nextId++;

	AnimationControl::getInstance()->addRotationInfinite(ent,trans,10000);

	return ent;
}
void EntityManager::addPointer() {

	Entity *ent = new Pointer(nextId, resources);

	entidades[Core::Entities::e_pointer].push_back(ent);

	while (nextId >= (int) idPosition.size())
		idPosition.push_back(-1);
	idPosition[nextId] = Core::Entities::e_pointer;
	sManager->addElement(ent, sManager->getNode(Graphics::DirectNodes::t_escena));

	numEntities++;
	nextId++;
}

Entity * EntityManager::addDoor(Point p, vector<Point> contorno, vector<int> vNodes, Pathfinder *pf_) {

	Entity *ent = new Door(nextId, p, contorno, vNodes, pf_);

	entidades[Core::Entities::e_door].push_back(ent);

	while (nextId >= (int) idPosition.size())
		idPosition.push_back(-1);
	idPosition[nextId] = Core::Entities::e_door;
	sManager->addElement(ent, sManager->getNode(Graphics::DirectNodes::t_escena));

	numEntities++;
	nextId++;

	return ent;
}

void EntityManager::addSmartEntity(Point p, float angle, Core::Entities::Type t, Pathfinder *pf_, Vector2D formation) {

	if (t > 0 && t <= 4) { // Compañero
		if (t != playerType) {
			Entity *ent = NULL;
			Player * player = (Player *) getPlayer();
			switch (t) {
			case 1:
				ent = new Captain(nextId, p, angle, resources, t, pf_);
				break;
			case 2:
				ent = new Technic(nextId, p, angle, resources, t, pf_);
				break;
			case 3:
				ent = new Especialist(nextId, p, angle, resources, t, pf_);
				break;
			case 4:
				ent = new Explosive(nextId, p, angle, resources, t, pf_);
				break;
			default:
				break;
			}
			((Bot *) ent)->setOffset(formation);

			if (player != NULL) {
				((Bot *) ent)->setLeader(player->getMovementComp());
			}

			if (ent != NULL) {
				int miraX = p.getX() + cos(angle) * 500;
				int miraY = p.getY() - sin(angle) * 500;
				Point mira(miraX, miraY);
				((Character *) ent)->generateVisionRotation(mira);
				((Character *) ent)->generateRay(mira);
			}

			entidades[t].push_back(ent);

			/*int miraX = p.getX() + cos(angle)*500;
			 int miraY = p.getY() - sin(angle)*500;
			 Point mira(miraX, miraY);
			 ((Character *) ent)->generateVisionRotation(mira);
			 ((Character *) ent)->generateRay(mira);*/

			while (nextId >= (int) idPosition.size())
				idPosition.push_back(-1);
			idPosition[nextId] = t;

			sManager->addCharacter(ent, sManager->getNode(Graphics::DirectNodes::t_escena));

			numEntities++;
			nextId++;
		}
	} else if (t > 4 && t <= 9) { // Enemigo

		vector<Point> patrol;
		Tri patP = map->getTri(p);
		patrol.push_back(patP.getA());
		patrol.push_back(patP.getB());
		patrol.push_back(patP.getC());

		Entity *ent = new Enemy(nextId, p, angle, resources, t, pf_, patrol);

		int miraX = p.getX() + cos(angle) * 500;
		int miraY = p.getY() - sin(angle) * 500;
		Point mira(miraX, miraY);
		((Character *) ent)->generateVisionRotation(mira);
		((Character *) ent)->generateRay(mira);

		entidades[t].push_back(ent);

		while (nextId >= (int) idPosition.size())
			idPosition.push_back(-1);
		idPosition[nextId] = t;

		sManager->addCharacter(ent, sManager->getNode(Graphics::DirectNodes::t_escena));

		numEntities++;
		nextId++;
	} else if (t > 7 && t <= 9) { // Jefe

	}
}

Entity * EntityManager::addWall(vector<Point> vP, float angle, Color<float> c) {
	Entity *ent = new Wall(nextId, Point(0, 0), angle, resources, c, vP);
	entidades[Core::Entities::e_wall].push_back(ent);

	//cout << "EM: " << ent->getIdDisplay() << endl;
	while (nextId >= (int) idPosition.size())
		idPosition.push_back(-1);
	idPosition[nextId] = Core::Entities::e_wall;

	sManager->addElement(ent, sManager->getNode(Graphics::DirectNodes::t_escena));

	numEntities++;
	nextId++;

	return ent;
}

void EntityManager::addFloor(vector<Point> vP, float angle, Color<float> c) {
	Entity *ent = new Floor(nextId, Point(0, 0), angle, resources, c, vP);
	entidades[Core::Entities::e_floor].push_back(ent);
	//	cout << "Ahora las paredes miden " << entidades[Core::Entities::e_wall].size() << endl;

	while (nextId >= (int) idPosition.size())
		idPosition.push_back(-1);
	idPosition[nextId] = Core::Entities::e_floor;

	sManager->addElement(ent, sManager->getNode(Graphics::DirectNodes::t_escena));

	numEntities++;
	nextId++;
}

Entity* EntityManager::getFloor() {

	if (entidades[Core::Entities::e_floor].size() > 0)
		return entidades[Core::Entities::e_floor][0];
	return NULL;
}

void EntityManager::removeFloors() {
	//	cout << "Quiero cargarmela " << entidades[Core::Entities::e_floor].size() << endl;
	Entity * entidad = NULL;
	vector<Entity*>::iterator iter;
	for (iter = entidades[Core::Entities::e_floor].begin(); iter != entidades[Core::Entities::e_floor].end(); iter++) {
		entidad = *iter;
		sManager->removeElement(entidad);
		entidades[Core::Entities::e_floor].erase(iter);
		delete entidad;
		entidad = NULL;
		//			cout << "Me la he cargado" << endl;
		break;
	}
}

void EntityManager::removeBot(int id) {
	Entity *entidad;
	vector<Entity*>::iterator iter;
	for (iter = entidades[Core::Entities::e_enemy2].begin(); iter != entidades[Core::Entities::e_enemy2].end(); iter++) {
		if ((*iter)->getId() == id) {
			entidad = *iter;
			entidades[Core::Entities::e_enemy2].erase(iter);
			delete entidad;
			entidad = NULL;
			break;
		}
	}
	numEntities--;

}

void EntityManager::removeEntity(int id) {

	if (id < (int) idPosition.size()) {
		int tipo = idPosition[id];
		if (tipo != -1) {
			Entity *entidad;
			vector<Entity*>::iterator iter;
			for (iter = entidades[tipo].begin(); iter != entidades[tipo].end(); iter++) {
				if ((*iter)->getId() == id) {
					entidad = *iter;
					entidades[tipo].erase(iter);
					delete entidad;
					entidad = NULL;
					break;
				}
			}

		}
	}

}

Entity*
EntityManager::getPlayer() {
	if (entidades[playerType].size() > 0) {
		return *entidades[playerType].begin();
	} else {
		//cerr << "Player no creado \n";
		return NULL;
	}
}

Entity*
EntityManager::getPointer() {
	if (entidades[Core::Entities::e_pointer].size() > 0) {
		return *entidades[Core::Entities::e_pointer].begin();
	} else {
		//cerr << "Player no creado \n";
		return NULL;
	}
}

vector<Entity*>&
EntityManager::getEntitiesbyType(Core::Entities::Type type_) {
	return entidades[type_];
}

void EntityManager::removeType(Core::Entities::Type type_, int id_) {
	Entity *entidad;
	vector<Entity*>::iterator iter;
	iter = entidades[type_].begin();

	if (type_ != Core::Entities::e_objects) {
		while (iter != entidades[type_].end()) {
			if ((*iter)->getId() == id_) {
				entidad = (*iter);
				sManager->removeCharacter(entidad);
				iter = entidades[type_].erase(iter);
				delete entidad;
				entidad = NULL;
				break;
			}
			iter++;
		}
	} else {
		while (iter != entidades[type_].end()) {
			if ((*iter)->getId() == id_) {
				entidad = (*iter);
				sManager->removeElement(entidad);
				iter = entidades[type_].erase(iter);
				delete entidad;
				entidad = NULL;
				break;
			}
			iter++;
		}
	}
}

vector<Entity*> EntityManager::getGoodPersons() {
	vector<Entity*> en;
	if (!entidades[Core::Entities::e_captain].empty()) {
		en.insert(en.end(), entidades[Core::Entities::e_captain].begin(), entidades[Core::Entities::e_captain].end());
	}
	if (!entidades[Core::Entities::e_tecnic].empty()) {
		en.insert(en.end(), entidades[Core::Entities::e_tecnic].begin(), entidades[Core::Entities::e_tecnic].end());
	}
	if (!entidades[Core::Entities::e_explosive].empty()) {
		en.insert(en.end(), entidades[Core::Entities::e_explosive].begin(), entidades[Core::Entities::e_explosive].end());
	}
	if (!entidades[Core::Entities::e_especialist].empty()) {
		en.insert(en.end(), entidades[Core::Entities::e_especialist].begin(), entidades[Core::Entities::e_especialist].end());
	}
	return en;
}

vector<Entity*> EntityManager::getIACompains() {
	vector<Entity*> en;
	if (playerType != Core::Entities::e_captain && !entidades[Core::Entities::e_captain].empty()) {
		en.insert(en.end(), entidades[Core::Entities::e_captain].begin(), entidades[Core::Entities::e_captain].end());
	}
	if (playerType != Core::Entities::e_tecnic && !entidades[Core::Entities::e_tecnic].empty()) {
		en.insert(en.end(), entidades[Core::Entities::e_tecnic].begin(), entidades[Core::Entities::e_tecnic].end());
	}
	if (playerType != Core::Entities::e_explosive && !entidades[Core::Entities::e_explosive].empty()) {
		en.insert(en.end(), entidades[Core::Entities::e_explosive].begin(), entidades[Core::Entities::e_explosive].end());
	}
	if (playerType != Core::Entities::e_especialist && !entidades[Core::Entities::e_especialist].empty()) {
		en.insert(en.end(), entidades[Core::Entities::e_especialist].begin(), entidades[Core::Entities::e_especialist].end());
	}
	return en;
}

vector<Entity*> EntityManager::getBadPersons() {
	vector<Entity*> en;
	if (!entidades[Core::Entities::e_enemy1].empty()) {
		en.insert(en.end(), entidades[Core::Entities::e_enemy1].begin(), entidades[Core::Entities::e_enemy1].end());
	}
	if (!entidades[Core::Entities::e_enemy2].empty()) {
		en.insert(en.end(), entidades[Core::Entities::e_enemy2].begin(), entidades[Core::Entities::e_enemy2].end());
	}
	if (!entidades[Core::Entities::e_enemy3].empty()) {
		en.insert(en.end(), entidades[Core::Entities::e_enemy3].begin(), entidades[Core::Entities::e_enemy3].end());
	}
	if (!entidades[Core::Entities::e_miniboss].empty()) {
		en.insert(en.end(), entidades[Core::Entities::e_miniboss].begin(), entidades[Core::Entities::e_miniboss].end());
	}
	if (!entidades[Core::Entities::e_megaboss].empty()) {
		en.insert(en.end(), entidades[Core::Entities::e_megaboss].begin(), entidades[Core::Entities::e_megaboss].end());
	}
	return en;
}

vector<Entity*> EntityManager::getCharacters() {
	vector<Entity*> good = getGoodPersons();
	vector<Entity*> bad = getBadPersons();
	good.insert(good.end(), bad.begin(), bad.end());

	return good;
}

vector<Entity*> EntityManager::getBots() {

	vector<Entity*> en; //TODO
	if (playerType != Core::Entities::e_tecnic) {
		if (!entidades[Core::Entities::e_tecnic].empty()) {
			en.insert(en.end(), entidades[Core::Entities::e_tecnic].begin(), entidades[Core::Entities::e_tecnic].end());
		}
	}
	if (playerType != Core::Entities::e_explosive) {
		if (!entidades[Core::Entities::e_explosive].empty()) {
			en.insert(en.end(), entidades[Core::Entities::e_explosive].begin(), entidades[Core::Entities::e_explosive].end());
		}
	}
	if (playerType != Core::Entities::e_especialist) {
		if (!entidades[Core::Entities::e_especialist].empty()) {
			en.insert(en.end(), entidades[Core::Entities::e_especialist].begin(), entidades[Core::Entities::e_especialist].end());
		}
	}
	if (playerType != Core::Entities::e_captain) {
		if (!entidades[Core::Entities::e_captain].empty()) {
			en.insert(en.end(), entidades[Core::Entities::e_captain].begin(), entidades[Core::Entities::e_captain].end());
		}
	}

	vector<Entity*> bad = getBadPersons();
	en.insert(en.end(), bad.begin(), bad.end());

	return en;
}

void EntityManager::addDead(Core::Entities::Type type_, int id_) {
	ForDead dead;
	dead.type = type_;
	dead.id = id_;
	deads.push_back(dead);
}

bool EntityManager::Update() {
	bool isDead = false;
	vector<ForDead>::iterator iter;
	iter = deads.begin();
	while (!deads.empty()) {
		if ((*iter).type == playerType) {
			isDead = true;
		} else {
			idPosition[(*iter).id] = -1;
			removeType((*iter).type, (*iter).id);
		}
		deads.erase(iter);
		iter = deads.begin();
	}

	//Control de Recompensas.

	vector<Entity*> obj = getEntitiesbyType(Core::Entities::e_objects);

	for (unsigned int i = 0; i < obj.size(); i++) {
		if (obj[i]->getBody()->TestPoint(getPlayer()->getCenter())) {
			((Object*) obj[i])->Apply((Character*) getPlayer());
			//((Object*)obj[i])->setObjectClass(Core::Objects::sniper);
			AnimationControl::getInstance()->rermoveAnimation(((Object*)obj[i])->myAnimation);
			addDead(Core::Entities::e_objects, obj[i]->getId());
		}
	}

	vector<Entity*> cha = getCharacters();

	int aux;
	for (unsigned int i = 0; i < cha.size(); i++) {
		if (((Character*) cha[i])->getMovementComp()->getMeEstoyMoviendo()) {
			if (cha[i]->getClock()->getElapsedMiliseconds() >= 200) {
				aux = (cha[i]->getIdDisplay() % 5 + 1) % 5;
				cha[i]->setIdDisplay(cha[i]->getType() * 5 + aux);
				cha[i]->getClock()->Reset();
				if (aux == 1 || aux == 3){
					AudioControl::getInstance()->playSoundStep(cha[i]->getCenter());
				}
			}
		} else {
			cha[i]->setIdDisplay(cha[i]->getType() * 5);
		}
	}

	UpdateGraphics();

	return isDead;
}

int EntityManager::getIdPos(int id) {
	int pos = -1;

	if (id < (int) idPosition.size()) {
		pos = idPosition[id];
	}

	return pos;
}

Entity * EntityManager::getEntity(int id) {
	Entity *pEnt = NULL;
	if (id < (int) idPosition.size()) {
		int vec = idPosition[id];
		if (vec >= 0) {
			vector<Entity*>::iterator iter;
			for (iter = entidades[vec].begin(); iter != entidades[vec].end(); iter++) {
				if ((*iter)->getId() == id) {
					pEnt = *iter;
					break;
				}
			}
		}
	}

	return pEnt;
}

bool EntityManager::isDynamic(Entity *entidad) {
	bool dynamic = false;
	if (entidad != NULL) {
		switch (entidad->getType()) {
		case Core::Entities::e_captain:
		case Core::Entities::e_especialist:
		case Core::Entities::e_explosive:
		case Core::Entities::e_tecnic:
		case Core::Entities::e_enemy1:
		case Core::Entities::e_enemy2:
		case Core::Entities::e_enemy3:
		case Core::Entities::e_megaboss:
		case Core::Entities::e_miniboss:
			dynamic = true;
			break;
		default:
			break;
		}
	}
	return dynamic;
}

bool EntityManager::isGood(Entity *entidad) {
	bool good = false;
	if (entidad != NULL) {
		switch (entidad->getType()) {
		case Core::Entities::e_captain:
		case Core::Entities::e_especialist:
		case Core::Entities::e_explosive:
		case Core::Entities::e_tecnic:
			good = true;
			break;
		default:
			break;
		}
	}
	return good;
}

bool EntityManager::isBad(Entity *entidad) {
	bool bad = false;
	if (entidad != NULL) {
		switch (entidad->getType()) {
		case Core::Entities::e_enemy1:
		case Core::Entities::e_enemy2:
		case Core::Entities::e_enemy3:
		case Core::Entities::e_megaboss:
		case Core::Entities::e_miniboss:
			bad = true;
			break;
		default:
			break;
		}
	}
	return bad;
}

bool EntityManager::isNeutral(Entity *entidad) {
	return (!isGood(entidad) && !isBad(entidad));
}

bool EntityManager::isPlayer(Entity *entidad) {
	bool player = false;

	if (entidad != NULL && entidad->getType() == playerType) {
		player = true;
	}

	return player;
}

void EntityManager::UpdateGraphics() {

	Entity * py = getPlayer();
	Point Posplayer;
	if (py != NULL)
		Posplayer = py->getCenter();

	GraphicNode *padre;
	Element *elem;
	vector<Entity*> en = getDynamicEntities();
	Point pos;
	float angle;
	GraphicNode* Nray;
	GraphicNode* N2D;
	GraphicNode* texto;
	for (unsigned int i = 0; i < en.size(); i++) {
		if (en[i] != NULL) {

			pos = en[i]->getCenter();
			angle = en[i]->getAngle();

			if (Point::distance(Posplayer, en[i]->getCenter()) > 750 && sManager->getMyClipping())
				en[i]->getNodo()->setVisible(false);
			else {
				en[i]->getNodo()->setVisible(true);
				padre = en[i]->getPadre();
				if (padre != NULL) {
					elem = padre->getItem();
					if (elem != NULL) {

						((Transform*) elem)->setIdentity();
						((Transform*) elem)->addTranslation(pos);
						((Transform*) elem)->addRotationZ(angle);

					}
				}

			}

			N2D = ((Entity*) en[i])->get2DNode();
			if (N2D != NULL) {
				elem = N2D->getItem();
				if (elem != NULL) {
					((Transform*) elem)->setIdentity();
					((Transform*) elem)->addTranslation(pos);
					((Transform*) elem)->addRotationZ(angle);
				}

			}

			//Actualizar los rayos.
			Nray = ((Character*) en[i])->getRay();
			if (Nray != NULL) {
				Element* ray = Nray->getItem();
				if (ray != NULL) {
					Point p1;
					Point p2;
					angle = ((Character*) en[i])->getAngle();
					p1 = ((Character*) en[i])->getCenter();
					p1.setX(p1.getX() + 33 * cos(angle * M_PI / 180));
					p1.setY(p1.getY() + 33 * sin(angle * M_PI / 180));
					p2 = ((Character*) en[i])->laser.point;
					p1.setZ(65);
					p2.setZ(65);

					if (((Character*) en[i])->isShooting()) {
						((Shape*) ray)->setShape(Polygon(p1, p2));
						((Shape*) ray)->setColor(Color<float>(0.8, 1, 0, 1));
						((Shape*) ray)->setTamano(4);
					} else {
						((Shape*) ray)->setShape(Polygon(p1, p2));
						((Shape*) ray)->setColor(Color<float>(1, 0, 0));
						((Shape*) ray)->setTamano(1);
					}

					((Character*) en[i])->setShooting(false);

				}
				//TODO: No se muy bien donde va esto
				((Character*) en[i])->setSlashing(false);
			}
		}
	}


	//LUCES:


	Light *l;
	padre = sManager->getNode(Graphics::DirectNodes::t_light0);

	if(padre != NULL)
	{
		l = (Light*)padre->getItem();

		if(l != NULL)
		{
			Point p(0,0,1000);
			l->setPosicion(Posplayer);
		}
	}

	padre = sManager->getNode(Graphics::DirectNodes::t_light1);

	if(padre != NULL)
	{
		l = (Light*)padre->getItem();

		if(l != NULL)
		{
			Point p(0,0,0);
			l->setPosicion(Posplayer);
		}
	}

	padre = sManager->getNode(Graphics::DirectNodes::t_light2);

	if(padre != NULL)
	{
		l = (Light*)padre->getItem();

		if(l != NULL)
		{
			Point p(0,0,700);
			l->setPosicion(p);
		}
	}


	vector<Entity *> obstacles = getEntitiesbyType(Core::Entities::e_obstacle);
	for (unsigned int i = 0; i < obstacles.size(); i++) {
		if (obstacles[i] != NULL) {
			pos = obstacles[i]->getCenter();
			angle = obstacles[i]->getAngle();

			if (Point::distance(Posplayer, obstacles[i]->getCenter()) > 750 && sManager->getMyClipping())
				obstacles[i]->getNodo()->setVisible(false);
			else {
				obstacles[i]->getNodo()->setVisible(true);
				padre = obstacles[i]->getPadre();
				if (padre != NULL) {
					elem = padre->getItem();
					if (elem != NULL) {
						((Transform*) elem)->setIdentity();
						((Transform*) elem)->addTranslation(pos);
						((Transform*) elem)->addRotationZ(angle);

					}
				}

			}
		}
	}

	vector<Entity *> objetos = getEntitiesbyType(Core::Entities::e_objects);
	for (unsigned int i = 0; i < objetos.size(); i++) {
		if (objetos[i] != NULL) {
			pos = objetos[i]->getCenter();
			angle = objetos[i]->getAngle();

			if (Point::distance(Posplayer, objetos[i]->getCenter()) > 750 && sManager->getMyClipping())
				objetos[i]->getNodo()->setVisible(false);
			else {
				objetos[i]->getNodo()->setVisible(true);
				padre = objetos[i]->getPadre();
				if (padre != NULL) {
					elem = padre->getItem();
					if (elem != NULL) {
						((Transform*) elem)->setIdentity();
						((Transform*) elem)->addTranslation(pos);
						((Transform*) elem)->addRotationZ(angle);

					}
				}

			}
		}
	}

	Entity *p = getPointer();

	if (p != NULL) {
		pos = ((Pointer*) p)->getAbsolutCenter(800, 600);

		padre = p->getPadre();
		if (padre != NULL) {
			elem = padre->getItem();
			if (elem != NULL) {
				((Transform*) elem)->setIdentity();
				((Transform*) elem)->addTranslation(pos);
			}
		}
	}

	Entity *player = getPlayer();
	//Text *txt;
	string tmp = "";
	char aux[50];
	int score, hp, balas;
	string texturesroot = RESOURCESROOT;
	texturesroot += "texturas/";

	if (player != NULL) {

		score = ((Player*) player)->getScore();
		hp = ((Player*) player)->getHp();
		balas = ((Player*) player)->getAmmunition();

		//sprintf(aux, "Puntuación: %d", score);
		sprintf(aux, "%d", score);
		tmp = aux;

		texto = sManager->getNode(Graphics::DirectNodes::t_puntuacion);

		if (texto != NULL)
			((Text*) texto->getItem())->setText(tmp);

		//sprintf(aux, "HP: %d", hp);
		sprintf(aux, "%d", hp);
		tmp = aux;
		texto = sManager->getNode(Graphics::DirectNodes::t_hp);

		if (texto != NULL)
			((Text*) texto->getItem())->setText(tmp);

		//sprintf(aux, "Munición: %d", balas);
		sprintf(aux, "%d", balas);
		tmp = aux;
		texto = sManager->getNode(Graphics::DirectNodes::t_balas);

		Core::Objects::Class clase = Core::Objects::none_class;
		Object *objeto = ((Player*) player)->getObject();
		if (objeto != NULL) {
			clase = objeto->getObjectClass();
		}
		padre = sManager->getNode(Graphics::DirectNodes::t_recompensa);

		if (padre != NULL) {
			TForm *recompensa = ((TForm*) padre->getItem());

			if (recompensa != NULL) {
				switch (clase) {
				case Core::Objects::health_pack_1:
					((TPicture*) recompensa->getWidgetsAbsoluts()[0])->setImage(texturesroot + "vida20.png");
					break;
				case Core::Objects::health_pack_2:
					((TPicture*) recompensa->getWidgetsAbsoluts()[0])->setImage(texturesroot + "vida50.png");
					break;
				case Core::Objects::health_pack_3:
					((TPicture*) recompensa->getWidgetsAbsoluts()[0])->setImage(texturesroot + "vida100.png");
					break;
				case Core::Objects::ammo_pack_1:
					((TPicture*) recompensa->getWidgetsAbsoluts()[0])->setImage(texturesroot + "ammo20.png");
					break;
				case Core::Objects::ammo_pack_2:
					((TPicture*) recompensa->getWidgetsAbsoluts()[0])->setImage(texturesroot + "ammo50.png");
					break;
				case Core::Objects::ammo_pack_3:
					((TPicture*) recompensa->getWidgetsAbsoluts()[0])->setImage(texturesroot + "ammo100.png");
					break;
				case Core::Objects::sniper:
					break;
				default:
					((TPicture*) recompensa->getWidgetsAbsoluts()[0])->setImage(texturesroot + "none.png");
					break;
				}
			}
		}

		if (texto != NULL)
			((Text*) texto->getItem())->setText(tmp);

	}
}

void EntityManager::setMap(Map *mapa) {
	map = mapa;
}
