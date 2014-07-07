/*
 * Element.h
 *
 *  Created on: 04/11/2011
 *      Author: Chutaos Team
 */

#ifndef ENTITYMANAGER_H_
#define ENTITYMANAGER_H_
#include <iostream>
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Captain.h"
#include "Technic.h"
#include "Especialist.h"
#include "Explosive.h"
#include "Wall.h"
#include "Floor.h"
#include "Obstacle.h"
#include "Point.h"
#include "ResourceManager.h"
#include "CoreNamespace.h"
#include "Pointer.h"
#include <vector>
#include "CharacterFeature.h"


using namespace std;


/** Clase ForDead para almacenar muertos
 * Clase auxiliar donde almacenar los muertos para luego ser eliminados
 */
class ForDead {
public:
	ForDead(){
		id = -1;
		type = Core::Entities::e_captain;
	}
	~ForDead(){
		id = -1;
		type = Core::Entities::e_captain;
	}
	ForDead(const ForDead &obj){
		id = obj.id;
		type = obj.type;
	}
	ForDead& operator=(const ForDead &obj){
		if (this != &obj){
			id = obj.id;
			type = obj.type;
		}
		return *this;
	}

	int id;
	Core::Entities::Type type;
};

class SceneManager;

/** Clase EntityManager encargada de llevar la gestion de entidades.
 */
class EntityManager {
public:
	/**Constructor con el un gestor de recursos pasado por parametro
	 * @param r Puntero al gestor de recursos
	 */
	EntityManager(ResourceManager *r);
	/** Destructor por defecto
	 */
	~EntityManager();
	/** Constructor de copia
	 * @param obj Entity Manager a copiar
	 */
	EntityManager(const EntityManager &obj);
	/** Operador igual
	 * @param obj Entity Manager a copiar
	 */
	EntityManager& operator=(const EntityManager &obj);

	/** getNumEntities funcion que devuelve el numero de entidades acutales
	 * @return entero con el numero de entidades
	 */
	int getNumEntities();

	/** addPlayer funcion para agregar una entidad de tipo player
	 * Crea una entidad de tipo player basico
	 * @param p con el punto inicial de la entidad
	 * @param angle con el angulo inicial de la entidad
	 * @param c Color de la entidad
	 */
	void addPlayer(Point p, float, Core::Entities::Type t);

	/** addBot funcion para agregar una entidad de tipo enemy_2
	 * Crea una entidad de tipo player basico
	 * @param p con el punto inicial de la entidad
	 * @param angle con el angulo inicial de la entidad
	 * @param c Color de la entidad
	 */
	//void addBot(Point p, float, Core::Entities::Type t);

	void addSmartEntity(Point p, float, Core::Entities::Type t, Pathfinder *pf_);

	/** addWall funcion para agregar una entidad de tipo wall
	 * Crea una entidad de tipo wall
	 * @param vP vector de puntos que forman la pared
	 * @param angle con el angulo inicial de la entidad
	 * @param c Color de la entidad
	 */
	void addWall(vector<Point> vP, float, Color<float> c);

	void addFloor(vector<Point> vP, float, Color<float> c);
	void addPointer();

	Entity* getFloor();

	/** getEntities Funcion que concatena todos los vectores y crea uno con todas las entidades
	 * @return vector de punteros a entidades con todas las entidades
	 */
	vector<Entity*> getEntities();

	vector<Entity*> getDynamicEntities();

	/** getPlayer que devuelve el palyer jugable por el usuario
	 * @return Puntero a la entidad del player
	 */
	Entity* getPlayer();

	Entity* getPointer();

	/** getResourceManager Devuelve un puntero al gestor de recursos
	 * NOTA: Posiblemente esta funcion no se use (candidata a borrar)
	 * @return Puntero al gestor de recursos
	 */
	ResourceManager* getResourceManager() {
		return resources;
	}

	/**getEntitiesbyType Devuelve un vector de entidades con las entidades de un tipo concreto
	 * Saca de la matriz de entidades la columna de un tipo concreto
	 * @param Tipo a devolver
	 * @return vector con las entidades del tipo
	 */
	vector<Entity*>& getEntitiesbyType(Core::Entities::Type);

	/** removeBot Funcion que borra un enemigo
	 * Borra del vector de enemigos el enemigo con el id pasado por parametro
	 * @param id del enemigo a borrar
	 */
	void removeBot(int);

	void removeEntity(int);

	/** removeBot Funcion que borra una entidad de un tipo
	 * Borra al entidad con el id pasado por parametro en el vector del tipo
	 * @param tipo a borrar
	 * @param id de la entidad a borrar
	 */
	void removeType(Core::Entities::Type, int id_);

	/** Funcion getGoodPerson que devuelve las entidades que son personajes no enemigos
	 * @return vector con las entidades del tipo
	 */
	vector<Entity*> getGoodPersons();

	/** Devuelve los companyeros con IA
	 * Devuelve un vector con todas la entidades que no sean de tu mismo tipo
	 * @return vector con las entidades del tipo
	 */
	vector<Entity*> getIACompains();

	/** Funcion getBadPersons que devuelve las entidades que son enemigos
	 * @return vector con las entidades del tipo
	 */
	vector<Entity*> getBadPersons();

	/** Funcion getBadPersons que devuelve todos los personajes
	 * @return vector con las entidades del tipo
	 */
	vector<Entity*> getCharacters();

	vector<Entity*> getBots();

	/** Funcion addDead para anyadir entidades para morir en el update
	 * Se anayade un id con un tipo (para que sea mas rapido) para eliminarla despues en el update
	 * @param type_ typo de la entidad a borrar
	 * @param id_ id de la entidad
	 */
	void addDead(Core::Entities::Type type_, int id_);

	/** Funcion de actualizacion de entidades
	 * Funcion que de momento elimina las entidades que se han matado en cada iteracion
	 * @return booleano con si ha muerto el jugador o no
	 */
	bool Update();

	/** Variable para almacenar el tipo de la entidad del player que manejara el jugador de teclado
	 */
	Core::Entities::Type playerType;

	int getIdPos(int id);

	Entity * getEntity(int id);

	/**
	 * Funcion que le pasa el puntero a las caracteristicas y se las aplica a todas
	 * @param f
	 */
	void setAllCharacterFeatures(CharacterFeature *f);

	bool isDynamic(Entity *entidad);
	bool isGood(Entity *entidad);
	bool isBad(Entity *entidad);
	bool isNeutral(Entity *entidad);
	bool isPlayer(Entity *entidad);

	void UpdateGraphics();

	void freeAllEntities();


private:
	//vector<Entity*> entities;
	//vector<NodeEntity*> entities;
	/** entidades Vector de vectores (matriz) de entidades
	 * Almacena las entidades en una matriz de tal forma que se codifica
	 * los tipos por columnas de la siguiente forma:
	 * entidades[core::Entities::Type][entidad]
	 * De tal forma que:
	 * core::Entities::Type es un entero para encontrar las entidades de un tipo
	 * entidad es una entidad concreta de un tipo
	 */
	vector< vector<Entity*> > entidades;
	/** Variable numEntities entero con el numero de entidades
	 */
	int numEntities;
	/** Variables entera para la creacion de id's no repetidos
	 */
	int nextId;
	/** Puntero al gestor de recursos para asignarlo en la creacion de entidades
	 */
	ResourceManager *resources;

	vector<ForDead> deads;

	/**\brief Indica en que lista esta cada entidad
	 */
	vector<int>	idPosition;
	SceneManager *sManager;

	void copiar(const EntityManager &obj);
};



#endif /* ENTITYMANAGER_H_ */
