/*
 * ASNode.h
 *
 *  Created on: Nov 11, 2011
 *      Author: Chutaos Team
 */

#ifndef ASNODE_H_
#define ASNODE_H_

#include <cstdlib>

using namespace std;

#include "Node.h"

class ASNode{

	friend ostream& operator<<(ostream &os, const ASNode &n);

public:

	/**\brief Constructor vacio
	 */
	ASNode();

	/**\brief Destructor por defecto
	 */
	virtual ~ASNode();

	/**\brief Constructor con un punto
	 */
    ASNode(Point centro);

    /**\brief Constructor de copia
	 */
    ASNode(const ASNode &asn);

    /**\brief Sobrecarga del operador de asignación
	 */
    ASNode & operator =(const ASNode &asn);

    /**\brief Sobrecarga de la comparacion
     * @param asn Nodo a comparar con this
     * @return True si this y asn son iguales.
     */
    bool operator==(const ASNode &asn);

    /**\brief Getter de f
     * Suma g + h lo asigna a f y devuelve el valor de f
     * f = g + h
     */
    double getF() const;

    /**\brief Getter de G
     */
    double getG() const;

    /**\brief Getter de H
     */
    double getH() const;

    /**\brief Getter de next
     */
    int getNext() const;

    /**\brief Getter de numChildren
     */
    double getNumChildren() const;

    /**\brief Getter de parent
     */
    int getParent() const;

    /**\brief Setter de g y h
	 * Ademas de asignarles esos valores a las variables calcula el valor de f
	 */
	void setGH(double G, double H);

    /**\brief Setter de next
     */
    void setNext(int Next);

    /**\brief Setter de numChildren
     */
    void setNumChildren(double NumChildren);

    /**\brief Setter de parent
     */
    void setParent(int Parent);

    /**\brief Setter del punto central
     */
    void setCenter(Point center_);

    /**\brief Getter de ls poición del nodo
     */
    Point getPosition();
    int getId() const;
    void setId(int id_);

    bool isInAdyacence(int id);

    bool addEdge(int  child);
    bool removeEdge(int child);

    std::vector<int> getAdyacence();

private:

    /**\brief Coste para llegar desde el nodo origen
	 */
    double g;

    /**\brief Coste para llegar al destino
	 */
    double h;

    /**\brief Suma de los costes g y h
	 */
    double f;

    /**\brief Numero de hijos que tiene este nodo
	 * Es el numero de nodos a los que se puede acceder desde este nodo.
	 */
    double numChildren;

    /**\brief Nodo desde el que se ha llegado
	 * Nodo desde el que se ha llegado durante el ultimo paso de A*
	 */
    int parent;

    /**\brief Nodo al que se va
	 * Nodo al que se pasara segun la ultima iteracion de A*
	 */
    int next;

    /**\brief Nodo con la posicion y los nodos adjacentes
     */
    //Node *node;

    /**\brief Lista de nodos adyacentes
     * Lista de los nodos que comparten una arista con este nodo almacenados mediante su id
     */
    std::vector<int> adyacentes;

    /**\brief Pone los valores de todas las variables a 0 o NULL
     */
    void initialize();

    /**\brief Copia los contenidos de asn en este nodo
     */
    void copy(const ASNode &asn);

    int id;
    Point center;

};

#endif /* ASNODE_H_ */
