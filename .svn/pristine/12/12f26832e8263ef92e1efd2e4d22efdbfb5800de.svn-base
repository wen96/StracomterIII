/*
 * AudioControl.cc
 *
 *  Created on: 10/04/2012
 *      Author: Chutaos Team
 */

#include "AudioControl.h"

AudioControl * AudioControl::_app = NULL;

AudioControl * AudioControl::getInstance(){
	if (_app == NULL){
		_app = new AudioControl();
	}
	return _app;
}

void AudioControl::playMusic()
{
	music->Play();
}

void AudioControl::pauseMusic()
{
	music->Pause();
}

void AudioControl::stopMusic()
{
	music->Stop();
}

void AudioControl::loadData(){
	GameOptions *op = GameOptions::getInstance();
	music->setVolume(op->getMusicVolume());
	effectsVolume = op->getEffectsVolume();
}

AudioControl::AudioControl() {
	music = new TMusic();
	music->setLoop(true);

	effectsVolume = 100;
	iter_sounds=0;
	iter_steps = 0;
	ifstream f("testFiles/sound/joke.txt",ios::in);
	string soundPath ="testFiles/sound/personal/";
	if (f){
		soundPath ="testFiles/sound/joke/";
		f.close();
	}

	/**
	 * Igual esto deberia estar en ResourceManager
	 */
	buffers.push_back(new TSoundBuffer(soundPath+"pistol.ogg"));
	buffers.push_back(new TSoundBuffer(soundPath+"explosion.ogg"));
	buffers.push_back(new TSoundBuffer(soundPath+"machine.ogg"));
	buffers.push_back(new TSoundBuffer(soundPath+"knife.ogg"));
	buffers.push_back(new TSoundBuffer(soundPath+"step.ogg"));
	buffers.push_back(new TSoundBuffer(soundPath+"dead.ogg"));
	buffers.push_back(new TSoundBuffer(soundPath+"ouch.ogg"));
	TListener::setPosition(Point());

}

void AudioControl::playSound(string fich){
	TSoundBuffer *sb = new TSoundBuffer(fich);
	TSound *s = new TSound(sb);
	s->Play();
	s->setLoop(true);
	while(s->getStatus() != Audio::Sound::s_stopped){}
	delete sb;
	delete s;
}

void AudioControl::playSound(Audio::Sound::Effect ef){
	sounds[iter_sounds].Stop();
	sounds[iter_sounds] = TSound(buffers[ef]);
	sounds[iter_sounds].setRelativeToListener(true);
	sounds[iter_sounds].setVolume(effectsVolume);
	if(ef==Audio::Sound::e_explosion)
	{
		sounds[iter_sounds].setAttenuation(5);
		sounds[iter_sounds].setMinDistance(600);
	}
	sounds[iter_sounds].Play();
	iter_sounds++;
	if(iter_sounds >= Audio::MAX_SOUNDS)
		iter_sounds=0;
}

void AudioControl::playSound(Audio::Sound::Effect ef, Point pos){
	sounds[iter_sounds].Stop();
	sounds[iter_sounds] = TSound(buffers[ef]);
	sounds[iter_sounds].setRelativeToListener(false);
	sounds[iter_sounds].setPosition(pos);
	sounds[iter_sounds].setVolume(effectsVolume);
	if(ef==Audio::Sound::e_explosion)
	{
		sounds[iter_sounds].setAttenuation(5);
		sounds[iter_sounds].setMinDistance(600);
	}
	sounds[iter_sounds].Play();
	iter_sounds++;
	if(iter_sounds >= Audio::MAX_SOUNDS)
		iter_sounds=0;
}

void AudioControl::playSoundStep(Point pos){
	steps[iter_steps].Stop();
	steps[iter_steps] = TSound(buffers[Audio::Sound::e_step]);
	steps[iter_steps].setRelativeToListener(false);
	steps[iter_steps].setPosition(pos);
	steps[iter_steps].setMinDistance(500);
	steps[iter_steps].setAttenuation(50000);
	steps[iter_steps].setVolume(effectsVolume);
	steps[iter_steps].Play();
	iter_steps++;
	if(iter_steps >= Audio::MAX_SOUNDS_STEPS)
		iter_steps=0;
}

AudioControl::~AudioControl() {
	if (music != NULL){
		delete music;
	}
	music = NULL;

	vector<TSoundBuffer*>::iterator iter;
	while (!buffers.empty()){
		TSoundBuffer*aux = buffers.front();
		buffers.erase(buffers.begin());
		delete aux;
	}
	buffers.clear();
}

void AudioControl::switchSong(Audio::Music::Song song){
	string ruta = "";
	switch(song){
	case Audio::Music::s_menu:
		ruta = "testFiles/sound/LegendsOfLiberty.ogg";
		break;
	case Audio::Music::s_action:
		ruta = "testFiles/sound/andorga.ogg";
		break;
	case Audio::Music::s_credits:
		ruta = "testFiles/sound/credits.ogg";
		break;
	default:
		cerr << "Error: Song not linked" << endl;
		break;
	}
	music->Stop();
	if (!music->OpenFile(ruta)){
		cerr << "Error: No se ha podido cargar la cacion" << endl;
	}else{
		music->Play();
	}
}
