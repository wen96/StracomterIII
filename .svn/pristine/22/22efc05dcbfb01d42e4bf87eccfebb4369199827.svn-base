#include "Pathfinder.h"

Pathfinder::Pathfinder() {
	mundo = new World();
}

Pathfinder::~Pathfinder() {

}

Pathfinder::Pathfinder(Point sI, Point iD, double r) : dTris(sI, iD) {
	supIzq = sI;
	infDer = iD;
	if(r > 0.0) charRadius = r;
	else 		charRadius = 0.0;
	mundo = new World();
}

void Pathfinder::setMap(string fName) {
	map.setMap(fName);
	pointList = map.getVertex();
	objectList = map.getObjects();

	expandGeometry();

	flattenGeometry();

	pointList = expObjs[0];

	objectList.clear();
	objectList.insert(objectList.begin(), expObjs.begin() + 1, expObjs.end());

	dTris.addPoints(pointList);

	std::vector<std::vector<Point> >::iterator vvIter;
	for (vvIter = objectList.begin(); vvIter != objectList.end(); vvIter++) {
		dTris.addPoints(*vvIter);
	}
}

void Pathfinder::generateTriangulation() {
	dTris.continueDelaunay();
	triangles = dTris.finishedDelaunay();

	//cout << triangles.size() << endl;
}

std::vector<Tri *> Pathfinder::getTriangulation() {
	return triangles;
}

