#include "Pathfinder.h"
#include "Map.h"

Pathfinder::Pathfinder() {
	mundo = new World();
	navigationGraph = new NavGraph();
	map = NULL;
	charRadius = 10;
}

Pathfinder::~Pathfinder() {
	delete mundo;
	delete navigationGraph;
}

Pathfinder::Pathfinder(Point sI, Point iD, double r) : dTris(sI, iD) {
	supIzq = sI;
	infDer = iD;
	if(r > 0.0) charRadius = r;
	else 		charRadius = 1.0;
	mundo = new World();
	navigationGraph = new NavGraph();
}

Pathfinder::Pathfinder(const Pathfinder &pf){

	if(pf.map != NULL){
		this->Copia(pf);
	}else{
		mundo = new World;
		navigationGraph = new NavGraph();
	}

}

Pathfinder & Pathfinder::operator=(const Pathfinder &pf){

	if(this != &pf){

		if(pf.map != NULL){
			this->Copia(pf);
		}else{
			mundo = new World;
			navigationGraph = new NavGraph();
		}

	}
	return *this;
}

Pathfinder::Pathfinder(Map *mapa){
	mundo = new World();
	navigationGraph = new NavGraph();
	charRadius = 10;

	map = mapa;
	this->loadFromMap();

	this->Init();

}

Pathfinder::Pathfinder(string fMapa){
	mundo = new World();
	navigationGraph = new NavGraph();
	charRadius = 10;

	map = new Map(fMapa);
	map->loadData();
	this->loadFromMap();

	this->Init();

}

void Pathfinder::setMap(string fName) {
	if(map != NULL){
		map->setMap(fName);
	}else{
		map = new Map(fName);
	}
	map->loadData();

	this->loadFromMap();

	this->Init();

}

void Pathfinder::setMap(Map * mapa){

	map = mapa;

	this->loadFromMap();

	this->Init();
}

void Pathfinder::loadFromMap(){
	supIzq = map->getSupIzq();
	infDer = map->getInfDer();
	pointList = map->getPerimeter();
	objectList = map->getObjects();
}

void Pathfinder::Copia(const Pathfinder &pf){
	navigationGraph = new NavGraph(*pf.navigationGraph);
	mundo = new World(*pf.mundo);
	supIzq = pf.supIzq;
	infDer = pf.infDer;
	charRadius = pf.charRadius;
	map = pf.map;
	pointList = pf.pointList;
	objectList = pf.objectList;
}

