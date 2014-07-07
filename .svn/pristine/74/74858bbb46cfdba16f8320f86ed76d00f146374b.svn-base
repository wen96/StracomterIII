#include "AI.h"

AI::AI() {
	for(int i = 0; i < Core::SmartEntities::size; i++){
		fsmV.push_back(makeFSM((Core::SmartEntities::Type) i));
	}
	pf = NULL;
}

void AI::Reset(){
	if (pf != NULL){
		delete pf;
		pf = NULL;
	}
}

AI::~AI() {

}

AI::AI(const AI & ia) {

	this->fsmV = ia.fsmV;
	this->pf = ia.pf;
}

AI & AI::operator =(const AI & ia) {

	if(this != &ia){

		this->fsmV = ia.fsmV;
		this->pf = ia.pf;
	}
	return *this;
}

void AI::setManager(EntityManager *manager_){
	entMan = manager_;
}

EntityManager * AI::getManager(){
	return entMan;
}

void AI::setControler(EventControl *events){
	eventos = events;
}

NavGraph *  AI::getTriangulation(){
	return pf->getDualGraph();
}

// BUCLE DE LA IA

void AI::Update(){

	// Recorremos las entidades del juego
	vector<Entity *> bots = entMan->getBots();//Consigo las entidades que tienen IA
	vector<Entity *>::iterator entIter;
	for(entIter = bots.begin(); entIter != bots.end(); entIter++){
		Bot *botAcual = (Bot *) (*entIter);
		string estado = botAcual->getStatusS();
		switch (botAcual->getType()){
			case Core::Entities::e_enemy1:
			case Core::Entities::e_enemy2:
			case Core::Entities::e_enemy3:
			case Core::Entities::e_miniboss:
			case Core::Entities::e_megaboss:
				((Enemy*)botAcual)->updateAI(entMan);
				break;
			case Core::Entities::e_explosive:
				(botAcual)->UpdateSanar();
				((Explosive*)botAcual)->updateAI(entMan);
				break;
			case Core::Entities::e_captain:
				(botAcual)->UpdateSanar();
				((Captain*)botAcual)->updateAI(entMan);
				break;
			case Core::Entities::e_tecnic:
				(botAcual)->UpdateSanar();
				((Technic*)botAcual)->updateAI(entMan);
				break;
			case Core::Entities::e_especialist:
				(botAcual)->UpdateSanar();
				((Especialist*)botAcual)->updateAI(entMan);
				break;
			default:
				break;
		}
	}

}

int AI::updateFSM(Core::SmartEntities::Type entidad, int estado, int input){
	int output;

	fsmV[entidad].makeCurrent(estado);
	output = fsmV[entidad].updateStates(input);

	return output;
}

void AI::initMap(Map * mapa, vector<Entity *> doors) {
	if(pf == NULL){
		pf = new Pathfinder();
	}

	//cout << "El area del mapa es " << mapa->getArea() << " pixeles cuadrados." << endl;

	pf->setMap(mapa);
	pf->setTriangulation(mapa->getTriangulation());
	pf->generateDualGraph();

	vector<Entity *>::iterator dIter;
	for(dIter = doors.begin(); dIter != doors.end(); dIter++){
		Door * pared = (Door *) *dIter;
		pared->setNodes(pf->addDoor(pared->getPoints()));
		pared->setPF(pf);
	}
}

vector<Point> AI::getPath(Point a, Point b) {
	return pf->AStar(a,b);
}



void AI::Init(){
	vector<Entity *> bots = entMan->getBots();//Consigo las entidades que tienen IA
	vector<Entity *>::iterator entIter;
	for(entIter = bots.begin(); entIter != bots.end(); entIter++){
		Bot *botAcual = (Bot *) (*entIter);
		botAcual->setPathfinder(pf);
	}
}

Pathfinder *AI::getPf(){
    return pf;
}