void Pathfinder::flattenTriangulation() {

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

		vCollAB = mundo->CutOffPoints(A, B);
		vCollBC = mundo->CutOffPoints(B, C);
		vCollCA = mundo->CutOffPoints(C, A);

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
			//cout << P << endl;
			dTris.addPoint(P);
			dTris.stepDelaunay();
			triangles = dTris.getTriangles();
			triter = triangles.begin();
			newPoints.push_back(P);

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


void Pathfinder::flattenGeometry(){

	vector<vector <Point> >::iterator vvIter1, vvIter2;
	vector<Point> vColl;
	World *mAux = new World;

	for(vvIter1 = expObjs.begin(); vvIter1 != expObjs.end() - 1; vvIter1++){

		Polygon pol1(*vvIter1);
		BodyData data1(pol1);
		data1.setSensor(true);
		Body bod1(*mAux, data1);

		for(vvIter2 = vvIter1 + 1; vvIter2 != expObjs.end(); vvIter2++){

			Polygon pol2(*vvIter2);
			BodyData data2(pol2);
			data2.setSensor(true);
			Body bod2(*mAux, data2);

			vColl = bod1.contact(bod2);
			addPoints(vColl);
			//cout << vColl.size() << endl;
		}
	}

	vector<Polygon> vPoly;
	for(vvIter1 = expObjs.begin(); vvIter1 != expObjs.end(); vvIter1++){
		Polygon pol(*vvIter1);
		vPoly.push_back(pol);
	}

	vvIter1 = expObjs.begin();
	int cont = 0;
	while(vvIter1 != expObjs.end()){

		vector<Point>::iterator pIter;
		pIter = (*vvIter1).begin();
		while(pIter != (*vvIter1).end()){
			cont++;
			bool elim = false;
			int rel = isInside(vPoly[0], *pIter);
			if(rel >= 0){
				vector<Polygon>::iterator polyIter;
				for(polyIter = vPoly.begin() + 1; polyIter != vPoly.end() && !elim; polyIter++){
					rel = isInside(*polyIter, *pIter);
					if(rel == 1){
						elim = true;
					}
				}
			}else{
				elim = true;
			}

			if(elim){
				pIter = (*vvIter1).erase(pIter);
			}else{
				pIter++;
			}
		}

		vvIter1++;
	}
}

void Pathfinder::addPoints(vector<Point> vPoints){
	vector<Point>::iterator pIter;
	for(pIter = vPoints.begin(); pIter != vPoints.end(); pIter++){
		addPoint(*pIter);
	}
}

void Pathfinder::addPoint(Point p) {

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
					//cout << Polygon(expObjs[0]) << endl;
					break;
				}
			}
		}
	}
	std::vector<std::vector<Point> >::iterator vvIter;
	for (vvIter = expObjs.begin() + 1; vvIter != expObjs.end();
			vvIter++) {
		for (piter = (*vvIter).begin(); piter != (*vvIter).end();
				piter++) {
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

void Pathfinder::createCollision() {
	Polygon perimetro(pointList);

	BodyData datosC(perimetro);

	datosC.setSensor(true);

	Body *cuerpo = new Body(*mundo, datosC);
	cuerpo->getPosition();

	std::vector<std::vector<Point> >::iterator vvIter;
	for (vvIter = objectList.begin(); vvIter != objectList.end(); vvIter++) {

		Polygon obj(*vvIter);
		BodyData datosObj(obj);

		datosObj.setSensor(true);

		Body *cuerpoObj = new Body(*mundo, datosObj);
		cuerpoObj->getPosition();
	}
}

void Pathfinder::removeNonNavigableTris() {

	removeTris2();

	/*
	removeTris(pointList);

	std::vector<std::vector<Point> >::iterator vvIter;
	for (vvIter = objectList.begin(); vvIter != objectList.end(); vvIter++) {
		removeTris(*vvIter);
	}
	 */
}

void Pathfinder::removeTris2(){

	bool borrar;
	std::vector<Tri *>::iterator triter = triangles.begin();

	while(triter != triangles.end()){
		borrar = false;
		Polygon poly(expObjs[0]);
		if(isInside(poly, (*triter)->getIncenter()) == 1){

			vector<vector <Point> >::iterator vvIter = expObjs.begin() + 1;
			while(vvIter != expObjs.end() && !borrar){
				poly = Polygon(*vvIter);
				if(isInside(poly, (*triter)->getIncenter()) == 1){
					borrar = true;
				}
				vvIter++;
			}
		}else{
			borrar = true;
		}

		if(borrar){
			dTris.removeT(*triter);
			triangles = dTris.getTriangles();
			triter = triangles.begin();

		}else{
			triter++;
		}
	}
}

int Pathfinder::isInside(Polygon poly, Point p){
	/*
	 * 1 Dentro
	 * 0 Pertenece
	 * -1 Fuera
	 */

	int inside = 0;
	bool parteDe = false;
	vector<Point> polyPoints = poly.getPuntos();
	vector<Point>::iterator pIter;
	for(pIter = polyPoints.begin(); pIter != polyPoints.end() && !parteDe; pIter++){
		if(p == *pIter){
			parteDe = true;
		}
	}

	if(!parteDe){

		World *wAux = new World();

		BodyData data(poly);
		data.setSensor(true);

		Body *cuerpo = new Body(*wAux, data);

		int nH = wAux->CutOffPoints(p,Point(-1,-1)).size();

		if(nH % 2 == 1){
			inside = 1;
		}else{
			inside = -1;
		}

		delete wAux;
	}
	return inside;
}

void Pathfinder::removeTris(){

	int nHB, nHI, nHM;
	std::vector<Tri *>::iterator triter = triangles.begin();
	while(triter != triangles.end()){
		nHB = mundo->CutOffPoints((*triter)->getBaricenter(), Point(0,0)).size();
		nHI = mundo->CutOffPoints((*triter)->getIncenter(), Point(0,0)).size();
		if(nHI % 2 == nHB % 2){
			if(nHI % 2 == 0){
				dTris.removeT(*triter);
				triangles = dTris.getTriangles();
				triter = triangles.begin();
			}else{
				triter++;
			}
		}else{
			Point puntoMedio(Point::interP((*triter)->getBaricenter(), (*triter)->getIncenter()));
			nHM = mundo->CutOffPoints(puntoMedio, Point(0,0)).size();
			if(nHM % 2 == 0){
				dTris.removeT(*triter);
				triangles = dTris.getTriangles();
				triter = triangles.begin();
			}else{
				triter++;
			}
		}
	}
}

void Pathfinder::removeTris(std::vector<Point> vPuntos) {

	std::vector<Point>::iterator piter;
	bool exterior = false;
	for (piter = vPuntos.begin(); piter != vPuntos.end(); piter++) {

		std::vector<Tri *>::iterator triter;

		triter = triangles.begin();

		while (triter != triangles.end()) {
			exterior = false;
			if (*piter == (*triter)->getA()) {
				if (piter == vPuntos.end() - 1) {
					if (*(vPuntos.begin()) == (*triter)->getC()) {
						exterior = true;
					}
				} else {
					if (*(piter + 1) == (*triter)->getC()) {
						exterior = true;
					}
				}
			}
			if (*piter == (*triter)->getB()) {
				if (piter == vPuntos.end() - 1) {
					if (*(vPuntos.begin()) == (*triter)->getA()) {
						exterior = true;
					}
				} else {
					if (*(piter + 1) == (*triter)->getA()) {
						exterior = true;
					}
				}
			}
			if (*piter == (*triter)->getC()) {
				if (piter == vPuntos.end() - 1) {
					if (*(vPuntos.begin()) == (*triter)->getB()) {
						exterior = true;
					}
				} else {
					if (*(piter + 1) == (*triter)->getB()) {
						exterior = true;
					}
				}
			}
			if (exterior) {
				dTris.removeT(*triter);
				removeAdyacent(*triter);
				triangles = dTris.getTriangles();
				triter = triangles.begin();
			} else {
				triter++;
			}
		}
	}

	triangles = dTris.getTriangles();
}

void Pathfinder::removeAdyacent(Tri *ori) {
	if (ori->getAb() != NULL) {
		if ((mundo->CutOffPoints(ori->getIncenter(),
				ori->getAb()->getIncenter())).empty()) {
			dTris.removeT(ori->getAb());
		}
	}
	if (ori->getBc() != NULL) {
		if ((mundo->CutOffPoints(ori->getIncenter(),
				ori->getBc()->getIncenter())).empty()) {
			dTris.removeT(ori->getBc());
		}
	}
	if (ori->getCa() != NULL) {
		if ((mundo->CutOffPoints(ori->getIncenter(),
				ori->getCa()->getIncenter())).empty()) {
			dTris.removeT(ori->getCa());
		}
	}
}

void Pathfinder::generateDualGraph() {
	NavGraph dualGraph;

	int id;
	std::vector<pair<int, Tri *> > vPar;
	pair<int, Tri *> pareja;
	std::vector<Tri *>::iterator triter;

	for (triter = triangles.begin(); triter != triangles.end(); triter++) {
		id = dualGraph.addNode(ASNode((*triter)->getIncenter()));
		pareja = make_pair(id, *triter);
		vPar.push_back(pareja);
	}

	Tri *pAB, *pBC, *pCA;
	int idOri;
	int idAB, idBC, idCA;
	std::vector<pair<int, Tri *> >::iterator parIter;

	for (triter = triangles.begin(); triter != triangles.end(); triter++) {
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

		if (pAB != NULL) {
			dualGraph.addEdge(idOri, idAB);
		}
		if (pBC != NULL) {
			dualGraph.addEdge(idOri, idBC);
		}
		if (pCA != NULL) {
			dualGraph.addEdge(idOri, idCA);
		}

		// Añadimos las esquinas como nodos

		int idA = dualGraph.addNode((*triter)->getA());
		int idB = dualGraph.addNode((*triter)->getB());
		int idC = dualGraph.addNode((*triter)->getC());

		dualGraph.addEdge(idOri, idA);
		dualGraph.addEdge(idOri, idB);
		dualGraph.addEdge(idOri, idC);

	}

	navigationGraph = dualGraph;
}

NavGraph Pathfinder::getDualGraph() {

	NavGraph nav;

	generateDualGraph();

	return navigationGraph;
}

std::vector<Point> Pathfinder::smoothPath(std::vector<Point> camino) {

	std::vector<Point> vColl;
	std::vector<Point>::iterator pIter, pIter2, atajo;
	std::vector<Point> newCamino = camino;

	if(!newCamino.empty()){
		pIter = newCamino.begin();
		while(pIter != newCamino.end() - 2){
			vColl = mundo->CutOffPoints(*pIter, *(pIter + 2));

			if(vColl.empty()){
				newCamino.erase(pIter + 1);
			}else{
				pIter++;
			}
		}
	}

	return newCamino;

	/*
	pIter = camino.begin();
	while (pIter < camino.end() - 2) {
		cout << "Desde " << *pIter << endl;
		atajo = pIter + 1;
		pIter2 = pIter + 2;
		while(pIter2 != camino.end()){
			vColl = mundo->CutOffPoints(*pIter, *pIter2);

			if(vColl.empty()){
				atajo = pIter2;
				cout << "Atajo hasta " << *atajo << endl;
			}

			pIter2++;
		}

		if(pIter + 1 <= atajo - 1){
			camino.erase(pIter + 1, atajo - 1);
		}

		pIter2 = pIter + 1;
		while(*pIter2 != atajo){
			pIter2 = camino.erase(pIter2);
		}

		pIter++;
	}

	pIter = camino.begin();
	while(pIter != camino.end() - 2){
		vColl = mundo->CutOffPoints(*pIter, *(pIter + 2));

		if(vColl.empty()){
			camino.erase(pIter + 1);
		}else{
			pIter++;
		}


	}

	return camino;*/
}

Point Pathfinder::getNearestCenter(Point p) {
	Point near;
	for (unsigned int i = 0; i < triangles.size(); i++) {
		if (triangles[i]->isInside(p) == 0 || triangles[i]->isInside(p) == 1) {
			//cout << triangles[i]->getIncenter() << endl;
			near = triangles[i]->getIncenter();
			break;
		}
	}
	return near;
}

/*vector<ASNode> Pathfinder::getAdyacence(int parent, vector<ASNode> closeList) {
	//Consigo la adyacencia del nodo
	vector<ASNode> adyacence = navigationGraph.getAdyacence(parent);
	vector<ASNode>::iterator iter;
	for (iter = adyacence.begin(); iter != adyacence.end(); iter++) {
		if (isInList((*iter), closeList)) {
			adyacence.erase(iter);
		}
	}
	//Pongo al padre
	for (iter = adyacence.begin(); iter != adyacence.end(); iter++) {
		(*iter).setParent(parent);
	}
	return adyacence;
}*/

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

	double min = lista[0].getF();
	bestNode = lista[0];
	for (unsigned int i = 0; i < lista.size(); i++) {
		if (lista[i].getF() < min) {
			min = lista[i].getF();
			bestNode = lista[i];
		}
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

	//origen = navigationGraph.getNode(ori);
	//destino = navigationGraph.getNode(des);

	//COMENTADO PARA PRUEBAS. DESCOMENTAR SI SE QUIERE QUE FUNCIONE CON TRIANGULACION
	origen = navigationGraph.getNode(getNearestCenter(ori));
	destino = navigationGraph.getNode(getNearestCenter(des));
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
					//cout << "El coste total es:" << best.getF() << endl;
					closeList.push_back(best);
					vector<ASNode>::iterator iter;
					for (iter = openList.begin(); iter < openList.end();
							iter++) {
						if ((*iter).getId() == best.getId()) {
							openList.erase(iter);
							break;
						}
					}
					encontrado = true;
				} else { //Sino seguimos

					//Quitamos el nodo de menos f de la lista abierta y lo metemos en la cerrada
					closeList.push_back(best);
					//cout << "Anyadimos a la cerrada: " << best << endl;
					vector<ASNode>::iterator iter;
					for (iter = openList.begin(); iter < openList.end();
							iter++) {
						if ((*iter).getId() == best.getId()) {
							openList.erase(iter);
							break;
						}
					}

					//Conseguimos la adyacencia del mejor nodo
					adyacencia = navigationGraph.getAdyacenceCalculated(
							best.getId(), destino.getId(), best.getG());

					//Miramos que adyacencias estan en la lista abierta o cerrada
					vector<ASNode>::iterator iterAdy;
					iterAdy = adyacencia.begin();
					while (iterAdy != adyacencia.end()) {
						//Si esta en la lista abierta
						ASNode getit;
						/*cout << "######Lista abierta#####" << endl;
						for (unsigned int i = 0; i < openList.size(); i++){
							cout << openList[i];
						}
						cout << "#######################" << endl;
						cout << (*iterAdy) << endl;
						cout << "#######################" << endl;
						int patata;
						cin >> patata;*/
						if (isInList((*iterAdy), openList, getit)) {
							//cout << "###Esta en la lista "<< (*iterAdy) << "|\n" << getit << endl;
							//Mirar cual tiene mejor f
							//Si el camino desde el nodo actual es mejor que el camino hasta ese anteiormente
							if (getit.getF()
									> (*iterAdy).getF()) {

								for (unsigned int i = 0; i < openList.size(); i++){
									if (openList[i].getId()==getit.getId()){
										openList[i].setParent(best.getId());
										break;
									}
								}
								//getit.setParent(best.getId());
								//Quitamos el best de la lista cerrada y ponemos este,
							}

						} else if (isInList((*iterAdy), closeList)) {
							//cout << "### Esta en cerrada" << endl;
							//Se ignora o eso creo

						} else {
							openList.push_back(*iterAdy);
						}
						iterAdy++;
					}

				}

			}
			if (!encontrado) {
				cerr << "No se ha encontrado un camino" << endl;
			} else {
				ruta = generatePath(origen, destino, closeList, ori, des);
				//cout << "Tamanyo de A* " << totalF << endl;
			}

		} else {
			cerr << "No se ha encontrado el nodo destino cercano al punto " << ori << endl;
		}
	} else {
		cerr << "No se ha encontrado el nodo origen cercano al punto " << des << endl;
	}

	return ruta;
}

