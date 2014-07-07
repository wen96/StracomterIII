/*
 * Map.cc
 *
 *  Created on: Nov 27, 2011
 *      Author: Chutaos team
 */

#include "Map.h"
#include "tinyxml.h"
#include "Pathfinder.h"

Map::Map() {
	mapFileS = "";
	manager = NULL;
	playerPos = Point(0, 0);
	charRadius = Core::Radius;
	mapWorld = NULL;
	gameWorld = NULL;
}

void Map::copia(const Map &mapa) {
	infDer = mapa.infDer;
	supIzq = mapa.supIzq;
	mapFileS = mapa.mapFileS;
	murosV = mapa.murosV;
	obstaclesV = mapa.obstaclesV;
	perimetroV = mapa.perimetroV;
	manager = mapa.manager;
	playerPos = mapa.playerPos;
	charRadius = Core::Radius;
	gameWorld = mapa.gameWorld;
}

Map::Map(const Map &m) {
	copia(m);
}

Map & Map::operator=(const Map & mapa) {

	if (this != &mapa) {

		copia(mapa);
	}

	return *this;
}

Map::~Map() {
	mapFileS = "";

	while (!triangles.empty()) {
		delete triangles.back();
		triangles.pop_back();
	}
	triangles.clear();

	if (mapWorld != NULL) {
		delete mapWorld;
	}
	mapWorld = NULL;

	gameWorld = NULL;

	pointList.clear();
	objectList.clear();
	expObjs.clear();
	dTris.Reset();

	perimetroV.clear();
	obstaclesV.clear();
	objectsV.clear();
	murosV.clear();
	supIzq = Point();
	infDer = Point();
	playerPos = Point();
}

Map::Map(string fName) {
	mapFileS = fName;
	manager = NULL;
	charRadius = Core::Radius;
	mapWorld = NULL;
	gameWorld = NULL;
}