FSM AI::makeFSM(Core::SmartEntities::Type entidad){
	FSM fsm;

	switch(entidad){
	case Core::SmartEntities::e_captain:

		// Seguimos al jugador
		fsm.addState("Follow");

		// Atacamos a un enemigo
		fsm.addState("Attack");

		// Recuperamos munición
		fsm.addState("Resupply");

		// Nos curamos
		fsm.addState("Retreat");

		// No pasa nada (vamos a Follow)

		fsm.addTransition(2, 1, 10);
		fsm.addTransition(3, 1, 10);
		fsm.addTransition(4, 1, 10);

		// Vemos un enemigo (vamos a Attack)

		fsm.addTransition(1, 2, 20);
		fsm.addTransition(3, 2, 20);
		fsm.addTransition(4, 2, 20);

		// Se nos acaba la municion (vamos a Resupply)

		fsm.addTransition(1, 3, 30);
		fsm.addTransition(2, 3, 30);
		fsm.addTransition(4, 3, 30);


		// Nos hacen daño (vamos a Retreat)

		fsm.addTransition(1, 4, 40);
		fsm.addTransition(2, 4, 40);
		fsm.addTransition(3, 4, 40);

		break;

	case Core::SmartEntities::e_tecnic:

		// Seguimos al jugador
		fsm.addState("Follow");

		// Atacamos a un enemigo
		fsm.addState("Attack");

		// Recuperamos munición
		fsm.addState("Resupply");

		// Nos curamos
		fsm.addState("Heal");

		// No pasa nada (vamos a Follow)

		fsm.addTransition(2, 1, 10);
		fsm.addTransition(3, 1, 10);
		fsm.addTransition(4, 1, 10);

		// Vemos un enemigo (vamos a Attack)

		fsm.addTransition(1, 2, 20);
		fsm.addTransition(3, 2, 20);
		fsm.addTransition(4, 2, 20);

		// Se nos acaba la municion (vamos a Resupply)

		fsm.addTransition(1, 3, 30);
		fsm.addTransition(2, 3, 30);
		fsm.addTransition(4, 3, 30);

		// Nos hacen daño (vamos a Heal)

		fsm.addTransition(1, 4, 40);
		fsm.addTransition(2, 4, 40);
		fsm.addTransition(3, 4, 40);

		break;

	case Core::SmartEntities::e_especialist:

		// Seguimos al jugador
		fsm.addState("Follow");

		// Atacamos a un enemigo
		fsm.addState("Attack");

		// Nos curamos
		fsm.addState("Heal");

		// No pasa nada (vamos a Follow)

		fsm.addTransition(2, 1, 10);
		fsm.addTransition(3, 1, 10);
		fsm.addTransition(4, 1, 10);

		// Vemos un enemigo (vamos a Attack)

		fsm.addTransition(1, 2, 20);
		fsm.addTransition(3, 2, 20);
		fsm.addTransition(4, 2, 20);

		// Nos hacen daño (vamos a Heal)

		fsm.addTransition(1, 3, 40);
		fsm.addTransition(2, 3, 40);
		fsm.addTransition(3, 3, 40);

		break;

	case Core::SmartEntities::e_explosives:

		// Seguimos al jugador
		fsm.addState("Follow");

		// Atacamos a un enemigo
		fsm.addState("Attack");

		// Recuperamos munición
		fsm.addState("Resupply");

		// Nos curamos
		fsm.addState("Heal");

		// No pasa nada (vamos a Follow)

		fsm.addTransition(2, 1, 10);
		fsm.addTransition(3, 1, 10);
		fsm.addTransition(4, 1, 10);

		// Vemos un enemigo (vamos a Attack)

		fsm.addTransition(1, 2, 20);
		fsm.addTransition(3, 2, 20);
		fsm.addTransition(4, 2, 20);

		// Se nos acaba la municion (vamos a Resupply)

		fsm.addTransition(1, 3, 30);
		fsm.addTransition(2, 3, 30);
		fsm.addTransition(4, 3, 30);

		// Nos hacen daño (vamos a Heal)

		fsm.addTransition(1, 4, 40);
		fsm.addTransition(2, 4, 40);
		fsm.addTransition(3, 4, 40);

		break;

	case Core::SmartEntities::e_enemy1:

		// Patrullamos la zona = 1
		fsm.addState("Patrol");

		// Atacamos a un enemigo = 2
		fsm.addState("Attack");

		// Perseguimos a un enemigo = 3
		fsm.addState("Pursue");


		// No pasa nada (vamos a Patrol)

		fsm.addTransition(2, 1, 10);
		fsm.addTransition(3, 1, 10);

		// Vemos un enemigo (vamos a Attack)

		fsm.addTransition(1, 2, 20);
		fsm.addTransition(3, 2, 20);

		// Se nos acaba la municion (vamos a Follow)

		fsm.addTransition(1, 3, 30);
		fsm.addTransition(2, 3, 30);

		break;

	case Core::SmartEntities::e_enemy2:

		// Patrullamos la zona
		fsm.addState("Patrol");

		// Atacamos a un enemigo
		fsm.addState("Attack");

		// Perseguimos a un enemigo
		fsm.addState("Pursue");


		// No pasa nada (vamos a Patrol)

		fsm.addTransition(2, 1, 10);
		fsm.addTransition(3, 1, 10);

		// Vemos un enemigo (vamos a Attack)

		fsm.addTransition(1, 2, 20);
		fsm.addTransition(3, 2, 20);

		// Se nos acaba la municion (vamos a Follow)

		fsm.addTransition(1, 3, 30);
		fsm.addTransition(2, 3, 30);

		break;

	case Core::SmartEntities::e_enemy3:

		// Patrullamos la zona
		fsm.addState("Patrol");

		// Atacamos a un enemigo
		fsm.addState("Attack");

		// Perseguimos a un enemigo
		fsm.addState("Pursue");


		// No pasa nada (vamos a Patrol)

		fsm.addTransition(2, 1, 10);
		fsm.addTransition(3, 1, 10);

		// Vemos un enemigo (vamos a Attack)

		fsm.addTransition(1, 2, 20);
		fsm.addTransition(3, 2, 20);

		// Se nos acaba la municion (vamos a Follow)

		fsm.addTransition(1, 3, 30);
		fsm.addTransition(2, 3, 30);

		break;

	case Core::SmartEntities::e_miniboss:

		// Patrullamos la zona
		fsm.addState("Patrol");

		// Atacamos a un enemigo
		fsm.addState("Attack");

		// Perseguimos a un enemigo
		fsm.addState("Pursue");


		// No pasa nada (vamos a Patrol)

		fsm.addTransition(2, 1, 10);
		fsm.addTransition(3, 1, 10);

		// Vemos un enemigo (vamos a Attack)

		fsm.addTransition(1, 2, 20);
		fsm.addTransition(3, 2, 20);

		// Se nos acaba la municion (vamos a Follow)

		fsm.addTransition(1, 3, 30);
		fsm.addTransition(2, 3, 30);

		break;

	case Core::SmartEntities::e_megaboss:

		// Patrullamos la zona
		fsm.addState("Patrol");

		// Atacamos a un enemigo
		fsm.addState("Attack");

		// Perseguimos a un enemigo
		fsm.addState("Pursue");


		// No pasa nada (vamos a Patrol)

		fsm.addTransition(2, 1, 10);
		fsm.addTransition(3, 1, 10);

		// Vemos un enemigo (vamos a Attack)

		fsm.addTransition(1, 2, 20);
		fsm.addTransition(3, 2, 20);

		// Se nos acaba la municion (vamos a Follow)

		fsm.addTransition(1, 3, 30);
		fsm.addTransition(2, 3, 30);

		break;
	default:
		break;
	}

	return fsm;
}
