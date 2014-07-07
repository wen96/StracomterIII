/*
 * TSound.cc
 *
 *  Created on: 10/04/2012
 *      Author: Chutaos Team
 */

#include "TSound.h"

TSound::TSound() {
	sound.SetVolume(100);
	sound.SetAttenuation(20);
	sound.SetMinDistance(300);
}
TSound::TSound(TSoundBuffer *buf) {
	sound.SetVolume(100);
	sound.SetAttenuation(20);
	sound.SetMinDistance(300);
	sound.SetBuffer(*buf->getBuffer());
}

TSound::TSound(const TSound &s){
	sound = s.sound;
}
TSound & TSound::operator=(const TSound &p){
	if (this != &p){
		sound = p.sound;
	}
	return *this;
}

void TSound::setBuffer(TSoundBuffer buf){
	sound.SetBuffer(*buf.getBuffer());
}

TSound::~TSound() {
	sound.SetVolume(0);
}

void TSound::setVolume(float vol) {
	sound.SetVolume(vol);
}

float TSound::getVolume() {
	return sound.GetVolume();
}

void TSound::setPosition(Point p) {
	sound.SetPosition(p.getX(),p.getY(),p.getZ());
}

Point TSound::getPosition() {
	Point p;
	p.setX(sound.GetPosition().x);
	p.setY(sound.GetPosition().y);
	p.setZ(sound.GetPosition().z);
	return p;
}

void TSound::setAttenuation(float ate) {
	sound.SetAttenuation(ate);
}

float TSound::getAttenuation() {
	return sound.GetAttenuation();
}

void TSound::setRelativeToListener(bool rel) {
	sound.SetRelativeToListener(rel);
}

bool TSound::isRelativeToListener() {
	return sound.IsRelativeToListener();
}

void TSound::setLoop(bool l) {
	sound.SetLoop(l);
}

bool TSound::isLoop() {
	return sound.GetLoop();
}

void TSound::setMinDistance(float dist) {
	sound.SetMinDistance(dist);
}

float TSound::getMinDistance() {
	return sound.GetMinDistance();
}


void TSound::Play()
{
	sound.Play();
}

void TSound::Pause()
{
	sound.Pause();
}

void TSound::Stop()
{
	sound.Stop();
}

Audio::Sound::Status TSound::getStatus() {
	switch(sound.GetStatus())
	{
	case sf::Sound::Playing:
		return Audio::Sound::s_playing;
	case sf::Sound::Paused:
		return Audio::Sound::s_paused;
	case sf::Sound::Stopped:
		cout << "Stoped" << endl;
		return Audio::Sound::s_stopped;
	default:
		cout << "asjdñlfkj" << endl;
		return Audio::Sound::s_stopped;
	}
}



