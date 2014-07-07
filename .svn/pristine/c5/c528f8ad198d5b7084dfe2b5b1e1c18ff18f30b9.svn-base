/*
 * Map.cc
 *
 *  Created on: Nov 27, 2011
 *      Author: Chutaos team
 */

#include "Map.h"
#include "tinyxml.h"


Map::Map() {
	mapFileS = "";
	manager = NULL;
	playerPos = Point(0,0);
}

void Map::copia(const Map &mapa){
	infDer = mapa.infDer;
	supIzq = mapa.supIzq;
	mapFileS = mapa.mapFileS;
	murosV = mapa.murosV;
	mesasV = mapa.mesasV;
	columnasV = mapa.columnasV;
	perimetroV = mapa.perimetroV;
	manager = mapa.manager;
	playerPos = mapa.playerPos;
}

Map::Map(const Map &m) {
	copia(m);
}

Map & Map::operator=(const Map & mapa){

	if(this != &mapa){

		copia(mapa);
	}

	return *this;
}

Map::~Map() {
	mapFileS = "";
}

Map::Map(string fName) {
	mapFileS = fName;
	manager = NULL;
}

void Map::setManager(EntityManager *manager_){
	this->manager = manager_;
}

void Map::setMap(string fName) {
	mapFileS = fName;
}

int Map::loadData() {
	int status = 0;

	TiXmlDocument doc(mapFileS.c_str());
	bool loadOkay = doc.LoadFile();

	if (loadOkay) {

		perimetroV.clear();
		mesasV.clear();
		columnasV.clear();
		murosV.clear();
		supIzq = Point();
		infDer = Point();
		playerPos = Point();

		int tipoI = 0;
		int hX = 0, lX = 0, hY = 0, lY = 0;
		Point p;

		TiXmlElement * objeto = doc.RootElement()->FirstChildElement();

		while(objeto != NULL && status >= 0){

			const char *tipoS = objeto->Attribute("type");

			if(tipoS != NULL){
				tipoI = Map::getType(tipoS);

				TiXmlElement * pCoords;
				vector<Point> vPAux;
				int x = 0, y = 0;
				double ang = 0.0;
				int clase = 0;

				switch(tipoI){
				case Core::Map::Perimeter:

					pCoords = objeto->FirstChildElement()->FirstChildElement();

					while(pCoords != NULL){

						pCoords->QueryIntAttribute("x", &x);
						pCoords->QueryIntAttribute("y", &y);

						// Cogemos los puntos extremos
						if(x >= hX)
							hX = x;
						if(x <= lX)
							lX = x;
						if(y >= hY)
							hY = y;
						if(y >= hY)
							hY = y;

						Point p(x, y);

						perimetroV.push_back(p);

						pCoords = pCoords->NextSiblingElement();

					}
					if(manager != NULL){
						manager->addFloor(perimetroV, 0.0, Color<float>(1.0,1.0,1.0));
					}
					status = 1;
					break;

				case Core::Map::Wall:
					// //cout << "Leo una pared" << endl;

					pCoords = objeto->FirstChildElement()->FirstChildElement();

					while(pCoords != NULL){

						pCoords->QueryIntAttribute("x", &x);
						pCoords->QueryIntAttribute("y", &y);

						p.setXY(x, y);

						vPAux.push_back(p);

						pCoords = pCoords->NextSiblingElement();
					}

					if (vPAux.size() != 4){
						status = -1;
					}else{
						murosV.push_back(vPAux);

						if(manager != NULL){
							for(int i = 0; i < 4; i++){
								Point p = vPAux[i];
								p.setZ(2);
								vPAux.push_back(p);
							}
							Color<float> color(1.0,0.0,0.0);
							manager->addWall(vPAux, 0.0, color );
						}
					}

					break;

				case Core::Map::Table:
					// //cout << "Leo una mesa" << endl;

					objeto->QueryIntAttribute("x", &x);
					objeto->QueryIntAttribute("y", &y);

					p.setXY(x, y);

					mesasV.push_back(p);

					if(manager != NULL){
						// addTable
					}

					break;

				case Core::Map::Column:
					// //cout << "Leo una columna" << endl;

					objeto->QueryIntAttribute("x", &x);
					objeto->QueryIntAttribute("y", &y);

					p.setXY(x, y);

					columnasV.push_back(p);

					if(manager != NULL){
						// addTable
					}

					break;

				case Core::Map::Computer:
					// //cout << "Leo un ordenador" << endl;
					if(manager != NULL){
						// addComputer
					}
					break;

				case Core::Map::Door:
					// //cout << "Leo una puerta" << endl;
					if(manager != NULL){
						// addDoor
					}
					break;

				case Core::Map::Player:
					// //cout << "Leo al player" << endl;

					objeto->QueryIntAttribute("x", &x);
					objeto->QueryIntAttribute("y", &y);

					objeto->QueryDoubleAttribute("angle", &ang);

					objeto->QueryIntAttribute("rank", &clase);

					if(manager != NULL){
						playerPos = Point(x,y);
						manager->addPlayer(playerPos, ang, (Core::Entities::Type) clase);
					}

					break;

				case Core::Map::Companion:

					if(manager != NULL){
						// addCompanion
					}
					break;

				case Core::Map::Enemy:

					// //cout << "Leo un enemigo" << endl;

					objeto->QueryIntAttribute("x", &x);
					objeto->QueryIntAttribute("y", &y);

					objeto->QueryDoubleAttribute("angle", &ang);

					objeto->QueryIntAttribute("rank", &clase);

					if(manager != NULL){
						manager->addSmartEntity(Point(x,y), ang, Core::Entities::e_enemy1,NULL);
						//manager->addEnemy(Point(x,y), ang, (Core::Entities::Type) (clase + 4));
					}

					break;

				default:
					// //cout << tipoS << " " << tipoI << endl;
					// //cout << "Tipo \"" << tipoS << "\" desconocido" << endl;
					break;
				}

				objeto = objeto->NextSiblingElement();
			}else{
				status = -2;
			}
		}
		supIzq = Point(lX, lY);
		infDer = Point(hX, hY);

	}

	return status;
}

