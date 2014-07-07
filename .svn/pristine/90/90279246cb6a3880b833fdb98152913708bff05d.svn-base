#include <iostream>
#include "Clock.h"
#include "TProgressBar.h"
#include "TWindow.h"
#include "TCheckBox.h"

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

int main(int argc, char * argv[]) {

	TWindow window;
	window.setNombreVentana("Stracometer III: A Star");
	window.openSFML(WIDTH, HEIGHT, false);
	window.Init();
	window.setFrameLimit(0);

	TProgressBar tp1(Point(50, 50), 400, 100);
	TProgressBar tp2(Point(50, 175), 400, 100);
	TProgressBar tp3(Point(50, 300), 400, 100);

	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WIDTH, 0, HEIGHT, -1, 1);
	glScalef(1, -1, 1);
	glTranslatef(0, -1.0 * HEIGHT, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	TCheckBox *chkBox = new TCheckBox(Point(500,500),"Hola mundo");

	Clock time;

	while (window.isOpen()) {

		tp1.setPercentage(time.getElapsedMiliseconds() / 5000.0);
		tp2.setPercentage(time.getElapsedMiliseconds() / 3000.0);
		tp3.setPercentage(time.getElapsedMiliseconds() / 1000.0);

		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		tp1.exportOpenGL();
		tp2.exportOpenGL();
		tp3.exportOpenGL();
		chkBox->Draw();

		window.display(true);
	}

	return 0;
}
