#include "Pathfinder.h"
#include "Map.h"

Pathfinder::Pathfinder() {
	navigationGraph = new NavGraph();
	map = NULL;
	charRadius = 10;
}

Pathfinder::~Pathfinder() {
	delete navigationGraph;
}

Pathfinder::Pathfinder(Point sI, Point iD, double r) {
	if (r > 0.0)
		charRadius = r;
	else
		charRadius = 1.0;
	navigationGraph = new NavGraph();
}

Pathfinder::Pathfinder(const Pathfinder &pf) {

	if (pf.map != NULL) {
		this->Copia(pf);
	} else {
		navigationGraph = new NavGraph();
	}

}

Pathfinder & Pathfinder::operator=(const Pathfinder &pf) {

	if (this != &pf) {

		if (pf.map != NULL) {
			this->Copia(pf);
		} else {
			navigationGraph = new NavGraph();
		}

	}
	return *this;
}

Pathfinder::Pathfinder(Map *mapa) {
	navigationGraph = new NavGraph();
	charRadius = 10;

	map = mapa;
}

Pathfinder::Pathfinder(string fMapa) {
	navigationGraph = new NavGraph();
	charRadius = 10;

	map = new Map(fMapa);
	map->loadData();
}

void Pathfinder::setMap(string fName) {
	if (map != NULL) {
		map->setMap(fName);
	} else {
		map = new Map(fName);
	}
	map->loadData();

}

void Pathfinder::setMap(Map * mapa) {

	map = mapa;
}

void Pathfinder::Copia(const Pathfinder &pf) {
	navigationGraph = new NavGraph(*pf.navigationGraph);
	charRadius = pf.charRadius;
	map = pf.map;
}

std::vector<Tri *> Pathfinder::getTriangulation() {
	return triangles;
}

double Pathfinder::getCharRadius() const {
	return charRadius;
}

void Pathfinder::setCharRadius(double charRadius) {
	this->charRadius = charRadius;
}

void Pathfinder::setTriangulation(vector<Tri *> tris) {
	triangles = tris;
}

void Pathfinder::generateDualGraph() {
	navigationGraph = Pathfinder::makeDualGraph(triangles);

}

NavGraph * Pathfinder::makeDualGraph(vector<Tri *> tris) {

	NavGraph * nav = new NavGraph();

	int id;
	std::vector<pair<int, Tri *> > vPar;
	pair<int, Tri *> pareja;
	std::vector<Tri *>::iterator triter;

	// Creo los nodos y enlazo su id con el triangulo que le corresponde
	for (triter = tris.begin(); triter != tris.end(); triter++) {
		id = nav->addNode(ASNode((*triter)->getIncenter()));
		pareja = make_pair(id, *triter);
		vPar.push_back(pareja);
	}

	Tri *pAB, *pBC, *pCA;
	int idOri;
	int idAB, idBC, idCA;
	std::vector<pair<int, Tri *> >::iterator parIter;

	for (triter = tris.begin(); triter != tris.end(); triter++) {
		pAB = (*triter)->getAb();
		pBC = (*triter)->getBc();
		pCA = (*triter)->getCa();

		for (parIter = vPar.begin(); parIter != vPar.end(); parIter++) {
			if ((*parIter).second == *triter) {
				idOri = (*parIter).first;
			} else if ((*parIter).second == pAB) {
				idAB = (*parIter).first;
			} else if ((*parIter).second == pBC) {
				idBC = (*parIter).first;
			} else if ((*parIter).second == pCA) {
				idCA = (*parIter).first;
			}
		}

		int idA = nav->addNode((*triter)->getA());
		int idB = nav->addNode((*triter)->getB());
		int idC = nav->addNode((*triter)->getC());

		if (pAB != NULL) {
			nav->addEdge(idOri, idAB);
		}else{
			nav->addEdge(idA, idB);
		}
		if (pBC != NULL) {
			nav->addEdge(idOri, idBC);
		}else{
			nav->addEdge(idB, idC);
		}
		if (pCA != NULL) {
			nav->addEdge(idOri, idCA);
		}else{
			nav->addEdge(idC, idA);
		}

		// Añadimos las esquinas como nodos

		nav->addEdge(idOri, idA);
		nav->addEdge(idOri, idB);
		nav->addEdge(idOri, idC);
	}

	return nav;

}

