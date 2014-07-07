/*
 * Player.h
 *
 *  Created on: 12/11/2011
 *      Author: Chutaos Team
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Character.h"
#include "EntityManager.h"
#include "MovementComp.h"
#include "Vector2D.h"

/**
 * Clase jugador
 * Se utiliza para manejo del jugador controlado por teclado y raton
 */
class Player: public Character {
	friend ostream& operator<<(ostream &os, const Player& obj);
public:
	//--------- FORMA CANÓNICA ------------//
	/**\brief Constructor por defecto.*/
	Player(ResourceManager *r, Core::Entities::Type t);
	/**\brief Constructor.
	 * \param idG - Es la ID global unica que representara a la entidad
	 * \param pos - Es el punto donde se encuentra el centro de la entidad
	 * \param col - Es el poligo que representa las colisiones de la entidad*/
	Player(const unsigned int, const Point, float, ResourceManager *col, Core::Entities::Type t);
	/**\brief Constructor de Copia.
	 * ¡Atencion, tambien se copia el id "unico", su correcto uso, exige que una de las dos entidades sea eliminada
	 * \param ene - Entidad enemigo a copiar*/
	Player(const Player&);
	/**\brief Destructor*/
	virtual ~Player();
	/**\brief Operador =.
	 * ¡Atencion, tambien se copia el id "unico", su correcto uso, exige que una de las dos entidades sea eliminada
	 * \param ene - Entidad enemigo que asignamos a this*/
	Player& operator=(const Player&);

	/**
	 * Vector con las posiciones de formacion
	 * @return
	 */
	vector<Vector2D> getFormation();

	/**
	 * Actualiza el vector de las posiciones arreglo a donde se encuentra y hacia donde va el personajes
	 * @param force
	 * @param p
	 */
	void UpdateMov(Vector2D force, Point p);


	void Update(Vector2D force, Point p);

	/**
	 * Para cambiar la recompensa seleccionada por el usario mediante el HUD
	 */
	void addIdRecompensa();

	/**
	 * Para aplicar la recompensa seleccionada
	 */
	void applyRecompensa();

	/**
	 * Devuelve el objeto recompensa seleccionado
	 * @return
	 */
	Object* getObject()
	{
		Object *aux = NULL;

		if(recompensa >= 0 && (unsigned)recompensa < recompensas.size())
		{
			aux = recompensas[recompensa];
		}

		return aux;

	}

	/**
	 * Devuelve el id d ela recompensa seleccionada
	 * @return
	 */
	int getRecompensa()
	{
		return recompensa;
	}

private:
	/**
	 * Vector con la formacion
	 */
	vector<Vector2D> formation;
	/**
	 * Id con la posicion del vector de la recompensa seleccionada
	 */
	int recompensa;
};
/*Atributos que Hereda en la parte privada:
 * 	Type type = e_Player2;
 *	int id=TotalID++;
 *	Box colision;
 *	Point center;
 *	bool visible = true;
 *	bool muvible = true;
 *	bool small = false;
 */
#endif /* PLAYER_H_ */
