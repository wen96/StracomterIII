/*
 * TControlMenu.h
 *
 *  Created on: 19/01/2012
 *      Author: Chutaos Team
 */

#ifndef TWIDGET_H_
#define TWIDGET_H_

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <Polygon.h>
#include <Body.h>
#include <World.h>
#include "Point.h"
#include "Color.h"
#include "MotorGrafico.h"
#include "BodyData.h"
#include "CoreNamespace.h"

using namespace std;
/**\class TWidget
 * \brief Clase para crear un widget.
 * Esta clase contiene un world ya que utiliza la box2D.
 * Por lo que se precisa un puntero a un World ya existente
 * de la aplicacion, o si este Widget pertenece a un formulario
 * de tipo TForm, el puntero deberia apuntar al World del TForm
 */
class TWidget {
public:
	/**\brief Constructor por defecto
	 */
	TWidget();
	/**\brief Destructor
	 */
	virtual ~TWidget();
	/**\brief Constructor de copia
	 *\param widget_ - widget a copiar
	 */
	TWidget(const TWidget&);
	/**\brief Operador de igualdad
	 *\param widget_ - widget a copiar
	 *\return this - el widget copiado
	 */
	TWidget& operator=(const TWidget&);
	/**\brief Esta dentro
	 *\param point - Point, normalmente la posicion del raton
	 *\return True si el punto esta dentro del widget
	 */
	bool isInside(Point) const;
	/**\brief Get atributo: Color
	 *\return color del widget*/
    Color<float> getColor() const;
	/**\brief Get atributo: evento
	 *\return entero con el evento del widget*/
    int getEvento() const;
	/**\brief Get atributo: phisicShape
	 *\return forma fisica del widget*/
    Body *getPhisicShape() const;
	/**\brief Get atributo: shape
	 *\return forma del widget*/
    Polygon *getShape() const;
	/**\brief Get atributo: enable
	 *\return true el widget esta activado*/
    bool isEnable() const;
    /**\brief Get atributo: visible
     *\return true el widget esta visible*/
    bool isVisible() const;
    /**\brief Set atributo: color
     *\param color - color del widget*/
    void setColor(Color<float> color);
    /**\brief Set atributo: color
     *\param color - color del widget*/
    void setEnable(bool enable);
    /**\brief Set atributo: evento
     *\param evento - evento del widget*/
    void setEvento(int evento);
    /**\brief Set atributo: phisicShape
     *\param phisicShape - forma fisica del widget*/
    virtual void setPhisicShape(Body *phisicShape);
    /**\brief Set atributo: shape
     *\param shape - forma (Poligono) del widget*/
    virtual void setShape(Polygon *shape);
    /**\brief Set atributo: visible
     *\param visible - visibilidad del widget*/
    void setVisible(bool visible);
    /**\brief Pinta el widget, funcion pura*/
    virtual void Draw()=0;
    /**\brief Get atributo: marginUp
     *\return marginUp - margen superior del widget*/
    int getMarginUp() const;
    /**\brief Set atributo: marginUp
     *\param marginUp - margen superior del widget*/
    void setMarginUp(int);
    /**\brief Add atributo: marginUp (se suma, no se sustituye)
     *\param marginUp - margen superior del widget*/
    void addMarginUp(int);
    /**\brief Get atributo: marginBottom
     *\return marginBottom - margen inferior del widget*/
    int getMarginBottom() const;
    /**\brief Set atributo: marginBottom
     *\param marginBottom - margen inferior del widget*/
    void setMarginBottom(int);
    /**\brief Add atributo: marginBottom (se suma, no se sustituye)
     *\param marginBottom - margen inferior del widget*/
    void addMarginBottom(int);
    /**\brief Get atributo: clicked
     *\return clicked - si esta clicado el widget*/
    bool isClicked() const;
    /**\brief Set atributo: clicked
     *\return clicked - si esta clicado el widget*/
    void setClicked(bool clicked);
    /**\brief Get atributo: widget
     *\return widget - Type del widget*/
    Core::Widget::Type getWidget() const;
    /**\brief Set atributo: widget
     *\param widget - Type del widget*/
    void setWidget(Core::Widget::Type widget);
    /**\brief Get atributo: marginLeft
     *\return marginLeft - margen izquiero del widget*/
    int getMarginLeft() const;
    /**\brief Get atributo: marginRight
     *\return marginRight - margen derecha del widget*/
    int getMarginRight() const;
    /**\brief Add atributo: marginRight (se suma, no se sustituye)
     *\param marginRight - margen derecha del widget*/
    void addMarginRight(int);
    /**\brief Add atributo: marginLeft (se suma, no se sustituye)
     *\param marginLeft - margen izquierda del widget*/
    void addMarginLeft(int);
    /**\brief Add atributo: marginLeft
     *\param marginLeft - margen izquierda del widget*/
    void setMarginLeft(int);
    /**\brief Add atributo: marginRight
     *\param marginRight - margen derecha del widget*/
    void setMarginRight(int);
    /**\brief Get atributo: over
     *\return over - si esta encima del widget*/
    bool isOver() const;
    /**\brief Set atributo: over
     *\param over - si esta encima del widget*/
    void setOver(bool over);
    /**\brief Get atributo: colorOver
     *\param colorOver - Color cuando esta encima del widget*/
    Color<float> getColorOver() const;
    /**\brief Get atributo: colorOver
     *\param colorOver - Color cuando esta encima del widget*/
    void setColorOver(Color<float> colorOver);
    /**
     * Devuelve el color en el que se pinta el boton cuando esta clicado
     * @return
     */
    Color<float> getColorClicked() const;

    /**
     * Cambiar el color que se aplica cuando se pinta
     * @param colorClicked
     */
    void setColorClicked(Color<float> colorClicked);
    /**\brief Puntero publico al mundo fisico*/
    World *world;
protected:
    /**\brief Type de Widget*/
    Core::Widget::Type widget;
    /**\brief Poligono del widget*/
    Polygon *shape;
    /**\brief body fisico del widget*/
    Body *phisicShape;
    /**\brief Color del widget*/
    Color<float> color;
    /**\brief Color del widget cuando esta el puntero encima*/
    Color<float> colorOver;
    /**\brief Color del widget cuando esta el puntero encima*/
    Color<float> colorClicked;
    /**\brief Si el widget esta visible*/
    bool visible;
    /**\brief Si el widget activo*/
    bool enable;
    /**\brief Id con el evento del widget*/
    int evento;
    /**\brief Margen superior del widget*/
    int marginUp;
    /**\brief Margen inferior del widget*/
    int marginBottom;
    /**\brief Margen derecho del widget*/
    int marginRight;
    /**\brief Margen izquierdo del widget*/
    int marginLeft;
    /**\brief Si el widget esta clicado*/
    bool clicked;
    /**\brief Si el puntero esta encima del widget*/
    bool over;
};

#endif /* TWIDGET_H_ */