void Pathfinder::Init(){

	//charRadius = 5; //TODO provisional

	dTris.createBorders(supIzq, infDer);

	vector<vector<Point> >::iterator iter;
	for(iter = objectList.begin(); iter != objectList.end(); iter++){
		Polygon pol(*iter);
		if(pol.isClockwise()){
			pol.Reverse();
			*iter = pol.getPuntos();
		}
	}

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


double Pathfinder::getCharRadius() const
{
	return charRadius;
}

void Pathfinder::setCharRadius(double charRadius)
{
	this->charRadius = charRadius;
}

void Pathfinder::flattenGeometry(){

	vector<vector <Point> >::iterator vvIter1, vvIter2;
	vector<Body *> bodyVec;
	World *mAux = new World;

	for(vvIter1 = expObjs.begin(); vvIter1 != expObjs.end(); vvIter1++){
		Polygon pol(*vvIter1);
		BodyData data(pol);
		data.setSensor(true);
		Body *body = new Body(*mAux, data);
		bodyVec.push_back(body);
	}

	vvIter1 = expObjs.begin() + 1;
	while( vvIter1 != expObjs.end()){

		bool unido = false;
		int i1 = vvIter1 - expObjs.begin();

		vvIter2 = vvIter1 + 1;
		while(vvIter2 != expObjs.end() && !unido){

			int i2 = vvIter2 - expObjs.begin();

			if(!bodyVec[i1]->contact(*bodyVec[i2]).empty()){

				Polygon pol1(*vvIter1);
				Polygon pol2(*vvIter2);
				pol1.Join(pol2);

				if(pol1.isClockwise()){
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
			}else{
				vvIter2++;
			}
		}
		if(!unido)
			vvIter1++;
	}

	Polygon periPoly(expObjs[0]);
	vvIter1 = expObjs.begin() + 1;
	while(vvIter1 != expObjs.end()){

		int i = vvIter1 - expObjs.begin();

		if(!bodyVec[0]->contact(*bodyVec[i]).empty()){
			Polygon pol(*vvIter1);

			pol.Inter(periPoly);

			if(pol.isClockwise()){
				pol.Reverse();
			}

			*vvIter1 = pol.getPuntos();

		}
		vvIter1++;
	}

	delete mAux;
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

	removeTris();
}

void Pathfinder::removeTris(){

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
		cuerpo->getPosition();

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
	int id;
	std::vector<pair<int, Tri *> > vPar;
	pair<int, Tri *> pareja;
	std::vector<Tri *>::iterator triter;

	for (triter = triangles.begin(); triter != triangles.end(); triter++) {
		id = navigationGraph->addNode(ASNode((*triter)->getIncenter()));
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
			navigationGraph->addEdge(idOri, idAB);
		}
		if (pBC != NULL) {
			navigationGraph->addEdge(idOri, idBC);
		}
		if (pCA != NULL) {
			navigationGraph->addEdge(idOri, idCA);
		}

		// Añadimos las esquinas como nodos

		int idA = navigationGraph->addNode((*triter)->getA());
		int idB = navigationGraph->addNode((*triter)->getB());
		int idC = navigationGraph->addNode((*triter)->getC());

		navigationGraph->addEdge(idOri, idA);
		navigationGraph->addEdge(idOri, idB);
		navigationGraph->addEdge(idOri, idC);
	}
}

NavGraph * Pathfinder::getDualGraph() {

	return navigationGraph;
}

std::vector<Point> Pathfinder::smoothPath(std::vector<Point> camino) {

	std::vector<Point> vColl;
	std::vector<Point>::iterator pIter, pIter2, atajo;
	std::vector<Point> newCamino = camino;

	if(newCamino.size() >= 3){
		pIter = newCamino.begin();
		while(pIter < newCamino.end() - 2){
			vColl = mundo->CutOffPoints(*pIter, *(pIter + 2));

			if(vColl.empty()){
				newCamino.erase(pIter + 1);
			}else{
				pIter++;
			}
		}
	}

	return newCamino;
}

Point Pathfinder::getNearestCenter(Point p) {
	Point near;
	Point nearReal;
	bool fistIter = true;
	bool foundTraingle = false;
	double distanceAnt = 0;


	vector<Tri*>::iterator iter;
	for (iter = triangles.begin(); iter != triangles.end() &&!foundTraingle; iter++){
		int isIn = (*iter)->isInside(p);
		if (isIn == 0 || isIn == 1){
			near = (*iter)->getIncenter();
			foundTraingle = true;
		}
		if (fistIter){
			nearReal = (*iter)->getIncenter();
			distanceAnt = Point::distance((*iter)->getIncenter(),p);
			fistIter = false;
		}else{
			double distAct = Point::distance((*iter)->getIncenter(),p);
			if (distAct < distanceAnt){
				nearReal = (*iter)->getIncenter();
				distanceAnt = distAct;
			}
		}

	}

	if (!foundTraingle){
		near = nearReal;
	}
	return near;
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
	origen = navigationGraph->getNode(getNearestCenter(ori));
	destino = navigationGraph->getNode(getNearestCenter(des));
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
					////cout << "Anyadimos a la cerrada: " << best << endl;
					vector<ASNode>::iterator iter;
					for (iter = openList.begin(); iter < openList.end();
							iter++) {
						if ((*iter).getId() == best.getId()) {
							openList.erase(iter);
							break;
						}
					}

					//Conseguimos la adyacencia del mejor nodo
					adyacencia = navigationGraph->getAdyacenceCalculated(
							best.getId(), destino.getId(), best.getG());

					//Miramos que adyacencias estan en la lista abierta o cerrada
					vector<ASNode>::iterator iterAdy;
					iterAdy = adyacencia.begin();
					while (iterAdy != adyacencia.end()) {
						//Si esta en la lista abierta
						ASNode getit;
						if (isInList((*iterAdy), openList, getit)) {
							if (getit.getF()
									> (*iterAdy).getF()) {

								for (unsigned int i = 0; i < openList.size(); i++){
									if (openList[i].getId()==getit.getId()){
										openList[i].setParent(best.getId());
										break;
									}
								}
							}

						} else if (isInList((*iterAdy), closeList)) {

						} else {
							openList.push_back(*iterAdy);
						}
						iterAdy++;
					}

				}

			}
			if (!encontrado) {
//				cerr << "No se ha encontrado un camino" << endl;
			} else {
				ruta = generatePath(origen, destino, closeList, ori, des);
			}

		} else {
//			cerr << "No se ha encontrado el nodo destino cercano al punto " << ori << endl;
		}
	} else {
//		cerr << "No se ha encontrado el nodo origen cercano al punto " << des << endl;
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

void Pathfinder::expandGeometry(){

	std::vector<Point> pVAux = pointList;
	std::vector<Point> tmpV;

	pVAux.insert(pVAux.begin(),pointList.end() - 1,pointList.end());
	pVAux.insert(pVAux.end(),pointList.begin(), pointList.begin() + 1);


	std::vector<Point>::iterator piter;
	Point P(0,0);
	for(piter = pVAux.begin() + 1; piter != pVAux.end() - 1; piter++){
		P = Polygon::getNewPoint(*(piter - 1), *piter, *(piter + 1), true, charRadius);

		tmpV.push_back(P);
	}

	expObjs.push_back(tmpV);

	std::vector<std::vector<Point> >::iterator vviter;

	for(vviter = objectList.begin(); vviter != objectList.end(); vviter++){
		tmpV.clear();
		pVAux = *vviter;

		pVAux.insert(pVAux.begin(),(*vviter).end() - 1,(*vviter).end());
		pVAux.insert(pVAux.end(),(*vviter).begin(), (*vviter).begin() + 1);

		for(piter = pVAux.begin() + 1; piter != pVAux.end() - 1; piter++){
			P = Polygon::getNewPoint(*(piter - 1), *piter, *(piter + 1), true, charRadius);
			tmpV.push_back(P);
		}
		expObjs.push_back(tmpV);
	}
}

std::vector<std::vector<Point> > Pathfinder::getExpPoints(){
	return expObjs;
}
