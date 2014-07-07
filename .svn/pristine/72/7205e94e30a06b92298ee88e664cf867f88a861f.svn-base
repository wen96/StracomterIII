/*
 * Animation.cc
 *
 *  Created on: 27/03/2012
 *      Author: Chutaos Team
 */

#include "Animation.h"
#include "GraphicTree.h"

Animation::Animation(Entity *entityAnimated_)
{
	entity = entityAnimated_;
	transform = NULL;
	initializeVars();
}

Animation::Animation(Transform *transformAnimated_)
{
	entity = NULL;
	transform = transformAnimated_;
	initializeVars();
}

Animation::Animation(Entity *entityAnimated_, Transform *transformAnimated_)
{
	entity = entityAnimated_;
	transform = transformAnimated_;
	initializeVars();
}

void Animation::initializeVars(){
	animTranlation = false;
	animRotation = false;
	animFadeColor = false;

	recorrido.clear();
	actualTrans = 0;

	rotaciones.clear();
	actualRot = 0;

	colores.clear();
	actualColor = 0;
}

Animation::~Animation() {
	entity = NULL;
	transform = NULL;
	initializeVars();
}

void Animation::init(){
	clockEntity.Reset(false);
	clockTransform.Reset(false);
	actualTrans = 0;
	actualRot = 0;
	actualColor = 0;
	if (entity != NULL && !colores.empty()){
		lastColores = colores[0];
		entity->setColor(lastColores);
		actualColor++;
	}
	if (entity != NULL && !recorrido.empty()){
		entity->setCenter(recorrido.front());
	}
	if (entity != NULL && !rotaciones.empty()){
		lastAngle = rotaciones.front();
		entity->setAngle(lastAngle);
		actualRot++;
	}
}

bool Animation::step(){
	bool terminado = true;
	if (animTranlation){
		if (!stepTranslation()){
			terminado = false;
		}
	}

	if (animRotation){
		if (!stepRotation()){
			terminado = false;
		}
	}

	if (animFadeColor){
		if (!stepFade()){
			terminado = false;
		}
	}

	return terminado;
}

void Animation::play(){
	while (!this->step());
}

bool Animation::stepTranslation(){
	bool terminado = true;

	Point ori;
	if (entity != NULL){
		//cout << "Trans entity: " << endl;
		float porcentaje = (clockEntity.getElapsedMiliseconds()*1.0/(timeAnimation/((float)recorrido.size())));
		if ((unsigned int)actualTrans < recorrido.size()){
			terminado = false;
			ori = lastPoint;
//			cout << "Orig:" << ori << endl;
			float mx = recorrido[actualTrans].getX();
			float my = recorrido[actualTrans].getY();
			float mz = recorrido[actualTrans].getZ();

			float dx = mx - ori.getX();
			float dy = my - ori.getY();
			float dz = mz - ori.getZ();

			ori.setXYZ(ori.getX()+dx*porcentaje,ori.getY()+dy*porcentaje,ori.getZ()+dz*porcentaje);
//			cout << "Dest:" << ori << endl;
//			cout << "Porcentaje: " << porcentaje << endl;
			entity->setCenter(ori);
			if ((int)porcentaje == 1){
				actualTrans++;
				lastPoint = entity->getCenter();
				clockEntity.Reset(false);
//				cout << "Paso" << endl;
			}

		}

	}
	if (transform != NULL){
		float porcentaje = (clockTransform.getElapsedMiliseconds()*1.0/(timeAnimation/((float)recorrido.size())));
		if ((int)porcentaje == 1)porcentaje=1;//Saturamos a 1
//		cout << "WTF: " << clockTransform.getElapsedMiliseconds()*1.0 << " / " << (timeAnimation/((float)recorrido.size())) << endl;
		if ((unsigned int)actualTrans < recorrido.size()){
			terminado = false;
			Point pact = recorrido[actualTrans];
			float tx = pact.getX()-lastPoint.getX();
			float ty =pact.getY()-lastPoint.getY();
			float tz =pact.getZ()-lastPoint.getZ();
//			cout << "Porc : " << porcentaje << " - " << lastPorcent << " =  " << porcentaje - lastPorcent << endl;
			porcentaje -= lastPorcent;
			lastPorcent += porcentaje;
			tx *= porcentaje;
			ty *= porcentaje;
			tz *= porcentaje;
			totalTranslated.setXYZ(totalTranslated.getX()+tx,totalTranslated.getY()+ty,totalTranslated.getZ()+tz);
//			cout << "Auxiliar: " << auxiliar << endl;
//			cout << "TransX:  " << pact.getX()+tx << endl;
//			cout << "TransY:  " << pact.getY()+ty << endl;
//			cout << "TransZ:  " << pact.getZ()+tz << endl;
//			cout << "Porc: " << porcentaje << endl;
			Point p(Point(tx,ty,tz));
//			cout << p << endl;
			transform->addTranslation(p);
			lastPoint = p;
//			cout <<"  Con porcentaje: " << lastPorcent << endl;

			if ((int)lastPorcent == 1){
				//TODO: No estoy seguro de esto, pero creo que es por fallo de precision asi que redondeo si no he recorrido lo que deberia
				//cout << "Error de: " << pact-totalTranslated << endl;
				pact-=totalTranslated;
				transform->addTranslation(pact);
				lastPorcent = 0;
				actualTrans++;
				clockTransform.Reset(false);
			}
		}


	}
	return terminado;
}

