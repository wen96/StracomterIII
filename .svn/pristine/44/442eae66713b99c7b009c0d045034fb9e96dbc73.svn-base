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
	efectVisible = Core::Entities::e_captain;
	directWidgets = vector<TWidget*>(Graphics::WidgetOptions::size,NULL);
}

GameMenu::~GameMenu() {
	efectVisible = Core::Entities::e_captain;
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
		if (!menus.empty()){
			if (menus[visible] == NULL){
				cerr << "Error: El menu no existe" << endl;
			}else{
				menus[visible]->Draw();
			}
		}
	}
}

TForm * GameMenu::getActive(){
	if (visible != Graphics::Menus::m_none) {
		return menus[visible];
	}else{
		return NULL;
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
void GameMenu::efectoVisible(int efecto)
{
	if(efecto > 0 && efecto <5)
	{
		string ruta;
		efectVisible = (Core::Entities::Type)efecto;
		//cout<<"EFECTO VISIBLE: "<<efectVisible<<endl;
		switch(efectVisible)
		{
		case Core::Entities::e_tecnic:
			ruta = "testFiles/img/tecnic.jpg";
			break;
		case Core::Entities::e_explosive:
			ruta = "testFiles/img/explosive.jpg";
			break;
		case Core::Entities::e_especialist:
			ruta = "testFiles/img/especial.jpg";
			break;
		case Core::Entities::e_captain:
			ruta = "testFiles/img/captain.jpg";
			break;
		default:
			ruta = "testFiles/img/captain.jpg";
			break;
		}
		//((TPicture*)(menus[visible]->getWidgetsAbsoluts()[1]))->setImage(ruta);
		((TPicture*)directWidgets[Graphics::WidgetOptions::imgSelect])->setImage(ruta);
	}

}

void GameMenu::StartUp() {
	GameOptions *op = GameOptions::getInstance();
	int width = op->getWindowWidth();
	int height = op->getWindowHeight();
	string texturesroot = RESOURCESROOT;
	texturesroot += "texturas/";
	string ruta = "testFiles/img/";

	TForm *mInicio = new TForm(width,height,Point(width/2,height/2));
	mInicio->addWidget(new TPicture(Point(), width, height, ruta + "fondo.jpg"));
	mInicio->setColor(Color<float>(0.4,0.4,0.4,0.7));
	TLabel *label = new TLabel(730,150,"Stracomter III");
	label->setMarginUp(40);
	label->setColorText(Color<float>(0.1,0.1,0.4));
	label->setSize(90);
	label->setFontText(Graphics::Font::tf2Build);
	mInicio->addWidget(label);
	label = new TLabel(485,50,"dos puntos espacio el mejor juego de la historia");
	label->setMarginUp(0);
	label->setColorText(Color<float>(0.2,0.2,0.2));
	label->setSize(20);
	mInicio->addWidget(label);
	TButton *button = new TButton(150,50,"Nueva partida");
	button->setWlabel(120);
	button->setColorBorder(Color<float>(0.2,0.2,0.4));
	button->setMarginUp(100);
	button->setEvento(Core::GameMode::Strategy + 100);
	mInicio->addWidget(button);
	button = new TButton(150,50,"Continuar");
	button->setWlabel(85);
	button->setColorBorder(Color<float>(0.2,0.2,0.4));
	button->setMarginUp(50);
	button->setEvento(Core::GameMode::Strategy);
	mInicio->addWidget(button);
	button = new TButton(150,50,"Personalizada");
	button->setWlabel(110);
	button->setColorBorder(Color<float>(0.2,0.2,0.4));
	button->setMarginUp(50);
	button->setEvento(Core::GameMode::Free);
	mInicio->addWidget(button);
	button = new TButton(150,50,"Opciones");
	button->setWlabel(80);
	button->setColorBorder(Color<float>(0.2,0.2,0.4));
	button->setMarginUp(50);
	button->setEvento(Core::GameMode::size + 1);
	mInicio->addWidget(button);
	button = new TButton(150,50,"Salir");
	button->setWlabel(40);
	button->setColorBorder(Color<float>(0.2,0.2,0.4));
	button->setMarginUp(50);
	button->setEvento(0);
	mInicio->addWidget(button);
	button = new TButton(120,50,"Creditos");
	button->setWlabel(70);
	button->setColorBorder(Color<float>(0.2,0.2,0.4));
	button->setEvento(Core::GameMode::Credits);
	mInicio->addWidget(button,Point(720,560));

	//Credits     ###################################################################
	TForm *mCredits = new TForm(width,height,Point(width/2,height/2));
	mCredits->addWidget(new TPicture(Point(), width, height, ruta + "molamos.png"));
	mCredits->setColor(Color<float>(0.4,0.4,0.4,0.7));
	label = new TLabel(300,50,"Stracomter III");
	label->setMarginUp(20);
	label->setFontText(Graphics::Font::tf2Build);
	label->setColorText(Color<float>(0.1,0.1,0.4));
	label->setSize(32);
	mCredits->addWidget(label);
	label = new TLabel(485,40,"dos puntos espacio el mejor juego de la historia");
	label->setMarginUp(0);
	label->setColorText(Color<float>(0.2,0.2,0.2));
	label->setSize(20);
	mCredits->addWidget(label);
	label = new TLabel(630,40,"dos puntos espacio los mejores desarrolladores de la historia");
	label->setMarginUp(0);
	label->setColorText(Color<float>(0.2,0.2,0.2));
	label->setSize(20);
	mCredits->addWidget(label);

	label = new TLabel(210,50,"Created by");
	label->setMarginUp(10);
	label->setColorText(Color<float>(0.1,0.1,0.4));
	label->setSize(30);
	mCredits->addWidget(label);
	label = new TLabel(200,50,"CHUTAOS TEAM");
	label->setMarginUp(18);
	label->setFontText(Graphics::Font::tf2Build);
	label->setColorText(Color<float>(0.1,0.1,0.4));
	mCredits->addWidget(label);
	label = new TLabel(215,30,"Sergio Gallardo Sales");
	label->setMarginUp(10);
	label->setColorText(Color<float>(0.1,0.1,0.1));
	label->setSize(17);
	mCredits->addWidget(label);
	label = new TLabel(245,30,"Martin Candela Calabuig");
	label->setMarginUp(10);
	label->setColorText(Color<float>(0.1,0.1,0.1));
	label->setSize(17);
	mCredits->addWidget(label);
	label = new TLabel(240,30,"Alejando Oñate Latorre");
	label->setMarginUp(10);
	label->setColorText(Color<float>(0.1,0.1,0.1));
	label->setSize(17);
	mCredits->addWidget(label);
	label = new TLabel(195,30,"Ruben Pardo Milla");
	label->setMarginUp(10);
	label->setColorText(Color<float>(0.1,0.1,0.1));
	label->setSize(17);
	mCredits->addWidget(label);

	label = new TLabel(150,50,"Music by");
	label->setMarginUp(20);
	label->setColorText(Color<float>(0.1,0.1,0.4));
	label->setSize(30);
	mCredits->addWidget(label);
	label = new TLabel(200,30,"Adrian Gomez Marin");
	label->setMarginUp(10);
	label->setColorText(Color<float>(0.1,0.1,0.1));
	label->setSize(17);
	mCredits->addWidget(label);
	label = new TLabel(245,30,"Almudena Segovia Calabuig");
	label->setMarginUp(10);
	label->setColorText(Color<float>(0.1,0.1,0.1));
	label->setSize(17);
	mCredits->addWidget(label);

	label = new TLabel(230,50,"Technologies");
	label->setMarginUp(20);
	label->setColorText(Color<float>(0.1,0.1,0.4));
	label->setSize(30);
	mCredits->addWidget(label);
	label = new TLabel(390,30,"SFML: Simple and fast multimedia library");
	label->setMarginUp(10);
	label->setColorText(Color<float>(0.1,0.1,0.1));
	label->setSize(17);
	mCredits->addWidget(label);
	label = new TLabel(200,30,"Wankel Particles");
	label->setMarginUp(10);
	label->setColorText(Color<float>(0.1,0.1,0.1));
	label->setSize(17);
	mCredits->addWidget(label);
	label = new TLabel(280,30,"BOX2D, FTGL, GPC and tinyXML");
	label->setMarginUp(10);
	label->setColorText(Color<float>(0.1,0.1,0.1));
	label->setSize(17);
	mCredits->addWidget(label);
	label = new TLabel(280,30,"g++, gdb, OpenGL and valgrind");
	label->setMarginUp(10);
	label->setColorText(Color<float>(0.1,0.1,0.1));
	label->setSize(17);
	mCredits->addWidget(label);

	label = new TLabel(380,50,"Special acknowledgment");
	label->setMarginUp(20);
	label->setColorText(Color<float>(0.1,0.1,0.4));
	label->setSize(30);
	mCredits->addWidget(label);
	label = new TLabel(300,30,"JohnCor Team and especially Esteve");
	label->setMarginUp(10);
	label->setColorText(Color<float>(0.1,0.1,0.1));
	label->setSize(17);
	mCredits->addWidget(label);
	label = new TLabel(150,30,"ABP Teachers");
	label->setMarginUp(10);
	label->setColorText(Color<float>(0.1,0.1,0.1));
	label->setSize(17);
	mCredits->addWidget(label);

	button = new TButton(120,50,"Atras");
	button->setWlabel(70);
	button->setColorBorder(Color<float>(0.2,0.2,0.4));
	button->setEvento(Core::GameMode::Menu);
	mCredits->addWidget(button,Point(720,560));

	//############################Menu opciones#####################################################
	TForm *mOptions = new TForm(width,height,Point(width/2,height/2));
	mOptions->addWidget(new TPicture(Point(), width, height, ruta + "fondo.jpg"));
	mOptions->setColor(Color<float>(0.4,0.4,0.4,0.7));
	label = new TLabel(730,150,"Opciones");
	label->setMarginUp(50);
	label->setColorText(Color<float>(0.1,0.1,0.4));
	label->setSize(100);
	label->setFontText(Graphics::Font::tf2Build);
	mOptions->addWidget(label);
	label = new TLabel(485,50,"Selecciona tus preferencias de juego");
	label->setMarginUp(0);
	label->setColorText(Color<float>(0.2,0.2,0.2));
	label->setSize(20);
	mOptions->addWidget(label);

	//Music volume//////
	label = new TLabel(80,30,"Musica:");//
	label->setMarginUp(5);
	label->setColorText(Color<float>(0.2,0.2,0.4));
	label->setSize(20);
	label->setMarginLeft(250);
	mOptions->addWidget(label,Point(100,170));

	button = new TButton(20,20,"-");
	button->setWlabel(5);
	button->setColorBorder(Color<float>(0.2,0.2,0.4));
	button->setMarginUp(20);
	button->setEvento(Core::GameMode::size+3);
	mOptions->addWidget(button,Point(100,200));

	label = new TLabel(5,5,"0");//
	label->setMarginUp(10);
	label->setColorText(Color<float>(0.2,0.2,0.4));
	label->setSize(20);
	directWidgets[Graphics::WidgetOptions::labelVolumeMusic] = label;
	mOptions->addWidget(label,Point(125,200));

	button = new TButton(20,20,"+");
	button->setWlabel(10);
	button->setColorBorder(Color<float>(0.2,0.2,0.4));
	button->setMarginUp(20);
	button->setEvento(Core::GameMode::size+2);
	mOptions->addWidget(button,Point(160,200));

	//----------//////
	//Effects volume//////
	label = new TLabel(80,30,"Efectos:");//
	label->setMarginUp(10);
	label->setColorText(Color<float>(0.2,0.2,0.4));
	label->setSize(20);
	mOptions->addWidget(label,Point(100,250));


	button = new TButton(20,20,"-");
	button->setWlabel(5);
	button->setColorBorder(Color<float>(0.2,0.2,0.4));
	button->setMarginUp(20);
	button->setEvento(Core::GameMode::size+5);
	mOptions->addWidget(button,Point(100,280));

	label = new TLabel(5,5,"0");//
	label->setMarginUp(10);
	label->setColorText(Color<float>(0.2,0.2,0.4));
	label->setSize(20);
	directWidgets[Graphics::WidgetOptions::labelVolumeEffects] = label;
	mOptions->addWidget(label,Point(125,280));


	button = new TButton(20,20,"+");
	button->setWlabel(5);
	button->setColorBorder(Color<float>(0.2,0.2,0.4));
	button->setMarginUp(20);
	button->setEvento(Core::GameMode::size+4);
	mOptions->addWidget(button,Point(160,280));
	//----------//////

	button = new TButton(150,50,"Back");
	button->setWlabel(50);
	button->setColorBorder(Color<float>(0.2,0.2,0.4));
	button->setMarginUp(50);
	label->setMarginLeft(0);
	button->setEvento(Core::GameMode::Menu);
	mOptions->addWidget(button,Point(700,500));


	button = new TButton(20,20,"<=");
	button->setWlabel(8);
	button->setColorBorder(Color<float>(0.2,0.2,0.4));
	button->setMarginUp(20);
	button->setEvento(Core::GameMode::size+6);
	mOptions->addWidget(button,Point(60,400));
	label = new TLabel(60,30,"Facil");//
	label->setMarginUp(10);
	label->setColorText(Color<float>(0.2,0.2,0.6));
	label->setSize(20);
	directWidgets[Graphics::WidgetOptions::labelDifficult] = label;
	mOptions->addWidget(label,Point(120,400));
	button = new TButton(20,20,"=>");
	button->setWlabel(8);
	button->setColorBorder(Color<float>(0.2,0.2,0.4));
	button->setMarginUp(20);
	button->setEvento(Core::GameMode::size+7);
	mOptions->addWidget(button,Point(180,400));


	button = new TButton(20,20,"<=");
	button->setWlabel(8);
	button->setColorBorder(Color<float>(0.2,0.2,0.4));
	button->setMarginUp(20);
	button->setEvento(Core::GameMode::size+9);
	mOptions->addWidget(button,Point(60,450));

	label = new TLabel(90,50,"Resolucion");//
	label->setMarginUp(10);
	label->setColorText(Color<float>(0.2,0.2,0.6));
	label->setSize(20);
	directWidgets[Graphics::WidgetOptions::labelResolution] = label;
	mOptions->addWidget(label,Point(120,450));


	button = new TButton(20,20,"=>");
	button->setWlabel(8);
	button->setColorBorder(Color<float>(0.2,0.2,0.4));
	button->setMarginUp(20);
	button->setEvento(Core::GameMode::size+8);
	mOptions->addWidget(button,Point(180,450));




	//SEGUNDA COLUMNA
	TCheckBox *chkBox = new TCheckBox(Point(500,170),"Fullscreen");
	chkBox->setChecked(true);
	chkBox->setEvento(Core::GameMode::size+10);
	directWidgets[Graphics::WidgetOptions::checkBoxFullScreen] = chkBox;
	mOptions->addWidget(chkBox);
	chkBox = new TCheckBox(Point(500,200),"Shaders");
	chkBox->setChecked(true);
	chkBox->setEvento(Core::GameMode::size+11);
	directWidgets[Graphics::WidgetOptions::checkBoxShaders] = chkBox;
	mOptions->addWidget(chkBox);
	chkBox = new TCheckBox(Point(500,230),"Particles");
	chkBox->setChecked(true);
	chkBox->setEvento(Core::GameMode::size+12);
	directWidgets[Graphics::WidgetOptions::checkBoxParticles] = chkBox;
	mOptions->addWidget(chkBox);


	label = new TLabel(40,50,"Reinicie el juego para aplicacar los cambios en resolucion y pantalla completa");//
	label->setMarginUp(10);
	label->setColorText(Color<float>(0.9,0.2,0.4));
	label->setSize(20);
	mOptions->addWidget(label,Point(20,570));

	//############################------------------#####################################################


	TForm *menuPause = new TForm(width,height,Point(width/2,height/2));
	TForm *menuGameOver = new TForm(width,height,Point(width/2,height/2));
	TForm *loadingScreen = new TForm(width,height,Point(width/2,height/2));
	TForm *menuWin = new TForm(width,height,Point(width/2,height/2));
	TForm *menuTheEnd = new TForm(width,height,Point(width/2,height/2));

	menuPause->setColor(Color<float>(0.4,0.4,0.4,0.7));
	label = new TLabel(240,150,"Pause");
	label->setMarginUp(100);
	label->setColorText(Color<float>(0.1,0.1,0.4));
	label->setSize(80);
	label->setFontText(Graphics::Font::tf2Build);
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
	label = new TLabel(650,100,"¡Segmentation Fault!");
	label->setMarginUp(200);
	label->setColorText(Color<float>(0.1,0.1,0.4));
	label->setSize(60);
	label->setFontText(Graphics::Font::tf2Build);
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
	label = new TLabel(610,100,"¡Nivel completado!");
	label->setMarginUp(200);
	label->setColorText(Color<float>(0.1,0.1,0.4));
	label->setSize(60);
	label->setFontText(Graphics::Font::tf2Build);
	menuWin->addWidget(label);
	continuar = new TButton(150,50,"Siguiente nivel");
	continuar->setWlabel(120);
	continuar->setColorBorder(Color<float>(0.2,0.2,0.4));
	continuar->setMarginUp(50);
	continuar->setEvento(Core::GameMode::Strategy);
	menuWin->addWidget(continuar);
	continuar = new TButton(150,50,"Salir");
	continuar->setWlabel(50);
	continuar->setColorBorder(Color<float>(0.2,0.2,0.4));
	continuar->setMarginUp(50);
	continuar->setEvento(1);
	menuWin->addWidget(continuar);

	loadingScreen->setColor(Color<float>(0.3,0.3,0.3));
	label = new TLabel(600,300,"Cargando...");
	label->setMarginUp(250);
	label->setColorText(Color<float>(0.1,0.1,0.4));
	label->setSize(100);
	label->setFontText(Graphics::Font::tf2Build);
	loadingScreen->addWidget(label);

	//MENU FIN DE JUEGO//
	menuTheEnd->addWidget(new TPicture(Point(), width, height, ruta + "fondo.jpg"));
	menuTheEnd->setColor(Color<float>(0.4,0.4,0.4,0.7));
	label = new TLabel(730,150,"¡ENHORABUENA!");
	label->setMarginUp(100);
	label->setColorText(Color<float>(0.1,0.1,0.4));
	label->setSize(90);
	label->setFontText(Graphics::Font::tf2Build);
	menuTheEnd->addWidget(label);
	label = new TLabel(400,50,"Tras derrotar al grupo terrorista,");
	label->setMarginUp(50);
	label->setColorText(Color<float>(0.2,0.2,0.8));
	label->setSize(20);
	menuTheEnd->addWidget(label);
	label = new TLabel(400,50,"el Chutaos Team recupera el control");
	label->setMarginUp(40);
	label->setColorText(Color<float>(0.2,0.2,0.8));
	label->setSize(20);
	menuTheEnd->addWidget(label);
	label = new TLabel(400,50,"de sus instalaciones. Jorobate Flanders.");
	label->setMarginUp(40);
	label->setColorText(Color<float>(0.2,0.2,0.8));
	label->setSize(20);
	menuTheEnd->addWidget(label);

	button = new TButton(120,50,"Creditos");
	button->setWlabel(60);
	button->setColorBorder(Color<float>(0.2,0.2,0.4));
	button->setMarginUp(50);
	label->setMarginLeft(0);
	button->setEvento(40);
	menuTheEnd->addWidget(button,Point(700,500));

	button = new TButton(120,50,"Menu");
	button->setWlabel(40);
	button->setColorBorder(Color<float>(0.2,0.2,0.4));
	button->setMarginUp(50);
	label->setMarginLeft(0);
	button->setEvento(20);
	menuTheEnd->addWidget(button,Point(100,500));

	//VENTANA DE CERRADO

	TForm *closingScreen = new TForm(width,height,Point(width/2,height/2));
	closingScreen->setColor(Color<float>(0.3,0.3,0.3));
	label = new TLabel(600,300,"Cerrando");
	label->setMarginUp(250);
	label->setFontText(Graphics::Font::tf2Build);
	label->setColorText(Color<float>(0.1,0.1,0.4));
	label->setSize(100);
	closingScreen->addWidget(label);

	TForm *mStrategy = new TForm(width,height,Point(width/2,height/2));
	mStrategy->setColor(Color<float>(0.4,0.4,0.5,0.7));
	label = new TLabel(750,20,"Elige un personaje:");
	label->setMarginUp(480);
	label->setMarginLeft(20);
	label->setColorText(Color<float>(0.1,0.1,0.4));
	label->setSize(20);
	mStrategy->addWidget(label);
	button = new TButton(200,45,"Jugar");
	button->setWlabel(50);
	button->setColorBorder(Color<float>(0.2,0.2,0.4));
	button->setMarginUp(20);
	button->setMarginLeft(250);
	button->setEvento(30);
	mStrategy->addWidget(button);
	button = new TButton(200,45,"Menú");
	button->setWlabel(50);
	button->setColorBorder(Color<float>(0.2,0.2,0.4));
	button->setMarginUp(30);
	button->setMarginLeft(0);
	button->setEvento(20);
	mStrategy->addWidget(button);


	TPicture *img_captain = new TPicture(Point(20,500), 90, 90,ruta+"mini-cap.jpg");
	img_captain->setEnable(true);
	img_captain->setEvento(11);
	TPicture *img_tecnic = new TPicture(Point(120,500), 90, 90,ruta+"mini-tec.jpg");
	img_tecnic->setEnable(true);
	img_tecnic->setEvento(12);
	TPicture *img_special = new TPicture(Point(220,500), 90, 90,ruta+"mini-esp.jpg");
	img_special->setEnable(true);
	img_special->setEvento(13);
	TPicture *img_explosive = new TPicture(Point(320,500), 90, 90,ruta+"mini-exp.jpg");
	img_explosive->setEnable(true);
	img_explosive->setEvento(14);


	TPicture *img_selected = new TPicture(Point(75,75), 300, 337,ruta+"captain.jpg");
	img_selected->setEnable(false);

	TPicture *img_recp = new TPicture(Point(580,350), 100, 100,"Graphics/Resources/texturas/none.png");
	img_recp->setEnable(false);

	TRadioButton *rb_zonas = new TRadioButton(3,Point(630,200), mStrategy->getWorld());
	rb_zonas->setMarginUp(20);
	rb_zonas->setMarginLeft(10);
	rb_zonas->setEvento(0);
	rb_zonas->Octogonal();
	directWidgets[Graphics::WidgetOptions::radioZone] = rb_zonas;
	directWidgets[Graphics::WidgetOptions::imgRecomp] = img_recp;
	directWidgets[Graphics::WidgetOptions::imgCap] = img_captain;
	directWidgets[Graphics::WidgetOptions::imgTec] = img_tecnic;
	directWidgets[Graphics::WidgetOptions::imgExp] = img_explosive;
	directWidgets[Graphics::WidgetOptions::imgEsp] = img_special;
	directWidgets[Graphics::WidgetOptions::imgSelect] = img_selected;

	mStrategy->addWidget(new TPicture(Point(), width, height, ruta + "fondo.jpg"));
	mStrategy->addWidget(img_selected);
	mStrategy->addWidget(img_captain);
	mStrategy->addWidget(img_explosive);
	mStrategy->addWidget(img_special);
	mStrategy->addWidget(img_tecnic);
	mStrategy->addWidget(rb_zonas);
	mStrategy->addWidget(img_recp);
	label = new TLabel(200,20,"Recompensa:");;
	label->setColorText(Color<float>(0.1,0.1,0.4));
	label->setSize(20);
	mStrategy->addWidget(label,Point(660,330));
	label = new TLabel(200,20,"Nivel:");;
	label->setColorText(Color<float>(0.1,0.1,0.4));
	label->setSize(20);
	mStrategy->addWidget(label,Point(690,50));
	label = new TLabel(200,20,"0");;
	label->setColorText(Color<float>(0.1,0.1,0.4));
	label->setSize(20);
	directWidgets[Graphics::WidgetOptions::labelNivel]= label;
	mStrategy->addWidget(label,Point(750,50));


	this->addMenu(Graphics::Menus::m_inicio,mInicio);
	this->addMenu(Graphics::Menus::m_options,mOptions);
	this->addMenu(Graphics::Menus::m_loading,loadingScreen);
	this->addMenu(Graphics::Menus::m_pause,menuPause);
	this->addMenu(Graphics::Menus::m_gameover,menuGameOver);
	this->addMenu(Graphics::Menus::m_closing,closingScreen);
	this->addMenu(Graphics::Menus::m_win,menuWin);
	this->addMenu(Graphics::Menus::m_theend,menuTheEnd);
	this->addMenu(Graphics::Menus::m_strategy,mStrategy);
	this->addMenu(Graphics::Menus::m_credits,mCredits);
}



TForm *GameMenu::getMenu(Graphics::Menus::Index index)
{
	if (index != Graphics::Menus::m_none) {
		return this->menus[index];
	}else{
		return NULL;
	}

}

void GameMenu::loadOptionsMenu() {
	GameOptions *op = GameOptions::getInstance();
	char aux[50];

	vector<TWidget*>widg = menus[Graphics::Menus::m_options]->getWidgets();

	sprintf(aux,"%d",(int)op->getMusicVolume());
	((TLabel*)directWidgets[Graphics::WidgetOptions::labelVolumeMusic])->setCaption(aux);
	sprintf(aux,"%d",(int)op->getEffectsVolume());
	((TLabel*)directWidgets[Graphics::WidgetOptions::labelVolumeEffects])->setCaption(aux);
	sprintf(aux,"%d x %d",(int)op->getWindowWidth(),(int)op->getWindowHeight());
	((TLabel*)directWidgets[Graphics::WidgetOptions::labelResolution])->setCaption(aux);
	((TLabel*)directWidgets[Graphics::WidgetOptions::labelDifficult])->setCaption(op->getStringDificult());
	((TCheckBox*)directWidgets[Graphics::WidgetOptions::checkBoxFullScreen])->setChecked(op->isFullScreen());
	((TCheckBox*)directWidgets[Graphics::WidgetOptions::checkBoxShaders])->setChecked(op->isUseShaders());
	((TCheckBox*)directWidgets[Graphics::WidgetOptions::checkBoxParticles])->setChecked(op->isParticlesOn());
}

vector<TForm*> GameMenu::getMenus() const
{
	return menus;
}

void GameMenu::setMenus(vector<TForm*> menus)
{
	this->menus = menus;
}

void GameMenu::loadStrategyStatus(){
	GameStatus *gs = GameStatus::getInstance();
	int planta = (int)gs->getNivelPlanta();
	if(planta < 9)
	{
		char aux[50];
		sprintf(aux,"%d",planta);
		if(planta != -1)
		{
			((TLabel*)directWidgets[Graphics::WidgetOptions::labelNivel])->setCaption(aux);
		}
		else
		{
			((TLabel*)directWidgets[Graphics::WidgetOptions::labelNivel])->setCaption("editorMap.xml");
		}

		if(planta == 8 || planta == -1)
			((TRadioButton*)directWidgets[Graphics::WidgetOptions::radioZone])->Octogonal(8,0,0);
		else
			((TRadioButton*)directWidgets[Graphics::WidgetOptions::radioZone])->Octogonal();
		efectoVisible(gs->getTypePlayer());
		if(!gs->isVivitoYColeando(Core::Entities::e_captain))
		{
			((TPicture*)directWidgets[Graphics::WidgetOptions::imgCap])->setEnable(false);
			((TPicture*)directWidgets[Graphics::WidgetOptions::imgCap])->setColor(Color<float>(0.5,0.5,0.5,0.5));
		}else
		{
			((TPicture*)directWidgets[Graphics::WidgetOptions::imgCap])->setEnable(true);
			((TPicture*)directWidgets[Graphics::WidgetOptions::imgCap])->setColor(Color<float>(1,1,1,1));
		}
		if(!gs->isVivitoYColeando(Core::Entities::e_tecnic))
		{
			((TPicture*)directWidgets[Graphics::WidgetOptions::imgTec])->setEnable(false);
			((TPicture*)directWidgets[Graphics::WidgetOptions::imgTec])->setColor(Color<float>(0.5,0.5,0.5,0.5));
		}else
		{
			((TPicture*)directWidgets[Graphics::WidgetOptions::imgTec])->setEnable(true);
			((TPicture*)directWidgets[Graphics::WidgetOptions::imgTec])->setColor(Color<float>(1,1,1,1));
		}
		if(!gs->isVivitoYColeando(Core::Entities::e_explosive))
		{
			((TPicture*)directWidgets[Graphics::WidgetOptions::imgExp])->setEnable(false);
			((TPicture*)directWidgets[Graphics::WidgetOptions::imgExp])->setColor(Color<float>(0.5,0.5,0.5,0.5));
		}else
		{
			((TPicture*)directWidgets[Graphics::WidgetOptions::imgExp])->setEnable(true);
			((TPicture*)directWidgets[Graphics::WidgetOptions::imgExp])->setColor(Color<float>(1,1,1,1));
		}
		if(!gs->isVivitoYColeando(Core::Entities::e_especialist))
		{
			((TPicture*)directWidgets[Graphics::WidgetOptions::imgEsp])->setEnable(false);
			((TPicture*)directWidgets[Graphics::WidgetOptions::imgEsp])->setColor(Color<float>(0.5,0.5,0.5,0.5));
		}else
		{
			((TPicture*)directWidgets[Graphics::WidgetOptions::imgEsp])->setEnable(true);
			((TPicture*)directWidgets[Graphics::WidgetOptions::imgEsp])->setColor(Color<float>(1,1,1,1));
		}
	}else
	{
		visible = Graphics::Menus::m_theend;
	}
}




void GameMenu::cambiaRecompensa(int aux)
{

	string ruta = "Graphics/Resources/texturas/";
	switch(aux)
	{
	case 1:
		((TPicture*)directWidgets[Graphics::WidgetOptions::imgRecomp])->setImage(ruta + "ammo20.png");
		break;
	case 2:
		((TPicture*)directWidgets[Graphics::WidgetOptions::imgRecomp])->setImage(ruta + "vida20.png");
		break;
	case 3:
		((TPicture*)directWidgets[Graphics::WidgetOptions::imgRecomp])->setImage(ruta + "ammo50.png");
		break;
	case 4:
		((TPicture*)directWidgets[Graphics::WidgetOptions::imgRecomp])->setImage(ruta + "vida50.png");
		break;
	case 5:
		((TPicture*)directWidgets[Graphics::WidgetOptions::imgRecomp])->setImage(ruta + "ammo100.png");
		break;
	case 6:
		((TPicture*)directWidgets[Graphics::WidgetOptions::imgRecomp])->setImage(ruta + "vida100.png");
		break;
	case 8:
		((TPicture*)directWidgets[Graphics::WidgetOptions::imgRecomp])->setImage(ruta + "win.png");
		break;
	default:
		((TPicture*)directWidgets[Graphics::WidgetOptions::imgRecomp])->setImage(ruta + "none.png");
		break;
	}
}




