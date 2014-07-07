/*
 * Enemy.h
 *
 *  Created on: 12/11/2011
 *      Author: alex
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include "DynamicEntity.h"


class Enemy: public DynamicEntity {
public:
	//--------- FORMA CANÓNICA ------------//
	/**\brief Constructor por defecto.*/
	Enemy(ResourceManager *r);
	/**\brief Constructor.
	 * \param idG - Es la ID global unica que representara a la entidad
	 * \param pos - Es el punto donde se encuentra el centro de la entidad
	 * \param r - Es el poligo que representa las colisiones de la entidad */
	Enemy(const unsigned int, const Point, float, ResourceManager *r, Color<float> color_);
	/**\brief Constructor de Copia.
	 * ¡Atencion, tambien se copia el id "unico", su correcto uso, exige que una de las dos entidades sea eliminada
	 * \param ene - Entidad enemigo a copiar*/
	Enemy(const Enemy&);
	/**\brief Destructor*/
	virtual ~Enemy();
	/**\brief Operador =.
	 * ¡Atencion, tambien se copia el id "unico", su correcto uso, exige que una de las dos entidades sea eliminada
	 * \param ene - Entidad enemigo que asignamos a this*/
	Enemy& operator=(const Enemy&);
	/**\brief Devuelve el valor del daño que hace la entidad
	 * \return damage*/
	int getDamage() const;
	/**\brief Devuelve el valor de la vida que tiene la entidad
	 * \return hp*/
	int getHp() const;
	/**\brief Devuelve el valor de la velocidad de  daño que hace la entidad
	 * \return rate*/
	float getRate() const;
	/**\brief Devuelve el valor de la velocidad que tiene la entidad
	 * \return speed*/
	int getSpeed() const;
	/**\brief Devuelve el valor del maximo de vida que puede alcanzar
	 * \return MAXhp*/
	unsigned int getMAXhp() const;
	/**\brief Modificar el valor del año que hace la entidad
	 * \param  damage - nuevo valor de damage*/
	void setDamage(int damage);
	/**\brief Devuelve el valor de la vida que tiene la entidad
	 * \param  hp - nuevo valor de hp*/
	void setHp(int hp);
	/**\brief Modifica el valor de la velocidad de  daño que hace la entidad
	 * \param  rate - nuevo valor de rate*/
	void setRate(float rate);
	/**\brief Modifica el valor de la velocidad que tiene la entidad
	 * \param  speed - nuevo valor de speed*/
	void setSpeed(int speed);

	void generateColision(){}
private:
	/**\brief, Variable que representa la vida de la entidad.*/
	int hp;
	/**\brief, Variable que representa la velocidad a la que se mueve la entidad.*/
	int speed;
	/**\brief, Variable que representa la velocidad de disparo de la entidad.*/
	float rate;
	/**\brief, Variable que representa el daño por disparo de la entidad.*/
	int damage;
	/**\brief, Constante que representa la vida maxima de la entidad.*/
	int MAXhp;
};
/*Atributos que Hereda en la parte privada:
 * 	Type type = e_enemy2;
 *	int id=TotalID++;
 *	Box colision;
 *	Point center;
 *	bool visible = true;
 *	bool muvible = true;
 *	bool small = false;
 */
#endif /* ENEMY_H_ */
