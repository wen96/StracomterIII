/*
 * TControlMenu.h
 *
 *  Created on: 19/01/2012
 *      Author: Chutaos Team
 */

#ifndef TBUTTON_H_
#define TBUTTON_H_

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
#include "TWidget.h"
#include "CoreNamespace.h"
#include "Text.h"
#include "TLabel.h"

using namespace std;
/**\class TButton
 * \brief Clase para crear un widget de tipo Button.
 * Esta clase hereda de TWidget, para mas información
 * consultar la clase padre.
 * */
class TButton: public TWidget{
public:
	/**\brief Constructor por defecto
	 */
	TButton();
	/**\brief Constructor por defecto
	 *\param caption_ - texto del boton.
	 */
	TButton(string);
	/**\brief Constructor por defecto
	 *\param width_ - ancho del boton
	 *\param height_ - alto del boton
	 *\param caption_ - texto del boton
	 */
	TButton(int, int, string);

	/**
	 *
	 * @param p
	 * @param
	 * @param
	 * @param
	 */
	TButton(Point p, int, int, string);

	/**\brief Destructor
	 */
	/**\brief Constructor por defecto
	 *\param p - posicion del boton (especifico para radioButton).
	 *\param w - mundo
	 */
	TButton(Point,World*);

	TButton(const TButton &);
	TButton& operator=(const TButton &);

	virtual ~TButton();
	/**\brief Dibuja el boton
	 */
	void Draw();
	/**\brief Get atributo: caption
	 *\return texto del boton*/
    string getCaption() const;
	/**\brief Get atributo: height
	 *\return altura del boton*/
    int getHeight() const;
	/**\brief Get atributo: width
	 *\return anchura del boton*/
    int getWidth() const;
	/**\brief Set atributo: caption
	 *\param caption - texto del boton*/
    void setCaption(string caption);
	/**\brief Set atributo: height
	 *\param height - altura del boton*/
    void setHeight(int height);
	/**\brief Get atributo: width
	 *\param width - anchura del boton*/
    void setWidth(int width);
	/**\brief Get atributo: font
	 *\return font - opciones de fuente del boton*/
    Text getFont() const;
	/**\brief Set atributo: font
	 *\param font - opciones de fuente del boton*/
    void setFont(Text font);
	/**\brief Set atributo: colorText
	 *\param colorText - Color del texto del boton*/
    void setColorText(Color<float> colorText);
	/**\brief Get atributo: colorText
	 *\return color del texto del boton*/
    Color<float> getColorText() const;
	/**\brief Set atributo: colorText
	 *\param colorText - Color del texto del boton*/
    void setColorBorder(Color<float> colorBorder);
	/**\brief Get atributo: colorText
	 *\return color del texto del boton*/
    Color<float> getColorBorder() const;
	/**\brief Set atributo: wLabel
	 *\param wLabel - Anchura del texto, #necesario cambiar si quieres texto centrado# */
    void setWlabel(int wLabel);
	/**\brief Get atributo: wLabel
	 *\return wLabel - Anchura del texto*/
    int getWlabel();
	/**\brief Set atributo: hLabel
	 *\param hLabel - Altura del texto*/
    void setHlabel(int hLabel);
	/**\brief Get atributo: hLabel
	 *\return hLabel - Altura del texto*/
    int getHlabel();
    /**\brief Set atributo: shape
     *\param shape - forma (Poligono) del widget*/
    void setShape(Polygon *shape);
    /**\brief Set atributo: phisicShape
     *\param phisicShape - forma fisica del widget*/
    void setPhisicShape(Body *phisicShape);
    /**\brief Get atributo: Text
     *\return text - TLabel con el texto del TButton*/
    TLabel *getText() const;
    /**\brief Set atributo: Text
     *\Param text - TLabel con el texto del TButton*/
    void setText(TLabel *text);
private:
    void Destructor();
    void Copiar(const TButton&);
    /**\brief Opciones del texto*/
    TLabel *text;
    /**\brief Anchura del boton*/
    int width;
    /**\brief Altura del boton*/
    int height;
};


#endif /* TBUTTON_H_ */