bool Animation::stepRotation(){
	bool terminado = true;

	if (entity != NULL){//Si se aplica a la entidad
		//cout << "Entra en el step" << endl;
		float porcentaje = (clockEntity.getElapsedMiliseconds()*1.0/(timeAnimation/((float)rotaciones.size())));
		if ((unsigned int)actualRot < rotaciones.size()){
			terminado = false;
			float objRot = rotaciones[actualRot];

			float aux = objRot - lastAngle;
			aux *= porcentaje;

			//			cout << "Porcentaje rot: " << porcentaje << "   Tiempo " << clock.getElapsedMiliseconds() << endl;
			//
			//			cout << "Last: "  << lastAngle << "Angulo: " << -entity->getAngle() << "  Obj: " << objRot << endl;

			entity->setAngle(aux+lastAngle);

			//cout << "Esta en " << entity->getAngle() << endl;

			if ((int)porcentaje == 1){
				lastAngle = -entity->getAngle();
				actualRot++;
				clockEntity.Reset(false);
			}
		}
	}
	if (transform != NULL){//Si se aplica a la transformacion
		float porcentaje = (clockEntity.getElapsedMiliseconds()*1.0/(timeAnimation/((float)rotTransform.size())));
		if ((unsigned int)actualRot < rotTransform.size()){
			terminado = false;
			float vect[3];
			vect[0]= rotTransform[actualRot][0];
			vect[1]= rotTransform[actualRot][1];
			vect[2]= rotTransform[actualRot][2];
			float tx = vect[0]-lastRotTransform[0];
			float ty =vect[1]-lastRotTransform[1];
			float tz =vect[2]-lastRotTransform[2];
			tx *= porcentaje;
			ty *= porcentaje;
			tz *= porcentaje;
//			cout << "RotX:  " << lastRotTransform[0]+tx << endl;
//			cout << "RotY:  " << lastRotTransform[1]+ty << endl;
//			cout << "RotZ:  " << lastRotTransform[2]+tz << endl;
			transform->addRotationX(lastRotTransform[0]+tx);
			transform->addRotationY(lastRotTransform[1]+ty);
			transform->addRotationZ(lastRotTransform[2]+tz);
//			cout << "Porcentaje rot: " << porcentaje << endl;
			if ((int)porcentaje == 1){
				lastRotTransform[0] = vect[0];
				lastRotTransform[1] = vect[1];
				lastRotTransform[2] = vect[2];
				actualRot++;
				clockEntity.Reset(false);
			}
		}
	}

	return terminado;
}

