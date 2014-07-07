/*
 * GraphUD.h
 *
 *  Created on: 06/11/2011
 *      Autor: Team Chutaos
 */

#ifndef GRAPHUD_H_
#define GRAPHUD_H_

#include <iostream>
#include <vector>
#include "Point.h"


using namespace std;




/**\brief Class GraphUD
 * Grafo no dirigido de Node.
 * Grafo que controla un conjunto de Node segun un numero identificador del mismo.
 * Los id de numeracion de los nodos empiezan en 0 y cuenten a partir de ahi.
 * Si se borra un nodo y se inserta otro, no se le aplicara el id del que se ha borrado si no que se aplicara
 * el siguiente id que se aplicaria correspondiendo con el numero de nodos insertados.
 */
template<class T>
class GraphUD {
	/**\brief Operador salida para el grafo
	 * Muestra los nodos uno a uno con un salto de linea entre ellos
	 */
	template<class U>
	friend ostream& operator<<(ostream &os, const GraphUD<U> &g);
public:
	/**\brief Constructor por defecto
	 */
	GraphUD();
	/**\brief Destructor por defecto
	 */
	virtual ~GraphUD();

	/**\brief Constructor de copia
	 */
	GraphUD(const GraphUD<T> &);

	/**\brief funcion de GraphUD insertArist
	 * Inserta una arista entre 2 nodos pasador por parametro
	 * \param ori int con el id del nodo origen
	 * \param dest int con el id del nodo destino
	 * \return bool indicando si se ha borrado o no
	 */
	bool insertArist(int ori, int dest);

	/**\brief funcion de GraphUD removetArist
	 * Borra una arista entre 2 nodos pasador por parametro
	 * \param ori int con el id del nodo origen
	 * \param dest int con el id del nodo destino
	 * \return bool indicando si se ha borrado o no
	 */
	bool removeArist(int ori, int dest);

	/**\brief funcion de GraphUD addNode
	 * Inserta un nodo con la posicion.
	 * El id del nodo sera el numero de nodos insertado en ese momento (numNodes) empezando por 0
	 * \param p Point con la posicion del nodo
	 * \return bool indicando si se ha insertado o no
	 */
	bool addNode(Point p);

	/**\brief funcion de GraphUD addNode
	 * Inserta un nodo en una posicion con unas aristas
	 * El id del nodo sera el numero de nodos insertado en ese momento (numNodes) empezando por 0
	 * \param p Point con la posicion del nodo
	 * \param a vector<Node*>, vector de punteros a Node con las aristas del nodo
	 * \return bool indicando si se ha insertado o no
	 */
	bool addNode(Point p, vector<T*> a);

	/**\brief funcion de GraphUD addNode
	 * Inserta, si no existe ya, un nodo pasado por paretro
	 * \param n Node con a insertar
	 * \return bool indicando si se ha insertado o no
	 */
	bool addNode(T n);

	/**\brief funcion de GraphUD removeNode
	 * Borra un nodo del grafo que tenga el id pasado por parametro
	 * \param id id del nodo a borrar
	 * \return bool indicando si se ha borrado o no
	 */
	bool removeNode(int id);

	/**\brief funcion de GraphUD removeNode
	 * busca un nodo mediante un id pasado por parametro y devuelve si lo encuentra o no.
	 * \param id id del nodo a buscar
	 * \return bool indicando si existe o no
	 */
	bool existsNode(int id);

	/**\brief funcion de GraphUD getNumNodes
	 * Devuelve el numero de nodos del grafo empezando en 1
	 * \retun int con el numero de nodos
	 */
    int getNumNodes() const;

	/**\brief funcion de GraphUD getNodes
	 * Devuelve un vector stl de punteros a nodo con todos los nodos del grafo
	 */
    vector<T*> getNodes() const;

private:
    /**\brief numNodes int con el numero de nodos que tiene el grafo
     */
	int numNodes;
	/**\brief nodes vector<Node*> Vector de punteros a nodo con los nodos que contiene el grafo
	 */
	vector<T*> nodes;

	/**\brief funcion de GraphUD setNumNodes
	 * Se le pasa un entero y lo aplica a la propiedad numNodes del grafo
	 *\param n int con el entero a aplicar
	 */
	void setNumNodes(int n);

	/**\brief funcion de GraphUD setNodes
	 * Se le pasa un vendor de nodos y lo aplica a la propiedad nodes del grafo
	 *\param vector<Node*> con los nodos a aplicar
	 */
	void setNodes(vector<T*> n);
};

//DECLARACIONES DE TODAS LA FUNCIONES YA QUE AL SER TEMPLATE NO DEJA QUE EL RESTO DE DECLARACIONES ESTEN EN OTRO FICHERO
//ES RARO SI, SI ENCONTRAIS COMO SOLUCIONARLO COMENTADMELO

template<class T>
GraphUD<T>::GraphUD() {
	numNodes = 0;
	nodes.clear();
}

