/*
 * Clock.h
 *
 *  Created on: Mar 17, 2012
 *      Author: rellik
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include <iostream>
using namespace std;
#include <string>
#include <SFML/System.hpp>
#include <cstdio>

class PausableClock{
public:
	PausableClock();
	~PausableClock();

	void Start();
	void Reset(bool paused=false);
	void Stop();
	void Pause();
	void Unpause();
	int getElapsedMiliseconds();
	int getElapsedSeconds();
	string toString();

private:
	sf::Clock reloj;
	bool paused;
	int elapsedTime;
};


#endif /* CLOCK_H_ */
