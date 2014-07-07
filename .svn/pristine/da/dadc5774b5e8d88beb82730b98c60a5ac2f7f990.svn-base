/*
 * NavGraph.h
 *
 *  Created on: Nov 18, 2011
 *      Author: Chutaos Team
 */

#ifndef NAVGRAPH_H_
#define NAVGRAPH_H_

#include <iostream>
#include "ASNode.h"
#include "Point.h"
#include <vector>

using namespace std;

class NavGraph{
	friend ostream& operator<<(ostream &os, const NavGraph &n);

public:


	NavGraph();

	~NavGraph();

	NavGraph(const NavGraph &ng);

	NavGraph & operator=(const NavGraph &ng);

	ASNode getNode(int id) const;

	ASNode getNode(Point p);


	int addNode(ASNode asn);

	bool removeNode(int id);

	bool addEdge(int ori, int dest);

	bool removeEdge(int ori, int dest);


	vector<ASNode> getAdyacence(int id);

	/**\brief funcion getAdyacence que devuelve la adyacencia de un nodo
	 * Devuelve la adyacencia de un nodo con sus calculos de g y h ya hechos
	 *
	 * @param id int del nodo a buscar la adyacencia
	 * @return vector<ASNode*> que devuelve un vector con los punteros adyacentes
	 */
	vector<ASNode> getAdyacenceCalculated(int idOrigen, int idDestino, int recorrido);

	void setNext(int id,int next);
	void setParent(int id,int parent);

	/** Variable nodes
	 * es publica para empezar a pensar en eficiencia
	 */
	vector<ASNode> nodes;

private:
	int numNodes;
	int nextId;
	double heuristicH(Point ori, Point dest);
	double absDouble(double n);
};


#endif /* NAVGRAPH_H_ */
