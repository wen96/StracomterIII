/*
 * TSoundBuffer.cc
 *
 *  Created on: 10/04/2012
 *      Author: Chutaos Team
 */

#include "TSoundBuffer.h"

TSoundBuffer::TSoundBuffer() {
	Buffer = new sf::SoundBuffer();

}
TSoundBuffer::TSoundBuffer(string ruta) {
	Buffer = new sf::SoundBuffer();
	Buffer->LoadFromFile(ruta);
}

TSoundBuffer::TSoundBuffer(const TSoundBuffer &buf){
	Buffer = new sf::SoundBuffer(*buf.Buffer);
}

TSoundBuffer::~TSoundBuffer() {
	if (Buffer != NULL){
		delete Buffer;
	}
	Buffer = NULL;
}

bool TSoundBuffer::LoadFile(string ruta)
{
	return Buffer->LoadFromFile(ruta);
}

TSoundBuffer & TSoundBuffer::operator=(const TSoundBuffer &p){
	if (this != &p){
		Buffer = new sf::SoundBuffer(*p.Buffer);
	}
	return *this;
}

sf::SoundBuffer* TSoundBuffer::getBuffer() const
{
    return Buffer;
}

void TSoundBuffer::setBuffer(sf::SoundBuffer *buffer)
{
    Buffer = buffer;
}





