/*
 * CharacterFeature.cc
 *
 *  Created on: 20/02/2012
 *      Author: Chutaos team
 */

#include "CharacterFeature.h"

CharacterFeature * CharacterFeature::_features = NULL;

CharacterFeature * CharacterFeature::getInstance(){
	if(_features == NULL){
		_features = new CharacterFeature();
	}
	return _features;
}

CharacterFeature * CharacterFeature::getInstance(string nomFich_){
	if(_features == NULL){
		_features = new CharacterFeature(nomFich_);
	}else{
		_features->nomFile = nomFich_;
	}
	return _features;
}

CharacterFeature::CharacterFeature() {
	nomFile = "";
	featuresContainer = vector<Features>(Core::Entities::size,Features());

}

CharacterFeature::~CharacterFeature() {
	featuresContainer.clear();
	nomFile = "";
}

string CharacterFeature::getNomFile() const {
	return nomFile;
}

bool CharacterFeature::loadData(string nomFile_) {
	this->nomFile = nomFile_;
	return loadData();
}

CharacterFeature::CharacterFeature(string nomFile_) {
	this->nomFile = nomFile_;
	for (int i = 0; i < Core::Entities::size; i++) {
		featuresContainer.push_back(Features());
	}
}

bool CharacterFeature::loadData() {
	bool open = true;
	//clearData();
	int status = 0;
	TiXmlDocument doc(nomFile.c_str());
	if (doc.LoadFile()){
		TiXmlElement * objeto = doc.RootElement()->FirstChildElement();//cojemos el primer objetos

		while (objeto != NULL && status >= 0) {//mientras se lean objetos
			const char *tipoS = objeto->Attribute("type");
			if (tipoS != NULL){//si se ha conseguido el type
				int type = getType(tipoS);

				if (type >= 0 && type < Core::Entities::size){
					Features auxf;
					objeto->QueryFloatAttribute("hp", &auxf.HP);
					objeto->QueryFloatAttribute("speed", &auxf.Speed);
					objeto->QueryFloatAttribute("force", &auxf.Force);
					objeto->QueryFloatAttribute("cadence", &auxf.Cadence);
					objeto->QueryFloatAttribute("damage", &auxf.Damage);
					objeto->QueryIntAttribute("moral", &auxf.Moral);
					objeto->QueryIntAttribute("exp", &auxf.expKill);
					TiXmlElement * color = objeto->FirstChildElement();
					if (color!=NULL){
						float r=1,g=1,b=1,a=1;
						color->QueryFloatAttribute("r",&r);
						color->QueryFloatAttribute("g",&g);
						color->QueryFloatAttribute("b",&b);
						color->QueryFloatAttribute("a",&a);
						auxf.color = Color<float>(r,g,b,a);
					}

					featuresContainer[type] = auxf;
				}

			}else{//si no se ha conseguido el type
				status = -2;
			}
			objeto = objeto->NextSiblingElement();//pasamos al siguiente objeto

		}

	}else {
		cerr << "Error: No se ha podido cargar el fichero" << endl;
		open = false;
	}
	return open;
}

CharacterFeature & CharacterFeature::operator =(const CharacterFeature & obj) {
	if (this != &obj){
		copy(obj);
	}
	return *this;
}

CharacterFeature::CharacterFeature(const CharacterFeature & obj) {
	copy(obj);
}

void CharacterFeature::setNomFile(string nomFile) {
	this->nomFile = nomFile;
}

Features CharacterFeature::getFeature(Core::Entities::Type t){
	Features auxf;
	if (t>=0 && t < Core::Entities::size)
		auxf =  featuresContainer[t];
	return auxf;
}

void CharacterFeature::clearData(){
	vector<Features>::iterator iter;
	Features auxf;
	for (iter = featuresContainer.begin(); iter != featuresContainer.end(); iter++){
		(*iter) = auxf;
	}
}

ostream& operator <<(ostream & os, const CharacterFeature & n)
{
	os << "Nomfich: " << n.nomFile << endl;

	for (unsigned int i = 0; i < n.featuresContainer.size(); i++){
		//cout << "\n\n";
		//cout << "Tipo:" << i << endl;
		os << (n.featuresContainer[i]);
	}
	return os;
}

void CharacterFeature::copy(const CharacterFeature & obj) {
	featuresContainer = obj.featuresContainer;
	nomFile = obj.nomFile;
}

int CharacterFeature::getType(const char * name){
	int type = -1;

	string sName = name;

	if(sName == "e_captain") 		type = 1;
	else if(sName == "e_tecnic")	 	type = 2;
	else if(sName == "e_especialist")	 	type = 3;
	else if(sName == "e_explosive") 	type = 4;
	else if(sName == "e_enemy1") 		type = 5;
	else if(sName == "e_enemy2")		type = 6;
	else if(sName == "e_enemy3")	type = 7;
	else if(sName == "e_miniboss")		type = 8;
	else if(sName == "e_megaboss")		type = 9;

	return type;
}

ostream & operator <<(ostream & os, const Features & n)
{
	os << "HP: " << n.HP << endl;
	os << "DPS: " << n.DPS << endl;
	os << "Cadence: " << n.Cadence << endl;
	os << "Damage: " << n.Damage << endl;
	os << "Velocity: " << n.Speed << endl;
	os << "Force: " << n.Force << endl;
	os << "ExpKill: " << n.expKill << endl;
	os << "Color: " << n.color << endl;
	os << "Moral: " << n.Moral << endl;

	return os;
}

Features::Features(const Features & obj)
{
	HP = obj.HP;
	DPS =obj.DPS;
	Speed = obj.Speed;
	Force = obj.Force;
	Cadence = obj.Cadence;
	Damage = obj.Damage;
	Moral = obj.Moral;
	expKill = obj.expKill;
	color = obj.color;
}



Features & Features::operator =(const Features & obj)
{
	if (this != &obj){
		HP = obj.HP;
		DPS =obj.DPS;
		Speed = obj.Speed;
		Force = obj.Force;
		Cadence = obj.Cadence;
		Damage = obj.Damage;
		Moral = obj.Moral;
		expKill = obj.expKill;
		color = obj.color;
	}
	return *this;
}




