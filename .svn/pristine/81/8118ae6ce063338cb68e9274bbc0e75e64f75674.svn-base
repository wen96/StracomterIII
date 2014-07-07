/*
 * Clock.cc
 *
 *  Created on: Mar 17, 2012
 *      Author: rellik
 */

#include "PausableClock.h"

PausableClock::PausableClock() {
	paused = true;
	elapsedTime = 0;
}

PausableClock::~PausableClock() {
	paused = true;
	elapsedTime = 0;
}

void PausableClock::Start() {
	elapsedTime = 0;
	paused = false;
	reloj.Reset();
}

void PausableClock::Reset(bool paused_) {
	reloj.Reset();
	elapsedTime = 0;
	paused = paused_;
}

void PausableClock::Stop() {
	paused = true;
	elapsedTime = 0;
}

void PausableClock::Pause() {
	if(!paused){
		paused = true;
		elapsedTime += reloj.GetElapsedTime();
	}
}

void PausableClock::Unpause(){
	if(paused){
		paused = false;
		reloj.Reset();
	}
}

int PausableClock::getElapsedMiliseconds() {
	return elapsedTime + reloj.GetElapsedTime();
}

int PausableClock::getElapsedSeconds() {
	if(paused)
		return elapsedTime / 1000;
	else
		return (elapsedTime + reloj.GetElapsedTime())/1000;
}

string PausableClock::toString() {
	int time = getElapsedSeconds();
	int min = time / 60;
	int sec = time % 60;

	char sMin[2], sSec[2];
	string sTime;

	if(min < 10)
		sprintf(sMin, "0%d", min);
	else
		sprintf(sMin, "%d", min);

	if(sec < 10)
		sprintf(sSec, "0%d", sec);
	else
		sprintf(sSec, "%d", sec);

	sTime = sMin;
	sTime += ":";
	sTime += sSec;

	return sTime;
}

