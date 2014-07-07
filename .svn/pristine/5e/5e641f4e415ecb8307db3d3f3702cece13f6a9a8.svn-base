#include <iostream>
#include "MovementComp.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <MotorGrafico.h>
#include "TWindow.h"
#include "IOControl.h"
using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

int main(int argc, char * argv[]){

	IOControl *eventosTeclado = NULL;
	TWindow window;
	window.setNombreVentana("Stracometer III: A Star");
	window.openSFML(WIDTH, HEIGHT, false);
	window.Init();
	window.setFrameLimit(0);
	eventosTeclado = new IOControl(&window);

	while (window.isOpen()) {

		glutSolidTeapot(0.8);

		window.display(true);
	}

	return 0;
}
