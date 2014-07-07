/*
 * GameStatus.h
 *
 *  Created on: 03/04/2012
 *      Author: Chutaos Team
 */

#ifndef GAMESTATUS_H_
#define GAMESTATUS_H_

#include <iostream>
#include "CoreNamespace.h"
#include <vector>
#include <fstream>
#include "EntityManager.h"
#include "CoreNamespace.h"
#include "Object.h"

using namespace std;

class CharacterStatus;

/**\brief Clase singleton
 * Clase para guardar la configuracion del juego actualmente
 * Cosas como player seleccionado, los players que quedan vivos y su vida y municion y lo que sea que contengan
 */
class GameStatus {
public:
	/** Crea una unica instancia de GameStatus
	 *	Comprueba que no exista ninguna instancia de GameStatus, si la hay devuelve un puntero,
	 *	 si no la crea y devuelve el puntero.
	 * @return
	 */
	static GameStatus * getInstance();

	/**
	 * Destructor
	 */
	virtual ~GameStatus();

	/**
	 * Carga los datos desde un ficheo pasado por parametro
	 * @param fich string con la ruta hasta el fichero
	 * @return true si lo ha podido cargar false si no
	 */
	bool loadData(string fich);

	/**
	 * Guarda los datos en el fichero especificado por parametro
	 * @param fich string con la ruta hasta el fichero
	 * @return true si lo ha podido guardar false si no
	 */
	bool saveData(string fich);

	/**
	 * Guarda el estado en un fichero binario llamando a la funcion saveData con el
	 * parametro de fichero almacenado en la variable nomFich
	 * @return True si se ha podido guardar, false si no
	 */
	bool saveData();

	/**
	 * Carga el estado desde un fichero binario llamando a la funcion loadData con el
	 * parametro de fichero almacenado en la variable nomFich
	 * @return bool con si se ha podido cargar o no
	 */
	bool loadData();

	/**
	 * Pone los valores por defecto a los players
	 * Recoge los valores de la clase CharacterFeatures
	 */
	void initializeVectorPlayers();

	/**
	 * Cambia el tipo de player con el que se jugara
	 * @param t cone el nuevo tipo
	 */
	void setTypePlayer(Core::Entities::Type t);

	/**
	 * Devuelve el tipo de player con el que se jugara
	 * @return tipoi del player
	 */
	Core::Entities::Type getTypePlayer() const;

	/**
	 * Guarda el estado de los personajes en el vector
	 * NOTA: Para guardan en fichero usar saveData(fichero)
	 * Llama a la funcion getGoodPerson para obetener los personajes
	 * @param ent entity manager para recoger la informacion
	 */
	void getCharacters(EntityManager *ent);

	/**
	 * Aplica el estado alamacenado en el vector a los personajes
	 * NOTA: Para cargar el estado guardad en un fichero al vector se debe llamar a loadData(fichero)
	 * Llama a la funcion getGoodPerson para obetener los personajes
	 * @param ent
	 */
	void applyCharacterStatus(EntityManager *ent);

	/**
	 * Suma 1 a la variable nivelPlanta
	 * nivelPlanta++;
	 */
	void incrementLevel();

	/**
	 * Devuelve la planta hasta la que tiene acceso el player
	 * @return
	 */
    int getNivelPlanta() const;
    /**
     * Cambia la planta hasta la que tiene acceso el player
     * @param nivelPlanta
     */
    void setNivelPlanta(int nivelPlanta);

    /**
     * Devuelve el vector de estado de personajes
     * @return
     */
    vector<CharacterStatus> getPlayers() const;

    /**
     * Cambia el vector de estado de personajes
     * @param players
     */
    void setPlayers(vector<CharacterStatus> players);

    /**
     * Muestra por pantalla el estado de los personajes
     */
    void showPlayers();

    /**
     * Devuelve la zona almacenada en la variable zonaPlanta
     * @return con el entero correspondiente a la zona
     */
    int getZona() const;

    /**
     * Cambia la variable zonaPlanta a la pasada por parametro
     * @param zona con la nueva zona
     */
    void setZona(int zona);

    /**
     * Selecciona la recompensa adecuada para la zona pasada por parametro y la almacena en la variable recompensa
     * @param zona con la zona a corresponder
     */
    void selectZona(int zona);

    /**
     * Sobrecara del operador de salida para la depuracion
     * @param os con el estream de salida
     * @param c con el estado del juego
     * @return os con la salida dentro
     */
    friend ostream& operator<<(ostream &os, const GameStatus &c);

    /**
     * Devuelve la recompensa almacenada en la variable recompensa
     * @return valor de la recompensa
     */
    Core::Objects::Class getRecompensa() const;

    /**
     * Cambia la recompensa a la pasada por parametro
     * @param recompensa con el valor de la recompensa
     */
    void setRecompensa(Core::Objects::Class recompensa);

