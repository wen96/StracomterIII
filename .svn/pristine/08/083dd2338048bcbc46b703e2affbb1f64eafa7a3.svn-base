/*
 * CharacterFeature.h
 *
 *  Created on: 20/02/2012
 *      Author: Chutaos team
 */

#ifndef CHARACTERFEATURE_H_
#define CHARACTERFEATURE_H_

#include <iostream>
#include "tinyxml.h"
#include "Color.h"
#include "CoreNamespace.h"
#include <vector>
using namespace std;

/**
 * Clase contenedora de las caracteristicas para los personajes
 */
class Features{
	/**
	 * Operador de salida sobrecargado
	 * @param os stream de salida
	 * @param n Feature
	 * @return os con la salida
	 */
	friend ostream& operator<<(ostream &os, const Features &n);
public:
	/**
	 * Constructor por defecto para inicializr valores a 0
	 */
	Features(){
		HP = 0;
		DPS = 0;
		Speed = 0;
		Force = 0;
		Cadence = 0;
		Damage = 0;
		Moral = 0;
		expKill = 0;
	}
	/**
	 * Constructor de copia
	 * @param obj a copiar
	 */
	Features(const Features& obj);
	/**
	 * Sobrecarga del operador igual
	 * @param obj a copiar
	 * @return Fetaure resultando
	 */
	Features & operator=(const Features &obj);

	/** Color
	 */
	Color<float> color;
	/** Puntos de vida
	 *  Health points
	 */
	float HP;
	/** Disparos por segundo
	 * Inutilizada
	 */
	float DPS;
	/** Velocidad
	 */
	float Speed;

	/** Fuerza de giro
	 */
	float Force;

	/** Cadencia de disparo, ratio, cada cuanto puede disparar en milisegundos
	 */
	float Cadence;

	/** Danyo de cada disparo
	 * Damage per shoot
	 */
	float Damage;

	/** Bonificador de moral
	 */
	int Moral;

	/** Experiencia que proporciona el ser matado
	 */
	int expKill;
};

/**
 * Clase para cargar de un fichero las caracteristica de los personajes y almacenarlas en vectores
 */
class CharacterFeature {
	/**
	 * Operador de salida sobrecargado
	 * @param os stream de salida
	 * @param n CharacterFeature a mostrar
	 * @return os con la salida
	 */
	friend ostream& operator<<(ostream &os, const CharacterFeature &n);
public:

	static CharacterFeature* getInstance();
	static CharacterFeature* getInstance(string nomFich_);

	/**
	 * Destructor por defecto
	 */
	virtual ~CharacterFeature();

	/**
	 * Constructor de copia
	 * @param obj a copiar
	 */
	CharacterFeature(const CharacterFeature &obj);

	/**
	 * Sobrecarga del operador igual
	 * @param obj a copiar
	 * @return resultado del copia
	 */
	CharacterFeature & operator=(const CharacterFeature &obj);

	/**
	 * Carga los datos del fichero actualmente guardado en la variable nomFile
	 * @return booleano con si se ha pordido cargar el fichero o no
	 */
	bool loadData();

	/**
	 * Carga los datos del fichero pasado por parametro
	 * @param nomFile_ con el fichero a cargar
	 * @return booleano con si se ha pordido cargar el fichero o no
	 */
	bool loadData(string nomFile_);

	/**
	 * Devuelve el nombre del fichero que se carga
	 * @return string con el nombre
	 */
    string getNomFile() const;

    /**
     * Cambia el nombre del fichero a cargar
     * @param nomFile string con el nombre del fichero
     */
    void setNomFile(string nomFile);

    /**
     * Devuelve las caracteristicas de un personaje en concreto
     * @param t tipo del que averiguar
     * @return caracteristica del personaje
     */
    Features getFeature(Core::Entities::Type t);

    /**
     * Funcion para averiguar el tipo dado el string del xml
     * @param name leido del fichero
     * @return enum adecuado
     */
    static int getType(const char * name);

    /**
     * Borra los datos almacenados actualmente de los personajes
     */
    void clearData();

    /**
     * Nombre del fichero a cargar
     */
    string nomFile;

    /**
     * Vector de caracteristicas cargadas
     * En publico por pereza de ir una a una pidiendolo con la funcion, ademas de por eficiencia
     */
    vector<Features> featuresContainer;
private:
    /**
     * Copia auxiliar el objeto
     * @param obj a copiar
     */
    void copy(const CharacterFeature &obj);

    /**
     * Constructor por defecto
     */
    CharacterFeature();

    /**
     * Constructor con un fichero de carga
     * @param nomFile_ string con la ruta del fichero de carga
     */
    CharacterFeature(string nomFile_);

    static CharacterFeature *_features;


};



#endif /* CHARACTERFEATURE_H_ */
