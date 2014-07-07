/*
 * Clock.cc
 *
 *  Created on: Mar 17, 2012
 *      Author: rellik
 */

#include "Clock.h"
#include <sstream>

Clock::Clock() {
	paused = true;
	elapsedTime = 0;
}

Clock::Clock(bool paused_) {
	paused = paused_;
	elapsedTime = 0;
	reloj.Reset();
}

Clock::~Clock() {
	paused = true;
	elapsedTime = 0;
}

Clock::Clock(const Clock &pc){

	paused = pc.paused;
	elapsedTime = pc.elapsedTime;
	reloj = pc.reloj;
}

Clock & Clock::operator=(const Clock &pc){
	if(this != &pc){
		paused = pc.paused;
		elapsedTime = pc.elapsedTime;
		reloj = pc.reloj;
	}
	return *this;
}

void Clock::Start() {
	elapsedTime = 0;
	paused = false;
	reloj.Reset();
}

void Clock::Reset(bool paused_) {
	reloj.Reset();
	elapsedTime = 0;
	paused = paused_;
}

void Clock::Stop() {
	paused = true;
	elapsedTime = 0;
}

void Clock::Pause() {
	if(!paused){
		paused = true;
		elapsedTime += reloj.GetElapsedTime();
	}
}

void Clock::Unpause(){
	if(paused){
		paused = false;
		reloj.Reset();
	}
}

int Clock::getElapsedMiliseconds() {
	return elapsedTime + reloj.GetElapsedTime();
}

int Clock::getElapsedSeconds() {
	if(paused)
		return elapsedTime / 1000;
	else
		return (elapsedTime + reloj.GetElapsedTime())/1000;
}

string Clock::toString() {
	int time = getElapsedSeconds();
	int min = time / 60;
	int sec = time % 60;

	string sTime;

	stringstream ss;

	if(min < 10){
		ss << "0";
	}

	ss << min << ":";

	if (sec < 10)
		ss << "0";

	ss << sec;

	sTime = ss.str();

	return sTime;
}

bool Clock::isPaused(){
	return paused;
}
