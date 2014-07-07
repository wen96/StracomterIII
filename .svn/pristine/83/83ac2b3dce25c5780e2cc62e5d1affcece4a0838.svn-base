/*
 * Musica.cc
 *
 *  Created on: 01/04/2012
 *      Author: Chutaos Team
 */

#include "TMusic.h"

TMusic::TMusic() {
	music.SetVolume(100);
	music.SetLoop(false);
}

TMusic::TMusic(bool bucle) {
	music.SetVolume(100);
	music.SetLoop(bucle);
}

TMusic::~TMusic() {
}

bool TMusic::OpenFile(string ruta)
{
	return music.OpenFromFile(ruta);
}

void TMusic::setVolume(float volumen)
{
	music.SetVolume(volumen);
}

void TMusic::setLoop(bool bucle)
{
	music.SetLoop(bucle);
}

void TMusic::Play()
{
	music.Play();
}

void TMusic::Pause()
{
	music.Pause();
}

void TMusic::Stop()
{
	music.Stop();
}


Audio::Music::Status TMusic::GetStatus()
{
	switch(music.GetStatus())
	{
	case sf::Music::Playing:
		return Audio::Music::s_playing;
	case sf::Music::Paused:
		return Audio::Music::s_paused;
	case sf::Music::Stopped:
		return Audio::Music::s_stopped;
	default:
		return Audio::Music::s_stopped;
	}

}
