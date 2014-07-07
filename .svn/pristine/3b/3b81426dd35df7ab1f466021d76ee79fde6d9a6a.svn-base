/*
 * EntityManger.cc
 *
 *  Created on: 04/11/2011
 *      Author: Chutaos Team
 */

#include "EntityManager.h"

/*
EntityManager::EntityManager(ResourceManager *r){
	numEntities = 0;
	nextId=0;
	resources = r;
}

EntityManager::~EntityManager(){
	numEntities = 0;
	nextId = 0;
	if (!entities.empty()){
		Entity* forDelete = NULL;
		vector<Entity*>::iterator iter;
		iter = entities.begin();
		while ( iter < entities.end()){
			forDelete = (*iter);
			iter = entities.erase(iter);
			if (forDelete!=NULL)
				delete forDelete;
		}
		entities.clear();
	}

}

EntityManager::EntityManager(const EntityManager &obj){
	this->entities = obj.entities;
	this->numEntities = obj.numEntities;
	this->nextId = obj.nextId;
}

EntityManager & EntityManager::operator =(const EntityManager & obj) {
	if (this!=&obj){
		this->~EntityManager();
		this->entities = obj.entities;
		this->numEntities = obj.numEntities;
		this->nextId = obj.nextId;
	}
	return *this;
}

vector<Entity*> EntityManager::getEntities(){
	return entities;
}
vector<Entity*>& EntityManager::getEntities(){
	return entities;
}

	if(body != NULL)
		{
			b2World *w = world->getWorld();
			w->DestroyBody(body);
			body = NULL;
		}
		if(bodydata != NULL)
		{
			delete bodydata;
			bodydata = NULL;
		}
		if(world != NULL)
			world = NULL;
int EntityManager::getNumEntities(){
	return numEntities;
}

void EntityManager::addPlayer(Point p, float angle, Color<float> c){
	Entity *ent = new Player(nextId, p, angle, resources, c);
	entities.push_back(ent);
	numEntities++;
	nextId++;
}

void EntityManager::addEnemy(Point p, float angle, Color<float> c) {
	Entity *ent = new Enemy(nextId, p, angle, resources, c);
	entities.push_back(ent);
	numEntities++;
	nextId++;
}

void EntityManager::addWall(Point p, float angle, Color<float> c) {
	Entity *ent = new Wall(nextId, p, angle, resources, c);
	entities.push_back(ent);
	numEntities++;
	nextId++;
}

void EntityManager::removeEntity(int indice)
{
	vector<Entity*>::iterator it;
	it = entities.begin();
	int in = 0;

	for(it = entities.begin(); it != entities.end(); it++, in++)
	{

		if(in == indice)
		{
			entities.erase(it);
		}
	}
}

Entity*
EntityManager::getPlayer() {

	bool encontrado = false;

}
*/

EntityManager::EntityManager(ResourceManager *r){
	numEntities = 0;
	nextId=0;
	resources = r;
	//Preparado del vector
	vector<Entity*>aux;
	for (int i = 0; i < Core::Entities::size; i++){
		entidades.push_back(aux);
	}
}

