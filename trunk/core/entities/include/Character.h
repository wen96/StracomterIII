/*
 * Character.h
 *
 *  Created on: 27/12/2011
 *      Author: Chutaos Team
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Entity.h"
#include "CharacterFeature.h"
#include "Shape.h"
#include "MovementComp.h"
#include <SFML/Graphics.hpp>
#include "Clock.h"

class Object;

/**
 * Clase para heredar cualquier entidad del mapa que se aun personaje
 * Contien atributos como municion, vida,  etc
 */
class Character : public Entity{
public:
	/**
	 * Constructor por defecto
	 */
	Character();

	/**
	 * Destructor
	 */
	virtual ~Character();
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
	float getSpeed() const;

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
	void setSpeed(float speed);

	/**\brief Devuelve el valor del maximo de vida que puede alcanzar
	 * \return MAXhp*/
    int getMaXhp() const;

    /**
     * Devuelve el grado de moral
     * @return
     */
    unsigned int getMoral() const;

    /**
     * Cambia la vida maxima del personaje
     * @param maXhp
     */
    void setMaXhp(int maXhp);

    /**
     * Cambia la moral del personaje
     * @param moral
     */
    void setMoral(unsigned int moral);

    /**
     * Cambia la fuerza de movimiento
     * @param f_
     */
    void setMaxForce(float f_);

    /**
     * Fuerza del movimiento
     * @return
     */
	float getMaxForce();

	/**
	 * Anyado puntuacion al personaje
	 * @param sc
	 */
    void addScore(int sc);

    /**
     * Cambia la puntuacion del personaje
     * @param sc
     */
    void setScore(int sc);

    /**
     * Devuelve la puntuacion del personaje
     * @return
     */
    int getScore();

    /** Funcion de disparo, con esto disapara
     * Devuelve el danyo que ha hecho en ese momento, reinicia el reloj que velocidad de disparo
     * y pone su estado de shooting tambien a true
     * @return entero que el danyo que ha hecho en ese momento
     */
    float shootDamage();

    /**
     * Dice que si ha pasado el tiempo suficiente desde el ultimo disparo como para disparar
     * @return booleano con si puede disparar o no
     */
    bool canShoot();

    /** Funcion para herir al personaje
     * Devuelve si lo han matado o no
     * @param damage con el danyo que se desea hacer
     * @return booleano con si ha muerto o no
     */
    bool hurt(int damage);

    /**
     * Genera las caracteristicas segun un tipo pasado por parametro
     * Si no existe el almacen de carateristicas, no funcionara
     * @param t del tipo deseado a crear
     */
    void generateFeatures(Core::Entities::Type t);

    /**
     * Genera el triangulo de vision del bot
     * @param mouse
     */
    void generateVisionRotation(Point mouse);

    /**
     * Genera el rayo en direccion a un punto pasado por parametro
     * @param mouse con el punto
     * @return rayo generado
     */
    RayData generateRay(Point mouse);

    /**
     * Devuelve si es una buena persona
     * Si no es un enemy1, enemy2, enemy3, boss1 o boss2 sera una buena persona
     * @return
     */
    bool isGoodPerson() const;

    /**
     * Cambia su boobleano de buena persona a mala persona
     * @param goodPerson
     */
    void setGoodPerson(bool goodPerson);

    /**
     * Devuelve si un personajes a disparado en una iteracion
     * Este valor se pone a false en cada iteracion con el Update() del EntityManager
     * @return
     */
    bool isShooting() const;

    /**
     * Cambia su estado a disparando o a no disparando
     * @param shooting con el booleano diciendo si dispara o no
     */
    void setShooting(bool shooting);

    /**
     * Devuelve el valor de la experiencia que dan al morir
     * @return con el valor
     */
    int getExpKill() const;

    /**
     * Cambia el valor de la experiencia que dan al morir
     * @param expKill
     */
    void setExpKill(int expKill);

    /**
     * Devuelve si el personaje esta muerto
     * Si esta muerto, no le afectaran las balas
     * @return
     */
    bool isDead() const;

    /**
     * Cambia su estado de vida
     * @param dead
     */
    void setDead(bool dead);

    /**
     * Gira la entidad una cierta cantidad para hacerlo girar dando una vuelta
     * @param grados_ grados a girar
     */
    void turnAround(float grados_);

    /**
     * Coge el puntero al cargador de caracteristicas
     * @return puntero con el cargador
     */
    CharacterFeature *getFeatures();

    /**
     * Cuando se hace un set de las caracteristicas estas se aplican
     * @param features_ con el puntero para poder recuperar las caracteristicas
     */
    void setFeatures(CharacterFeature *features_);

    /**
     * Vector con el rayo de disparo del personaje
     */
    RayData laser;


    /************************************** QUE ES ESTO ***********************************************************/
    /**
     * No se
     * @param nodo
     */
    void setRay(GraphicNode *nodo) {
    	ray = nodo;
    }

    /**
     * No se
     * @return
     */
    GraphicNode* getRay() {
    	return ray;
    }
    /************************************** ----------- ***********************************************************/


    /**
     * Devuelve la componente de movimiento
     */
    MovementComp * getMovementComp();

    /**
     * Inserte la componente de movimiento
     * @param mov componente
     */
    void setMovementComp(MovementComp *mov);

    /**
     * Cura al personaje cada 2 segundos si tiene la moral alta
     */
    void UpdateSanar();

