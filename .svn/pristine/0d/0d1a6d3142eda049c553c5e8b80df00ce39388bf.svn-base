/*
 * TWindow.h
 *
 *  Created on: 09/11/2011
 *      Author: Chutaos Team
 */

#ifndef TWINDOW_H_
#define TWINDOW_H_

#include <iostream>
#include <cstring>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include <SFML/Graphics.hpp>

using namespace std;

/** class TWindow
 * Clase ventana para la gestion y creacion de una ventena.
 * Actualmente se pueden crear ventana con glut o con la libreria SFML.
 */
class TWindow {
public:
	/**\brief Constructor por defecto
	 * pone screen a NULL
	 */
	TWindow();

	/**\brief Destructor
	 */
	virtual ~TWindow();

	/**\brief Funcion open de Glut
	 * Funcion que abre una ventena en modo completo o no dependiendo del boobleano que se le paso como parametro
	 * \param full bool con el booleano de si debe ser pantalla completa o no
	 */
	void open(bool full);

	/**\brief Funcion openSFML
	 * Funcion que abre una ventena con la resolucion optima para la pantalla del ordenador en pantalla minimizada
	 */
	void openSFML();

	/**\brief Funcion openSFML
	 * Funcion que abre una ventena en modo completo o no dependiendo del boobleano que se le paso como parametro
	 * \param full bool con el booleano de si debe ser pantalla completa o no
	 */
	void openSFML(bool full);

	/**\brief Funcion openSFML
	 * Funcion que abre una ventana con un tamanyo pasado por parametro
	 * \param width con el ancho
	 * \param height con el alto
	 */
	void openSFML(int width, int height);

	/**\brief Funcion openSFML
	 * Funcion que abre una ventena en modo completo o no dependiendo del boobleano que se le paso como parametro y con un tamanyo especifico
	 * \param width con el ancho
	 * \param height con el alto
	 * \param full bool con el booleano de si debe ser pantalla completa o no
	 */
	void openSFML(int width, int height, bool full);

	/**\brief isOpen
	 * Funcio que devuelve si la ventana esta abierta o no
	 * NOTA: Solo valido para SFML
	 * \return bool con si esta abierta o no
	 */
	bool isOpen();

	/**\brief display
	 * Funcion que refresca la ventana y detecta los eventos basicos de la misma.
	 * NOTA: Solo valido para SFML.
	 * El pause, se se pulsa la tecla p, se le dara la vuelta al valor pasado por parametro.
	 * \param paused_ con el valor actual del pausado
	 * \return bool con si se ha pausado el juego o no
	 */
	bool display(bool paused_);

	/** diplay
	 * Funcion simple de actualizacion de ventana, sin captura de eventos
	 * Nota: No se capturaran eventos como cerrar la ventana, por lo que si usas este metodo deberas hacerlo manualmente
	 */
	void display();

	/**\brief Funcion close()
	 * Funcion que cierra la ventana
	 * NOTA: Solo valido para SFML
	 */
	void close();

	/** getFrameTime devuelve el tiempo que se tarda entre mostrar un frame y otro
	 * @return float con el valor de tiempo
	 */
	float getFrameTime();

	/** setFrameLimit Limita fps
	 * funcion que pone el limite de tiempo que debe ocurrir entre refrescos
	 * @param limit con el limite que se desea poner
	 */
	void setFrameLimit(unsigned int limit);

	/** getHeight devuelve el alto de la ventana.
	 * @return entero con el alto de la ventana.
	 */
	const unsigned int getHeight() const;

	/** getWidth devuelve el ancho de la ventana.
	 * @return entero con el ancho de la ventana.
	 */
	const unsigned int getWidth() const;

	/** getFullscreen devuelve si la ventana esta en pantalla completa o no.
	 * @return bool con si esta a pantalla completa o no.
	 */
	const bool getFullscreen() const;

	/** showMouseCursos funcion para cambiar si mostrar o no el cursor cuando esta encima de le ventana
	 * @param mostrar booleano con si se desea mostrar o no
	 */
	void showMouseCursos(bool mostrar);

	/** Init funcion para inicializar las funciones y valores necesarios antes de usar la ventana.
	 * Nota: Por el momento solo contiene glutInit.
	 */
	void Init();

	/**Funcion para capturas en forma de pila los eventos de la ventana
	 * @param event variable pasada por referencia para almacenar el evento
	 * @return bool con si quedan o no mas eventos en la pila
	 */
	bool getEvent(sf::Event &event);

	void setNombreVentana(string n);

	sf::Window *getWindow();

private:
	/**\brief Varibale screen
	 * Puntero a Window de sfml.
	 * Window es una ventana para escribir con OpenGL.
	 * En este tipo de ventana no se puede pintar con SFML.
	 */
	sf::Window *screen;

	/**\brief Varibale fullscreen
	 * Variable para almacenar si la ventana esta a tamaño completo.
	 */
	bool fullscreen;

	/** String nombreVentana para almecenar el texto que se desea mostrar como nombre de la ventana
	 */
	string nombreVentana;

};

#endif /* TWINDOW_H_ */
