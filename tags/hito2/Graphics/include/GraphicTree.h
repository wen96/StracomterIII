/*
 * GraphicTree.h
 *
 *  Created on: 19/01/2012
 *      Author: Chutaos Team
 */

#ifndef GRAPHICTREE_H_
#define GRAPHICTREE_H_

#include <iostream>
#include <vector>
#include "Element.h"
#include "Transformacion.h"
#include "Light.h"
#include "Camera.h"
#include "Bot.h"
#include "Shape.h"
#include "Text.h"
#include "GameMenu.h"
#include "CoreNamespace.h"
#include "Model.h"
#include "Wall.h"
#include "Floor.h"
#include "Pointer.h"
#include <GL/gl.h>
using namespace std;

class GraphicNode;

class GraphicTree {

	friend class GraphicNode;
	friend ostream& operator<<(ostream &, const GraphicTree &);

public:
    /**\brief Constructor*/
	GraphicTree();
    /**\brief Destructor*/
	virtual ~GraphicTree();
	/**\brief Constructor de copia
	 * param tree - arbol a copiar.*/
	GraphicTree(const GraphicTree&);
	/**\brief Sobrecarga del operador de asignación
	 * \param tree - arbol a copiar.
	 * \return Devuelve una copia del arbol.*/
	GraphicTree & operator=(const GraphicTree&);

	//GraphicNode* Insertar(GraphicTree *);
	/**\brief Insertar elemento.
	 * Inserta elemento colgando de otro elemento
	 * \param element - elemento a insertar.
	 * \param padre - elemento padre
	 * \return Nodo creado.*/
	GraphicNode* Insertar(Element*, Element* padre= NULL);
	/**\brief Insertar elemento.
	 * Inserta elemento colgando de un nodo
	 * \param element - elemento a insertar.
	 * \param padre - nodo padre
	 * \return Nodo creado.*/
	GraphicNode* Insertar(Element*, GraphicNode *);
	/**\brief Devuelve el nodo raiz.
	 * \return Nodo raiz.*/
	GraphicNode* getRaiz() const;
	/**\brief Devuelve el nodo que contiene el elemento.
	 * \param element - elemento que contiene el nodo
	 * \return Nodo.*/
	GraphicNode* getNode(Element*) const;
	/**\brief Existe elemento.
	 * \param element - elemento a comprobar
	 * \return true - si existe.*/
	bool Existe(Element*) const;
	/**\brief Existe elemento.
	 * funcion auxiliar
	 * \param element - elemento a comprobar
	 * \param existe -  buleano anterior.
	 * \return true - si existe.*/
	bool ExisteAux(Element*, bool&) const;
	/**\brief Arbol en preorden.
	 * \return vector<Element*> - arbol en forma de vector.*/
	vector<Element*> Preorden() const;
	/**\brief Busca elemento.
	 * \param elemento - elemento a buscar
	 * \return nodo - que contiene el elemento.*/
	GraphicNode* BuscarElemento(Element*) const;
	/**\brief Busca elemento.
	 * funcion auxiliar
	 * \param elemento - elemento a buscar
	 * \param nodo - nodo raiz anterior
	 * \return nodo - que contiene el elemento.*/
	GraphicNode* BuscarElementoAux(Element*, GraphicNode*) const;
	/**\brief Busca elemento.
	 * MEDIANTE EL ID
	 * \param _id - id del elemento a buscar
	 * \return nodo - que contiene el elemento.*/
	GraphicNode* BuscarElemento(int) const;
	/**\brief Busca elemento.
	 * MEDIANTE EL ID
	 * funcion auxiliar
	 * \param _id - id del elemento a buscar
	 * \return nodo - que contiene el elemento.*/
	GraphicNode* BuscarElementoAux(int, GraphicNode*) const;
	/**\brief Busca elemento, con un nodo
	 * \param elemento - nodo a buscar
	 * \return nodo - que contiene el elemento.*/
	GraphicNode* BuscarElemento(GraphicNode*) const;
	/**\brief Busca elemento, con un nodo
	 * funcion auxiliar
	 * \param elemento - nodo a buscar
	 * \return nodo - que contiene el elemento.*/
	GraphicNode* BuscarElementoAux(GraphicNode*, GraphicNode*) const;
	/**\brief Devuelve el nodo padre.
	 * \param elemento - del que obtener el padre
	 * \return Nodo padre.*/
	GraphicNode* getPadre(GraphicNode*) const;
	/**\brief Devuelve el nodo por su id.
	 * \param id_ - id del nodo a buscar
	 * \return Nodo con id = id_.*/
	GraphicNode* getNodeById(int id_) const;
	/**\brief Devuelve el nodo padre.
	 * funcion auxiliar
	 * \param elemento - del que obtener el padre
	 * \return Nodo padre.*/
	GraphicNode* getPadreAux(GraphicNode*, GraphicNode*, GraphicNode*) const;
	/**\brief Renderizado del arbol.
	 * Pinta los elementos del arbol*/
	void Render() const;
	/**\brief Borra la rama apartir de un nodo
	 * \param elemento - elemento al que borrar sus hijos*/
	void BorrarRama(GraphicNode*);
	/**\brief Borra la rama apartir de un elemento
	 * \param elemento - elemento al que borrar sus hijos*/
	void BorrarRama(Element*);
	/**\brief Borra el elemento (y su rama)
	 * \param elemento - elemento que queremos borrar*/
	void BorrarElemento(Element*) const;

private:
	/**\brief Arbol en preorden.
	 * funcion auxiliar
	 * \return vector<Element*> - arbol en forma de vector.*/
	void PreordenAux(vector<Element*>&) const;
	/**\brief Nodo raiz*/
	GraphicNode *raiz;
};

class GraphicNode {

	friend class GraphicTree;

public:
    /**\brief Constructor*/
	GraphicNode();
	GraphicNode(Element *, int id_ = -1);
    /**\brief Destructor*/
	virtual ~GraphicNode();
    /**\brief Constructor de copia
     *param node - nodo a copiar.*/
	GraphicNode(const GraphicNode&);
	  /**\brief Sobrecarga del operador de asignación
        * \param node - nodo a copiar.
        * \return Devuelve una copia del nodo.*/
	GraphicNode & operator=(const GraphicNode&);
	  /**\brief Obtener el vector de hijos
	   * \return hijos - vector de hijos*/
    vector<GraphicTree*> getHijos() const;
	  /**\brief Obtener el elemento del nodo
      * \return element - elemento del nodo*/
    Element *getItem() const;
	/**\brief Asignar un vector de hijos
	 * \param hijos - nuevo vector de hijos*/
    void setHijos(vector<GraphicTree*> hijos);
	/**\brief Asignar un elemento al nodo
	 * \param item - nuevo elemento del nodo*/
    void setItem(Element *item);
	/**\brief Renderizado del elemento*/
    void Render();
	/**\brief Asignar visibilidad al nodo
	 * \param visible_ - asigna si es visible*/
    void setVisible(bool);
	/**\brief Asignar un id al nodo
	 * \param id_ - nuevo id del nodo*/
    void setId(int);
	/**\brief Obtiene el id del nodo
	 * \return id del nodo*/
    int getId() const;
	/**\brief Obtiene visibilidad del nodo
	 * \return visible del nodo*/
    bool getVisible() const;
private:
	/**\brief Elemento del nodo*/
	Element* item;
	/**\brief Vector de hijos*/
	vector<GraphicTree*> hijos;
	/**\brief Visibilidad del elemento*/
	bool visible;
	/**\brief id del nodo*/
	int id;
};

#endif /* GRAPHICTREE_H_ */