    /**
     * Anayade balas a las bales actuales
     * @param num numero de balas adicionales
     */
    void addBullets(int num);

    /**
     * Sube la municion si ha pasado el tiempo necesario entra la ultima vez que le subio
     */
    void updateAmmunition();

    /**
     * Devuelve la moral propia cargada desde fichero
     */
    void returnMoral();

    /**
     * Devuelve la moral del personajes
     * @return con el grado de moral
     */
    int getAmmunition() const;

    /**
     * Cambia la municion restante del personaje
     * @param ammunition numero de proyectiles
     */
    void setAmmunition(int ammunition);

    /**
     * Devuelve si el enemigo esta cortando con el cuchillo en ese momento
     * @return booleano con si esta usando el cuchillo o no
     */
    bool isSlashing() const;

    /**
     * Cambia el estado de usar del duchillo con uno pasado por parametro
     * @param slashing con el nuevo valor
     */
    void setSlashing(bool slashing);

    /**
     * Devuelve el danyo que hace el personaje con el cuchillo
     * @return
     */
    int slashDamage();

    /**
     * Devuelve si puede acuchillar o no. Esto depende del reloj de acuchillamiento
     * @return con si puede o no
     */
    bool canSlash();

    /**
     * Le anyade un objeto de tipo recompensa al vector de recompensas
     * @param o con el objeto recompensa
     * @return con si se ha podido poner en el vector o no
     */
    bool addObject(Object *);

    /**
     * Borra la recompensa pasada por parametro del vector de recompensas
     * @param o con la recompensa a borrar
     * @return con si se ha podido borrar o no
     */
    bool removeObject(Object*);

    /**
     * Le aplica una recompensa al jugador.
     * La recompensa viene dada por el entero pasado por parametro que correspondra con el vector
     * Debe ir de 0 a 4
     * @param id con la posicion del vector correspondiente con la recompensa a aplicar
     * @return con si se ha podido aplicar o no
     */
    bool ApplyObject(int);

    /**
     * Devuelve si se tiene alguna recompensa que de vida
     * @return con si tiene o no
     */
    bool haveHealthobject();

    /**
     * Devuelve si tiene o no alguna recompensa que de municion
     * @return con si tiene o no
     */
    bool haveArmmorobject();

    /**
     * Aplica la primera recompensa de vida que encuentre en su vector de recompensas
     * Para la IA
     * @return con si se ha aplicado o no
     */
    bool applyObjectHealth();

    /**
     * Aplica la primera recompensa de municion que encuentre en su vector de recompensas
     * Para la IA
     * @return con si se ha aplicado o no
     */
    bool applyobjectArmmor();

    /**
     * Devuelve el vector de recompensas
     * @return vector de recompensas
     */
    vector<Object*> getRecompensas() const;

    /**
     * Cambia el vector de recompensas al pasado por parametro
     * @param recompensas con las nuevas recompensas
     */
    void setRecompensas(vector<Object*> recompensas);

protected:
	/**\brief, Variable que representa la vida de la entidad.*/
	int hp;
	/**\brief, Variable que representa la velocidad a la que se mueve la entidad.*/
	float speed;
	/**\brief, Variable que representa la con la que gira la entidad.*/
	float force;
	/**\brief, Variable que representa la velocidad de disparo de la entidad.*/
	float rate;
	/**\brief, Variable que representa el daño por disparo de la entidad.*/
	float damage;
	/**\brief, Constante que representa la vida maxima de la entidad.*/
	float MAXhp;

	/**
	 * Bonificacion del estado del personaje
	 */
	unsigned int moral;

	/**
	 * Reloj de control de cuando sanar
	 */
	Clock clkSanar;

	/**
	 * PUntuacion del personajes
	 */
	int score;

	/**
	 * Momento del ultimo disparo
	 */
	Clock lastShoot;

	/**
	 * Reloj para comprobar si se puede tajar o no
	 */
	Clock lastSlash;

	/**
	 * Booleano para distinguir a quien atacar
	 */
	bool goodPerson;

	/**
	 * Booleano para pintar el disparo en amarillo
	 */
	bool shooting;

	/**
	 * Experencia que se gana al matar a este personaje
	 */
	int expKill;

	/**
	 * Booleano para saber si esta muerto
	 */
	bool dead;

	/**
	 * Booleano para saber si un personaje esta acuchillando a alguien o no
	 */
	bool slashing;

	/**
	 * Municion restante
	 */
	int ammunition;

	/**
	 * Danyo que hace cuerpo a cuerpo
	 */
	int bodyDamage;

	/**
	 * Ratio que acuchillamiento.
	 * Cada cuanto puede acuchillar un personaje en milisegundos
	 */
	float slashRate;

	/**
	 * Para comprobar si tiene la moral alta y si es asi subir su municion
	 */
	Clock clkAmmu;

	/**
	 * Alamacen de caracteristicas de personajes
	 */
	CharacterFeature *features;

	/**
	 * Rayo para el arbol
	 */
	GraphicNode *ray;

	// Para el movimiento
	/**
	 * Componen de movimiento, par alas formaciones
	 */
	MovementComp *mov;

	/**
	 * Vector de recompensas
	 * Tiene 5 elementos de tipo objeto correspondientes con recompensas
	 */
	vector<Object*> recompensas;

};

#endif /* CHARACTER_H_ */
