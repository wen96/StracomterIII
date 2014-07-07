/*
 * FSM.cc
 *
 *  Created on: Dec 22, 2011
 *      Author: rellik
 */

#include "FSM.h"

		/*
		 * 		FSMState
		 */

FSMState::FSMState() {
	name = "";
	id = 0;
}

FSMState::~FSMState() {
	name = "";
	id = 0;
	vTransitions.clear();
}

FSMState::FSMState(const FSMState & fsms) {
	name = fsms.name;
	id = fsms.id;
	vTransitions = fsms.vTransitions;
}

FSMState & FSMState::operator =(const FSMState & fsms) {
	if(this != &fsms){

		name = fsms.name;
		id = fsms.id;
		vTransitions = fsms.vTransitions;
	}

	return *this;
}

FSMState::FSMState(string Name, int Id) {
	name = Name;
	id = Id;
}

FSMState::FSMState(string Name, int Id, vector<pair<int, int> > Transitions) {
	name = Name;
	id = Id;
	vTransitions = Transitions;
}

void FSMState::setName(string Name) {
	name = Name;
}

void FSMState::setId(int nId) {
	id = nId;
}

bool FSMState::addTransition(int input, int destination) {
	bool inExists = false;

	vector<pair<int,int> >::iterator pIter;
	for(pIter = vTransitions.begin(); pIter != vTransitions.end() && !inExists; pIter++){
		if(input == (*pIter).first){
			inExists = true;
		}
	}

	if(!inExists){
		vTransitions.push_back(make_pair(input, destination));
	}

	return !inExists;
}

bool FSMState::removeTransition(int des){
	bool eliminado = false;

	vector<pair<int,int> >::iterator pIter;
	for(pIter = vTransitions.begin(); pIter != vTransitions.end(); pIter++){
		if((*pIter).second == des){
			vTransitions.erase(pIter);
			eliminado = true;
			break;
		}
	}

	return eliminado;
}

int FSMState::updateState(int input) {

	int state = id;

	vector<pair<int,int> >::iterator pIter;
	for(pIter = vTransitions.begin(); pIter != vTransitions.end(); pIter++){
		if(input == (*pIter).first)
			state = (*pIter).second;
	}

	return state;
}

string FSMState::getName() {
	return name;
}

int FSMState::getId() {
	return id;
}

vector<pair<int, int> > FSMState::getTransitions() {
	return vTransitions;
}

		/*
		 * 		FSM
		 */


FSM::FSM() {
	currentState = 0;
	nState = 1;
	debug = false;
}

FSM::~FSM() {
	currentState = 0;
	vStates.clear();
	nState = 1;
	debug = false;
}

FSM::FSM(const FSM & fsm) {
	currentState = fsm.currentState;
	vStates = fsm.vStates;
	nState = fsm.nState;
	debug = fsm.debug;
}

FSM & FSM::operator =(const FSM & fsm) {
	if(this != &fsm){

		currentState = fsm.currentState;
		vStates = fsm.vStates;
		nState = fsm.nState;
		debug = fsm.debug;
	}
	return *this;
}

bool FSM::loadData(string fName){
	bool leido = false;
	char c;
	int input;
	string sO, sD;

	ifstream fDatos;

	fDatos.open(fName.c_str(), ios::in);

	if(fDatos.is_open()){

		while(!fDatos.eof()){
			fDatos >> c;

			if(c == 'e'){
				fDatos >> sO;
				addState(sO);
			}else if(c == 't'){

				fDatos >> sO;
				fDatos >> input;
				fDatos >> sD;

				if(addTransition(getId(sO), getId(sD), input)){
					////cout << "Añado " << sO << " ---[" << input << "]-->" << sD << endl;
				}else{
					////cout << "No añado " << sO << " ---[" << input << "]-->" << sD << endl;
				}
			}else if(c == 'i'){
				fDatos >> sO;
				makeCurrent(getId(sO));
			}
		}

		leido = true;
	}

	return leido;
}

int FSM::addState(string name) {
	FSMState newState(name, nState);
	nState++;

	int nSi = newState.getId();

	vStates.push_back(newState);

	return nSi;
}

bool FSM::removeState(int id){
	bool eliminado = false;

	vector<FSMState>::iterator eIter = vStates.begin();
	while(eIter != vStates.end()){

		if((*eIter).getId() == id){
			eIter = vStates.erase(eIter);
			eliminado = true;
		}else{
			removeTransition((*eIter).getId(), id);
			eIter++;
		}
	}

	return eliminado;
}

bool FSM::addTransition(int ori, int des, int inp) {
	bool inserted = false;
	if(ori < nState && des < nState){
		vector<FSMState>::iterator sIter;
		for(sIter = vStates.begin(); sIter != vStates.end(); sIter++){
			if((*sIter).getId() == ori){
				inserted = (*sIter).addTransition(inp, des);
			}
		}
	}

	return inserted;
}

bool FSM::removeTransition(int ori, int des){
	bool eliminado = false;

	vector<FSMState>::iterator eIter;
	for(eIter = vStates.begin(); eIter != vStates.end(); eIter++){

		if((*eIter).getId() == ori){
			(*eIter).removeTransition(des);
			eliminado = true;
		}

	}

	return eliminado;
}

bool FSM::makeCurrent(int state) {
	bool changed = false;
	vector<FSMState>::iterator sIter;
	for(sIter = vStates.begin(); sIter != vStates.end(); sIter++){
		if((*sIter).getId() == state){
			currentState = state;
			changed = true;
		}
	}
	if(debug)	cout << "# FSM CURRENT STATE # " << getCurrentS() << endl;
	return changed;
}

int FSM::updateStates(int input) {
	int newState = currentState;

	vector<FSMState>::iterator sIter;
	for(sIter = vStates.begin(); sIter != vStates.end(); sIter++){
		if((*sIter).getId() == currentState){
			newState = (*sIter).updateState(input);
		}
	}

	if(debug)	cout << "# FSM TRANSITION " << getCurrentS() << " --[" << input << "]--> ";
	currentState = newState;
	if(debug) 	cout << getCurrentS() << " #" << endl;

	return newState;
}

int FSM::getCurrentI() {
	return currentState;
}

string FSM::getCurrentS() {
	string sName = "";
	vector<FSMState>::iterator sIter;
	for(sIter = vStates.begin(); sIter != vStates.end(); sIter++){
		if((*sIter).getId() == currentState){
			sName = (*sIter).getName();
		}
	}
	return sName;
}

vector<FSMState> FSM::getStates() {
	return vStates;
}

string FSM::getName(int id){
	string nombre = "";
	vector<FSMState>::iterator sIter;
	for(sIter = vStates.begin(); sIter != vStates.end(); sIter++){
		if((*sIter).getId() == id){
			nombre = (*sIter).getName();
		}
	}
	return nombre;
}

int FSM::getId(string name){
	int id = 0;
	vector<FSMState>::iterator sIter;
	for(sIter = vStates.begin(); sIter != vStates.end(); sIter++){
		if((*sIter).getName() == name){
			id = (*sIter).getId();
		}
	}
	return id;
}

vector<pair<int,int> > FSM::getTransitions(int id){

	vector<pair<int,int> > trans;

	vector<FSMState>::iterator sIter;
	for(sIter = vStates.begin(); sIter != vStates.end(); sIter++){
		if((*sIter).getId() == id){
			trans = (*sIter).getTransitions();
		}
	}
	return trans;
}

void FSM::setDebug(bool debugOn){
	debug = debugOn;
}

bool FSM::getDebug(){
	return debug;
}