vector<int> Pathfinder::addDoor(vector<Point> puerta) {

	vector<int> nodos;

	if (navigationGraph != NULL) {

		World *mundo = new World();

		// Creamos el objeto fisico de la puerta
		Polygon poly(puerta);
		// Hacemos que sea de tipo poligono
		BodyData data(poly);
		data.setSensor(true);
		Body *cuerpo = new Body(*mundo, data);

		// Creamos el nodo central de la puerta
		ASNode nodo(poly.getCentroid());
		int id = navigationGraph->addNode(nodo);

		vector<ASNode>::iterator asIter1;
		for (asIter1 = navigationGraph->nodes.begin(); asIter1 != navigationGraph->nodes.end(); asIter1++) {
			if ((*asIter1).isEnabled()) {	// Si el nodo no esta habilitado no tenemos que procesarlo

				Point pos = (*asIter1).getPosition();

				// Si el punto esta dentro deshabilitamos el nodo
				if (mundo->CutOffPoints(pos, Point(-99999,-99999)).size() % 2 == 1) {
					(*asIter1).isEnabled(false);
					nodos.push_back((*asIter1).getId());
				} else {
					vector<ASNode> vecinos = navigationGraph->getAdyacence((*asIter1).getId());
					vector<ASNode>::iterator asIter2;
					for (asIter2 = vecinos.begin(); asIter2 != vecinos.end(); asIter2++) {
						if((*asIter2).isEnabled()){	// Si no esta habilitado no lo procesamos

							if(!mundo->Ray(pos, (*asIter2).getPosition())){	// Si lanzamos un rayo y no llega del nodo anterior a este
								int id1 = (*asIter1).getId(),
										id2 = (*asIter2).getId();

								// Eliminamos la arista
								(*asIter1).removeEdge(id2);
								(*asIter2).removeEdge(id1);

								// Creamos las dos nuevas
								navigationGraph->addEdge(id, id1);
								navigationGraph->addEdge(id1, id);//Esto no deberia de estar aqui TODO
								navigationGraph->addEdge(id, id2);
								navigationGraph->addEdge(id2, id);//Esto no deberia de estar aqui TODO
							}
						}
					}
				}
			}
		}

		if(navigationGraph->getAdyacence(id).empty()){
			navigationGraph->removeNode(id);
		}else{
			nodos.push_back(id);
		}
	}

	return nodos;
}

NavGraph * Pathfinder::getDualGraph() {

	return navigationGraph;
}

std::vector<Point> Pathfinder::smoothPath(std::vector<Point> camino) {

	std::vector<Point> vColl;
	std::vector<Point>::iterator pIter, pIter2, atajo;
	std::vector<Point> newCamino = camino;

	if (newCamino.size() >= 3) {
		pIter = newCamino.begin();
		while (pIter != newCamino.end() - 2) {

			if (map->hasVision(*pIter, *(pIter + 2))) {
				newCamino.erase(pIter + 1);
			} else {
				pIter++;
			}
		}
	}

	return newCamino;
}

ASNode Pathfinder::getNearestCenter(Point p){
	ASNode nearest;
	if(map->isNavegable(p)){
		Point candPoint;
		double distance, candDist;
		bool found = false;
		vector<ASNode>::iterator iter;
		for (iter = navigationGraph->nodes.begin(); iter != navigationGraph->nodes.end(); iter++) {
			if ((*iter).isEnabled()){
				if (found) { // Si ya tengo un candidato

					candPoint = (*iter).getPosition();
					candDist = Point::distance(p, candPoint);
					// Si la distancia es menor y puedo verlo
					if (candDist < distance && map->hasVision(p, candPoint)) {
						nearest = (*iter);
						distance = candDist;
					}

				} else {
					nearest = (*iter);
					if (map->hasVision(p, nearest.getPosition())) {
						found = true;
						distance = Point::distance(p, nearest.getPosition());
					}

				}
			}else{
				//cout << "Nodo desactivado en nearest" << endl;
			}
		}
	}
	//cout << "Encontrado: " << found << endl;
	//cout << "En posicion: " << nearest.getPosition() << endl;

	return nearest;
}

bool Pathfinder::isInList(ASNode node, vector<ASNode> list, ASNode &getIt) {
	bool esta = false;
	for (unsigned int i = 0; i < list.size(); i++) {
		if (node.getId() == list[i].getId()) {
			getIt = list[i];
			esta = true;
			break;
		}
	}

	return esta;
}

bool Pathfinder::isInList(ASNode node, vector<ASNode> list) {
	bool esta = false;
	for (unsigned int i = 0; i < list.size(); i++) {
		if (node.getId() == list[i].getId()) {
			esta = true;
			break;
		}
	}

	return esta;
}

ASNode Pathfinder::getMinCost(vector<ASNode> lista) {
	ASNode bestNode;
	if (!lista.empty()){
		double min = lista[0].getF();
		bestNode = lista[0];
		for (unsigned int i = 0; i < lista.size(); i++) {
			if (lista[i].isEnabled()){
				if (lista[i].getF() < min) {
					min = lista[i].getF();
					bestNode = lista[i];
				}
			}else{
				//cout << "Nodo desactivado en minCost" << endl;
			}
		}
	}else{
		cerr << "Warning: Buscando en lista vacia" << endl;
	}

	return bestNode;
}

