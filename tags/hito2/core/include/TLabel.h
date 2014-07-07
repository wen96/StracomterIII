/*
 * TControlMenu.h
 *
 *  Created on: 19/01/2012
 *      Author: Chutaos Team
 */

#ifndef TLABEL_H_
#define TLABEL_H_

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

using namespace std;

class TLabel: public TWidget{
public:
	/**\brief Constructor por defecto
	 */
	TLabel();
	/**\brief Constructor por defecto
	 *\param caption_ - texto del label.
	 */
	TLabel(string,int);
	/**\brief Constructor por defecto
	 *\param width_ - ancho del label
	 *\param height_ - alto del label
	 *\param caption_ - texto del label
	 */
	TLabel(int, int, string, int = 18);
	/**\brief Destructor
	 */
	virtual ~TLabel();
	/**\brief Dibujar el label
	 */
	void Draw();
	/**\brief Get atributo: caption
	 *\return texto del boton*/
    string getCaption() const;
	/**\brief Get atributo: colorBorder
	 *\return color del borde del boton*/
    Color<float> getColorBorder() const;
	/**\brief Get atributo: colorText
	 *\return color del texto del boton*/
    Color<float> getColorText() const;
	/**\brief Get atributo: height
	 *\return altura del boton*/
    int getHeight() const;
	/**\brief Get atributo: size
	 *\return tamaño del texto del boton*/
    int getSize() const;
	/**\brief Get atributo: width
	 *\return anchura del boton*/
    int getWidth() const;
	/**\brief Get atributo: font
	 *\return font - opciones de fuente del texto*/
    Text getFont() const;
	/**\brief Set atributo: caption
	 *\param caption - texto del label*/
    void setCaption(string caption);
	/**\brief Set atributo: colorBorder
	 *\param colorBorder - Color del borde del boton*/
    void setColorBorder(Color<float> colorBorder);
	/**\brief Set atributo: colorText
	 *\param colorText - Color del texto del boton*/
    void setColorText(Color<float> colorText);
	/**\brief Set atributo: height
	 *\param height - altura del boton*/
    void setHeight(int height);
    /**\brief Set atributo: size
     *\param size - tamaño del texto del boton*/
    void setSize(int size);
    /**\brief Set atributo: width
     *\param width - anchura del boton*/
    void setWidth(int width);
	/**\brief Get atributo: font
	 *\param font - opciones de fuente del texto*/
    void setFont(Text font);
private:
    /**\brief Texto del label*/
	string caption;
	/**\brief Opciones del texto*/
	Text font;
	/**\brief Ancho del label*/
	int width;
	/**\brief Alto del label*/
	int height;
	/**\brief Color del borde del label*/
	Color<float>colorBorder;
};

#endif /* TLABEL_H_ */
