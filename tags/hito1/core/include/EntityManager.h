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
#include "Wall.h"
#include "Point.h"
#include "ResourceManager.h"
#include "CoreNamespace.h"
#include <vector>

using namespace std;

//TODO: A cambiar y eliminar esto.
class NodeEntity {
	friend class EntityManager;
public:
	NodeEntity(Core::Entities::Type type_) {
		type = type_;
	}
	~NodeEntity() {
	}
	void removeElement(unsigned int);
	void addEntity(Entity* entity) {
		entities.push_back(entity);
	}

private:
	Core::Entities::Type type;
	vector<Entity*> entities;
};

/** Clase EntityManager encargada de llevar la gestion de entidades.
 * Nota: En construccion, no es estable.
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
	void addPlayer(Point p, float, Color<float> c);

	/** addEnemy funcion para agregar una entidad de tipo enemy_2
	 * Crea una entidad de tipo player basico
	 * @param p con el punto inicial de la entidad
	 * @param angle con el angulo inicial de la entidad
	 * @param c Color de la entidad
	 */
	void addEnemy(Point p, float, Color<float> c);

	/** addWall funcion para agregar una entidad de tipo wall
	 * Crea una entidad de tipo player basico
	 * @param p con el punto inicial de la entidad
	 * @param angle con el angulo inicial de la entidad
	 * @param c Color de la entidad
	 */
	void addWall(Point p, float, Color<float> c);

	/** getEntities Funcion que concatena todos los vectores y crea uno con todas las entidades
	 * @return vector de punteros a entidades con todas las entidades
	 */
	vector<Entity*> getEntities();

	/** getPlayer que devuelve el palyer jugable por el usuario
	 * @return Puntero a la entidad del player
	 */
	Entity* getPlayer();

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

	/** removeEnemy Funcion que borra un enemigo
	 * Borra del vector de enemigos el enemigo con el id pasado por parametro
	 * @param id del enemigo a borrar
	 */
	void removeEnemy(unsigned int);

	/** removeEnemy Funcion que borra todas las entidades de un tipo
	 * Borra del vector de entidades del tipo pasado por parametro
	 * @param tipo a borrar
	 */
	void removeType(Core::Entities::Type);

	/**
	 * DESUSO
	 * @param
	 * @return
	 */
	NodeEntity* getNodeByType(Core::Entities::Type);
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
};



#endif /* ENTITYMANAGER_H_ */
