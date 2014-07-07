/*
 * GameStatus.cc
 *
 *  Created on: 03/04/2012
 *      Author: Chutaos Team
 */

#include "GameStatus.h"

GameStatus * GameStatus::_app = NULL;

GameStatus* GameStatus::getInstance() {
	if (_app == NULL) {
		_app = new GameStatus();
	}
	return _app;
}

void GameStatus::incrementLevel() {
	nivelPlanta++;
}

GameStatus::GameStatus() {
	typePlayer = Core::Entities::e_captain;
	players = vector<CharacterStatus>(Core::Entities::size);
	initializeVectorPlayers();
	nivelPlanta = 0;
	zonaPlanta = -1;
	puntuacionPlayer = 0;
	nomFich = "testFiles/save.dat";
}
void GameStatus::initializeVectorPlayers() {
	CharacterFeature *cf = CharacterFeature::getInstance();
	cf->loadData("testFiles/features/f1.xml");
	for (unsigned int i = 1; i < 5 && i < players.size(); i++) {
		CharacterStatus cs;
		cs.hp = cf->featuresContainer[i].HP;
		cs.ammo = 50;
		cs.score = 0;
		cs.type = (Core::Entities::Type) i;
		players[i] = cs;
	}
}

GameStatus::~GameStatus() {
	typePlayer = Core::Entities::e_captain;
	players.clear();
	nivelPlanta = 0;
	zonaPlanta = -1;
	puntuacionPlayer = 0;
	nomFich = "";
}

void GameStatus::showPlayers() {
	for (unsigned int i = 1; i < 5 && i < players.size(); i++) {
		//cout << "========" << endl;
		//cout << players[i];
	}
	//cout << "========" << endl;
}

void GameStatus::getCharacters(EntityManager *ent) {
	//Entity *aux = NULL;
	puntuacionPlayer = ((Character*) ent->getPlayer())->getScore();
	for (int i = 1; i < 5; i++) {
		Core::Entities::Type t = (Core::Entities::Type) i;
		vector<Entity *> vect = ent->getEntitiesbyType(t);
		CharacterStatus cs;
		if (!vect.empty()) {
			Character *person = (Character*) vect[0];
			cs.hp = person->getHp();
			cs.ammo = person->getAmmunition();
			cs.score = person->getScore();
			cs.type = person->getType();
			for (unsigned int i = 0; i < (person->getRecompensas()).size(); i++) {
				if (i == 0)
					cs.recomp1 = (person->getRecompensas())[0]->getObjectClass();
				if (i == 1)
					cs.recomp2 = (person->getRecompensas())[1]->getObjectClass();
				if (i == 2)
					cs.recomp3 = (person->getRecompensas())[2]->getObjectClass();
				if (i == 3)
					cs.recomp4 = (person->getRecompensas())[3]->getObjectClass();
				if (i == 4)
					cs.recomp5 = (person->getRecompensas())[4]->getObjectClass();
			}
			players[t] = cs;
		} else {
			players[t] = cs;
		}
	}

	/*
	 vector<Entity*>::iterator iter;
	 for (iter = vect.begin(); iter != vect.end(); iter++){
	 Character *person = (Character*)(*iter);
	 CharacterStatus cs;
	 cs.hp = person->getHp();
	 cs.ammo = person->getAmmunition();
	 cs.score = person->getScore();
	 cs.type = person->getType();
	 players[person->getType()] = cs;
	 //cout << "guardo: " << cs.hp << endl;
	 }
	 */
}

void GameStatus::applyCharacterStatus(EntityManager *ent) {
	vector<Entity *> vect = ent->getGoodPersons();
	vector<Entity*>::iterator iter;
	for (iter = vect.begin(); iter != vect.end(); iter++) {
		Character *person = (Character*) (*iter);
		person->setHp(players[person->getType()].hp);
		person->setAmmunition(players[person->getType()].ammo);
		person->setScore(players[person->getType()].score);
		////cout << "Cargo" << person->getHp() << endl;

		if (players[person->getType()].recomp1 != -1)
			person->addObject(new Object(((Core::Objects::Class) (players[person->getType()]).recomp1)));
		if (players[person->getType()].recomp2 != -1)
			person->addObject(new Object(((Core::Objects::Class) (players[person->getType()]).recomp2)));
		if (players[person->getType()].recomp3 != -1)
			person->addObject(new Object(((Core::Objects::Class) (players[person->getType()]).recomp3)));
		if (players[person->getType()].recomp4 != -1)
			person->addObject(new Object(((Core::Objects::Class) (players[person->getType()]).recomp4)));
		if (players[person->getType()].recomp5 != -1)
			person->addObject(new Object(((Core::Objects::Class) (players[person->getType()]).recomp5)));

		//Object *a = new Object((Core::Objects::Class)players[person->getType()].recomp5);
		if (person->getHp() <= 0) {
			////cout << "Hay un muerto" << endl;
			ent->addDead(person->getType(), person->getId());
		}
	}
	((Character*) ent->getPlayer())->setScore(puntuacionPlayer);
}

