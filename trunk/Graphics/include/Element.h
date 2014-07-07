/*
 * Element.h
 *
 *  Created on: 01/01/2012
 *      Author: Chutaos Team
 */

#ifndef ELEMENT_H_
#define ELEMENT_H_

#include <iostream>
using namespace std;

#include "CoreNamespace.h"

class GraphicTree;
class GraphicNode;

/**\brief Element
 * \brief Clase que representa todos los objetos gráficos.*/
class Element {
public:
	/**\brief Constructor por defecto de Element.*/
	Element();
	/**\brief Destructor().*/
	virtual ~Element();
	/**\brief Constructor de Copia.
	 * \param e Elemento a copiar.*/
	Element(const Element& e);
	/**\brief Sobrecarga del operador de asignación.
	 * \param e Elemento a copiar.
	 * \return Devuelve el elemento copiado.*/
	Element& operator=(const Element &);
	/**\brief Inidca el tipo de elemento que es.
	 * \return Devuelve el tipo de elemento.*/
	Core::Element::Type getElementType() const;
	/**\brief Indica en un string el tipo de elemto.
	 * \return un string con el tipo de elemento.*/
	string getName() const;
	/**\brief Inidca el tipo de elemento que es.
	 * \return Devuelve el tipo de elemento.*/
    Core::Element::Type getElement() const;
    /**\brief Accede al nodo gráfico del Elemento.
     * \return Devuelve el nodo gráfico del Elemento.*/
    GraphicNode *getNodo() const;
    /**\brief Accede al padre del nodo gráfico del Elemento.
	* \return Devuelve el padre del nodo gráfico del Elemento.*/
    GraphicNode *getPadre() const;
    /**\brief Cambia el tipo de Elemento.
	* \param element Nuevo tipo de elemento.*/
    void setElement(Core::Element::Type element);
    /**\brief Cambia el nodo gráfico del Elemento.
	* \param nodo_ Nuevo nodo gráfico del Elemento.*/
    void setNodo(GraphicNode *nodo_);
    /**\brief Cambia el padre del nodo gráfico del Elemento.
	* \param padre_ Nuevo padre del nodo gráfico del Elemento.*/
    void setPadre(GraphicNode *padre_);
protected:
    /**\brief Tipo de Elemento.*/
    Core::Element::Type element;
    /**\brief Nodo gráfico.*/
    GraphicNode *nodo;
    /**\brief Padre del nodo gráfico.*/
    GraphicNode *padre;
};

#endif /* ELEMENT_H_ */
