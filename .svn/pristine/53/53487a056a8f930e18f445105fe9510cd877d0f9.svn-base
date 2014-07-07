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
#include "Object.h"
#include "Door.h"
#include "Point.h"
#include "ResourceManager.h"
#include "CoreNamespace.h"
#include "Pointer.h"
#include <vector>
#include "CharacterFeature.h"
#include "Map.h"


using namespace std;


/** Clase ForDead para almacenar muertos
 * Clase auxiliar donde almacenar los muertos para luego ser eliminados
 */
class ForDead {
public:
	/**
	 * Constructor
	 */
	ForDead(){
		id = -1;
		type = Core::Entities::e_captain;
	}
	/**
	 * Destructor
	 */
	~ForDead(){
		id = -1;
		type = Core::Entities::e_captain;
	}
	/**
	 * Constructor de copia
	 * @param obj objeto a copiar
	 */
	ForDead(const ForDead &obj){
		id = obj.id;
		type = obj.type;
	}
	/**
	 * Sobrecarga del operador igual
	 * @param obj objeto a copiar
	 * @return
	 */
	ForDead& operator=(const ForDead &obj){
		if (this != &obj){
			id = obj.id;
			type = obj.type;
		}
		return *this;
	}

	/**
	 * Id correspondiente a borrar
	 */
	int id;

	/**
	 * Tipo para el acceso rapido
	 */
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
	 */
	void addPlayer(Point p, float);

	/** addBot funcion para agregar una entidad de tipo enemy_2
	 * Crea una entidad de tipo player basico
	 * @param p con el punto inicial de la entidad
	 * @param angle con el angulo inicial de la entidad
	 * @param c Color de la entidad
	 */
	//void addBot(Point p, float, Core::Entities::Type t);

	void addSmartEntity(Point p, float, Core::Entities::Type t, Pathfinder *pf_, Vector2D formation = Vector2D());

	/** addWall funcion para agregar una entidad de tipo wall
	 * Crea una entidad de tipo wall
	 * @param vP vector de puntos que forman la pared
	 * @param angle con el angulo inicial de la entidad
	 * @param c Color de la entidad
	 */
	Entity * addWall(vector<Point> vP, float, Color<float> c);

	void addFloor(vector<Point> vP, float, Color<float> c);
	void addPointer();

	Entity * addDoor(Point p, vector<Point> contorno, vector<int> vNodes = vector<int>(), Pathfinder *pf_ = NULL);

	Entity* getFloor();

	/** getEntities Funcion que concatena todos los vectores y crea uno con todas las entidades
	 * @return vector de punteros a entidades con todas las entidades
	 */
	vector<Entity*> getEntities();

	/**
	 * Devuelve la entidades que se mueven
	 * @return con un vector con las entidasdes
	 */
	vector<Entity*> getDynamicEntities();

	/** getPlayer que devuelve el palyer jugable por el usuario
	 * @return Puntero a la entidad del player
	 */
	Entity* getPlayer();

	/**
	 * Devuelve la entidad e tipo puntero
	 * @return
	 */
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

	/**
	 * Borra una entidad por su id
	 * @param id con el id de la entidad
	 */
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

	/**
	 * Devuelve todos los personajes que no son player
	 * @return
	 */
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

	/**
	 * Devuelve una entidad dado su id
	 * @param id con el identificador de la entidad
	 * @return puntero a la entidad
	 */
	Entity * getEntity(int id);

	/**
	 * Funcion que le pasa el puntero a las caracteristicas y se las aplica a todas
	 * @param f
	 */
	void setAllCharacterFeatures(CharacterFeature *f);

	/**
	 * Devuelve si una entidad es dinamica
	 * Comprueba su tipo y responde arreglo a ello
	 * @param entidad a comprobar
	 * @return booleano son si es o no
	 */
	bool isDynamic(Entity *entidad);

	/**
	 * Devuelve si una entidad es del bando el jugador
	 * Comprueba su tipo y responde arreglo a ello
	 * @param entidad a comprobar
	 * @return booleano son si es o no
	 */
	bool isGood(Entity *entidad);

	/**
	 * Devuelve si una entidad es del bando contrario al del jugador
	 * Comprueba su tipo y responde arreglo a ello
	 * @param entidad a comprobar
	 * @return booleano son si es o no
	 */
	bool isBad(Entity *entidad);

	/**
	 * Devuelve si no es una entidad ni mala ni buena
	 * Comprueba su tipo y responde arreglo a ello
	 * @param entidad a comprobar
	 * @return booleano son si es o no
	 */
	bool isNeutral(Entity *entidad);

	/**
	 * Devuelve si no es una entidad es el player controlado por teclado
	 * Comprueba su tipo y responde arreglo a ello
	 * @param entidad a comprobar
	 * @return booleano son si es o no
	 */
	bool isPlayer(Entity *entidad);


	Entity * addObstacle(Core::Obstacles::Type, Point, float);
	void addObstacle(Core::Obstacles::Type, Point, float, string, int, int, int);
	Entity *  addObject(Core::Objects::Class c, Point center_, float angle_);

	void UpdateGraphics();

	void freeAllEntities();

	void removeFloors();

	void setMap(Map *mapa);

	/**
	 * Devuelve el tipo del player que esta jugando.
	 * Devuelve el tipo de entidad que se maneja mediante teclado
	 * @return tipo del player
	 */
    Core::Entities::Type getPlayerType() const;

    /**
	 * Cambia el tipo del player que esta jugando.
	 * Cambia el tipo de entidad que se maneja mediante teclado
     * @param playerType con el nuevo tipo
     */
    void setPlayerType(Core::Entities::Type playerType);
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

	/**
	 * Vector para almacenar futuros muertos que seran borrados mediante el update de esta clase
	 */
	vector<ForDead> deads;

	/**\brief Indica en que lista esta cada entidad
	 */
	vector<int>	idPosition;

	/**
	 * Puntero a la escena par apoder anyadir entidades al arbol
	 */
	SceneManager *sManager;

	/**
	 * Funcion auxiliar para copiar un objeto
	 * @param obj
	 */
	void copiar(const EntityManager &obj);

	/**
	 * Puntero al mapa, para poder gestionar lo que hay en el
	 */
	Map * map;
};



#endif /* ENTITYMANAGER_H_ */
