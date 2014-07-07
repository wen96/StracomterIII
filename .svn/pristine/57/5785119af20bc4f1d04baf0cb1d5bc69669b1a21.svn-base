/*
 * Optimization.h
 *
 *  Created on: 24/02/2012
 *      Author: Chutaos Team
 */

#ifndef OPTIMIZATION_H_
#define OPTIMIZATION_H_

#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include "Simplex.h"
#include "Map.h"
#include "EntityManager.h"
#include "Point.h"
#include "Pathfinder.h"

/**\class Optimization
 * Clase encargada de integrar Simplex en el juego.
 * Contiene un puntero a simplex y la cantidad de enemigos
 * de cada tipo. Ademas nos permine generarlos y meternos en
 * un EntityManager*/
class Optimization {

public:
	/**\brief Constructor por defecto.*/
	Optimization();
	/**\brief Constructor de copia.
	 *\param opti - elemento a copiar*/
	Optimization(const Optimization &opti);
	/**\brief Constructor por defecto
	 *\param _E1 - cantidad de enemigo 1.
	 *\param _E2 - cantidad de enemigo 2.
	 *\param _E3 - cantidad de enemigo 3.*/
	Optimization(int _E1, int _E2, int _E3);
	/**\brief Operador de igualdad.
	 *\param opti - elemento de la derecha, a asignar
	 *\return this - el elemento de la izquierda asignado*/
	Optimization& operator=(const Optimization &opti);
	/**\brief Destructor por defecto*/
	virtual ~Optimization();

	/**\brief Devuelve la cantidad de enemigos de tipo 1*/
    int getE1() const;
	/**\brief Devuelve la cantidad de enemigos de tipo 2*/
    int getE2() const;
	/**\brief Devuelve la cantidad de enemigos de tipo 3*/
    int getE3() const;
	/**\brief Devuelve el atributo simplex*/
    Simplex *getSimplex() const;
    /**\brief Asigna la cantidad de enemigos de tipo 1
	 *\param e3 - nueva cantidad de enemigos tipo 1*/
    void setE1(int e1);
    /**\brief Asigna la cantidad de enemigos de tipo 2
    	 *\param e3 - nueva cantidad de enemigos tipo 2*/
    void setE2(int e2);
	/**\brief Asigna la cantidad de enemigos de tipo 3
	 *\param e3 - nueva cantidad de enemigos tipo 3*/
    void setE3(int e3);
	/**\brief Asigna un nuevo simplex
	 *\param simplex - nuevo simplex*/
    void setSimplex(Simplex *simplex);


	/**\brief Crea y carga la funcion objetivo.
	 *\param tam - tamaño del mapa
	 *\param dif - dificultad del mapa [0-8]*/
	void CargarFuncionObjetivo(double tam,float dif);
	/**\brief Calcula la cantidad de enemigos de cada tipo*/
	void CalcularEnemigos();
	/**\brief Carga los enemigos en el EntityManager
	 * Calcula la posicion de los enemigos.
	 *\param em - EntityManager donde introducir los enemigos
	 *\return insertados - numero total de enemigos insertados*/
	int CargarEnemigos(Map* map, Pathfinder *pf);

private:
	/**\brief Variable con el algoritmo simplex*/
	Simplex *simplex;
	/**\brief Cantidad de enemigos de tipo 1*/
	int E1;
	/**\brief Cantidad de enemigos de tipo 2*/
	int E2;
	/**\brief Cantidad de enemigos de tipo 3*/
	int E3;
	/**\brief Cantidad maxima de enemigos*/
	float MaxEnemies;
};

#endif /* OPTIMIZATION_H_ */
