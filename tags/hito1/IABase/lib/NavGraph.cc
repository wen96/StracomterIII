/*
 * NavGraph.cc
 *
 *  Created on: Nov 18, 2011
 *      Author: Chutaos Team
 */
#include "NavGraph.h"

NavGraph::NavGraph() {
	numNodes = 0;
	nextId = 0;
	nodes.clear();
}

NavGraph::~NavGraph() {
	if (this != NULL) {
		if (!nodes.empty()) {
			nodes.clear();
		}
		numNodes = 0;
		nextId = 0;
	}
}

NavGraph::NavGraph(const NavGraph & ng) {
	numNodes = ng.numNodes;
	nextId =  ng.nextId;
	for (unsigned int i=0; i < ng.nodes.size(); i++){
		this->nodes.push_back(ng.nodes[i]);
	}
}

NavGraph & NavGraph::operator =(const NavGraph &ng) {
	if (this != &ng){
		//this->~NavGraph();
		numNodes = ng.numNodes;
		nextId =  ng.nextId;
		nodes = ng.nodes;
		/*for (unsigned int i =0; i < ng.nodes.size(); i++){
			nodes.push_back(ng.nodes[i]);
		}*/

	}
	return *this;
}

ASNode NavGraph::getNode(int id) const {
	ASNode node;
	for (unsigned int i = 0; i < nodes.size(); i++){
		if (nodes[i].getId() == id){
			node = nodes[i];
			break;
		}
	}
	return node;
}

ASNode NavGraph::getNode(Point p) {
	ASNode node;
	for (unsigned int i = 0; i < nodes.size(); i++){
		if (nodes[i].getPosition() == p){
			node = nodes[i];
			break;
		}
	}
	return node;
}

int NavGraph::addNode(ASNode asn) {

	int id = nextId;
	bool existe = false;

	vector<ASNode>::iterator iter;
	for (iter = nodes.begin(); iter < nodes.end() && !existe; iter++) {
		if((*iter).getPosition() == asn.getPosition()){
			id = (*iter).getId();
			existe = true;
		}
	}

	if(!existe){
		ASNode aux = asn;
		aux.setId(id);
		nodes.push_back(aux);

		nextId++;
		numNodes++;
	}
	return id;
}

bool NavGraph::removeNode(int id) {
	bool borrado = false;
	vector<ASNode>::iterator iter;
	for (iter = nodes.begin(); iter < nodes.end(); iter++) {
		if ((*iter).getId() == id) {
			nodes.erase(iter);
			borrado = true;
			break;
		}
	}
	return borrado;
}

bool NavGraph::addEdge(int ori, int dest) {
	bool added = false;
	if (ori!=dest){
		bool getori = false, getdest = false;
		unsigned int oriNode = -1, destNode = -1;
		for (unsigned int i = 0; i < nodes.size(); i++){
			if (nodes[i].getId() == ori){
				oriNode = i;
				getori = true;
			}else if(nodes[i].getId() == dest){
				destNode = i;
				getdest = true;
			}
			if (getori && getdest){
				if (!nodes[oriNode].isInAdyacence(dest)){
					nodes[oriNode].addEdge(nodes[destNode].getId());
					nodes[destNode].addEdge(nodes[oriNode].getId());
					added = true;
				}
				break;
			}
		}
	}
	return added;
}

bool NavGraph::removeEdge(int ori, int dest) {
	bool removed = false;
	bool getori = false, getdest = false;
	unsigned int oriNode = -1, destNode = -1;
	for (unsigned int i = 0; i < nodes.size(); i++){
		if (nodes[i].getId() == ori){
			oriNode = nodes[i].getId();
			getori = true;
		}else if(nodes[i].getId() == dest){
			destNode = nodes[i].getId();
			getdest = true;
		}
		if (getori && getdest){
			if (nodes[oriNode].isInAdyacence(dest)){
				nodes[oriNode].removeEdge(nodes[destNode].getId());
				nodes[destNode].removeEdge(nodes[oriNode].getId());
				removed = true;
			}
			break;
		}
	}
	return removed;
}

vector<ASNode> NavGraph::getAdyacenceCalculated(int idOrigen, int idDestino, int recorrido){
	//Vector para los punteros de nodos adyacentes
	vector<ASNode> aux;
	//Vector para los id de punteros de nodos adyacentes
	vector<int> ady;
	ASNode origen;
	ASNode destino;
	bool foundOri = false;
	bool foundDest = false;

	//Conseguimos la adyacencia del nodo
	for (unsigned int i = 0; i < nodes.size(); i++){
		if (nodes[i].getId() == idOrigen){
			ady = nodes[i].getAdyacence();
			origen = nodes[i];
			foundOri = true;
		}
		if (nodes[i].getId() == idDestino){
			destino = nodes[i];
			foundDest = true;
		}
		if (foundOri && foundDest) break;
	}

	//Si se encuentra hacemos el calculo de g, h y f
	if (foundOri && foundDest){
		ASNode auxNode;
		double g = 0;
		double h = 0;
		Point destPosition = destino.getPosition();
		Point origPosition = origen.getPosition();
		//Creamos el vector de punteros con la adyacencia del nodo
		for (unsigned int i = 0; i < ady.size(); i++){
			auxNode =this->getNode(ady[i]);
			g = Point::distance(origPosition, auxNode.getPosition()) + recorrido;
			h = this->heuristicH(destPosition, auxNode.getPosition());
			auxNode.setGH(g,h);
			auxNode.setParent(idOrigen);
			aux.push_back(auxNode);
		}
	}else{
		cerr << "###ERROR: El nodo " << idOrigen << " o " << idDestino << " no existe" << endl;
	}


	return aux;
}

vector<ASNode> NavGraph::getAdyacence(int id) {
	//Vector para los punteros de nodos adyacentes
	vector<ASNode> aux;
	//Vector para los id de punteros de nodos adyacentes
	vector<int> ady;
	ASNode origen;
	bool found = false;

	//Conseguimos la adyacencia del nodo
	for (unsigned int i = 0; i < nodes.size(); i++){
		if (nodes[i].getId() == id){
			ady = nodes[i].getAdyacence();
			origen = nodes[i];
			found = true;
			break;
		}
	}

	//Si se encuentra hacemos el calculo de g, h y f
	if (found){
		ASNode destino;
		Point destPosition = origen.getPosition();
		//Creamos el vector de punteros con la adyacencia del nodo
		for (unsigned int i = 0; i < ady.size(); i++){
			destino =this->getNode(ady[i]);
			aux.push_back(destino);
		}
	}else{
		cerr << "###ERROR: El nodo " << id << " no existe" << endl;
	}


	return aux;
}

double NavGraph::heuristicH(Point ori, Point dest){
	double total = 0;
	total = Point::distance(ori, dest);
	return total;
}

void NavGraph::setNext(int id, int next){
	for (unsigned int i = 0; i < nodes.size(); i++){
		if (nodes[i].getId() == id){
			nodes[i].setNext(next);
			break;
		}
	}
}

void NavGraph::setParent(int id, int parent){
	for (unsigned int i = 0; i < nodes.size(); i++){
		if (nodes[i].getId() == id){
			nodes[i].setParent(parent);
			break;
		}
	}
}

double NavGraph::absDouble(double n){
	if (n < 0){
		return n*(-1.0);
	}else{
		return n;
	}
}

ostream& operator<<(ostream &os, const NavGraph &n){
	os << "####### GRAFO DE NAVEGACION #######" << endl;
	for (unsigned int i = 0; i < n.nodes.size(); i++){
		os << n.nodes[i] << endl;
	}

	return os;
}