bool Animation::stepFade(){
	bool terminado = true;
	if ((unsigned int)actualColor < colores.size()){
		terminado = false;
		Color<float> actColor = colores[actualColor];
		float porcentaje = (clockTransform.getElapsedMiliseconds()*1.0/(timeAnimation/colores.size()));
		if (porcentaje >= 1) porcentaje = 1;
		float r = actColor.getR() - lastColores.getR();
		float g = actColor.getG() - lastColores.getG();
		float b = actColor.getB() - lastColores.getB();
		float a = (actColor.getAlpha() - lastColores.getAlpha());
		//cout << "##" << actColor.getAlpha() - lastColores.getAlpha() << endl;
		r *= porcentaje;
		g *= porcentaje;
		b *= porcentaje;
		a *= porcentaje;
		//cout << "Origen: " << lastColores << "   Destino:" << actColor << endl;
		//cout << "Porcentaje: " << porcentaje << "   Color:" << Color<float>(r+lastColores.getR(),g+lastColores.getG(),
			//	b+lastColores.getB(),lastColores.getAlpha()+a) << endl;

		entity->setColor(Color<float>(r+lastColores.getR(),g+lastColores.getG(),
				b+lastColores.getB(),lastColores.getAlpha()+a));

		if ((int)porcentaje == 1){
			lastColores = entity->getColor();
			actualColor++;
			clockTransform.Reset(false);
		}
	}
	return terminado;
}

void Animation::createTranslation(vector<Point> points_){
	clockEntity.Reset(false);
	recorrido = points_;
	actualTrans = 0;
	animTranlation = true;
	if (entity != NULL && !recorrido.empty()){
		lastPoint = entity->getCenter();
	}
}

void Animation::createTranslationTransform(vector<Point> points_){
	clockTransform.Reset(false);
	recorrido = points_;
	actualTrans = 0;
	animTranlation = true;
	lastPorcent = 0;
	if (transform != NULL && !recorrido.empty()){
		//lastPoint = transform->getPoint();
	}
}

void Animation::createRotation(vector<float> grados_){
	clockEntity.Reset(false);
	rotaciones = grados_;
	actualRot = 0;
	animRotation = true;
	if (entity != NULL && !rotaciones.empty()){
		lastAngle = entity->getAngle();
		entity->setAngle(lastAngle);
		actualRot++;
	}
}

void Animation::createRotationTransform(vector<vector<float> > v){
	clockTransform.Reset(false);
	rotTransform = v;
	actualRot = 0;
	animRotation = true;
	if (transform != NULL && !rotTransform.empty()){
		lastRotTransform = vector<float>(3,0);
	}
}

void Animation::createFade(vector<Color<float> > colores_){
	clockEntity.Reset(false);
	colores = colores_;
	actualColor = 0;
	animFadeColor = true;
	if (entity != NULL && !colores.empty()){
		lastColores = entity->getColor();
//		entity->setColor(lastColores);
//		actualColor++;
	}
}

vector<Color<float> > Animation::getColores() const
{
    return colores;
}

Entity *Animation::getEntity() const
{
    return entity;
}

vector<Point> Animation::getRecorrido() const
{
    return recorrido;
}

vector<float> Animation::getRotaciones() const
{
    return rotaciones;
}

Transform *Animation::getTranform() const
{
    return transform;
}

bool Animation::isAnimFadeColor() const
{
    return animFadeColor;
}

bool Animation::isAnimRotation() const
{
    return animRotation;
}

bool Animation::isAnimTranlation() const
{
    return animTranlation;
}

void Animation::setAnimFadeColor(bool animFadeColor)
{
    this->animFadeColor = animFadeColor;
}

void Animation::setAnimRotation(bool animRotation)
{
    this->animRotation = animRotation;
}

void Animation::setAnimTranlation(bool animTranlation)
{
    this->animTranlation = animTranlation;
}

void Animation::setColores(vector<Color<float> > colores)
{
    this->colores = colores;
}

void Animation::setEntity(Entity *entity)
{
    this->entity = entity;
}

void Animation::setRecorrido(vector<Point> recorrido)
{
    this->recorrido = recorrido;
}

void Animation::setRotaciones(vector<float> rotaciones)
{
    this->rotaciones = rotaciones;
}

void Animation::setTranform(Transform *tranform)
{
    this->transform = tranform;
}

int Animation::getTimeAnimation() const
{
    return timeAnimation;
}

void Animation::setTimeAnimation(int timeAnimation)
{
    this->timeAnimation = timeAnimation;
}





