#include <iostream>
#include "EntityManager.h"

using namespace std;

int main(int argc, char *argv[]){
	World *w = new World();
	ResourceManager *r = new ResourceManager(w);
	EntityManager man(r);
	man.addPlayer(Point(0,0),1.0,Color<float>(1.0,1.0,1.0));
	man.addWall(Point(0,0),1.0,Color<float>(1.0,1.0,1.0));
	man.addEnemy(Point(0,0),1.0,Color<float>(1.0,1.0,1.0));
	cout << man.getNumEntities() << endl;
	if(r != NULL)
		delete r;
	if(w != NULL)
		delete w;

	return 0;
}
