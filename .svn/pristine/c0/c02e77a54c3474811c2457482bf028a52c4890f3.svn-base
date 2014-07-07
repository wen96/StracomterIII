/*
 * TConsole.cc
 *
 *  Created on: Feb 7, 2012
 *      Author: Chutaos Team
 */

#include "TConsole.h"

TConsole::TConsole(int visibleLines, IOControl *io) {
	maxLines = visibleLines;
	ioCont = io;
	escena = NULL;
	open = false;
	currLine = "";
	prevLineIndex = 0;
	cursorPos = 0;

	vector<Point> caja;
	int y = (maxLines + 1) * 16;
	caja.push_back(Point(0,0));
	caja.push_back(Point(800,0));
	caja.push_back(Point(800,y));
	caja.push_back(Point(0,y));

	Polygon pol(caja);
	pol.setType(0);
	shBox = new Shape(pol, Color<float>(0.4,0.4,0.4,0.8),true);
}

TConsole::~TConsole() {

	textManager.clear();

	maxLines = 0;
	ioCont = NULL;
	escena = NULL;
	open = false;
	currLine = "";
	prevLineIndex = 0;

	delete shBox;
	shBox = NULL;
	vector<Text *>::iterator tIter;
	for(tIter = textManager.begin(); tIter != textManager.end(); tIter++){
		delete *tIter;
	}
	textManager.clear();

}

void TConsole::Init(){
	sManager = SceneManager::getInstance();

	treeBranch = sManager->getNode(Graphics::DirectNodes::t_console);

	if(treeBranch != NULL){

		if(!textManager.empty()){
			sManager->addElement(shBox, treeBranch);
			vector<Text *>::iterator tIter;
			for(tIter = textManager.begin(); tIter != textManager.end(); tIter++){
				sManager->addElement(*tIter,treeBranch);
			}
		}else{

			treeBranch->setVisible(false);
			sManager->addElement(shBox, treeBranch);

			int y = maxLines * 16;

			Text *texto = new Text(Graphics::Font::Monospace, Point(20,y), Color<float>(1,1,1,1), 14, "> |");
			sManager->addElement(texto,treeBranch);
			textManager.push_back(texto);

			for(unsigned int i = 0; i < maxLines * 2; i++){
				y -= 16;
				texto = new Text(Graphics::Font::Monospace, Point(20,y), Color<float>(1,1,1,1), 12, "");
				sManager->addElement(texto,treeBranch);
				textManager.push_back(texto);
			}
		}
	}
}

void TConsole::setScene(Scene *scene){
	escena = scene;
}

string TConsole::getCurrLine() {
	return currLine;
}

vector<string> TConsole::getPrevLines(){
	return prevLines;
}

bool TConsole::getStatus(){
	return open;
}

void TConsole::Open(){
	open = true;
	treeBranch->setVisible(true);
}

void TConsole::Close(){
	open = false;
	treeBranch->setVisible(false);
}

