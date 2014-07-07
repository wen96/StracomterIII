/*
 * Map.cc
 *
 *  Created on: Nov 27, 2011
 *      Author: rellik
 */

#include "Map.h"

Map::Map(){
	mapFileS = "";
	mapGraph = GraphUD<Node>();
}

Map::Map(const Map &m){
	mapFileS = m.mapFileS;
	mapGraph = m.mapGraph;
}

Map::~Map(){
	mapFileS = "";
	mapGraph = GraphUD<Node>();
}

void Map::setMap(string fName){
	mapFileS = fName;

	generatePointVectors();
}

GraphUD<Node> Map::getGraph(){
	return mapGraph;
}

std::vector<Point> Map::getVertex(){
	return puntos;
}

std::vector<std::vector<Point> > Map::getObjects(){
	return objectList;
}

void Map::generatePointVectors() {
	GraphUD<Node> mapa;

	ifstream fin;

	fin.open(mapFileS.c_str(), ios::in);

	if (fin.is_open()) {
		string line;
		getline(fin, line);
		getline(fin, line);
		getline(fin, line);

		getline(fin, line);

		while (line != "\t\t</vertexlist>") {
			int *info = getInfo(line);
			Point p(info[1], info[2]);
			//cout << p << endl;
			mapa.addNode(p);
			puntos.push_back(p);
			delete[] info;
			getline(fin, line);
		}

		getline(fin, line);
		getline(fin, line);
		while (line != "</map>") {
			getline(fin, line);
			getline(fin, line);
			std::vector<Point> obj;
			while (line != "\t\t</vertexlist>") {
				int *info = getInfo(line);
				Point p(info[1], info[2]);
				//cout << p << endl;
				mapa.addNode(p);
				obj.push_back(p);
				delete[] info;
				getline(fin, line);
			}
			objectList.push_back(obj);
			getline(fin, line);
			getline(fin, line);
		}
	}else{
		cerr << "No se ha podido abrir el fichero" << endl;
	}

	mapGraph = mapa;
}


int *
Map::getInfo(string line) {
	string id = "";
	string x = "";
	string y = "";
	int count = 0;

	for (int i = 0; i < line.length(); i++) {
		if (line[i] == '=' && count == 0) {
			i++;
			while (line[i] != '>') {
				id += line[i];
				i++;
			}
			count++;
		}
		if (line[i] == '>' && count == 1) {
			i++;
			while (line[i] != ',') {
				x += line[i];
				i++;
			}
			count++;
		}
		if (line[i] == ',' && count == 2) {
			i++;
			while (line[i] != '<') {
				y += line[i];
				i++;
			}
			count++;
		}
		if (count == 3) {
			break;
		}
	}

	int *info = new int[3];

	info[0] = atoi(id.c_str());
	info[1] = atof(x.c_str());
	info[2] = atof(y.c_str());

	return info;
}

