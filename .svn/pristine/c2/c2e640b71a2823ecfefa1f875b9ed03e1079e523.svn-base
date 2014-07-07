#include <iostream>
#include "TWindow.h"
#include "Camera.h"
#include "TForm.h"
#include "IOControl.h"
#include "SoundNamespace.h"
#include "TListener.h"
#include "TSound.h"
#include "TSoundBuffer.h"
#include "TMusic.h"
#include <SFML/Audio.hpp>

using namespace std;

const int HEIGHT = 600;
const int WIDTH = 800;

void PlaySound(TSound Sound);

int main(int argc, char * argv[]){
	TWindow *window = new TWindow();
	window->openSFML(WIDTH,HEIGHT,false);
	window->setFrameLimit(60);
	IOControl *eventosTeclado = new IOControl(window);
	ResourceManager *res = ResourceManager::getInstance();


	Camera c_panel;
	c_panel= Camera(WIDTH,HEIGHT,-1,1);
	c_panel.setOrtho();
	c_panel.setScale(400);

	TForm *form = new TForm(800, 600, Point(400,300));
	form->setColor(Color<float>(0.6,0.8,0.7));
	TLabel *label = new TLabel(400,80,"PRUEBA DE AUDIO");
	label->setMarginUp(10);
	label->setColorText(Color<float>(0.1,0.1,0.4));
	label->setSize(50);
	form->addWidget(label);
	form->addWidget(new TLabel(150,30,"Arriba abajo, volumen"));
	TLabel *volumLabel = new TLabel(100,100,"100");
	volumLabel->setMarginUp(10);
	volumLabel->setColorText(Color<float>(0.1,0.1,0.4));
	volumLabel->setSize(50);
	form->addWidget(volumLabel);
	TButton *b = new TButton("PLAY");
	b->setMarginUp(10);
	b->setMarginLeft(10);
	b->setEvento(1);
	form->addWidget(b);
	form->addWidget(new TLabel(150,30,"Spacio para sonido"));
	TButton *pum = new TButton("PUM");
	pum->setMarginUp(10);
	pum->setMarginLeft(10);
	pum->setEvento(2);
	form->addWidget(pum);
	form->addWidget(new TLabel(700,30,"Clicks para cambiar posicion sonido (blanco) y escuchante(rojo)"));

	Point radio(400,300);
	Point player(400,300);
	Point mouse;
	float volumen = 100;

	string cancion = "testFiles/sound/acdc.ogg";
	if (argc >= 2){
		cancion = argv[1];
	}

	TMusic music;
	if (!music.OpenFile(cancion))
	         return EXIT_FAILURE;

	string sonido = "testFiles/sound/go.ogg";
	if (argc >= 3){
		sonido = argv[2];
	}
	TSoundBuffer *Buffer = new TSoundBuffer();
	    if (!Buffer->LoadFile(sonido))
	        return EXIT_SUCCESS;
	TSound sound(Buffer);
	sound.Play();
	while (sound.getStatus() == Audio::Sound::s_playing){}


	sound.setPosition(radio);
	sound.setAttenuation(0.5);
	sound.setMinDistance(50);

	TListener::setPosition(player);
	TListener::setVolumen(volumen);

	 music.setLoop(true);
	 music.setVolume(volumen);




	while(window->isOpen()){
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		bool bang = false;

		mouse.setXY(eventosTeclado->GetMouseX(),eventosTeclado->GetMouseY());

		TWidget *clickEvent = form->whoIsClicked(mouse);
		sf::Event event;
		while (window->getEvent(event)){
			//Eventos de control
			if (event.Type == sf::Event::Closed) { //control de cerrado de ventana
				window->close();
			} else if (event.Type == sf::Event::KeyPressed) {

				if (event.Key.Code == sf::Keyboard::Escape) { //control de cerrado de ventana
					window->close();
				}else if (event.Key.Code == sf::Keyboard::Up) {
					if (volumen < 100){
						volumen+=5;
						char aux[50];
						sprintf(aux, "%f", volumen);
						string tmp = aux;
						volumLabel->setCaption(tmp);
					}
				}else if (event.Key.Code == sf::Keyboard::Down) {
					if (volumen > 0){
						volumen-=5;
						char aux[50];
						sprintf(aux, "%f", volumen);
						string tmp = aux;
						volumLabel->setCaption(tmp);
					}
				}else if (event.Key.Code == sf::Keyboard::P) {
					sound.Play();
				}
			}else if (event.Type == sf::Event::MouseButtonPressed){
				if (event.MouseButton.Button == sf::Mouse::Left){
					if (clickEvent != NULL){
						if (clickEvent->getEvento()==1){
							if (music.GetStatus() == Audio::Music::s_paused || music.GetStatus() == Audio::Music::s_stopped){
								b->setCaption("PAUSE");
								music.Play();
							}else{
								b->setCaption("PLAY");
								music.Pause();
							}
						}
					}else{
						radio = mouse;

					}
				}else if (event.MouseButton.Button == sf::Mouse::Right){
					player = mouse;
				}
			}


		}
		if (eventosTeclado->IsKeyDown(Core::Key::Space)){
			PlaySound(sound);
			bang = true;
		}
		if (eventosTeclado->isMouseButtonDown(Core::Mouse::Left)){
			if (clickEvent != NULL){
				if (clickEvent->getEvento()==2){
					PlaySound(sound);
					bang = true;
				}
			}
		}

		c_panel.exportOpenGL();
		glScalef(1, -1, 1);
		glTranslatef(-1.0 * WIDTH/2, -1.0 * HEIGHT/2, 0.0);


		form->Draw();
		if (bang){
			DrawSolidCircle(radio,30,Color<float>(1,1,0));
		}else{
			DrawSolidCircle(radio,30,Color<float>());
		}

		DrawSolidCircle(player,10,Color<float>(1,0,0));


		sound.setPosition(radio);
		TListener::setPosition(player);
		music.setVolume(volumen);

		window->display();
	}

	delete window;
	delete Buffer;
	return 0;
}

void PlaySound(TSound Sound)
{

    // Start the sound
    Sound.Play();
    cout << "Primera" << Sound.getStatus() << endl;

    // Loop while the sound is playing
    while (Sound.getStatus() == Audio::Sound::s_playing)
    {
    	cout << Sound.getStatus() << endl;
        // Leave some CPU time for other processes
        //sf::Sleep(0.1f);
    }
}


