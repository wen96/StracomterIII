#include "Transformacion.h"

Transform::Transform() {
	this->loadIdentity();
}

Transform::Transform(const Transform & t) {
		angle = t.angle;
		rx = t.rx;
		ry = t.ry;
		rz = t.rz;

		tx = t.tx;
		ty = t.ty;
		tz = t.tz;

		sx = t.sx;
		sy = t.sy;
		sz = t.sz;
}

Transform::~Transform() {
	angle = 0;
	rx = 0;
	ry = 0;
	rz = 0;

	tx = 0;
	ty = 0;
	tz = 0;

	sx = 1;
	sy = 1;
	sz = 1;
}

Transform & Transform::operator =(const Transform & t) {
	if (this != &t) {
		this->~Transform();
		angle = t.angle;
		rx = t.rx;
		ry = t.ry;
		rz = t.rz;

		tx = t.tx;
		ty = t.ty;
		tz = t.tz;

		sx = t.sx;
		sy = t.sy;
		sz = t.sz;
	}

	return *this;
}

void Transform::loadIdentity() {

	angle = 0;
	rx = 0;
	ry = 0;
	rz = 0;

	tx = 0;
	ty = 0;
	tz = 0;

	sx = 1;
	sy = 1;
	sz = 1;
}

void Transform::addRotation(double angle_, double rx_, double ry_, double rz_) {

	angle += angle_;

}


void Transform::addTranslation(double tx_, double ty_, double tz_) {
	tx += tx_;
	ty += ty_;
	tz += tz_;
}

void Transform::addScale(double sx_, double sy_, double sz_) {
	sx *= sx_;
	sy *= sy_;
	sz *= sz_;
}

void Transform::loadTranslation(double tx_, double ty_, double tz_) {
	tx = tx_;
	ty = ty_;
	tz = tz_;
}

void Transform::loadScale(double sx_, double sy_, double sz_) {
	sx = sx_;
	sy = sy_;
	sz = sz_;
}

void Transform::loadRotation(double angle_, double rx_, double ry_, double rz_) {
	angle = angle_; //Este ángulo va en Grados.
	rx = rx_;
	ry = ry_;
	rz = rz_;
}

double Transform::getAngle() const {
	return angle;
}

double Transform::getRx() const {
	return rx;
}

double Transform::getRy() const {
	return ry;
}

double Transform::getRz() const {
	return rz;
}

double Transform::getSx() const {
	return sx;
}

double Transform::getSy() const {
	return sy;
}

double Transform::getSz() const {
	return sz;
}

double Transform::getTx() const {
	return tx;
}

double Transform::getTy() const {
	return ty;
}


double Transform::getTz() const {
	return tz;
}

void
Transform::loadTranslation(Point p) {
	tx = p.getX();
	ty = p.getY();
	tz = p.getZ();
}

void
Transform::addTranslation(Point p) {
	tx += p.getX();
	ty += p.getY();
	tz += p.getZ();
}

void
Transform::loadOpenGL() const {
	glTranslatef(tx,ty,tz);
	glRotatef(angle, rx,ry,rz);
	glScalef(sx,sy,sz);
}
ostream &operator <<(ostream & os, const Transform & t) {
	cout << "Angle:" << t.getAngle() << endl;
	cout << "rx:" << t.getRx() << " ";
	cout << "ry:" << t.getRy() << " ";
	cout << "rz:" << t.getRz() << endl;
	cout << "tx:" << t.getTx() << " ";
	cout << "ty:" << t.getTy() << " ";
	cout << "tz:" << t.getTz() << endl;
	cout << "sx:" << t.getSx() << " ";
	cout << "sy:" << t.getSy() << " ";
	cout << "sz:" << t.getSz() << endl;
	return os;
}

Transform
Transform::operator+(const Transform &t) {

	Transform tmp;
	tmp.tx += t.tx;
	tmp.ty += t.ty;
	tmp.tz += t.tz;

	tmp.sx *= t.sx;
	tmp.sy *= t.sy;
	tmp.sz *= t.sz;

	return t;
}

