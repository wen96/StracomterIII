/*
 * Camera.cc
 *
 *  Created on: 05/01/2012
 *      Author: Chutaos Team
 */

#include "Camera.h"

Camera::Camera() {
	width = 0;
	height = 0;
	near = 0;
	far = 0;
	angle = 0.0;
	scale = 1.0;
	position = Point();
	projection = Graphics::Projection::c_none;
	element = Core::Element::e_camera;
}

Camera::Camera(int width_,int height_,int near_,int far_,Point p) {
	width = width_;
	height = height_;
	near = near_;
	far = far_;
	scale = 1.0;
	position = p;
	angle = 45;
	projection = Graphics::Projection::c_none;
	element = Core::Element::e_camera;
}

Camera::~Camera() {
	width = 0;
	height = 0;
	near = 0;
	far = 0;
	angle = 0.0;
	scale = 0.0;
	projection = Graphics::Projection::c_none;
	element = Core::Element::e_none;
}

void
Camera::Copiar(const Camera &c) {
	width = c.width;
	height = c.height;
	near = c.near;
	far = c.far;
	angle = c.angle;
	projection = c.projection;
	position = c.position;
	scale = c.scale;
	element = c.element;
}

Camera::Camera(const Camera &c) {
	this->Copiar(c);
}

Camera&
Camera::operator=(const Camera &c) {

	if(this != &c)
	{
		this->~Camera();
		this->Copiar(c);
	}

	return *this;
}

int
Camera::getWidth() const{
	return width;
}

int
Camera:: getHeight() const{
	return height;
}

int
Camera:: getNear() const {
	return near;
}

int
Camera:: getFar() const {
	return far;
}

float
Camera::getAngle() const {
	return angle;
}

float
Camera::getScale() const {
	return scale;
}

Point
Camera::getPosition() const {
	return position;
}

Graphics::Projection::Type
Camera::getProjection() const  {
	return projection;
}

void
Camera::setWidth(int width_) {
	width = width_;
}

void
Camera::setHeight(int height_) {
	height = height_;
}

void
Camera::setNear(int near_) {
	near = near_;
}

void
Camera::setFar(int far_) {
	far = far_;
}

void
Camera::setAngle(float angle_) {
	angle = angle_;
}

void
Camera::setScale(float scale_) {
	scale = scale_;
}

void
Camera::setPosition(Point position_) {
	position = position_;
}
void
Camera::setOrtho() {
	projection = Graphics::Projection::c_ortho;
}

void
Camera::setPerspective() {
	projection = Graphics::Projection::c_perspective;
}

void
Camera::exportOpenGL() const {

	float aspect = (float)width/(float)height;

	switch(projection)
	{
	case Graphics::Projection::c_ortho:
		glViewport(position.getX(),position.getY(), width,height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-scale, scale, -scale/aspect, scale/aspect, near,far);

		break;
	case Graphics::Projection::c_perspective:
		glViewport((int) position.getX(),((int) position.getY()), width,height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(angle,aspect, near, far);
		//glFrustum(-width/2, width/2, -height/2, height/2, near,far);
		break;
	default:
		break;
	}
}