void Map::setManager(EntityManager *manager_) {
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

		while (!triangles.empty()) {
			delete triangles.back();
			triangles.pop_back();
		}
		triangles.clear();

		if (mapWorld != NULL)
			delete mapWorld;

		pointList.clear();
		objectList.clear();
		expObjs.clear();
		objectsV.clear();
		dTris.Reset();

		perimetroV.clear();
		obstaclesV.clear();
		murosV.clear();
		supIzq = Point();
		infDer = Point();
		playerPos = Point();

		int tipoI = 0;
		int hX = 0, lX = 0, hY = 0, lY = 0;
		Point p;
		obsCont obs;

		TiXmlElement * objeto = doc.RootElement()->FirstChildElement();

		while (objeto != NULL && status >= 0) {

			const char *tipoS = objeto->Attribute("type");

			if (tipoS != NULL) {
				tipoI = Map::getType(tipoS);

				TiXmlElement * pCoords;
				vector<Point> vPAux;
				int x = 0, y = 0;
				double ang = 0.0;
				int clase = 0;
				//cout << tipoS << " " << tipoI << endl;
				switch (tipoI) {
				case Core::Map::Perimeter:

					pCoords = objeto->FirstChildElement()->FirstChildElement();

					while (pCoords != NULL) {

						pCoords->QueryIntAttribute("x", &x);
						pCoords->QueryIntAttribute("y", &y);

						// Cogemos los puntos extremos
						if (x >= hX)
							hX = x;
						if (x <= lX)
							lX = x;
						if (y >= hY)
							hY = y;
						if (y >= hY)
							hY = y;

						Point p(x, y);

						perimetroV.push_back(p);

						pCoords = pCoords->NextSiblingElement();

					}
					if (manager != NULL) {
						manager->addFloor(perimetroV, 0.0, Color<float>(1.0, 1.0, 1.0));
					}
					status = 1;
					break;

				case Core::Map::Wall:
					// ////cout << "Leo una pared" << endl;

					pCoords = objeto->FirstChildElement()->FirstChildElement();

					while (pCoords != NULL) {

						pCoords->QueryIntAttribute("x", &x);
						pCoords->QueryIntAttribute("y", &y);

						p.setXY(x, y);

						vPAux.push_back(p);

						pCoords = pCoords->NextSiblingElement();
					}

					if (vPAux.size() != 4) {
						status = -1;
					} else {
						murosV.push_back(vPAux);

						if (manager != NULL) {
							Color<float> color(1.0, 0.0, 0.0);
							manager->addWall(vPAux, 0.0, color);
						}
					}

					break;

				case Core::Map::Obstacle:
					// ////cout << "Leo un Obstaculo" << endl;

					objeto->QueryIntAttribute("x", &x);
					objeto->QueryIntAttribute("y", &y);

					objeto->QueryDoubleAttribute("angle", &ang);

					objeto->QueryIntAttribute("subtype", &clase);

					if (manager != NULL) {
						manager->addObstacle((Core::Obstacles::Type) clase, Point(x, y), ang);
					}
					break;

				case Core::Map::Objects:
					// ////cout << "Leo un Obstaculo" << endl;

					objeto->QueryIntAttribute("x", &x);
					objeto->QueryIntAttribute("y", &y);

					objeto->QueryDoubleAttribute("angle", &ang);

					objeto->QueryIntAttribute("subtype", &clase);

					if (manager != NULL) {
						manager->addObject((Core::Objects::Class) clase, Point(x, y), ang);
					}
					break;

				case Core::Map::Door:
					// ////cout << "Leo una puerta" << endl;

					pCoords = objeto->FirstChildElement()->FirstChildElement();

					while (pCoords != NULL) {

						pCoords->QueryIntAttribute("x", &x);
						pCoords->QueryIntAttribute("y", &y);

						p.setXY(x, y);

						vPAux.push_back(p);

						pCoords = pCoords->NextSiblingElement();
					}

					if (vPAux.size() != 4) {
						status = -1;
					} else {
						doorsV.push_back(vPAux);

						if (manager != NULL) {
							Polygon poly(vPAux);
							manager->addDoor(Point(), vPAux);
						}
					}
					break;

				case Core::Map::Player:
					// ////cout << "Leo al player" << endl;

					objeto->QueryIntAttribute("x", &x);
					objeto->QueryIntAttribute("y", &y);

					objeto->QueryDoubleAttribute("angle", &ang);

					if (manager != NULL) {
						playerPos = Point(x, y);
						manager->addPlayer(playerPos, ang);
					}

					break;

				case Core::Map::MiniBoss:

					// ////cout << "Leo un enemigo" << endl;

					objeto->QueryIntAttribute("x", &x);
					objeto->QueryIntAttribute("y", &y);

					objeto->QueryDoubleAttribute("angle", &ang);

					if (manager != NULL) {
						manager->setMap(this);
						miniBoss = Point(x, y);
					}

					break;

				case Core::Map::MegaBoss:

					// ////cout << "Leo un enemigo" << endl;

					objeto->QueryIntAttribute("x", &x);
					objeto->QueryIntAttribute("y", &y);

					objeto->QueryDoubleAttribute("angle", &ang);

					if (manager != NULL) {
						manager->setMap(this);
						megaBoss = Point(x, y);
					}

					break;

				default:
					////cout << tipoS << " " << tipoI << endl;
					// ////cout << "Tipo \"" << tipoS << "\" desconocido" << endl;
					break;
				}

				objeto = objeto->NextSiblingElement();
			} else {
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

bool Map::setPerimeter(vector<Point> periVP) {

	bool added = false;

	if (periVP.size() >= 3) {
		perimetroV = periVP;
		added = true;
	}

	return added;
}

bool Map::addWall(vector<Point> vP) {

	murosV.push_back(vP);

	return true;
}

void Map::addDoor(vector<Point> vP) {
	doorsV.push_back(vP);
}

vector<vector<Point> > Map::getDoors() {
	return doorsV;
}

bool Map::addObstacle(Core::Obstacles::Type tipo, Point p, double ang) {
	obsCont contenedor;
	contenedor.tipo = tipo;
	contenedor.p = p;
	contenedor.a = ang;

	obstaclesV.push_back(contenedor);

	return true;
}

bool Map::addObject(Core::Objects::Class tipo, Point p, double ang) {
	objCont contenedor;
	contenedor.tipo = tipo;
	contenedor.p = p;
	contenedor.a = ang;

	objectsV.push_back(contenedor);

	return true;
}

bool Map::writeFile(string fName) {
	bool escrito = false;

	TiXmlDocument doc;
	TiXmlDeclaration * decl = new TiXmlDeclaration("1.0", "", "");
	doc.LinkEndChild(decl);

	TiXmlElement * map = new TiXmlElement("map");
	doc.LinkEndChild(map);

	if (!perimetroV.empty()) {

		TiXmlElement * object = new TiXmlElement("object");
		map->LinkEndChild(object);

		object->SetAttribute("type", "perimeter");

		TiXmlElement * vxlist = new TiXmlElement("vertexlist");
		object->LinkEndChild(vxlist);

		int idCont = 0;
		vector<Point>::iterator pIter;
		for (pIter = perimetroV.begin(); pIter != perimetroV.end(); pIter++) {
			TiXmlElement * vertex = new TiXmlElement("vertex");
			vertex->SetAttribute("id", idCont);
			idCont++;
			vertex->SetAttribute("x", (*pIter).getX());
			vertex->SetAttribute("y", (*pIter).getY());

			vxlist->LinkEndChild(vertex);
		}

		vector<vector<Point> >::iterator vvIter;
		for (vvIter = murosV.begin(); vvIter != murosV.end(); vvIter++) {
			object = new TiXmlElement("object");
			map->LinkEndChild(object);

			object->SetAttribute("type", "wall");

			vxlist = new TiXmlElement("vertexlist");
			object->LinkEndChild(vxlist);

			idCont = 0;
			for (pIter = (*vvIter).begin(); pIter != (*vvIter).end(); pIter++) {
				TiXmlElement * vertex = new TiXmlElement("vertex");
				vertex->SetAttribute("id", idCont);
				idCont++;
				vertex->SetAttribute("x", (*pIter).getX());
				vertex->SetAttribute("y", (*pIter).getY());

				vxlist->LinkEndChild(vertex);
			}
		}

		for (vvIter = doorsV.begin(); vvIter != doorsV.end(); vvIter++) {
			object = new TiXmlElement("object");
			map->LinkEndChild(object);

			object->SetAttribute("type", "door");

			vxlist = new TiXmlElement("vertexlist");
			object->LinkEndChild(vxlist);

			idCont = 0;
			for (pIter = (*vvIter).begin(); pIter != (*vvIter).end(); pIter++) {
				TiXmlElement * vertex = new TiXmlElement("vertex");
				vertex->SetAttribute("id", idCont);
				idCont++;
				vertex->SetAttribute("x", (*pIter).getX());
				vertex->SetAttribute("y", (*pIter).getY());

				vxlist->LinkEndChild(vertex);
			}
		}

		vector<obsCont>::iterator oCIter;
		for (oCIter = obstaclesV.begin(); oCIter != obstaclesV.end(); oCIter++) {

			object = new TiXmlElement("object");
			map->LinkEndChild(object);

			object->SetAttribute("type", "obstacle");

			object->SetAttribute("subtype", (int) (*oCIter).tipo);

			object->SetAttribute("x", (*oCIter).p.getX());
			object->SetAttribute("y", (*oCIter).p.getY());

			object->SetAttribute("angle", (*oCIter).a);
		}

		vector<objCont>::iterator objCIter;
		for (objCIter = objectsV.begin(); objCIter != objectsV.end(); objCIter++) {

			object = new TiXmlElement("object");
			map->LinkEndChild(object);

			object->SetAttribute("type", "objects");

			object->SetAttribute("subtype", (int) (*objCIter).tipo);

			object->SetAttribute("x", (*objCIter).p.getX());
			object->SetAttribute("y", (*objCIter).p.getY());

			object->SetAttribute("angle", (*objCIter).a);
		}

		object = new TiXmlElement("object");
		map->LinkEndChild(object);

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

EntityManager *Map::getManager() const {
	return manager;
}

int Map::getType(const char * name) {
	int type = -1;

	string sName = name;

	if (sName == "perimeter")
		type = 0;
	else if (sName == "wall")
		type = 1;
	else if (sName == "door")
		type = 2;
	else if (sName == "player")
		type = 3;
	else if (sName == "obstacle")
		type = 4;
	else if (sName == "objects")
		type = 5;
	else if (sName == "miniBoss")
		type = 6;
	else if (sName == "megaBoss")
		type = 7;

	return type;
}

Point Map::getSupIzq() {
	return supIzq;
}

Point Map::getInfDer() {
	return infDer;
}

Point Map::getPlayerPos() {
	return playerPos;

}

void Map::generateTriangulation() {

	objectList = murosV;

	//TODO Añadir los obstaculos
	vector<Entity *> obstaclesV = manager->getEntitiesbyType(Core::Entities::e_obstacle);
	vector<Entity *>::iterator obsIter;
	for (obsIter = obstaclesV.begin(); obsIter != obstaclesV.end(); obsIter++) {
		Obstacle *obs = (Obstacle *) *obsIter;
		vector<Point> vPAux;

		Model2D m(obs->getObstacle());

		vPAux = m.getShape()->getPuntos();
		vector<Point>::iterator piter;
		for (piter = vPAux.begin(); piter != vPAux.end(); piter++) {
			Vector2D ori(*piter);
			ori.Rotate(obs->getAngle());
			Vector2D desp(obs->getCenter());
			*piter = (ori + desp).toPoint();
		}

		objectList.push_back(vPAux);
	}
	//cout << "Obstaculos" << endl;
	pointList = perimetroV;

	vector<vector<Point> >::iterator iter;
	for (iter = objectList.begin(); iter != objectList.end(); iter++) {
		Polygon pol(*iter);
		if (pol.isClockwise()) {
			pol.Reverse();
			*iter = pol.getPuntos();
		}
	}

	expandGeometry();
	//cout << "Expandido" << endl;
	flattenGeometry();
	//cout << "Flatten" << endl;
	double x, y, hX = expObjs[0][0].getX(), hY = expObjs[0][0].getY(), lX = expObjs[0][0].getX(), lY = expObjs[0][0].getY();

	for (unsigned int i = 0; i < expObjs.size(); i++) {
		for (unsigned int j = 0; j < expObjs[i].size(); j++) {

			x = expObjs[i][j].getX();
			y = expObjs[i][j].getY();

			if (x >= hX)
				hX = x;
			if (x <= lX)
				lX = x;
			if (y >= hY)
				hY = y;
			if (y >= hY)
				hY = y;
		}
	}
	supIzq = Point(lX, lY);
	infDer = Point(hX, hY);

	pointList = expObjs[0];

	objectList.clear();
	objectList.insert(objectList.begin(), expObjs.begin() + 1, expObjs.end());

	dTris.createBorders(supIzq, infDer);
	dTris.addPoints(pointList);

	std::vector<std::vector<Point> >::iterator vvIter;
	for (vvIter = objectList.begin(); vvIter != objectList.end(); vvIter++) {
		dTris.addPoints(*vvIter);
	}
	//cout << "Puntos añadidos" << endl;
	dTris.continueDelaunay();
	triangles = dTris.finishedDelaunay();
	//cout << "Triangulado" << endl;
	flattenTriangulation();
	//cout << "Aplanado" << endl;
	removeTris();
	//cout << "Limpiado" << endl;
	generateDoorColisions();
	//cout << "puertas" << endl;
	addExtraCollision();
	//cout << "Extra" << endl;
}

void Map::addExtraCollision() {

	Polygon auxP(perimetroV);

	auxP.Expand(charRadius * 0.95, false);

	BodyData datosC(auxP);

	datosC.setSensor(true);

	Body *cuerpo = new Body(*mapWorld, datosC);
	cuerpo->getPosition();

	std::vector<std::vector<Point> >::iterator vvIter;
	for (vvIter = murosV.begin(); vvIter != murosV.end(); vvIter++) {

		Polygon obj(*vvIter);
		obj.Expand(charRadius * 0.95, false);

		BodyData datosObj(obj);

		datosObj.setSensor(true);

		Body *cuerpoObj = new Body(*mapWorld, datosObj);
		cuerpoObj->getPosition();
	}
}

void Map::flattenTriangulation() {

	createCollision();

	std::vector<Tri *>::iterator triter;

	triter = triangles.begin();

	std::vector<Point> newPoints;

	Point A, B, C, P;
	std::vector<Point> vCollAB, vCollBC, vCollCA;
	bool added = false;
	while (triter != triangles.end()) {

		added = false;
		A = Point((*triter)->getA());
		B = Point((*triter)->getB());
		C = Point((*triter)->getC());

		vCollAB = mapWorld->CutOffPoints(A, B);
		vCollBC = mapWorld->CutOffPoints(B, C);
		vCollCA = mapWorld->CutOffPoints(C, A);

		if (!vCollAB.empty()) {
			P = vCollAB[0];
			added = true;
		} else if (!vCollBC.empty()) {
			P = vCollBC[0];
			added = true;
		} else if (!vCollCA.empty()) {
			P = vCollCA[0];
			added = true;
		}

		if (added) {
			if (dTris.addPoint(P)) {
				if (dTris.stepDelaunay()) {
					//cout << triangles.size() << " ";
					triangles = dTris.getTriangles();
					//cout << triangles.size() << endl;
					triter = triangles.begin();
					newPoints.push_back(P);
				}else {
					triter++;
				}
			} else {
				triter++;
			}
		} else {
			triter++;
		}
	}

	dTris.continueDelaunay();
	triangles = dTris.getTriangles();
	std::vector<Point>::iterator piter;

	for (piter = newPoints.begin(); piter != newPoints.end(); piter++) {
		addPoint(*piter);
	}

}

void Map::removeTris() {

	std::vector<Tri *>::iterator triter = triangles.begin();

	while(triter != triangles.end()){

		if(mapWorld->CutOffPoints((*triter)->getIncenter(), Point(-999999,-999999)).size() % 2 == 0){
			dTris.removeT(*triter);
			triangles = dTris.getTriangles();
		}else{
			triter++;
		}
	}
}

void Map::expandGeometry() {
	Polygon pol(pointList);
	pol.Expand(charRadius, true);
	expObjs.push_back(pol.getPuntos());

	std::vector<std::vector<Point> >::iterator vviter;
	for (vviter = objectList.begin(); vviter != objectList.end(); vviter++) {

		Polygon p(*vviter);
		p.Expand(charRadius, true);
		expObjs.push_back(p.getPuntos());
	}
	pointList = expObjs[0];
}

void Map::createCollision() {

	mapWorld = new World();

	Polygon perimetro(pointList);

	BodyData datosC(perimetro);

	datosC.setSensor(true);

	Body *cuerpo = new Body(*mapWorld, datosC);
	cuerpo->getPosition();

	std::vector<std::vector<Point> >::iterator vvIter;
	for (vvIter = objectList.begin(); vvIter != objectList.end(); vvIter++) {
		Polygon obj(*vvIter);

		BodyData datosObj(obj);

		datosObj.setSensor(true);

		Body *cuerpoObj = new Body(*mapWorld, datosObj);
		cuerpoObj->getPosition();
	}
}

void Map::addPoints(vector<Point> vPoints) {
	vector<Point>::iterator pIter;
	for (pIter = vPoints.begin(); pIter != vPoints.end(); pIter++) {
		addPoint(*pIter);
	}
}

void Map::addPoint(Point p) {

	std::vector<Point>::iterator piter;

	Point a, b;

	for (piter = expObjs[0].begin(); piter != expObjs[0].end(); piter++) {
		a = *piter;
		if (piter == expObjs[0].end() - 1) {
			b = *(expObjs[0].begin());
		} else {
			b = *(piter + 1);
		}

		if (Tri::side(a, b, p) == 0) {
			double dotP = (p.getX() - a.getX()) * (b.getX() - a.getX()) + (p.getY() - a.getY()) * (b.getY() - a.getY());
			if (dotP >= 0) {
				double sqlng = (b.getX() - a.getX()) * (b.getX() - a.getX()) + (b.getY() - a.getY()) * (b.getY() - a.getY());
				if (dotP < sqlng) {
					if (piter == expObjs[0].end() - 1) {
						expObjs[0].push_back(p);
					} else {
						expObjs[0].insert(piter + 1, p);
					}
					break;
				}
			}
		}
	}
	std::vector<std::vector<Point> >::iterator vvIter;
	for (vvIter = expObjs.begin() + 1; vvIter != expObjs.end(); vvIter++) {
		for (piter = (*vvIter).begin(); piter != (*vvIter).end(); piter++) {
			a = *piter;
			if (piter == (*vvIter).end() - 1) {
				b = *((*vvIter).begin());
			} else {
				b = *(piter + 1);
			}

			if (Tri::side(a, b, p) == 0) {
				double dotP = (p.getX() - a.getX()) * (b.getX() - a.getX()) + (p.getY() - a.getY()) * (b.getY() - a.getY());
				if (dotP >= 0) {
					double sqlng = (b.getX() - a.getX()) * (b.getX() - a.getX()) + ((b.getY() - a.getY()) * (b.getY() - a.getY()));
					if (dotP < sqlng) {
						if (piter == (*vvIter).end() - 1) {
							(*vvIter).push_back(p);
						} else {
							(*vvIter).insert(piter + 1, p);
						}
						break;
					}
				}
			}
		}
	}
}

void Map::removeAdyacent(Tri *ori) {
	if (ori->getAb() != NULL) {
		if ((mapWorld->CutOffPoints(ori->getIncenter(), ori->getAb()->getIncenter())).empty()) {
			dTris.removeT(ori->getAb());
		}
	}
	if (ori->getBc() != NULL) {
		if ((mapWorld->CutOffPoints(ori->getIncenter(), ori->getBc()->getIncenter())).empty()) {
			dTris.removeT(ori->getBc());
		}
	}
	if (ori->getCa() != NULL) {
		if ((mapWorld->CutOffPoints(ori->getIncenter(), ori->getCa()->getIncenter())).empty()) {
			dTris.removeT(ori->getCa());
		}
	}
}

void Map::flattenGeometry() {

	vector<vector<Point> >::iterator vvIter1, vvIter2;
	vector<Body *> bodyVec;
	World *mAux = new World;

	for (vvIter1 = expObjs.begin(); vvIter1 != expObjs.end(); vvIter1++) {
		Polygon pol(*vvIter1);
		BodyData data(pol);
		data.setSensor(true);
		Body *body = new Body(*mAux, data);
		bodyVec.push_back(body);
	}

	vvIter1 = expObjs.begin() + 1;
	while (vvIter1 != expObjs.end()) {

		bool unido = false;
		int i1 = vvIter1 - expObjs.begin();

		vvIter2 = vvIter1 + 1;
		while (vvIter2 != expObjs.end() && !unido) {

			int i2 = vvIter2 - expObjs.begin();

			if (!bodyVec[i1]->contact(*bodyVec[i2]).empty()) {

				Polygon pol1(*vvIter1);
				Polygon pol2(*vvIter2);
				pol1.Join(pol2);

				if (pol1.isClockwise()) {
					pol1.Reverse();
				}

				BodyData data(pol1);
				data.setSensor(true);
				Body *body = new Body(*mAux, data);
				delete bodyVec[i1];
				bodyVec[i1] = body;

				delete bodyVec[i2];
				bodyVec.erase(bodyVec.begin() + i2);

				*vvIter1 = pol1.getPuntos();

				expObjs.erase(vvIter2);

				unido = true;
			} else {
				vvIter2++;
			}
		}
		if (!unido)
			vvIter1++;
	}

	Polygon periPoly(expObjs[0]);
	vvIter1 = expObjs.begin() + 1;
	while (vvIter1 != expObjs.end()) {

		int i = vvIter1 - expObjs.begin();

		if (!bodyVec[0]->contact(*bodyVec[i]).empty()) {
			Polygon pol(*vvIter1);

			pol.Inter(periPoly);

			if (pol.isClockwise()) {
				pol.Reverse();
			}

			*vvIter1 = pol.getPuntos();

		}
		vvIter1++;
	}

	delete mAux;
}

int Map::isInside(Polygon poly, Point p) {
	/*
	 * 1 Dentro
	 * 0 Pertenece
	 * -1 Fuera
	 */

	int inside = 0;
	bool parteDe = false;
	vector<Point> polyPoints = poly.getPuntos();
	vector<Point>::iterator pIter;
	for (pIter = polyPoints.begin(); pIter != polyPoints.end() && !parteDe; pIter++) {
		if (p == *pIter) {
			parteDe = true;
		}
	}

	if (!parteDe) {

		World *wAux = new World();

		BodyData data(poly);
		data.setSensor(true);

		Body *cuerpo = new Body(*wAux, data);
		cuerpo->getPosition();

		int nH = wAux->CutOffPoints(p, Point(-99999, -99999)).size();

		if (nH % 2 == 1) {
			inside = 1;
		} else {
			inside = -1;
		}

		delete wAux;
	}
	return inside;
}

vector<Tri *> Map::getTriangulation() {

	return triangles;
}

double Map::getArea() {

	double area = 0;

	//cout << "Número de triángulos" << triangles.size() << endl;
	vector<Tri *>::iterator tIter;
	for (tIter = triangles.begin(); tIter != triangles.end(); tIter++) {
		area += ((*tIter)->Area() / 1000.0);
	}

	return area;
}

bool Map::hasVision(Point a, Point b) {

	if (mapWorld != NULL && mapWorld->CutOffPoints(a, b).empty())
		return true;

	return false;
}

void Map::setPlayerPos(Point p) {
	playerPos = p;
}

Tri Map::getTri(Point p) {
	vector<Tri *>::iterator tIter;
	for (tIter = triangles.begin(); tIter != triangles.end(); tIter++) {
		int in = (*tIter)->isInside(p);
		if (in == 0 || in == 1) {
			return **tIter;
		}
	}
	return Tri();
}

void Map::generateDoorColisions() {
	vector<vector<Point> >::iterator vvIter;
	for (vvIter = doorsV.begin(); vvIter != doorsV.end(); vvIter++) {
		Polygon poly(*vvIter);
		poly.Expand(charRadius);

		BodyData datosC(poly);
		datosC.setSensor(true);

		Body *cuerpo = new Body(*mapWorld, datosC);
		cuerpo->getPosition();
	}
}

void Map::setWorld(World *world) {
	if (gameWorld != NULL)
		delete gameWorld;
	gameWorld = world;
}

bool Map::isNavegable(Point p) {
	return true;
	//cout << p << " colisiona con " << mapWorld->CutOffPoints(p, Point(-99999, -99999)).size() << " puntos." << endl;
	return mapWorld->CutOffPoints(p, Point(-99999, -99999)).size() % 2 == 0;
}

vector<Point> Map::getTriCenters(int minArea){
	vector<Point> centros;

	vector<Tri *>::iterator iter;
	for(iter = triangles.begin(); iter != triangles.end(); iter++){
		if((*iter)->Area() >= minArea)
			centros.push_back((*iter)->getIncenter());
	}

	return centros;
}