int TConsole::getInput() {

	int status = 2;
	sf::Event event;
	while(ioCont->window->getEvent(event)){
		if (event.Type == sf::Event::Closed){
			status = 1;
		}

		if(event.Type == sf::Event::KeyPressed){
			if(event.Key.Code == sf::Keyboard::Up){		// Pulsamos Arriba
				if(prevLines.size() > prevLineIndex){
					currLine = prevLines[prevLineIndex];
					prevLineIndex++;
					cursorPos = currLine.size();
				}
				textManager[0]->setText("> " + currLine + "|");
			}else if(event.Key.Code == sf::Keyboard::Down){		// Pulsamos Abajo
				if(prevLineIndex > 0){
					prevLineIndex--;
					currLine = prevLines[prevLineIndex];
					cursorPos = currLine.size();
				}else if(prevLineIndex == 0){
					currLine = "";
					cursorPos = 0;
				}
				textManager[0]->setText("> " + currLine + "|" );
			}else if(event.Key.Code == sf::Keyboard::Left){		// Pulsamos Izquierda

				if(cursorPos > 0){ // Muevo el cursor a la izquierda
					cursorPos--;
					displayLine = currLine;
					displayLine.insert(cursorPos, "|");
					textManager[0]->setText("> " + displayLine);
				}
			}else if(event.Key.Code == sf::Keyboard::Right){	// Pulsamos Derecha
				if(cursorPos < currLine.length()){
					cursorPos++;
					displayLine = currLine;
					displayLine.insert(cursorPos, "|");
					textManager[0]->setText("> " + displayLine);
				}
			}else if(event.Key.Code == sf::Keyboard::End){		// Pulsamos Fin
				cursorPos = currLine.length();
				displayLine = currLine + "|";
				textManager[0]->setText("> " + displayLine);

			}else if(event.Key.Code == sf::Keyboard::Home){		// Pulsamos Inicio
				cursorPos = 0;
				displayLine = "|" + currLine;
				textManager[0]->setText("> " + displayLine);
			}
		}

		if (event.Type == sf::Event::TextEntered) {
			if(event.Text.Unicode == 8){	// Pulsado Backspace
				if(currLine.size() > 0 && cursorPos > 0){

					currLine.erase(cursorPos - 1, 1);
					cursorPos--;
					displayLine = currLine;
					displayLine.insert(cursorPos, "|");

					textManager[0]->setText("> " + displayLine);
				}

			}else if(event.Text.Unicode == 127){	// Pulsado Suprimir
				if(currLine.size() > 0 && cursorPos < currLine.length()){

					currLine.erase(cursorPos, 1);
					displayLine = currLine;
					displayLine.insert(cursorPos, "|");

					textManager[0]->setText("> " + displayLine);
				}

			}else if(event.Text.Unicode == 13){	// Pulsado Enter

				vector<string> entrada = split(currLine, ' ');

				if(prevLines.size() == maxLines){
					prevLines.pop_back();
				}
				prevLines.insert(prevLines.begin(), currLine);
				prevLineIndex = 0;

				commandQueue.push_back(entrada);

				updateTextNodes();
				cursorPos = 0;
				currLine = "";

			}else if (event.Text.Unicode == 186) {

				status = 0;

			}else if (event.Text.Unicode < 128) {

				string newChar;
				newChar = static_cast<char>(event.Text.Unicode);

				currLine.insert(cursorPos,newChar);
				cursorPos++;
				displayLine = currLine;
				displayLine.insert(cursorPos, "|");

				textManager[0]->setText("> " + displayLine);
			}
		}

	}
	return status;
}

int TConsole::getMaxLines(){
	return maxLines;
}
vector<string> TConsole::getCommand() {
	vector<string> comando;

	if(!commandQueue.empty()){
		comando = commandQueue.front();
		commandQueue.erase(commandQueue.begin());
	}

	return comando;
}

vector<vector<string> > TConsole::getCommandQueue() {

	vector<vector<string> > comandos = commandQueue;

	commandQueue.clear();

	return comandos;
}

void TConsole::Render(){
	if(open && escena != NULL){

		escena->Reshape(Point(), 1);

		Text *texto = new Text();
		texto->setFont(0);
		texto->setSize(12);
		texto->setColor(Color<float>(1,1,1));

		Polygon pol(shBox->getShape());
		pol.setType(0);

		DrawSolidPolygon(pol, Color<float>(1,1,1,0.3));

		string cadena = "> " + currLine + "|";

		//int y = 600 - ((maxLines + 1) * 16);
		int y = maxLines * 16;

		texto->renderText(cadena, Point(20,y));

		vector<string>::iterator iter;
		for(iter = prevLines.begin(); iter != prevLines.end(); iter++){
			y -= 16;
			texto->renderText(*iter, Point(20, y));
		}

		escena->Reshape(Point(), 0);
	}
}

void TConsole::updateTextNodes(){
	vector<Text *>::iterator tIter;

	for(tIter = textManager.end() - 1; tIter != textManager.begin() + 1; tIter--){
		(*tIter)->setText((*(tIter - 1))->getText());
	}

	textManager[1]->setText(currLine);
	textManager[0]->setText("> |");

}

vector<string> TConsole::split(string cadena, char c){

	vector<string> subCadenas;
	string subString = "";

	for(unsigned int i = 0; i < cadena.length(); i++){
		if(cadena[i] == c){
			if(subString != ""){
				subCadenas.push_back(subString);
				subString = "";
			}
		}else{
			subString += cadena[i];
		}
	}
	if(subString != ""){
		subCadenas.push_back(subString);
	}

	return subCadenas;
}