vector<Point> Map::getPerimeter() {
	return perimetroV;
}

vector<vector<Point> > Map::getObjects() {

	return murosV;
}

vector<vector<Point> > Map::getWalls() {

	return murosV;
}

bool Map::setPerimeter(vector<Point> periVP){

	bool added = false;

	if(periVP.size() >= 3){
		perimetroV = periVP;
		added = true;
	}

	return added;
}

bool Map::addWall(vector<Point> vP){

	murosV.push_back(vP);

	return true;
}

bool Map::addObject(Point p, Core::Entities::Type tipo){
	bool added = false;

	switch(tipo){
	case Core::Entities::e_table:
		mesasV.push_back(p);
		added = true;
		break;

	case Core::Entities::e_columne:
		columnasV.push_back(p);
		added = true;
		break;

	case Core::Entities::e_captain:
		playerPos = p;
		added = true;
		break;

	case Core::Entities::e_enemy1:
		//
		//added = true;
		break;

	case Core::Entities::e_enemy2:
		//
		//added = true;
		break;

	case Core::Entities::e_enemy3:
		//
		//added = true;
		break;
	default:
		break;
	}

	return added;
}



bool Map::writeFile(string fName){
	bool escrito = false;

	TiXmlDocument doc;
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
	doc.LinkEndChild( decl );

	TiXmlElement * map = new TiXmlElement( "map" );
	doc.LinkEndChild( map );

	if(!perimetroV.empty()){

		TiXmlElement * object = new TiXmlElement( "object" );
		map->LinkEndChild( object );

		object->SetAttribute("type", "perimeter");

		TiXmlElement * vxlist = new TiXmlElement( "vertexlist" );
		object->LinkEndChild(vxlist);

		int idCont = 0;
		vector<Point>::iterator pIter;
		for(pIter = perimetroV.begin(); pIter != perimetroV.end(); pIter++){
			TiXmlElement * vertex = new TiXmlElement( "vertex" );
			vertex->SetAttribute("id", idCont);
			idCont++;
			vertex->SetAttribute("x", (*pIter).getX());
			vertex->SetAttribute("y", (*pIter).getY());

			vxlist->LinkEndChild(vertex);
		}

		vector<vector<Point> >::iterator vvIter;
		for(vvIter = murosV.begin(); vvIter != murosV.end(); vvIter++){
			object = new TiXmlElement( "object" );
			map->LinkEndChild( object );

			object->SetAttribute("type", "wall");

			vxlist = new TiXmlElement( "vertexlist" );
			object->LinkEndChild(vxlist);

			idCont = 0;
			for(pIter = (*vvIter).begin(); pIter != (*vvIter).end(); pIter++){
				TiXmlElement * vertex = new TiXmlElement( "vertex" );
				vertex->SetAttribute("id", idCont);
				idCont++;
				vertex->SetAttribute("x", (*pIter).getX());
				vertex->SetAttribute("y", (*pIter).getY());

				vxlist->LinkEndChild(vertex);
			}
		}

		for(pIter = mesasV.begin(); pIter != mesasV.end(); pIter++){

			object = new TiXmlElement( "object" );
			map->LinkEndChild( object );

			object->SetAttribute("type", "table");

			object->SetAttribute("x", (*pIter).getX());
			object->SetAttribute("y", (*pIter).getY());
		}

		for(pIter = columnasV.begin(); pIter != columnasV.end(); pIter++){

			object = new TiXmlElement( "object" );
			map->LinkEndChild( object );

			object->SetAttribute("type", "column");

			object->SetAttribute("x", (*pIter).getX());
			object->SetAttribute("y", (*pIter).getY());
		}

		object = new TiXmlElement( "object" );
		map->LinkEndChild( object );

		object->SetAttribute("type", "player");
		object->SetAttribute("angle", "0.0");
		object->SetAttribute("rank", "1");

		object->SetAttribute("x", playerPos.getX());
		object->SetAttribute("y", playerPos.getY());

		doc.SaveFile(fName.c_str());

		escrito = true;
	}

	return escrito;
}

EntityManager *Map::getManager() const
{
    return manager;
}

int Map::getType(const char * name){
	int type = -1;

	string sName = name;

	if(sName == "perimeter") 		type = 0;
	else if(sName == "wall") 		type = 1;
	else if(sName == "table")	 	type = 2;
	else if(sName == "column")	 	type = 3;
	else if(sName == "computer") 	type = 4;
	else if(sName == "door") 		type = 5;
	else if(sName == "player")		type = 6;
	else if(sName == "companion")	type = 7;
	else if(sName == "enemy")		type = 8;

	return type;
}

Point Map::getSupIzq(){
	return supIzq;
}

Point Map::getInfDer(){
	return infDer;
}

Point Map::getPlayerPos(){
	return playerPos;

}
