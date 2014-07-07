/*
 * GameMenu.cc
 *
 *  Created on: 26/12/2011
 *      Author: Chutaos Team
 */

#include "GameMenu.h"

GameMenu::GameMenu(HIDControl *hid_) {
	element = Core::Element::e_menu;
	visible = Graphics::Menus::m_none;
	menus = vector<TForm*>(Graphics::Menus::size, NULL);
	hid = hid_;
}

GameMenu::~GameMenu() {
	element = Core::Element::e_none;
	visible = Graphics::Menus::m_none;
	vector<TForm*>::iterator iter;
	while (!menus.empty()){
		TForm*aux = menus.front();
		menus.erase(menus.begin());
		delete aux;
	}
	menus.clear();
}

int GameMenu::Update() {
	if (visible != Graphics::Menus::m_none) {
		return (hid->formMenuControl(menus[visible]));
	}
	return -1;
}

void GameMenu::Render() {
	if (visible != Graphics::Menus::m_none) {
		if (menus[visible] == NULL){
			cerr << "Error: El menu no existe" << endl;
		}else{
			menus[visible]->Draw();
		}
	}
}



Graphics::Menus::Index GameMenu::getVisible() const {
	return visible;
}

void GameMenu::addMenu(Graphics::Menus::Index index, TForm *menu) {
	menus[index] = menu;
}

void GameMenu::exportOpenGL() {
	/*if (visible != Graphics::Menus::m_none) {
		if (menus[visible] == NULL){
			cerr << "Error: El menu no existe" << endl;
		}else{
			menus[visible]->Draw();
		}
	}*/
}

void GameMenu::setVisible(Graphics::Menus::Index visible) {
	this->visible = visible;
}

