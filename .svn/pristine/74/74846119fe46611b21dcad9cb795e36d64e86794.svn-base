/*
 * EntityManger.cc
 *
 *  Created on: 04/11/2011
 *      Author: Chutaos Team
 */

#include "EntityManager.h"
#include "SceneManager.h"


EntityManager::EntityManager(ResourceManager *r){
	numEntities = 0;
	nextId=0;
	resources = r;
	//Preparado del vector
	vector<Entity*>aux;
	entidades = vector< vector<Entity*> >(Core::Entities::size,aux);
	sManager = SceneManager::getInstance();
}

EntityManager::~EntityManager(){
	numEntities = 0;
	nextId = 0;//TODO
	resources = NULL;
	sManager = NULL;
	vector<vector<Entity*> >::iterator iterPadre;
	vector<Entity*>::iterator iter;
	Entity *entidad = NULL;

	iterPadre = entidades.begin();
	while (!entidades.empty()){
		iter = (*iterPadre).begin();
		while (!(*iterPadre).empty()){
			entidad = *iter;
			if (entidad!= NULL){
				delete entidad;
			}
			iter = (*iterPadre).erase(iter);

		}
		(*iterPadre).clear();
		iterPadre=entidades.erase(iterPadre);
	}
	entidades.clear();
}

void EntityManager::freeAllEntities(){
	//Si es character pones: sManager->removeCharacter(entidad);
	vector<vector<Entity*> >::iterator iterPadre;
	vector<Entity*>::iterator iter;
	Entity *entidad = NULL;

	iterPadre = entidades.begin();
	while (!entidades.empty()){
		iter = (*iterPadre).begin();
		while (!(*iterPadre).empty()){
			entidad = *iter;
			if (isGood(entidad)||isBad(entidad)){
				sManager->removeCharacter(entidad);
			}else{
				sManager->removeElement(entidad);
			}

			if (entidad!= NULL){
				delete entidad;
			}
			iter = (*iterPadre).erase(iter);

		}
		(*iterPadre).clear();
		iterPadre=entidades.erase(iterPadre);
	}
}


void EntityManager::setAllCharacterFeatures(CharacterFeature *f){
	vector<Entity*> entitiesChar = getCharacters();
	vector<Entity*>::iterator iterChar;
	for (iterChar=entitiesChar.begin(); iterChar != entitiesChar.end(); iterChar++){
		((Character*)(*iterChar))->setFeatures(f);
	}
}