    /**
     * Devuelve si el tipo de entidad pasado por parametro sigue vivo o no
     * Mira el player almacenado en la position t del vector de players tiene vida <=0
     * @param t con el tipo de entidad a comprobar
     * @return booleano con si est vivo ono
     */
    bool isVivitoYColeando(Core::Entities::Type t);

    /**
     * Devuelve la puntuaciond del player almacenada
     * @return int con la puntuacion
     */
    int getPuntuacionPlayer() const;

    /**
     * Cambia la puntuacion del player a la pasada por parametro
     * @param puntuacionPlayer con la nueva puntuacion
     */
    void setPuntuacionPlayer(int puntuacionPlayer);

private:
	/**
	 * Constructor privado para singleton
	 */
	GameStatus();
	/**
	 * Puntero a si mismo para comvertirlo en singleton
	 */
	static GameStatus *_app;

	/**
	 * Tipo del player con el que se jugara
	 */
	Core::Entities::Type typePlayer;

	/**
	 * Vector que almacena el estado de los personajes del juego
	 */
	vector<CharacterStatus>players;

	/**
	 * Almacena la planta en a la que tiene acceso el player
	 */
	int nivelPlanta;

	/**
	 * Almacena la zona que a elegido el player
	 */
	int zonaPlanta;

	/**
	 * Variable para almacenar la puntuacion del jugador a lo largo del juego independientemente del tipo de clase que elija
	 */
	int puntuacionPlayer;

	/**
	 * RECOMPENSA DEL NIVEL ACTUAL (no guardar)
	 * No se guarda en el fichero es para tiempo dinamico
	 */
    Core::Objects::Class recompensa;

    /**
     * Funcion para almacenar la ruta del fichero que se va a utilizar en la funciones saveData() y  loadData()
     */
	string nomFich;
};


/**
 * Clase auxiliar para almacenar el estado de un caracter concreto
 * Esta clase solo sirve como auxiliar para GameStatus
 */
class CharacterStatus{
public:
	/**
	 * Constructor por defecto
	 */
	CharacterStatus(){
		type = Core::Entities::e_captain;
		hp = 0;
		ammo = 0;
		score = 0;
		recomp1=recomp2=recomp3=recomp4=recomp5=-1;
	}
	/**
	 * Destructor
	 */
	~CharacterStatus(){
		type = Core::Entities::e_captain;
		hp = 0;
		ammo = 0;
		score = 0;
		recomp1=recomp2=recomp3=recomp4=recomp5=-1;
	}
	/**
	 * Constructor con parametros, para hacer la vida mas facil
	 * @param t
	 * @param hp_
	 * @param ammo_
	 * @param score_
	 */
	CharacterStatus(Core::Entities::Type t, int hp_,int ammo_,int score_){
		type = t;
		hp = hp_;
		ammo = ammo_;
		score = score_;
		recomp1=recomp2=recomp3=recomp4=recomp5=-1;
	}

	/**
	 * Constructor de copia
	 * @param obj
	 */
	CharacterStatus(const CharacterStatus& obj){
		type = obj.type;
		hp = obj.hp;
		ammo = obj.ammo;
		score = obj.score;

		recomp1=obj.recomp1;
		recomp2=obj.recomp2;
		recomp3=obj.recomp3;
		recomp4=obj.recomp4;
		recomp5=obj.recomp5;
	}

	/**
	 * Sobrecarga del operador igual
	 * @param obj
	 * @return
	 */
	CharacterStatus& operator=(const CharacterStatus& obj){
		if (&obj != this){
			type = obj.type;
			hp = obj.hp;
			ammo = obj.ammo;
			score = obj.score;
			recomp1=obj.recomp1;
			recomp2=obj.recomp2;
			recomp3=obj.recomp3;
			recomp4=obj.recomp4;
			recomp5=obj.recomp5;
		}
		return *this;
	}

	/**
	 * Operador de salida par la depuracion
	 * @param os cone l stream de salida
	 * @param c cone la clase a mostrar
	 * @return con el stream de salida con la salida dentro
	 */
	friend ostream& operator<<(ostream &os, const CharacterStatus &c){
		os << "Tipo: " << c.type << endl;
		os << "HP: " << c.hp  << endl;
		os << "Ammo: " << c.ammo << endl;
		os << "Score: " << c.score << endl;
		return os;
	}

	/**
	 * Tipo del personaje
	 */
	Core::Entities::Type type;
	/**
	 * Vida del personaje
	 */
	int hp;
	/**
	 * Municion del personaje
	 */
	int ammo;
	/**
	 * Puntuacion del personaje
	 */
	int score;

	/**
	 * Recompensa 1 para el vector
	 */
	int recomp1;

	/**
	 * Recompensa 2 para el vector
	 */
	int recomp2;

	/**
	 * Recompensa 3 para el vector
	 */
	int recomp3;

	/**
	 * Recompensa 4 para el vector
	 */
	int recomp4;

	/**
	 * Recompensa 5 para el vector
	 */
	int recomp5;
};

#endif /* GAMESTATUS_H_ */