vector<Point> Pathfinder::generatePath(ASNode origen, ASNode destino,
		vector<ASNode> closeList, Point ori, Point des) {
	vector<Point> ruta;
	ASNode actual;
	ruta.push_back(des);
	actual = getNode(destino.getId(), closeList);
	while (actual.getId() != origen.getId()) {
		//cout << "Generando" << endl;
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

void Pathfinder::expandGeometry(){

	std::vector<Point> pVAux = pointList;
	std::vector<Point> tmpV;

	pVAux.insert(pVAux.begin(),pointList.end() - 1,pointList.end());
	pVAux.insert(pVAux.end(),pointList.begin(), pointList.begin() + 1);


	std::vector<Point>::iterator piter;
	Point P(0,0);
	for(piter = pVAux.begin() + 1; piter != pVAux.end() - 1; piter++){
		P = getNewPoint2(*(piter - 1), *piter, *(piter + 1));
		tmpV.push_back(P);
	}
	/*
	cout << pointList.size() << " ";
	pointList.clear();
	cout << pointList.size() << " ";
	pointList.insert(pointList.begin(), tmpV.begin(), tmpV.end());
	cout << pointList.size() << endl;*/
	expObjs.push_back(tmpV);
	tmpV.clear();

	std::vector<std::vector<Point> >::iterator vviter;

	for(vviter = objectList.begin(); vviter != objectList.end(); vviter++){

		pVAux = *vviter;

		pVAux.insert(pVAux.begin(),(*vviter).end() - 1,(*vviter).end());
		pVAux.insert(pVAux.end(),(*vviter).begin(), (*vviter).begin() + 1);

		for(piter = pVAux.begin() + 1; piter != pVAux.end() - 1; piter++){
			P = getNewPoint2(*(piter - 1), *piter, *(piter + 1));
			tmpV.push_back(P);
		}

		expObjs.push_back(tmpV);

		//	cout << tmpV.size() << " " << (*vviter).size() << endl;

		tmpV.clear();
	}


}

std::vector<std::vector<Point> > Pathfinder::getExpPoints(){
	return expObjs;
}


Point Pathfinder::getNewPoint2(Point A, Point B, Point C){

	Point P(0,0);

	double alfa = getAngle(A, B, B, C)*180/M_PI;
	double beta = 90 + alfa/2;
	double gamma;

	if(Tri::side(A, B, C) == -1){
		gamma = getAngle(B, Point(B.getX() + 10, B.getY()), A, B)*180/M_PI;
	}else{
		gamma = getAngle(B, Point(B.getX() + 10, B.getY()), B, C)*180/M_PI;
	}

	double epsilon = 0.0;

	if(A.getX() == B.getX() && A.getY() > B.getY() && B.getY() == C.getY() && C.getX() > B.getX()){
		epsilon = 315;
	}else if(C.getY() < B.getY()){
		epsilon = gamma - beta;
	}else{
		epsilon = -gamma - beta;
	}

	while(epsilon < 0)
		epsilon += 360;

	while(epsilon >= 360)
		epsilon -= 360;

	//cout << A << B << C << " (" << "A: " << alfa << ", G: " << gamma << ", B: " << beta << ", E: " << epsilon << " )" << endl;

	double x = 0.0, y = 0.0;
	//Temporal
	double radio = charRadius*1.414213562;

	x = B.getX() + radio * cos(epsilon * (M_PI / 180));
	y = B.getY() + radio * (-sin(epsilon * (M_PI / 180)));

	P.setXY(x, y);

	return P;
}

Point Pathfinder::getNewPoint(Point A, Point B, Point C){

	Point p(0,0);
	double alfa = getAngle(A, B, B, C)*180/M_PI;
	double beta = 90 + alfa/2;

	double gamma = getAngle(Point(0,0), Point(0, 10), B, C)*180/M_PI;

	//cout << A << B << C << " " << gamma << " " << alfa << " " << beta << endl;

	double nBeta = abs(fmod(beta + gamma, 360));

	double betaAux = abs(fmod(nBeta, 360));

	double x = 0.0, y = 0.0;
	//Temporal
	double radio = charRadius*1.414213562;

	x = B.getX() + radio * sin(betaAux * (M_PI / 180));
	y = B.getY() + radio * (-cos(betaAux * (M_PI / 180)));
	Point betaP(x, y);

	if(Tri::side(A, B, betaP) == -1 && Tri::side(B, C, betaP) == -1){
		p = betaP;
	}else{
		betaAux = abs(fmod(nBeta + 90, 360));

		x = B.getX() + radio * sin(betaAux * (M_PI / 180));
		y = B.getY() + radio * (-cos(betaAux * (M_PI / 180)));
		betaP.setXY(x, y);

		if(Tri::side(A, B, betaP) == -1 && Tri::side(B, C, betaP) == -1){
			p = betaP;
		}else{
			betaAux = abs(fmod(nBeta + 180, 360));

			x = B.getX() + radio * sin(betaAux * (M_PI / 180));
			y = B.getY() + radio * (-cos(betaAux * (M_PI / 180)));
			betaP.setXY(x, y);

			if(Tri::side(A, B, betaP) == -1 && Tri::side(B, C, betaP) == -1){
				p = betaP;
			}else{
				betaAux = abs(fmod(nBeta + 270, 360));

				x = B.getX() + radio * sin(betaAux * (M_PI / 180));
				y = B.getY() + radio * (-cos(betaAux * (M_PI / 180)));
				p.setXY(x, y);
			}
		}
	}
	return p;
}

double Pathfinder::getAngle(Point A1, Point A2, Point B1, Point B2){

	double Ax = A2.getX() - A1.getX();
	double Ay = A2.getY() - A1.getY();
	double Bx = B2.getX() - B1.getX();
	double By = B2.getY() - B1.getY();

	double modA = sqrt(Ax*Ax + Ay*Ay);
	double modB = sqrt(Bx*Bx + By*By);

	double suma = Ax*Bx + Ay*By;

	double cosAng = suma / (modA*modB);

	double angle = acos(cosAng);

	return angle;
}


