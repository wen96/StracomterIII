#include <iostream>
#include "GameStatus.h"

using namespace std;

int main(){
	GameStatus *gs = GameStatus::getInstance();
	gs->setTypePlayer((Core::Entities::Type)1);

	vector<CharacterStatus>players(Core::Entities::size);
	players[1].hp = 30;
	players[2].hp = 40;
	players[3].hp = 60;
	players[4].hp = 90;
	gs->setPlayers(players);

	cout << "Guardamos:" << endl;
	gs->showPlayers();
	gs->saveData("stat.bin");
	gs->setTypePlayer((Core::Entities::Type)4);
	players[1].hp = 10;
	players[2].hp = 10;
	players[3].hp = 10;
	players[4].hp = 10;
	gs->setPlayers(players);
	cout << "Lo cambiamos:" << endl;
	gs->showPlayers();


	cout << gs->loadData("stat.bin") << endl;
	cout << gs->getTypePlayer() << " y " << gs->getNivelPlanta() << endl;

	cout << "Y recuperamos:" << endl;
	gs->showPlayers();

	delete gs;

	return 0;
}
