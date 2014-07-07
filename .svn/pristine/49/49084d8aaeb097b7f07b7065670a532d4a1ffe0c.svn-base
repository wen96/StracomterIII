#include <iostream>
#include "Aplication.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

using namespace std;

int main(int argc, char *argv[]){

	Aplication * app = NULL;

	app = Aplication::getInstance();

	if(argc == 2)
		app->setMap(argv[1]);

	app->Launch();

	delete app;


	return 0;
}