void EntityManager::copiar(const EntityManager &obj){
	this->numEntities = obj.numEntities;
	this->nextId = obj.nextId;

	this->idPosition = obj.idPosition;

	//Preparado del vector
	vector<Entity*>aux;
	for (int i = 0; i < Core::Entities::size; i++){
		entidades.push_back(aux);
	}
	Entity *pl = NULL;
	for (unsigned int i = 0; i < obj.entidades.size(); i++){
		for (unsigned int j = 0; j < obj.entidades[i].size(); j++){
			if (obj.entidades[i][j] != NULL){
				switch (obj.entidades[i][j]->getType()){
				case Core::Entities::e_captain:
				case Core::Entities::e_tecnic:
				case Core::Entities::e_especialist:
				case Core::Entities::e_explosive:
					pl = new Player(*((Player*)obj.entidades[i][j]));
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
					pl = new Wall(*((Wall*)obj.entidades[i][j]));
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

EntityManager::EntityManager(const EntityManager &obj){
	copiar(obj);
}

EntityManager & EntityManager::operator =(const EntityManager & obj) {
	if (this!=&obj){
		this->~EntityManager();
		copiar(obj);
	}
	return *this;
}

vector<Entity*> EntityManager::getEntities(){

	vector<Entity*> en;
	for (unsigned int i = 0; i < entidades.size(); i++) {
		if (entidades[i].size() > 0)
			en.insert(en.end(), entidades[i].begin(),
					entidades[i].end());
	}
	return en;
}

vector<Entity*> EntityManager::getDynamicEntities() {

	vector<Entity*> en;
	en = getCharacters();
	return en;
}

int EntityManager::getNumEntities(){
	return numEntities;
}

void EntityManager::addPlayer(Point p, float angle, Core::Entities::Type t){
	Entity *ent = new Player(nextId, p, angle, resources, t);
	entidades[t].push_back(ent);

	while(nextId >= (int)idPosition.size()) idPosition.push_back(-1);
	idPosition[nextId] = t;
	sManager->addCharacter(ent,sManager->getNode(Graphics::DirectNodes::t_escena));

	numEntities++;
	nextId++;
	playerType = t;
}

/*void EntityManager::addBot(Point p, float angle, Core::Entities::Type t) {
	Entity *ent = new Bot(nextId, p, angle, resources, t);
	entidades[t].push_back(ent);

	int miraX = p.getX() + cos(angle)*500;
	int miraY = p.getY() - sin(angle)*500;
	Point mira(miraX, miraY);
	((Character *) ent)->generateVisionRotation(mira);
	((Character *) ent)->generateRay(mira);

	while(nextId >= (int)idPosition.size()) idPosition.push_back(-1);
	idPosition[nextId] = t;

	numEntities++;
	nextId++;
}*/

void EntityManager::addPointer() {

	Entity *ent = new Pointer(nextId, resources);

	entidades[Core::Entities::e_pointer].push_back(ent);

	while(nextId >= (int)idPosition.size()) idPosition.push_back(-1);
	idPosition[nextId] = Core::Entities::e_pointer;
	sManager->addElement(ent,sManager->getNode(Graphics::DirectNodes::t_escena));

	numEntities++;
	nextId++;
}

void EntityManager::addSmartEntity(Point p, float angle, Core::Entities::Type t, Pathfinder *pf_){

	if(t > 0 && t <= 4){		// Compañero
		if (t!=playerType){
			Entity *ent = NULL;
			Player * player = (Player *) getPlayer();
			switch (t){
			case 1:
				ent = new Captain(nextId, p, angle, resources,t,pf_);
				break;
			case 2:
				ent = new Technic(nextId, p, angle, resources,t,pf_);
				((Bot *) ent)->setOffset(player->getFormation()[0]);
				break;
			case 3:
				ent = new Especialist(nextId, p, angle, resources,t,pf_);
				((Bot *) ent)->setOffset(player->getFormation()[1]);
				break;
			case 4:
				ent = new Explosive(nextId, p, angle, resources,t,pf_);
				((Bot *) ent)->setOffset(player->getFormation()[2]);
				break;
			default:
				break;
			}

			if(player != NULL){
				((Bot *) ent)->setLeader(player->getMovementComp());
			}

			if (ent!= NULL){
				int miraX = p.getX() + cos(angle)*500;
				int miraY = p.getY() - sin(angle)*500;
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

			while(nextId >= (int)idPosition.size()) idPosition.push_back(-1);
			idPosition[nextId] = t;

			sManager->addCharacter(ent,sManager->getNode(Graphics::DirectNodes::t_escena));



			numEntities++;
			nextId++;
		}
	}else if(t > 4 && t <= 7){ 	// Enemigo
		Entity *ent = new Enemy(nextId, p, angle, resources, t,pf_);

		int miraX = p.getX() + cos(angle)*500;
		int miraY = p.getY() - sin(angle)*500;
		Point mira(miraX, miraY);
		((Character *) ent)->generateVisionRotation(mira);
		((Character *) ent)->generateRay(mira);

		entidades[t].push_back(ent);

		while(nextId >= (int)idPosition.size()) idPosition.push_back(-1);
		idPosition[nextId] = t;

		sManager->addCharacter(ent,sManager->getNode(Graphics::DirectNodes::t_escena));

		numEntities++;
		nextId++;
	}else if(t > 7 && t <= 9){	// Jefe

	}
}

void EntityManager::addWall(vector<Point> vP, float angle, Color<float> c) {
	Entity *ent = new Wall(nextId, Point(0,0), angle, resources, c, vP);
	entidades[Core::Entities::e_wall].push_back(ent);

	while(nextId >= (int)idPosition.size()) idPosition.push_back(-1);
	idPosition[nextId] = Core::Entities::e_wall;

	sManager->addElement(ent,sManager->getNode(Graphics::DirectNodes::t_escena));

	numEntities++;
	nextId++;
}

void EntityManager::addFloor(vector<Point> vP, float angle, Color<float> c){
	Entity *ent = new Floor(nextId, Point(0,0), angle, resources, c, vP);
	entidades[Core::Entities::e_wall].push_back(ent);

	while(nextId >= (int)idPosition.size()) idPosition.push_back(-1);
	idPosition[nextId] = Core::Entities::e_floor;

	sManager->addElement(ent,sManager->getNode(Graphics::DirectNodes::t_escena));

	numEntities++;
	nextId++;
}

Entity* EntityManager::getFloor(){
	for(unsigned int i=0; i<entidades[Core::Entities::e_wall].size();i++)
	{
		if((entidades[Core::Entities::e_wall][i])->getType() ==  Core::Entities::e_floor)
		{
			return (entidades[Core::Entities::e_wall][i]);
		}
	}
	return NULL;
}

void EntityManager::removeBot(int id) {
	Entity *entidad;
	vector<Entity*>::iterator iter;
	for (iter = entidades[Core::Entities::e_enemy2].begin();
			iter != entidades[Core::Entities::e_enemy2].end(); iter++){
		if ((*iter)->getId() == id){
			entidad = *iter;
			entidades[Core::Entities::e_enemy2].erase(iter);
			delete entidad;
			entidad = NULL;
			break;
		}
	}
	numEntities--;

}

void EntityManager::removeEntity(int id){

	if(id < (int)idPosition.size()){
		int tipo = idPosition[id];
		if(tipo != -1){
			Entity *entidad;
			vector<Entity*>::iterator iter;
			for(iter = entidades[tipo].begin(); iter != entidades[tipo].end(); iter++){
				if ((*iter)->getId() == id){
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
	if (entidades[playerType].size()>0){
		return *entidades[playerType].begin();
	}else{
		//cerr << "Player no creado \n";
		return NULL;
	}
}

Entity*
EntityManager::getPointer() {
	if (entidades[Core::Entities::e_pointer].size()>0){
		return *entidades[Core::Entities::e_pointer].begin();
	}else{
		//cerr << "Player no creado \n";
		return NULL;
	}
}

vector<Entity*>&
EntityManager::getEntitiesbyType(Core::Entities::Type type_) {
	return entidades[type_];
}

void
EntityManager::removeType(Core::Entities::Type type_, int id_) {
	Entity *entidad;
	vector<Entity*>::iterator iter;
	iter = entidades[type_].begin();
	while (iter != entidades[type_].end()){
		if ((*iter)->getId() == id_){
			entidad = (*iter);
			sManager->removeCharacter(entidad);
			iter = entidades[type_].erase(iter);
			delete entidad;
			entidad = NULL;
			break;
		}
		iter++;
	}
}

vector<Entity*> EntityManager::getGoodPersons(){
	vector<Entity*> en;
	if (!entidades[Core::Entities::e_captain].empty()){
		en.insert(en.end(), entidades[Core::Entities::e_captain].begin(),
				entidades[Core::Entities::e_captain].end());
	}
	if (!entidades[Core::Entities::e_tecnic].empty()){
		en.insert(en.end(), entidades[Core::Entities::e_tecnic].begin(),
				entidades[Core::Entities::e_tecnic].end());
	}
	if (!entidades[Core::Entities::e_explosive].empty()){
		en.insert(en.end(), entidades[Core::Entities::e_explosive].begin(),
				entidades[Core::Entities::e_explosive].end());
	}
	if (!entidades[Core::Entities::e_especialist].empty()){
		en.insert(en.end(), entidades[Core::Entities::e_especialist].begin(),
				entidades[Core::Entities::e_especialist].end());
	}
	return en;
}

vector<Entity*> EntityManager::getIACompains(){
	vector<Entity*> en;
	if (playerType!=Core::Entities::e_captain && !entidades[Core::Entities::e_captain].empty()){
		en.insert(en.end(), entidades[Core::Entities::e_captain].begin(),
				entidades[Core::Entities::e_captain].end());
	}
	if (playerType!=Core::Entities::e_tecnic && !entidades[Core::Entities::e_tecnic].empty()){
		en.insert(en.end(), entidades[Core::Entities::e_tecnic].begin(),
				entidades[Core::Entities::e_tecnic].end());
	}
	if (playerType!=Core::Entities::e_explosive && !entidades[Core::Entities::e_explosive].empty()){
		en.insert(en.end(), entidades[Core::Entities::e_explosive].begin(),
				entidades[Core::Entities::e_explosive].end());
	}
	if (playerType!=Core::Entities::e_especialist && !entidades[Core::Entities::e_especialist].empty()){
		en.insert(en.end(), entidades[Core::Entities::e_especialist].begin(),
				entidades[Core::Entities::e_especialist].end());
	}
	return en;
}

vector<Entity*> EntityManager::getBadPersons(){
	vector<Entity*> en;
	if (!entidades[Core::Entities::e_enemy1].empty()){
		en.insert(en.end(), entidades[Core::Entities::e_enemy1].begin(),
				entidades[Core::Entities::e_enemy1].end());
	}
	if (!entidades[Core::Entities::e_enemy2].empty()){
		en.insert(en.end(), entidades[Core::Entities::e_enemy2].begin(),
				entidades[Core::Entities::e_enemy2].end());
	}
	if (!entidades[Core::Entities::e_enemy3].empty()){
		en.insert(en.end(), entidades[Core::Entities::e_enemy3].begin(),
				entidades[Core::Entities::e_enemy3].end());
	}
	if (!entidades[Core::Entities::e_miniboss].empty()){
		en.insert(en.end(), entidades[Core::Entities::e_miniboss].begin(),
				entidades[Core::Entities::e_miniboss].end());
	}
	if (!entidades[Core::Entities::e_megaboss].empty()){
		en.insert(en.end(), entidades[Core::Entities::e_megaboss].begin(),
				entidades[Core::Entities::e_megaboss].end());
	}
	return en;
}

vector<Entity*> EntityManager::getCharacters(){
	vector<Entity*> good = getGoodPersons();
	vector<Entity*> bad = getBadPersons();
	good.insert(good.end(), bad.begin(), bad.end());

	return good;
}

vector<Entity*> EntityManager::getBots(){

	vector<Entity*> en; //TODO
	if (playerType != Core::Entities::e_tecnic){
		if (!entidades[Core::Entities::e_tecnic].empty()){
			en.insert(en.end(), entidades[Core::Entities::e_tecnic].begin(),
					entidades[Core::Entities::e_tecnic].end());
		}
	}
	if (playerType != Core::Entities::e_explosive){
		if (!entidades[Core::Entities::e_explosive].empty()){
			en.insert(en.end(), entidades[Core::Entities::e_explosive].begin(),
					entidades[Core::Entities::e_explosive].end());
		}
	}
	if (playerType != Core::Entities::e_explosive){
		if (!entidades[Core::Entities::e_especialist].empty()){
			en.insert(en.end(), entidades[Core::Entities::e_especialist].begin(),
					entidades[Core::Entities::e_especialist].end());
		}
	}
	if (playerType != Core::Entities::e_captain){
		if (!entidades[Core::Entities::e_captain].empty()){
			en.insert(en.end(), entidades[Core::Entities::e_captain].begin(),
					entidades[Core::Entities::e_captain].end());
		}
	}

	vector<Entity*> bad = getBadPersons();
	en.insert(en.end(), bad.begin(), bad.end());



	return en;
}

void EntityManager::addDead(Core::Entities::Type type_, int id_){
	ForDead dead;
	dead.type = type_;
	dead.id = id_;
	deads.push_back(dead);
}

bool EntityManager::Update(){
	bool isDead = false;
	vector<ForDead>::iterator iter;
	iter = deads.begin();
	while (!deads.empty()){
		if ((*iter).type == playerType){
			isDead = true;
		}else{
			idPosition[(*iter).id] = -1;
			removeType((*iter).type, (*iter).id);
		}
		deads.erase(iter);
		iter = deads.begin();
	}

	UpdateGraphics();

	return isDead;
}

int EntityManager::getIdPos(int id){
	int pos = -1;

	if(id < (int)idPosition.size()){
		pos = idPosition[id];
	}

	return pos;
}

Entity * EntityManager::getEntity(int id){
	Entity *pEnt = NULL;
	if(id < (int)idPosition.size()){
		int vec = idPosition[id];
		if (vec >= 0){
			vector<Entity*>::iterator iter;
			for(iter = entidades[vec].begin(); iter != entidades[vec].end(); iter++){
				if((*iter)->getId() == id){
					pEnt = *iter;
					break;
				}
			}
		}
	}

	return pEnt;
}

bool EntityManager::isDynamic(Entity *entidad){
	bool dynamic = false;
	if(entidad != NULL){
		switch(entidad->getType()){
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

bool EntityManager::isGood(Entity *entidad){
	bool good = false;
	if(entidad != NULL){
		switch(entidad->getType()){
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

bool EntityManager::isBad(Entity *entidad){
	bool bad = false;
	if(entidad != NULL){
		switch(entidad->getType()){
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

bool EntityManager::isNeutral(Entity *entidad){
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

	GraphicNode *padre;
	Element *elem;
	vector<Entity*> en = getDynamicEntities();
	Point pos;
	float angle;
	GraphicNode* Nray;
	GraphicNode* N2D;
	for(unsigned int i = 0; i < en.size(); i++)
	{
		if(en[i] != NULL)
		{
			padre = en[i]->getPadre();
			if(padre != NULL)
			{
				elem = padre->getItem();
				if(elem != NULL)
				{
					pos = en[i]->getCenter();
					angle = en[i]->getAngle();

					((Transform*)elem)->setIdentity();
					((Transform*)elem)->addTranslation(pos);
					((Transform*)elem)->addRotationZ(angle);

					N2D = ((Entity*)en[i])->get2DNode();
					if(N2D != NULL)
					{
						elem = N2D->getItem();
						if(elem != NULL)
						{
							((Transform*)elem)->setIdentity();
							((Transform*)elem)->addTranslation(pos);
							((Transform*)elem)->addRotationZ(angle);
						}

					}

				}

			}

			//Actualizar los rayos.
			Nray = ((Character*)en[i])->getRay();
			if(Nray != NULL)
			{
				Element* ray = Nray->getItem();
				if(ray != NULL)
				{
					Point p1;
					Point p2;
					angle = ((Character*)en[i])->getAngle();
					p1 = ((Character*)en[i])->getCenter();
					p1.setX(p1.getX() + 33*cos(angle*M_PI/180));
					p1.setY(p1.getY() + 33*sin(angle*M_PI/180));
					p2 = ((Character*)en[i])->laser.point;
					p1.setZ(65);
					p2.setZ(65);

					if(((Character*)en[i])->isShooting())
					{
						((Shape*)ray)->setShape(Polygon(p1,p2));
						((Shape*)ray)->setColor(Color<float> (0.8,1,0, 1));
						((Shape*)ray)->setTamano(4);
					}
					else
					{
						((Shape*)ray)->setShape(Polygon(p1,p2));
						((Shape*)ray)->setColor(Color<float> (1,0,0));
						((Shape*)ray)->setTamano(1);
					}

					((Character*)en[i])->setShooting(false);
				}
			}
		}
	}

	Entity *p = getPointer();

	if(p != NULL)
	{
		pos = ((Pointer*)p)->getAbsolutCenter(800, 600);

		padre = p->getPadre();
		if(padre != NULL)
		{
			elem = padre->getItem();
			if(elem != NULL)
			{
				((Transform*)elem)->setIdentity();
				((Transform*)elem)->addTranslation(pos);
			}
		}
	}

	Entity *player = getPlayer();
	Text *txt;
	string tmp = "";
	char aux[50];
	int score, hp, balas;

	if(player != NULL)
	{
		score = ((Player*)player)->getScore();
		hp = ((Player*)player)->getHp();
		balas = ((Player*)player)->getAmmunition();

		//sprintf(aux, "Puntuación: %d", score);
		sprintf(aux, "%d", score);
		tmp = aux;
		txt = ((Text*)sManager->getNode(Graphics::DirectNodes::t_puntuacion)->getItem());
		txt->setText(tmp);

		//sprintf(aux, "HP: %d", hp);
		sprintf(aux, "%d", hp);
		tmp = aux;
		txt = ((Text*)sManager->getNode(Graphics::DirectNodes::t_hp)->getItem());
		txt->setText(tmp);

		//sprintf(aux, "Munición: %d", balas);
		sprintf(aux, "%d", balas);
		tmp = aux;
		txt = ((Text*)sManager->getNode(Graphics::DirectNodes::t_balas)->getItem());
		txt->setText(tmp);

	}
}