std::vector<Point> Pathfinder::AStar(Point ori, Point des) {
	vector<Point> ruta;
	ASNode origen;
	ASNode destino;
	//double totalF = 0;
	vector<ASNode> openList;
	vector<ASNode> closeList;
	vector<ASNode> pathBestF;
	bool encontrado = false;

	//Consigo los nodos mas cercanos al punto origen y fin
	origen = getNearestCenter(ori);
	destino = getNearestCenter(des);
	if (origen.getId()==-1){
		cerr << "ERROR: No se ha encontrado un punto cercano al origen. " << ori << endl;
	}
	if (destino.getId()==-1){
		cerr << "ERROR: No se ha encontrado un punto cercano al destino. " << des << endl;
	}

	//Si se encuentra el orgien
	if (origen.getId() != -1) {
		//Si se encuentra el destino
		if (destino.getId() != -1) {
			ASNode best;
			vector<ASNode> adyacencia;
			//Anyadimos a la lista abierta el nodo inicial

			openList.push_back(origen);
			//Bucle principipal
			while (!openList.empty() && !encontrado) {
				//Asigno a best el nodo de menor nodo de la lista abierta (mejor nodo = coste f mas bajo)
				best = getMinCost(openList);
				//Si hemos llegado a nuestro destino
				if (best.getId() == destino.getId()) {
					////cout << "El coste total es:" << best.getF() << endl;
					closeList.push_back(best);
					vector<ASNode>::iterator iter;
					for (iter = openList.begin(); iter < openList.end(); iter++) {
						if ((*iter).getId() == best.getId()) {
							openList.erase(iter);
							break;
						}
					}
					encontrado = true;
				} else { //Sino seguimos

					//Quitamos el nodo de menos f de la lista abierta y lo metemos en la cerrada
					closeList.push_back(best);
					////cout << "Anyadimos a la cerrada: " << best << endl;
					vector<ASNode>::iterator iter;
					for (iter = openList.begin(); iter < openList.end(); iter++) {
						if ((*iter).getId() == best.getId()) {
							openList.erase(iter);
							break;
						}
					}

					//Conseguimos la adyacencia del mejor nodo
					adyacencia = navigationGraph->getAdyacenceCalculated(best.getId(), destino.getId(), best.getG());

					//Miramos que adyacencias estan en la lista abierta o cerrada
					vector<ASNode>::iterator iterAdy;
					iterAdy = adyacencia.begin();
					while (iterAdy != adyacencia.end()) {
						//Si el nodo esta activo lo miramos si no pasamos de largo
						if (iterAdy->isEnabled()){
							//Si esta en la lista abierta
							ASNode getit;
							if (isInList((*iterAdy), openList, getit)) {
								if (getit.getF() > (*iterAdy).getF()) {

									for (unsigned int i = 0; i < openList.size(); i++) {
										if (openList[i].getId() == getit.getId()) {
											openList[i].setParent(best.getId());
											break;
										}
									}
								}

							} else if (isInList((*iterAdy), closeList)) {

							} else {
								openList.push_back(*iterAdy);
							}
						}else{
							//cout << "Nodo desactivado en AStar" << endl;
						}
						iterAdy++;
					}

				}

			}
			if (!encontrado) {
				//cerr << "No se ha encontrado un camino" << endl;
			} else {
				ruta = generatePath(origen, destino, closeList, ori, des);
			}

		} else {
			cerr << "No se ha encontrado el nodo destino cercano al punto " << ori << endl;
		}
	} else {
		cerr << "No se ha encontrado el nodo origen cercano al punto " << des << endl;
	}

	return ruta;
}

vector<Point> Pathfinder::generatePath(ASNode origen, ASNode destino, vector<ASNode> closeList, Point ori, Point des) {
	vector<Point> ruta;
	ASNode actual;
	ruta.push_back(des);
	actual = getNode(destino.getId(), closeList);
	while (actual.getId() != origen.getId()) {
		////cout << "Generando" << endl;
		ruta.push_back(actual.getPosition());
		actual = getNode(actual.getParent(), closeList);
	}
	ruta.push_back(actual.getPosition());
	ruta.push_back(ori);

	std::reverse(ruta.begin(), ruta.end());
	return ruta;
}

ASNode Pathfinder::getNode(int id, vector<ASNode> lista) {
	ASNode as;
	for (unsigned int i = 0; i < lista.size(); i++) {
		if (lista[i].getId() == id) {
			as = lista[i];
			break;
		}
	}
	return as;
}

Map * Pathfinder::getMap() {
	return map;
}
