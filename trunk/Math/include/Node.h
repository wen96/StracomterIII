/*
 * Node.h
 *
 *  Created on: 06/11/2011
 *      Author: Team Chutaos
 */

#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <cstring>
#include <vector>
#include "Point.h"

using namespace std;

/**\brief Class Node (nodo)
 * Clase para almacenar y gestionar un nodo y sus aristas
 */
class Node {
	/**\brief Operador de salida para el Node
	 *	Muestra el nodo de la siguiente forma:
	 *		Nodo id (x,y)
	 *			=>idDestino
	 *			...
	 *	Donde:
	 *		id = id del nodo
	 *		(x,y) posicion del nodo
	 *		=> Indica que es un arista
	 *			idDestino = id del nodo destino de arista
	 *		... Resto de aristas si las hay
	 */
	friend ostream& operator<<(ostream &os, const Node &n);
public:
	/**\brief Constructor de Node por defecto
	 */
	Node();
	/**\brief Destructor de Node
	 */
	virtual ~Node();

	/**\brief Constructor de Node sobrecargado para id
	 * \param n id
	 */
	Node(int n);

	/**\brief Constructor de Node sobrecargado para posicion
	 * \param n Point con la posicion
	 */
	Node(Point n);

	/**\brief Constructor de Node sobrecargado para aristas
	 * \param a vector de punteros a nodo
	 */
	Node(vector<Node*> a);

	/**\brief Constructor de Node sobrecargado para id y nombre
	 * \param n id
	 * \param ps Point con la posicion
	 */
	Node(int n, Point ps);

	/**\brief Constructor de Node sobrecargado para id y nombre y aristas
	 * \param n id
	 * \param ps Point con la posicion
	 * \param a vector de punteros a nodo
	 */
	Node(int n, Point ps, vector<Node*> a);

	/**\brief Constructor de copia para Node
	 * \param obj, Nodo a copiar
	 */
	Node(const Node &obj);

	/**\brief Sobrecarga del operador =
	 * \param obj, Nodo a copiar
	 * \return Node con el nodo resultante
	 */
	Node& operator=(const Node &obj);

	/**\brief Funcion de Node getAdjancency
	 * Devuelve un vector con la adyacencia de aristas del mismo, es decir, todos los nodos con los que esta conectado
	 * \return vector<Node*> Vector de punteros a Node con la adyacencia del nodo
	 */
	vector<Node*> getAdjacency();

	/**\brief Funcion de Node addArist
	 * Anyade una arista al vector de aristas con push_back
	 *\param node puntero a Node con el nodo destino
	 *\return bool indicando si la arista se anyadio correctamente
	 */
	bool addArist(Node *node);

	/**\brief Funcion de Node removeArist
	 * Borra una arista de la lista de adyacencia del Nodo, es decir, borrar un elemento del vector de punteros a Nodo
	 * Atencion: se borrara solo la primera arista que apunte a ese nodo
	 *\param node puntero de Node a borrar
	 *\return bool indicando si la arista se borro o no (true = se ha borrado; false = no se ha borrado)
	 */
	bool removeArist(Node* node);

	/**\brief Funcion de Node removeAllArist
	 * Borrara todas las aristas de la lista de adyacencia del Nodo que apunten a node, es decir, borrar los elmentos del vector de punteros a Nodo
	 *\param node puntero de Node a borrar
	 *\return bool indicando si la arista se borro o no (true = se ha borrado; false = no se ha borrado)
	 */
	bool removeAllArist(Node* node);

	/**\brief Funcion de Node removeAllAristById
	 * Borra las aristas de su adyacencia con un id, es decir, borrara uno o mas elementos del vector de punteros a Nodo que tengan un id concreto
	 * Atencio: Si existe mas de un nodo en la lista de adyacencia con ese id se borrara tambien
	 *\param n id de la arita o aristas a borrar
	 *\return bool indicando si la arista se borro o no (true = se ha borrado; false = no se ha borrado)
	 */
	bool removeAllAristById(int n);

	/**\brief Funcion de Node removeAristById
	 * Borra la arista de su adyacencia con un id, es decir, borrara un elmento del vector de punteros a Nodo que tengan un id concreto
	 * Atencio: Si existe mas de un nodo en la lista de adyacencia con ese id no se borrara
	 *\param n id de la arita o aristas a borrar
	 *\return bool indicando si la arista se borro o no (true = se ha borrado; false = no se ha borrado)
	 */
	bool removeAristById(int n);

	/**\brief Funcion de Node getPosition
	 * Devuelve la posicion del nodo, es decir, el atributo position de Node
	 *\return Point con la posicion
	 */
	Point getPosition() const;

	/**\brief Funcion de Node getId
	 * Devuelve el id del nodo, es decir, el atributo id de Node
	 *\return int con el id
	 */
	int getId() const;

	/**\brief Funcion de Node setPosition
	 * Cambia la posicion del nodo, es decir, cambia el atributo name del nodo
	 *\param n Point con la posicion a la que cambiar el nombre del nodo
	 */
	void setPosition(Point n);

	/**\brief Funcion de Node setId
	 * Cambia el id del nodo, es decir, cambia el atributo id del nodo
	 *\param n int con el numero al que cambiar el id del nodo
	 */
	void setId(int n);

	/**\brief Funcion de Node getArists
	 * Devuelve las aritas de un nodo
	 * \return vector<Node*> con las aristas
	 */
	vector<Node*> getArists();

	bool showArists();

private:
	/**\brief Atributo id
	 * int para almacenar el id el nodo
	 */
	int id;

	/**\brief Atributo position
	 * Position para almacenar la posicion del nodo
	 */
	Point position;

	/**\brief Atributo arists
	 * Vector stl de punteros a nodo (Node*) con la adyacencia del nodo
	 */
	vector<Node*> arists;



};

#endif /* NODE_H_ */