EntityManager::~EntityManager(){
	numEntities = 0;
	nextId = 0;//TODO
	resources = NULL;
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

EntityManager::EntityManager(const EntityManager &obj){
	//this->entities = obj.entities;
	this->numEntities = obj.numEntities;
	this->nextId = obj.nextId;
	this->entidades = obj.entidades;
}

EntityManager & EntityManager::operator =(const EntityManager & obj) {
	if (this!=&obj){
		this->~EntityManager();
		//this->entities = obj.entities;
		this->numEntities = obj.numEntities;
		this->nextId = obj.nextId;
		this->entidades = obj.entidades;
	}
	return *this;
}
/*
vector<Entity*> EntityManager::getEntities(){
	return entities;
}*/
vector<Entity*> EntityManager::getEntities(){

	vector<Entity*> en;
	/*for(unsigned int i = 0; i < entities.size(); i++)
	{
		if(entities[i]->entities.size() > 0)
		en.insert(en.end(), entities[i]->entities.begin(), entities[i]->entities.end());
	}*/
	for (unsigned int i = 0; i < entidades.size(); i++) {
		if (entidades[i].size() > 0)
			en.insert(en.end(), entidades[i].begin(),
					entidades[i].end());
	}
	return en;
}


int EntityManager::getNumEntities(){
	return numEntities;
}

void EntityManager::addPlayer(Point p, float angle, Color<float> c){
	Entity *ent = new Player(nextId, p, angle, resources, c);
	//getEntitiesbyType(Core::Entities::e_captain).push_back(ent);

	entidades[Core::Entities::e_captain].push_back(ent);
	//entities.push_back(ent);
	numEntities++;
	nextId++;
}

void EntityManager::addEnemy(Point p, float angle, Color<float> c) {
	Entity *ent = new Enemy(nextId, p, angle, resources, c);
	//getEntitiesbyType(Core::Entities::e_enemy2).push_back(ent);

	entidades[Core::Entities::e_enemy2].push_back(ent);
	//entities.push_back(ent);
	numEntities++;
	nextId++;
}

void EntityManager::addWall(Point p, float angle, Color<float> c) {

	Entity *ent = new Wall(nextId, p, angle, resources, c);
	//getEntitiesbyType(Core::Entities::e_wall).push_back(ent);

	entidades[Core::Entities::e_wall].push_back(ent);
	//entities.push_back(ent);
	numEntities++;
	nextId++;
}


void EntityManager::removeEnemy(unsigned int id) {

	//getNodeByType(Core::Entities::e_enemy2)->removeElement(id);
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
NodeEntity*
EntityManager::getNodeByType(Core::Entities::Type type_) {

	NodeEntity *en = NULL;
	/*bool encontrado = false;
	for(unsigned int i = 0; i < entities.size() && !encontrado; i++)
	{
		if(entities[i]->type == type_)
		{
			en = entities[i];
			encontrado = true;
		}
	}*/

	return en;
}

void
NodeEntity::removeElement(unsigned int id) {


	bool borrado = false;
	vector<Entity*>::iterator it;
	Entity *entidad;
	it = entities.begin();
	for(unsigned int i = 0; i < entities.size() && !borrado; i++)
	{
		if(entities[i]->getId() == id)
		{
			entidad = *it;
			entities.erase(it);
			entidad->~Entity();
			borrado = true;
		}
		it++;
	}
}


Entity*
EntityManager::getPlayer() {

	/*vector<Entity*> en = getEntitiesbyType(Core::Entities::e_captain);
	Entity *player = NULL;
	if(en.size() > 0)
		player = en[0];*/

	return *entidades[Core::Entities::e_captain].begin();

	//return player;

}

vector<Entity*>&
EntityManager::getEntitiesbyType(Core::Entities::Type type_) {

	/*bool encontrado = false;
	int indice = 0;
	for(unsigned int i = 0; i < entities.size() && !encontrado; i++)
	{
		if(entities[i]->type == type_)
		{
			encontrado = true;
			indice = i;
		}
	}

	if(!encontrado)
	{
		NodeEntity *node = new NodeEntity(type_);
		entities.push_back(node);
		indice = entities.size()-1;
	}

	return entities[indice]->entities;*/
	return entidades[type_];
}

void
EntityManager::removeType(Core::Entities::Type type_) {

	//vector<NodeEntity*>::iterator it;
	//bool borrado = false;

	/*for(it = entities.begin(); it != entities.end() && !borrado; it++)
	{
		if((*it)->type == type_)
		{
			entities.erase(it);
			borrado = true;
		}
	}*/
	Entity *entidad;
	vector<Entity*>::iterator iter;//TODO Arreglar perdida de memoria
	iter = entidades[type_].begin();
	while (!entidades[type_].empty()){
		entidad = (*iter);
		iter = entidades[type_].erase(iter);
		delete entidad;
		entidad = NULL;
	}
	entidades[type_].clear();
}
