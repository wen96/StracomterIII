/*
 * TWindow.cc
 *
 *  Created on: 09/11/2011
 *      Author: Chutaos Team
 */

#include "TWindow.h"

#include <iostream>
using namespace std;
TWindow::TWindow() {
	screen = NULL;
	nombreVentana = "Stracomter III dos puntos espacio El mejor juego de la historia";
}

TWindow::~TWindow() {
	delete screen;
}

void TWindow::open(bool full){
	int argc = 1;
	char **argv = NULL;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(20,20);
	glutInitWindowSize(640, 480);
	if (fullscreen){
		glutFullScreen();
	}
	fullscreen=full;
	glutCreateWindow(nombreVentana.c_str());
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);
}
void TWindow::openSFML(bool full){
	if (screen==NULL){
		if (full){
			screen = new sf::Window(sf::VideoMode::GetMode(0),nombreVentana,sf::Style::Fullscreen);
			fullscreen=full;
		}else{
			screen = new sf::Window(sf::VideoMode::GetMode(0),nombreVentana,sf::Style::Titlebar | sf::Style::Close);
			fullscreen=full;
		}
		screen->Display();
	}
}

bool TWindow::isOpen(){
	bool opened = false;
	if (screen != NULL){
		opened = screen->IsOpened();
	}
	return opened;
}

void TWindow::openSFML() {
	if (screen==NULL){
		screen = new sf::Window(sf::VideoMode::GetMode(0),nombreVentana);
		screen->Display();
		fullscreen=false;
	}
}

void TWindow::openSFML(int width, int height) {
	if (screen==NULL){
		screen = new sf::Window(sf::VideoMode(width,height),nombreVentana);
		screen->Display();
		fullscreen=false;
	}
}

void TWindow::openSFML(int width, int height, bool full) {
	if (screen==NULL){
		if (full){
			screen = new sf::Window(sf::VideoMode(width,height),nombreVentana,sf::Style::Fullscreen);
			fullscreen=full;
		}else{
			screen = new sf::Window(sf::VideoMode(width,height),nombreVentana,
					sf::Style::Titlebar | sf::Style::Close);
			fullscreen=full;
		}
		screen->SetFramerateLimit(60);
		screen->Display();
	}
}

void TWindow::showMouseCursos(bool mostrar){
	screen->ShowMouseCursor(mostrar);
}

void TWindow::close(){
	if (screen!=NULL){
		screen->Close();
		delete screen;
		screen = NULL;
		fullscreen=false;
	}
}

void TWindow::Init(){

	int argc = 1;
	char **argv = NULL;
	glutInit(&argc, argv);
	//glViewport(0,0,400, 300);
	//glOrtho(0, 640, 0, 300, -1, 1);
	//glClearColor(1.0, 1.0, 1.0, 1.0);
	/*cout << width << endl;
	glOrtho(-800, 800 , -600, 600, -100, 100);
	//gluOrtho2D(-width, width, -height, height); // DE AQUI NO LEE EL ORTHO*/
	//glClear(GL_COLOR_BUFFER_BIT);
}

bool TWindow::display(bool paused_){

	bool paused = paused_;
	sf::Event event;

	if (screen!=NULL){
		//Reestructurando la pantalla
		while(screen->GetEvent(event)){
			if (event.Type == sf::Event::Closed || (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Escape)){
					screen->Close();
			}
			if (event.Type == sf::Event::Resized){
				//glViewport(0,0, event.Size.Width, event.Size.Height);

			}
			if (event.Type == sf::Event::KeyReleased && event.Key.Code == sf::Key::P){
					paused = !paused;
			}
		}
		screen->Display();
	}
	return paused;
}

void TWindow::display(){
	if (screen!=NULL){
		//Reestructurando la pantalla
		screen->Display();
	}
}

const sf::Input & TWindow::getInputs() const{
	return  screen->GetInput();
}

const unsigned int TWindow::getHeight() const{
	if (screen != NULL){
		return  screen->GetHeight();
	}else{
		return 0;
	}
}

const unsigned int TWindow::getWidth() const{
	if (screen != NULL){
		return  screen->GetWidth();
	}else{
		return 0;
	}
}

const bool TWindow::getFullscreen() const{
	return  fullscreen;
}

float TWindow::getFrameTime() {
	if (screen != NULL){
		return screen->GetFrameTime();
	}else{
		return 0;
	}
}

void TWindow::setFrameLimit(unsigned int limit) {
	if (screen != NULL){
		screen->SetFramerateLimit(limit);
	}
}

bool TWindow::getEvent(sf::Event &event){
	if (screen != NULL){
		return screen->GetEvent(event);
	}else{
		return false;
	}
}

void TWindow::setNombreVentana(string n){
	nombreVentana = n;
}


