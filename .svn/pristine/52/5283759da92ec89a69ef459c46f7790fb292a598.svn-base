/*
 * GraphUD.cc
 *
 *  Created on: 06/11/2011
 *      Author: Team Chutaos
 */

//FICHERO INUTIL A CAUSA DE CREAR EL GRAFO CON TEMPLATES YA QUE ESTO OBLIGA (NO SE PORQUE) A QUE TODO ESTE DEFINIDO EN EL .H
/*
#include "GraphUD.h"
#include <vector>

using namespace std;

template<class T>
GraphUD<T>::GraphUD() {
	numNodes = 0;
	nodes.clear();
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
		cout << (**iter) << endl;
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
}*/

