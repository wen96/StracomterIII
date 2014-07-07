/*
 * GameOptions.cc
 *
 *  Created on: 17/04/2012
 *      Author: Chutaos team
 */

#include "GameOptions.h"

GameOptions * GameOptions::_app = NULL;

GameOptions *GameOptions::getInstance() {
	if (_app == NULL) {
		_app = new GameOptions();
	}
	return _app;
}

void GameOptions::upMusicVolume() {
	if (musicVolume < 100) {
		musicVolume+=5;
	}
}

void GameOptions::downMusicVolume() {
	if (musicVolume > 0) {
		musicVolume-=5;
	}
}

void GameOptions::upEffectsVolume() {
	if (effectsVolume < 100) {
		effectsVolume+=5;
	}
}

void GameOptions::downEffectsVolume() {
	if (effectsVolume > 0) {
		effectsVolume-=5;
	}
}

void GameOptions::upDificult() {
	if (dificultad == 1.0f){
		dificultad = 1.3f;
	}else if (dificultad == 1.3f){
		dificultad = 1.5f;
	}
}

void GameOptions::downDificult() {
	if (dificultad == 1.5f){
		dificultad = 1.3f;
	}else if (dificultad == 1.3f){
		dificultad = 1.0f;
	}
}

string GameOptions::getStringDificult(){
	if (dificultad == 1.0f){
		return "Fácil";
	}else if (dificultad == 1.3f){
		return "Normal";
	}else if (dificultad == 1.5f){
		return "Difícil";
	}else{
		return "No definida";
	}
	return "Error";
}

bool GameOptions::loadData(string fich) {
	bool abierto = false;
	ifstream file;
	file.open(fich.c_str(),ios::in);
	if (file.is_open()){
		abierto = true;
		string line;
		getline(file, line);
		while (!file.eof()) {
			string prop, value;
			if (parseString(line,prop,value)){
				setProperty(prop,value);
			}
			getline(file, line);
		}
		file.close();
	}
	return abierto;
}

void GameOptions::switchFullScreen()
{
	fullScreen = !fullScreen;
}

void GameOptions::switchShaders()
{
	useShaders = !useShaders;
}

void GameOptions::upResolution()
{
	if (windowWidth < 1024 && windowHeight < 768){
		windowWidth = 1024;
		windowHeight = 768;
	}
}

void GameOptions::downResolution()
{
	if (windowWidth > 800 && windowHeight > 600){
		windowWidth = 800;
		windowHeight = 600;
	}
}

bool GameOptions::setProperty(string property, string value){
	bool aply = true;

	if (property == "music"){
		this->setMusicVolume(atof(value.c_str()));
	}else if (property == "effects"){
		this->setEffectsVolume(atof(value.c_str()));
	}else if (property == "width"){
		this->setWindowWidth(atoi(value.c_str()));
	}else if (property == "height"){
		this->setWindowHeight(atoi(value.c_str()));
	}else if (property == "full"){
		this->setFullScreen((bool)atoi(value.c_str()));
	}else if (property == "shader"){
		this->setUseShaders((bool)atoi(value.c_str()));
	}else if (property == "difficult"){
		this->setDificultad(atof(value.c_str()));
	}else if (property == "particles"){
		this->setParticles((bool)atoi(value.c_str()));
	}else{
		aply = false;
	}

	return aply;
}

bool GameOptions::parseString(string ori, string &property, string &value){
	bool correct = false;
	string aux = "";
	for (unsigned int i = 0; i < ori.length(); i++){
		if (ori[i] == ':'){
			property = aux;
			correct = true;
			aux = "";
		}else{
			aux += ori[i];
		}
	}
	value = aux;

	return correct;
}

void GameOptions::saveData(string fich) {
	ofstream file;
	file.open(fich.c_str(),ios::out);
	if (file.is_open()){
		file << "music:" << musicVolume << endl;
		file << "effects:" << effectsVolume << endl;
		file << "width:" << windowWidth << endl;
		file << "height:" << windowHeight << endl;
		file << "full:" << fullScreen << endl;
		file << "shader:" << useShaders << endl;
		file << "difficult:" << dificultad << endl;
		file << "particles:" << useParticles << endl;
		file.close();
	}
}

GameOptions::GameOptions() {
	musicVolume = 100;
	effectsVolume = 100;
	windowWidth = 800;
	windowHeight = 600;
	fullScreen = false;
	useShaders = false;
	dificultad = 1;
	useParticles = true;
}

GameOptions::~GameOptions() {
	musicVolume = 0;
	effectsVolume = 0;
	windowWidth = 800;
	windowHeight = 600;
	fullScreen = false;
	useShaders = false;
	dificultad = 1;
}

float GameOptions::getEffectsVolume() const {
	return effectsVolume;
}

float GameOptions::getMusicVolume() const {
	return musicVolume;
}

void GameOptions::setEffectsVolume(float effectsVolume) {
	if (effectsVolume > 100){
		this->effectsVolume = 100;
	}else if (effectsVolume < 0){
		this->effectsVolume = 0;
	}else {
		this->effectsVolume = effectsVolume;
	}
}

void GameOptions::setMusicVolume(float musicVolume) {
	if (musicVolume > 100){
		this->musicVolume = 100;
	}else if (musicVolume < 0){
		this->musicVolume = 0;
	}else {
		this->musicVolume = musicVolume;
	}
}

float GameOptions::getDificultad() const {
	return dificultad;
}

int GameOptions::getWindowWidth() const {
	return windowWidth;
}

bool GameOptions::isFullScreen() const {
	return fullScreen;
}

bool GameOptions::isUseShaders() const {
	return useShaders;
}

void GameOptions::setDificultad(float dificultad) {
	if (dificultad == 1.0f || dificultad == 1.3f || dificultad == 1.5f){
		this->dificultad = dificultad;
	}else{
		this->dificultad = 1.0f;
	}

}

void GameOptions::setFullScreen(bool fullScreen) {
	this->fullScreen = fullScreen;
}

void GameOptions::setUseShaders(bool useShaders) {
	this->useShaders = useShaders;
}

void GameOptions::setWindowWidth(int windowWidth) {
	this->windowWidth = windowWidth;
}

int GameOptions::getWindowHeight() const {
	return windowHeight;
}

void GameOptions::setWindowHeight(int windowHeight) {
	this->windowHeight = windowHeight;
}

void GameOptions::setResolution(int width, int height) {
	this->windowWidth = width;
	this->windowHeight = height;
}

bool GameOptions::isParticlesOn(){
	return useParticles;
}

void GameOptions::setParticles(bool on){
	useParticles = on;
}

void GameOptions::switchParticles(){
	useParticles = !useParticles;
}
