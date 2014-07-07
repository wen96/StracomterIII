/*
 * TControlMenu.h
 *
 *  Created on: 19/01/2012
 *      Author: Chutaos Team
 */

#ifndef TFORM_H_
#define TFORM_H_

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <Polygon.h>
#include <Body.h>
#include <World.h>
#include "CoreNamespace.h"
#include "Point.h"
#include "Color.h"
#include "MotorGrafico.h"
#include "BodyData.h"
#include "TWidget.h"
#include "TLabel.h"
#include "TButton.h"
#include "TPicture.h"
#include "Element.h"
#include "TCheckBox.h"

using namespace std;
/**\class TForm
 * \brief Clase para generar un formulario.
 * Esta clase contiene un vector del tipo TWidget.
 * Para poder interactuar con los widget se necesita un World
 * que por motivos de unicidad el cosntructor de copia hace una
 * copia de puntores, por lo que al acabar de el programa se precisa
 * la llamada a la funcion DeleteWolrd();
 */
class TForm: public Element{
	/**\brief Clase amiga TWidget, para poder aceder a la parte privada.
	 */
	friend class TWidget;
public:
	/**\brief Constructor por defecto
	 */
	TForm();
	/**\brief Constructor
	 *\param width_ - ancho del formulario
	 *\param height_ - alto del formulario
	 *\param center_ - Posicion donde estara el centro
	 */
	TForm(int, int, Point);
	/**\brief Destructor
	 */
	virtual ~TForm();
	/**\brief Constructor de copia
	 *\param form - formulario a copiar
	 */
	TForm(const TForm&);
	/**\brief Operador de igualdad
	 *\param form - formulario a copiar
	 *\return this - el formulario copiado
	 */
	TForm& operator=(const TForm&);
	/**\brief Añadir widget.
	 * Añade un nuevo widget al vector
	 *\param widget_ - widget a añadir
	 */
	void addWidget(TWidget*);
	/**\brief Añadir widget.
	 * Añade un nuevo widget al vector
	 *\param widget_ - widget a añadir
	 */
	void addWidget(TWidget*, Point);
	/**\brief Quien esta clicado.
	 * Nos devuelve el widget que esta clicado
	 *\param point - Punto, posicion del raton
	 *\return Twidget - Con el widget que este clicado
	 */
	TWidget* whoIsClicked(Point);
	/**\brief Get atributo: Color
	 *\return color del formulario*/
    Color<float> getColor() const;
	/**\brief Get atributo: panel
	 *\return Poligono del formulario*/
    Polygon *getPanel() const;
	/**\brief Get atributo: widgets
	 *\return widgets del formulario*/
    vector<TWidget*> getWidgets() const;
	/**\brief Get atributo: world
	 *\return world del formulario*/
    World *getWorld() const;
	/**\brief Set atributo: Color
	 *\param color - color del formulario*/
    void setColor(Color<float> color);
	/**\brief Set atributo: panel
	 *\param panel - panel del formulario*/
    void setPanel(Polygon *panel);
	/**\brief Set atributo: widgets
	 *\param widgets - widgets del formulario*/
    void setWidgets(vector<TWidget*> widgets);
	/**\brief Set atributo: world
	 *\param world - world del formulario*/
    void setWorld(World *world);
	/**\brief Pinta el formulario*/
	void Draw();
	/**\brief Actualiza el estado del formulario
	 *\param frametime - tiempo de actualizacion*/
	void Update(int);
	/**\brief Get atributo: height
	 *\return height del formulario*/
    int getHeight() const;
	/**\brief Get atributo: width
	 *\return width del formulario*/
    int getWidth() const;
	/**\brief Get atributo: center
	 *\return si los elementos del formulario iran centrados*/
    bool isCenter() const;
	/**\brief Set atributo: center
	 *\param center_ - centrar o no el formulario*/
    void centerForm(bool);
	/**\brief Set atributo: height
	 *\param height del formulario*/
    void setHeight(int height);
	/**\brief Set atributo: width
	 *\param width del formulario*/
    void setWidth(int width);
	/**\brief Borra el mundo
	 * por motivos de unicidad el cosntructor de copia hace una
	 * copia de puntores, por lo que al acabar de el programa se precisa
	 * la llamada a la funcion DeleteWolrd();*/
    void removeWorld();
    vector<TWidget*> getWidgetsAbsoluts() const;
    void setCenter(bool center);
    void setWidgetsAbsoluts(vector<TWidget*> widgetsAbsoluts);

private:
    /**\brief Poligono que representa la forma del formulario*/
	Polygon* panel;
	/**\brief Vector con los widgets del formulario*/
	vector <TWidget*> widgets;
	/**\brief Vector con los widgets del formulario*/
	vector <TWidget*> widgetsAbsoluts;
	/**\brief Mundo fisico del formulario*/
	World* world;
	/**\brief Color del formulario*/
	Color<float> color;
	/**\brief Anchura del formulario*/
	int width;
	/**\brief Altura del formulario*/
	int height;
	/**\brief Posicion del formulario en la ventana (representa el centro del formulario)*/
	bool center;
};


#endif /* TFORM_H_ */
