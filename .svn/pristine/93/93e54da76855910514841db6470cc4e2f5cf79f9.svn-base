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

	vector<Vector2D> getFormation();

	void UpdateMov(Vector2D force, Point p);

	void Update(Vector2D force, Point p);

private:
	vector<Vector2D> formation;
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
