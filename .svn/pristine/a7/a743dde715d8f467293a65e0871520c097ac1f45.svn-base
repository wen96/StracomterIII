/*
 * Bot.h
 *
 *  Created on: 12/11/2011
 *      Author: Chutaos Team
 */

#ifndef BOT_H_
#define BOT_H_

#include "Character.h"
#include "Tri.h"
#include "FSM.h"
#include "Pathfinder.h"
#include "Vector2D.h"
#include <queue>
#include <list>

using namespace std;

class EventControl;
class EntityManager;

class Bot: public Character {
	friend ostream& operator<<(ostream &os, const Bot& obj);
public:
	//--------- FORMA CANÓNICA ------------//
	/**\brief Constructor por defecto.*/
	Bot();
	/**
	 * Constructor
	 * @param r gestor de recursos
	 * @param t tipo
	 */
	Bot(ResourceManager *r, Core::Entities::Type t);
	/**\brief Constructor.
	 * \param idG - Es la ID global unica que representara a la entidad
	 * \param pos - Es el punto donde se encuentra el centro de la entidad
	 * \param r - Es el poligo que representa las colisiones de la entidad */
	Bot(const int, const Point, float, ResourceManager *r, Core::Entities::Type t);
	/**\brief Constructor de Copia.
	 * ¡Atencion, tambien se copia el id "unico", su correcto uso, exige que una de las dos entidades sea eliminada
	 * \param ene - Entidad enemigo a copiar*/
	Bot(const Bot&);
	/**\brief Destructor*/
	virtual ~Bot();
	/**\brief Operador =.
	 * ¡Atencion, tambien se copia el id "unico", su correcto uso, exige que una de las dos entidades sea eliminada
	 * \param ene - Entidad enemigo que asignamos a this*/
	Bot& operator=(const Bot&);

	/**
	 * Genera el triangulo de vision y lo aplica al personaje
	 * @return triangulo de vision
	 */
	Tri generateVisionTri();

	/**
	 * Devuelve el triangulo de vision del personaje
	 * @return
	 */
	Tri getVision();

	/**
	 * Poner ciego
	 * @param isBlind
	 */
	void setBlindness(bool isBlind);

	/**
	 * Pregunto si es ciego
	 * @return
	 */
	bool isBlind();

	/**
	 * Devuelve el id del estado de su maquina de estados
	 * @return
	 */
    int getStatus() const;

    /**
     * Cambia el estado de su maquina de estados
     * @param status
     */
    void setStatus(int status);

    /**
     * Devuelve su estado en modo string
     * @return string con el tado
     */
    string getStatusS();

    /**
     * Devuelve el estado en modo enteros
     * @return
     */
    int getStatusI();

    /**
     * Interfaz para obligar a los que hereden a generar su maquina de estados
     */
    virtual void generateFSM() = 0;

    /**
     * Cambia el puntero da la variable de pathfinder
     * @param pf
     */
    void setPathfinder(Pathfinder *pf);

    /**
     * Devuelve el camino que van a seguir
     * @return
     */
    vector<Point> getPath() const;

    /**
     * Cambia el camino que van a seguir
     * @param path
     */
    void setPath(vector<Point> path);

    /**
     * Pregunta si un punto esta dentro de su campo de vision
     * @param p punto a calcular
     * @return entero con 0 si no lo ve, 1 si esta en el FOV principal y 2 si esta en el secundario
     */
    int isInsideFOV(Point p);

    /**
     * Calcula el camino a un punto
     * @param destino
     */
    void calculatePath(Point destino);

    /**
     * Selecciona el mejor ojectivo a su alcance
     * @param manager EntityManager para poder buscar objetivos
     * @return Entity con el objetivo seleccionado. NULL si no encuentra ningun objetivo
     */
    Entity * selectObjetive(EntityManager *manager);

    /**
     * Funcion de heuristica para calcular el valor de un objetivo
     * @param enemigo
     * @return
     */
    double enemyValue(Character *enemigo);

    /**
     * Funcion para moverse a traves de su camino
     * @return booleano con si ha llegado o no
     */
    bool Move();

    /**
     * Cambia el leader al que seguir
     * @param mov
     */
    void setLeader(MovementComp *mov);

    /**
     * No tengo ni idea TODO
     * @param vec
     */
    void setOffset(Vector2D vec);

    /**
     * Movimientos segun su rotacion y pasandole el margen de error como un radio
     * @param radius radio del margen de error
     * @return booleano con si ha llegado o no
     */
    bool Move(int radius);

    /**
     * Cambia su estado a estado debug, para pruebas
     */
    void setDebug();

    /**
     * Actualiza el estado dado un input
     * @param input
     */
    void updateState(int input);

    /**
     * Funcion que devuelve si ha localizado un enemigo, si lo encuentra los mete en su cola de objetivos
     * @param manager
     * @return
     */
    bool enemySpotted(EntityManager* manager);

    /**
     * Segira y dispara hacia un objetivo
     * @param objetivo
     */
    void Dispara(Entity *objetivo);

    /**
     * Anyade un punto desde donde le han atacado
     * @param p
     */
    void addAtacker(Point p);

    /**
     * Funcion que devuelve si estan atacando al personaje
     * Mira si su cola de atacante esta vacia o no
     * @param manager
     * @return
     */
    bool meAtacan(EntityManager* manager);

protected:
    /**
     * EN DESUSO
     */
    Point lastShooted;
    /**
     * Triangulo de vision
     */
	Tri vision;

	/**
	 * Triangulo de vision secundaria
	 */
	Tri secondaryVision;

	/**
	 * Booleano con el estado de ceguera del personaje
	 */
	bool blind;

	/**
	 * Maquina de estados
	 */
	FSM statusMachine;

	/**
	 * Puntero al pathfinder para encontrar caminos
	 */
	Pathfinder *pf;

	/**
	 * Vector de puntos a seguir
	 */
	vector<Point > path;

	/**
	 * Cola de puntos desde donde te han atacado
	 */
	queue<Point> atackers;


	/**
	 * Lista con los id de los objetivos que se han seleccionado
	 */
	list<int> memory;

	/**
	 * Variable con el punto del objetivo actual
	 */
	Point * currentObj;
};

#endif /* BOT_H_ */