template<class T>
GraphUD<T>::GraphUD(const GraphUD<T> &gud) {
	numNodes = gud.numNodes;

	typename std::vector<T*>::iterator iter;
	for(iter = nodes.begin(); iter != nodes.end(); iter++){
		T *nodo = new T(**iter);

		nodes.push_back(nodo);
	}
}

template<class T>
GraphUD<T>::~GraphUD() { //el destructor sigue sin funcionar muy bien
	if (this != NULL) {
		if (!nodes.empty()) {
			T *forDelete = NULL;

			typename vector<T*>::iterator iter;
			iter = nodes.begin();
			while (iter < nodes.end()) {
				forDelete = (*iter);
				nodes.erase(iter);
				if (forDelete != NULL)
					delete forDelete;
			}

			nodes.clear();

			forDelete = NULL;
		}
		numNodes = 0;
	}
}

template<class T>
int GraphUD<T>::getNumNodes() const {
	return numNodes + 1;
}

template<class T>
vector<T*> GraphUD<T>::getNodes() const {
	return nodes;
}

template<class T>
bool GraphUD<T>::existsNode(int id) {
	bool existe = false;
	typename vector<T*>::iterator iter;
	for (iter = nodes.begin(); iter < nodes.end(); iter++) {
		if ((*iter)->getId() == id) {
			existe = true;
			break;
		}
	}

	return existe;
}

template<class T>
bool GraphUD<T>::insertArist(int ori, int dest) {
	typename vector<T*>::iterator iter;
	T *node1 = NULL;
	T *node2 = NULL;
	bool insertado = false;

	//TODO: Comprobar que no se inserte mas de una arista igual

	for (iter = nodes.begin(); iter < nodes.end(); iter++) {
		if ((*iter)->getId() == ori) {
			node1 = (*iter);
			break;
		}
	}

	for (iter = nodes.begin(); iter < nodes.end(); iter++) {
		if ((*iter)->getId() == dest) {
			node2 = (*iter);
			break;
		}
	}

	if (node1 != NULL && node2 != NULL) {
		node1->addArist(node2);
		node2->addArist(node1);
		insertado = true;
	}

	return insertado;
}

template<class T>
bool GraphUD<T>::removeArist(int ori, int dest) {
	typename vector<T*>::iterator iter;
	T *node1 = NULL;
	T *node2 = NULL;
	bool borrado = false;

	//TODO: Comprobar que no se inserte mas de una arista igual

	for (iter = nodes.begin(); iter < nodes.end(); iter++) {
		if ((*iter)->getId() == ori) {
			node1 = (*iter);
			break;
		}
	}

	for (iter = nodes.begin(); iter < nodes.end(); iter++) {
		if ((*iter)->getId() == dest) {
			node2 = (*iter);
			break;
		}
	}

	if (node1 != NULL && node2 != NULL) {
		node1->removeArist(node2);
		node2->removeArist(node1);
		borrado = true;
	}

	return borrado;
}

template<class T>
bool GraphUD<T>::addNode(Point p) {
	bool insertado = false;
	T *newNode = NULL;
	newNode = new T(numNodes, p);
	nodes.push_back(newNode);
	numNodes++;
	insertado = true;

	////cout << *(nodes[nodes.size() -1]) << endl;

	return insertado;
}

template<class T>
bool GraphUD<T>::addNode(Point p, vector<T*> a) {
	bool insertado = false;
	T *newNode = NULL;
	newNode = new T(numNodes, p, a);
	nodes.push_back(newNode);
	numNodes++;
	insertado = true;
	return insertado;
}

template<class T>
bool GraphUD<T>::addNode(T n) {
	bool insertado = false;
	if (!this->existsNode(n.getId())) {
		T *newNode = NULL;
		newNode = new T(n);
		nodes.push_back(newNode);
		numNodes++;
		insertado = true;
	} else {
		insertado = false;
	}
	return insertado;
}

template<class T>
bool GraphUD<T>::removeNode(int id) {
	typename vector<T*>::iterator iter;
	bool borrado = false;
	T *forDelete = NULL;

	for (iter = nodes.begin(); iter < nodes.end(); iter++) {
		if ((*iter)->getId() == id) {
			forDelete = (*iter);
			nodes.erase(iter);
			delete forDelete;
			borrado = true;
			break;
		}
	}
	return borrado;
}

template<class U>
ostream& operator<<(ostream &os, const GraphUD<U> &g) {
	typename vector<U*>::const_iterator iter;
	for (iter = g.nodes.begin(); iter < g.nodes.end(); iter++) {
		//cout << (**iter) << endl;
	}

	return os;
}

template<class T>
void GraphUD<T>::setNumNodes(int n) {
	numNodes = n;
}

template<class T>
void GraphUD<T>::setNodes(vector<T*> n) {
	nodes = n;
}

#endif /* GRAPHUD_H_ */
