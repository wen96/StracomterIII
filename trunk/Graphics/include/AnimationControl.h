/*
 * AnimationControl.h
 *
 *  Created on: 30/03/2012
 *      Author: Chutaos Team
 */

#ifndef ANIMATIONCONTROL_H_
#define ANIMATIONCONTROL_H_

#include "Animation.h"
#include "TWindow.h"
#include "GameMenu.h"
#include "SceneManager.h"

/**
 * Clase para el manejo de las animaciones
 */
class AnimationControl {
public:
	/**
	 * 	Crea una unica instancia de AnimationControl
	 *	Comprueba que no exista ninguna instancia de AnimationControl, si la hay devuelve un puntero,
	 *	 si no la crea y devuelve el puntero.
	 * @param w para las animaciones de slide con menus
	 * @param gameMenu_ para las animaciones de slide con menus
	 * @return instancia de AnimationControl
	 */
	static AnimationControl * getInstance(TWindow *w,GameMenu *gameMenu_);

	/** Crea una unica instancia de AnimationControl
	 *	Comprueba que no exista ninguna instancia de AnimationControl, si la hay devuelve un puntero,
	 *	 si no la crea y devuelve el puntero.
	 * @return instancia de AnimationControl
	 */
	static AnimationControl * getInstance();

	/**
	 * Destructor
	 */
	virtual ~AnimationControl();

	/**
	 * Hace un efecto de desplazamiento hacia arriba entre 2 menus
	 * Tiene su propio bucle de dibujo dentro, es decir deja la aplicacion bloqueada hasta que termine la animacion
	 * @param menu1
	 * @param menu2
	 * @param node Nodo del que se desea aplicar la transformacion
	 */
	void slideUp(Graphics::Menus::Index menu1, Graphics::Menus::Index menu2, Graphics::DirectNodesMenu::Index node);

	/**
	 * Hace un efecto de desplazamiento hacia abajo entre 2 menus
	 * Tiene su propio bucle de dibujo dentro, es decir deja la aplicacion bloqueada hasta que termine la animacion
	 * @param menu1
	 * @param menu2
	 * @param node Nodo del que se desea aplicar la transformacion
	 */
	void slideDown(Graphics::Menus::Index menu1, Graphics::Menus::Index menu2, Graphics::DirectNodesMenu::Index node);

	/**
	 * Hace un efecto de desplazamiento hacia la derecha entre 2 menus
	 * Tiene su propio bucle de dibujo dentro, es decir deja la aplicacion bloqueada hasta que termine la animacion
	 * @param menu1
	 * @param menu2
	 * @param node Nodo del que se desea aplicar la transformacion
	 */
	void slideRight(Graphics::Menus::Index menu1, Graphics::Menus::Index menu2, Graphics::DirectNodesMenu::Index node);

	/**
	 * Hace un efecto de desplazamiento hacia la izquierda entre 2 menus
	 * Tiene su propio bucle de dibujo dentro, es decir deja la aplicacion bloqueada hasta que termine la animacion
	 * @param menu1
	 * @param menu2
	 * @param node Nodo del que se desea aplicar la transformacion
	 */
	void slideLeft(Graphics::Menus::Index menu1, Graphics::Menus::Index menu2, Graphics::DirectNodesMenu::Index node);

	/**
	 * Devuelve el tiempo que duran las animaciones
	 * @return tiempo
	 */
    int getTime() const;

    /**
     * Cambia el tiempo que duran las animaciones
     * @param time
     */
    void setTime(int time);

    /**
     * Hace un efecto de aparacion, desde el alpha actual de la entidad hasta 1
     * @param ent Entidad a la que aplicar la animacion de color.
     * @param time_ Tiempo en milisegundos de la animacion.
     */
    void addFadeIn(Entity* ent, int time_);

    /**
     * Hace un efecto de desapracion, desde el alpha actual de la entidad hasta 1
     * @param ent Entidad a la que aplicar la animacion de color.
     * @param time_ Tiempo en milisegundos de la animacion.
     */
    void addFadeOut(Entity* ent, int time_);

    void addRotationInfinite(Entity* ent, Transform *trans, int time_);

    /**
     * Acutaliza las animaciones creadas con las funciones de add:
     * 		addFadeIn,addFadeOut...
     * Recorre el vector de animaciones del vector de animacioes, si han termiando las borra.
     */
    void Update();

    bool rermoveAnimation(Animation *anim);

    void freeAllAnimations();
private:
    /**
     * Funcion de desplazamiento de animacion generica, es donde realmente se hace todo el slide, las publicas son solo para decidir hacia donde
     * @param menu1
     * @param menu2
     * @param node Nodo para la transformacion
     * @param despX Cantidad de desplazamiento en x (ancho del form)
     * @param despY Cantidad de desplazamiento en y (alto del form)
     */
    void slide(Graphics::Menus::Index menu1, Graphics::Menus::Index menu2, Graphics::DirectNodesMenu::Index node,double despX, double despY);

	/**
	 * Constructor
	 * @param w
	 * @param gameMenu_
	 */
	AnimationControl(TWindow *w,GameMenu *gameMenu_);

	/**
	 * Puntero a si mismo para comvertirlo en singleton
	 */
	static AnimationControl *_app;

    /**
     * Vector de animaciones para almacenar las animaciones que se actualizan con update()
     * Cuando han terminado se borran
     */
	vector<Animation*> animationsFinite;

	/**
	 * Vector de animaciones para almacenar las animaciones que se actualizan con update()
	 * Cuando han terminado se reinician
	 * En construccion
	 */
	vector<Animation*> animationsInfinite;

	/**
	 * Ventana para hacer el display
	 */
	TWindow *window;

	/**
	 * Controlador de menu para pintar los menus individualmente
	 */
	GameMenu *gameMenu;

	/**
	 * Tiempo de las animaciones
	 */
	int time;
};

#endif /* ANIMATIONCONTROL_H_ */