bool GameStatus::saveData() {
	return saveData(nomFich);
}

bool GameStatus::loadData() {
	return loadData(nomFich);
}

bool GameStatus::loadData(string fich) {
	bool loaded = false;
	ifstream file(fich.c_str(), ios::in | ios::binary);

	if (file) {
		file.read((char*) &typePlayer, sizeof(int));
		file.read((char*) &nivelPlanta, sizeof(int));
		file.read((char*) &puntuacionPlayer, sizeof(int));

		//Guardamos el estado de los players
		for (unsigned int i = 1; i < 5 && i < players.size(); i++) {
			file.read((char*) &players[i], sizeof(CharacterStatus));
		}

		file.close();
		loaded = true;
	}
	return loaded;
}

bool GameStatus::saveData(string fich) {
	bool saved = false;
	ofstream file;
	file.open(fich.c_str(), ios::out | ios::binary | ios::trunc);

	file.write((char*) &typePlayer, sizeof(int));
	file.write((char*) &nivelPlanta, sizeof(int));
	file.write((char*) &puntuacionPlayer, sizeof(int));

	//Guardamos el estado de los players
	for (unsigned int i = 1; i < 5 && i < players.size(); i++) {
		file.write((char*) &players[i], sizeof(CharacterStatus));
	}

	file.close();
	saved = true;

	return saved;
}

ostream& operator<<(ostream &os, const GameStatus &c) {
	for (unsigned int i = 1; i < 5 && i < c.players.size(); i++) {
		//cout << c.players[i] << endl;
	}
	return os;
}

void GameStatus::setTypePlayer(Core::Entities::Type t) {
	typePlayer = t;
}

Core::Entities::Type GameStatus::getTypePlayer() const {
	return typePlayer;
}

int GameStatus::getNivelPlanta() const {
	return nivelPlanta;
}

void GameStatus::setNivelPlanta(int nivelPlanta) {
	this->nivelPlanta = nivelPlanta;
}

vector<CharacterStatus> GameStatus::getPlayers() const {
	return players;
}

void GameStatus::setPlayers(vector<CharacterStatus> players) {
	this->players = players;
}

int GameStatus::getZona() const {
	return zonaPlanta;
}

void GameStatus::setZona(int zona) {
	this->zonaPlanta = zona;
}

void GameStatus::selectZona(int zona) {
	switch (zona) {
	case 1:
		recompensa = Core::Objects::ammo_pack_1;
		break;
	case 2:
		recompensa = Core::Objects::health_pack_1;
		break;
	case 3:
		recompensa = Core::Objects::ammo_pack_2;
		break;
	case 4:
		recompensa = Core::Objects::health_pack_2;
		break;
	case 5:
		recompensa = Core::Objects::ammo_pack_3;
		break;
	case 6:
		recompensa = Core::Objects::health_pack_3;
		break;
	}
	this->zonaPlanta = zona;
}

Core::Objects::Class GameStatus::getRecompensa() const {
	return recompensa;
}

void GameStatus::setRecompensa(Core::Objects::Class recompensa) {
	this->recompensa = recompensa;
}

bool GameStatus::isVivitoYColeando(Core::Entities::Type t) {
	bool vivito = false;
	if (t > 0 && t < 5)
		vivito = players[t].hp != 0;

	//cout<<"LA VIDA DE "<<t<<" VALE: "<< players[t].hp<<endl;
	return vivito;
}

int GameStatus::getPuntuacionPlayer() const {
	return puntuacionPlayer;
}

void GameStatus::setPuntuacionPlayer(int puntuacionPlayer) {
	this->puntuacionPlayer = puntuacionPlayer;
}