void GameMenu::StartUp() {
	string texturesroot = RESOURCESROOT;
	texturesroot += "texturas/";

	TForm *mInicio = new TForm(800,600,Point(400,300));
	mInicio->addWidget(new TPicture(Point(), 800, 600, texturesroot + "fondo.jpg"));
	mInicio->setColor(Color<float>(0.4,0.4,0.4,0.7));
	TLabel *label = new TLabel(730,150,"Stracomter III");
	label->setMarginUp(100);
	label->setColorText(Color<float>(0.1,0.1,0.4));
	label->setSize(100);
	mInicio->addWidget(label);
	label = new TLabel(485,50,"dos puntos espacio el mejor juego de la história");
	label->setMarginUp(0);
	label->setColorText(Color<float>(0.2,0.2,0.2));
	label->setSize(20);
	mInicio->addWidget(label);
	TButton *button = new TButton(150,50,"Comenzar");
	button->setWlabel(90);
	button->setColorBorder(Color<float>(0.2,0.2,0.4));
	button->setMarginUp(100);
	button->setEvento(3);
	mInicio->addWidget(button);
	button = new TButton(150,50,"Opciones");
	button->setWlabel(85);
	button->setColorBorder(Color<float>(0.2,0.2,0.4));
	button->setMarginUp(50);
	button->setEvento(1);
	mInicio->addWidget(button);
	button = new TButton(150,50,"Salir");
	button->setWlabel(50);
	button->setColorBorder(Color<float>(0.2,0.2,0.4));
	button->setMarginUp(50);
	button->setEvento(0);
	mInicio->addWidget(button);


	TForm *menuPause = new TForm(800,600,Point(400,300));
	TForm *menuGameOver = new TForm(800,600,Point(400,300));
	TForm *loadingScreen = new TForm(800,600,Point(400,300));
	TForm *menuWin = new TForm(800,600,Point(400,300));

	menuPause->setColor(Color<float>(0.4,0.4,0.4,0.7));
	label = new TLabel(240,150,"Pause");
	label->setMarginUp(100);
	label->setColorText(Color<float>(0.1,0.1,0.4));
	label->setSize(80);
	menuPause->addWidget(label);
	TButton *continuar = new TButton(150,50,"Fortsetzen");
	continuar->setWlabel(90);
	continuar->setColorBorder(Color<float>(0.2,0.2,0.4));
	continuar->setMarginUp(100);
	continuar->setEvento(0);//lo enlazo al evento 0 para decir que se debe continuar
	menuPause->addWidget(continuar);
	continuar = new TButton(150,50,"Sortie");
	continuar->setWlabel(50);
	continuar->setColorBorder(Color<float>(0.2,0.2,0.4));
	continuar->setMarginUp(50);
	continuar->setEvento(1);//lo enlazo al evento del modo menu
	menuPause->addWidget(continuar);

	menuGameOver->setColor(Color<float>(0.4,0.4,0.4,0.7));
	label = new TLabel(640,100,"       ¡No hay Wifi!");
	label->setMarginUp(200);
	label->setColorText(Color<float>(0.1,0.1,0.4));
	label->setSize(60);
	menuGameOver->addWidget(label);
	continuar = new TButton(150,50,"Reiniciar");
	continuar->setWlabel(80);
	continuar->setColorBorder(Color<float>(0.2,0.2,0.4));
	continuar->setMarginUp(50);
	continuar->setEvento(3);//lo enlazo al evento 0 para decir que se debe salir
	menuGameOver->addWidget(continuar);
	continuar = new TButton(150,50,"Salir");
	continuar->setWlabel(50);
	continuar->setColorBorder(Color<float>(0.2,0.2,0.4));
	continuar->setMarginUp(50);
	continuar->setEvento(1);//lo enlazo al evento de cargar menu
	menuGameOver->addWidget(continuar);

	menuWin->setColor(Color<float>(0.4,0.4,0.4,0.7));
	label = new TLabel(580,100,"¡Nivel completado!");
	label->setMarginUp(200);
	label->setColorText(Color<float>(0.1,0.1,0.4));
	label->setSize(60);
	menuWin->addWidget(label);
	continuar = new TButton(150,50,"Nueva partida");
	continuar->setWlabel(130);
	continuar->setColorBorder(Color<float>(0.2,0.2,0.4));
	continuar->setMarginUp(50);
	continuar->setEvento(3);//lo enlazo al evento 0 para decir que se debe salir
	menuWin->addWidget(continuar);
	continuar = new TButton(150,50,"Salir");
	continuar->setWlabel(50);
	continuar->setColorBorder(Color<float>(0.2,0.2,0.4));
	continuar->setMarginUp(50);
	continuar->setEvento(1);//lo enlazo al evento de cargar menu
	menuWin->addWidget(continuar);

	loadingScreen->setColor(Color<float>(0.3,0.3,0.3));
	label = new TLabel(600,300,"Cargando...");
	label->setMarginUp(250);
	label->setColorText(Color<float>(0.1,0.1,0.4));
	label->setSize(100);
	loadingScreen->addWidget(label);

	TForm *closingScreen = new TForm(800,600,Point(400,300));
	closingScreen->setColor(Color<float>(0.3,0.3,0.3));
	label = new TLabel(600,300,"Cerrando");
	label->setMarginUp(250);
	label->setColorText(Color<float>(0.1,0.1,0.4));
	label->setSize(100);
	closingScreen->addWidget(label);


	this->addMenu(Graphics::Menus::m_inicio,mInicio);
	this->addMenu(Graphics::Menus::m_loading,loadingScreen);
	this->addMenu(Graphics::Menus::m_pause,menuPause);
	this->addMenu(Graphics::Menus::m_gameover,menuGameOver);
	this->addMenu(Graphics::Menus::m_closing,closingScreen);
	this->addMenu(Graphics::Menus::m_win,menuWin);
}

vector<TForm*> GameMenu::getMenus() const
{
    return menus;
}

void GameMenu::setMenus(vector<TForm*> menus)
{
    this->menus = menus;
}



