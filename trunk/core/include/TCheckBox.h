/*
 * TCheckBox.h
 *
 *  Created on: 19/04/2012
 *      Author: Chutaos team
 */

#ifndef TCHECKBOX_H_
#define TCHECKBOX_H_

#include <iostream>
#include "TWidget.h"
#include "Text.h"

using namespace std;

/**
 * Control de checkbox.
 * Control con una casilla de ticado, para control de valores booleanos
 */
class TCheckBox : public TWidget {
public:
	/**
	 * Constructor
	 */
	TCheckBox();
	/**
	 * Constructor con parametros
	 * Sirve para crear un checkbox que va a colocarse de forma absoluta
	 * @param p punto en el que se coloca
	 * @param text_ texto que contiene
	 */
	TCheckBox(Point p, string text_);
	/**
	 * Destructor
	 */
	virtual ~TCheckBox();
	/**
	 * Cambia su estado de checked al contrario
	 * checked = !checked
	 */
	void switchCheck();
	/**
	 * Devuelve el punto donde se encuentra
	 * @return punto donde se encuentra
	 */
    Point getPosition() const;
    /**
     * Devuelve el poligono de forma checkeada
     * @return poligono con la forma
     */
    Polygon getShapeCheck() const;
    /**
     * Devuelve el poligono de forma no checkeada
     * @return poligono con la forma
     */
    Polygon getShapeCheckInside() const;
    /**
     * Devuelve el texto que se muestra
     * @return string con el texto
     */
    string getText() const;
    /**
     * Devuelve un booleano con si esta checkeado o no
     * @return
     */
    bool isChecked() const;
    /**
     * Cambia el estado e checkeado
     * @param checked
     */
    void setChecked(bool checked);
    /**
     * Cambia la posicion del boton
     * NO CAMBIA LA FORMA
     * @param position
     */
    void setPosition(Point position);

    /**
     * Cambia el poligono de la forma checkeada
     * @param shapeCheck
     */
    void setShapeCheck(Polygon shapeCheck);

    /**
     * Cambia la fomra del poligono del inteerior del boton
     * @param shapeCheckInside
     */
    void setShapeCheckInside(Polygon shapeCheckInside);
    /**
     * Cambia el texto del boton
     * @param text
     */
    void setText(string text);
    /**
     * Dibuja con OpenGL
     */
    void Draw();

    /**
     * Cambia el mundo al que pertenece el body
     * @param w
     */
    void setBody(World *w);
private:
    /**
     * Position absoluta a partir de la cual se crea la forma del checkbox
     */
	Point position;
	/**
	 * ALfmacena si el checkbox esta checkeado o no.
	 * Si lo esta se dibujara la el boton de dentro que indica que esta ceckeado
	 */
	bool checked;
	/**
	 * Ancho del boton
	 * El texto se ajusto arreglo a esto
	 */
	int width;
	/**
	 * Alto del boton
	 * Otros widgests se podran salapar si se pone muy grande
	 */
	int height;
	/**
	 * Texto que se muetras al lado del boton
	 */
	string text;
	/**
	 * Polygono exterior para con el boton
	 */
	Polygon shapeCheck;
	/**
	 * Polygono interior para indicar que esta el boton checkeado
	 * Si este se dibja tras dibjar shapeCheck parecera que esta checkeado
	 */
	Polygon shapeCheckInside;
	/**\brief Opciones del texto*/
	Text font;
};

#endif /* TCHECKBOX_H_ */
