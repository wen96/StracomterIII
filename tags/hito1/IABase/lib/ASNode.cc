/*
 * ASNode.cpp
 *
 *  Created on: Nov 11, 2011
 *      Author: ChutaosTeam
 */

#include "ASNode.h"

bool ASNode::operator==(const ASNode &asn){
	//ESTO NO ES LO MISMO QUE MIRAR SI SON IGUALES...
	return center == asn.center;
}

void ASNode::initialize() {
	g = 0;
	h = 0;
	f = 0;
	numChildren = 0;
	parent = -1;
	next = -1;
	id = -1;
	center = Point(0,0);
	/*if (node != NULL)
		delete node;
	node = NULL;*/
}

int ASNode::getId() const {
	return id;
}

void ASNode::setId(int id_) {
	id = id_;
}

std::vector<int> ASNode::getAdyacence() {
	return adyacentes;
}

void ASNode::setCenter(Point center_) {
	center = center_;
}

bool ASNode::addEdge(int child) {
	numChildren++;
	adyacentes.push_back(child);
	return true;
}

bool ASNode::isInAdyacence(int id) {
	bool isIn = false;
	for (unsigned int i = 0; i < adyacentes.size();i++){
		if (adyacentes[i]== id){
			isIn = true;
			break;
		}
	}

	return isIn;
}

bool ASNode::removeEdge(int child) {
	bool borrado = false;
	std::vector<int>::iterator iter;
	for (iter = adyacentes.begin(); iter != adyacentes.end(); iter++){
		if ((*iter) == child){
			adyacentes.erase(iter);
			numChildren--;
			borrado = true;
			break;
		}
	}
	return borrado;
}

void ASNode::copy(const ASNode &asn) {
	g = asn.g;
	h = asn.h;
	f = asn.f;
	numChildren = asn.numChildren;
	parent = asn.parent;
	next = asn.next;
	id = asn.id;
	center = asn.center;
	adyacentes = asn.adyacentes;
	/*if (asn.node != NULL)
		node = new Node(*asn.node);
	else
		node = NULL;*/
}

ASNode::ASNode() {
	initialize();
}

ASNode::~ASNode() {
	g = 0;
	h = 0;
	f = 0;
	numChildren = 0;
	parent = 0;
	next = 0;
	id = 0;
	center = Point(0,0);
	/*if (node != NULL)
		delete node;
	node = NULL;*/
}

ASNode::ASNode(Point centro) {
	initialize();
	center = centro;
	//node = new Node(centro);
}

ASNode::ASNode(const ASNode & asn) {
	copy(asn);
}

ASNode & ASNode::operator =(const ASNode & asn) {
	if (this != &asn) {
		initialize();
		copy(asn);
	}
	return *this;
}

double ASNode::getF() const {
	return f;
}

double ASNode::getG() const {
	return g;
}

double ASNode::getH() const {
	return h;
}

int ASNode::getNext() const {
	return next;
}

double ASNode::getNumChildren() const {
	return numChildren;
}

int ASNode::getParent() const {
	return parent;
}

Point ASNode::getPosition() {
	return center;
}

void ASNode::setGH(double G, double H) {
	g = G;
	h = H;
	f = g + h;
}

void ASNode::setNext(int Next) {
	next = Next;
}

void ASNode::setNumChildren(double NumChildren) {
	numChildren = NumChildren;
}

void ASNode::setParent(int Parent) {
	parent = Parent;
}

ostream& operator<<(ostream &os, const ASNode &n){
	os << "ASNode " << n.id << n.center << endl;
	os << "Padre: " << n.parent << endl;
	os << "Next: " << n.next << endl;
	os << "Funcion: " << n.g << " + " << n.h << " = " << n.f << endl;
	os << "Hijos(" << n.numChildren << "):" << endl;
	for (unsigned int i = 0; i < n.adyacentes.size(); i++){
		os << "\tNodo" << n.adyacentes[i] << endl;
	}


	return os;
}




