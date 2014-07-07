#include "Transformacion.h"
/**/
Transform::Transform() {

	transform = new Matrix<double>(4,4);
	this->setIdentity();
	mode = Graphics::MatrixMode::m_modelview;
	element = Core::Element::e_transform;
}

Transform::Transform(Graphics::MatrixMode::Type mode_) {

	transform = new Matrix<double>(4,4);
	this->setIdentity();
	mode = mode_;
	element = Core::Element::e_transform;
}

Transform::Transform(const Transform & t) {

	transform = new Matrix<double>(4,4);
	*transform = (*t.transform);
	element = t.element;
	mode = t.mode;
}

Transform::~Transform() {

	if(transform != NULL)
	{
		delete transform;
		transform = NULL;
	}
	mode = Graphics::MatrixMode::m_none;
}

Transform & Transform::operator=(const Transform & t) {
	if (this != &t) {
		this->~Transform();
		transform = new Matrix<double>(4,4);
		*transform = *(t.transform);
		element = t.element;
		mode = t.mode;
	}

	return *this;
}

void Transform::setIdentity() {

	transform->setIdentity();
}

void Transform::addTranslation(double tx_, double ty_, double tz_) {
	Matrix<double> aux(4,4);
	aux.setIdentity();
	aux(1,4) = tx_;
	aux(2,4) = ty_;
	aux(3,4) = tz_;
	(*transform) = (*transform) * aux;

}

void Transform::addScale(double sx_, double sy_, double sz_) {
	Matrix<double> aux(4,4);
	aux.setIdentity();
	aux(1,1) = sx_;
	aux(2,2) = sy_;
	aux(3,3) = sz_;
	*(transform) = *(transform) * aux;
}
void Transform::addRotationX(double rx_) {
	double seno, coseno;
	seno = sin(rx_*M_PI/180);
	coseno = cos(rx_*M_PI/180);

	Matrix<double> aux(4,4);
	aux.setIdentity();
	aux(2,2) = coseno;
	aux(2,3) = -seno;
	aux(3,2) = seno;
	aux(3,3) = coseno;
	*(transform) = *(transform) * aux;

}

void Transform::addRotationY(double ry_) {
	double seno, coseno;
	seno = sin(ry_*M_PI/180);
	coseno = cos(ry_*M_PI/180);

	Matrix<double> aux(4,4);
	aux.setIdentity();
	aux(1,1) = coseno;
	aux(3,1) = -seno;
	aux(1,3) = seno;
	aux(3,3) = coseno;
	*(transform) = *(transform) * aux;
}

void Transform::addRotationZ(double rz_) {

	double seno, coseno;
	seno = sin(rz_*M_PI/180);
	coseno = cos(rz_*M_PI/180);

	Matrix<double> aux(4,4);
	aux.setIdentity();
	aux(1,1) = coseno;
	aux(1,2) = -seno;
	aux(2,1) = seno;
	aux(2,2) = coseno;
	*(transform) = *(transform) * aux;
}

void
Transform::addTranslation(Point p) {
	double tx = p.getX();
	double ty = p.getY();
	double tz = p.getZ();

	Matrix<double> aux(4,4);
	aux.setIdentity();
	aux(1,4) = tx;
	aux(2,4) = ty;
	aux(3,4) = tz;
	*(transform) = *(transform) * aux;
}

void
Transform::exportOpenGL() const {


	if(mode == Graphics::MatrixMode::m_modelview)
		glMatrixMode(GL_MODELVIEW);
	else if(mode == Graphics::MatrixMode::m_projection)
		glMatrixMode(GL_PROJECTION);
	else if(mode == Graphics::MatrixMode::m_texture)
		glMatrixMode(GL_TEXTURE);

	glLoadIdentity();
	GLdouble matrix[16];

	int num_celda = 0;
	for(int i = 1; i <= 4; i++)
		for(int j = 1; j <= 4; j++)
		{

			matrix[num_celda] = (*transform)(j,i);
			num_celda++;
		}
	glLoadMatrixd(matrix);
}

void
Transform::addOpenGL() const {

	if(mode == Graphics::MatrixMode::m_modelview)
		glMatrixMode(GL_MODELVIEW);
	else if(mode == Graphics::MatrixMode::m_projection)
		glMatrixMode(GL_PROJECTION);
	else if(mode == Graphics::MatrixMode::m_texture)
		glMatrixMode(GL_TEXTURE);

	GLdouble matrix[16];
	int num_celda = 0;
	for(int i = 1; i <= 4; i++)
		for(int j = 1; j <= 4; j++)
		{

			matrix[num_celda] = (*transform)(j,i);
			num_celda++;
		}
	glMultMatrixd(matrix);

}

Transform
Transform::operator+(const Transform &t) const {

	Transform tmp;

	*(tmp.transform) = (*transform) * (*(t.transform));

	return tmp;
}
ostream &operator <<(ostream & os, const Transform & t) {

	switch(t.mode)
	{
	case Graphics::MatrixMode::m_modelview:
		os << "Mode: MODELVIEW" << endl;
		break;
	case Graphics::MatrixMode::m_projection:
		os << "Mode: PROJECTION" << endl;
		break;
	case Graphics::MatrixMode::m_texture:
		os << "Mode: TEXTURE" << endl;
		break;
	case Graphics::MatrixMode::m_none:
		os << "Mode: NONE" << endl;
		break;
	}
	os << *(t.transform);
	return os;
}

Graphics::MatrixMode::Type Transform::getMode() const
{
    return mode;
}

Matrix<double> *Transform::getTransform() const
{
    return transform;
}

void Transform::setMode(Graphics::MatrixMode::Type mode_)
{
    this->mode = mode_;
}

void Transform::setTransform(Matrix<double> *transform_)
{
    this->transform = new Matrix<double>(*transform_);
}

void Transform::setModelView()
{
	mode = Graphics::MatrixMode::m_modelview;
}



void Transform::setProjection()
{
	mode = Graphics::MatrixMode::m_projection;
}

void Transform::importOpenGL()
{
	GLdouble matrix[16];

	if(mode == Graphics::MatrixMode::m_modelview)
		glGetDoublev(GL_MODELVIEW_MATRIX, matrix);
	else if(mode == Graphics::MatrixMode::m_projection)
		glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	else if(mode == Graphics::MatrixMode::m_texture)
		glGetDoublev(GL_TEXTURE_MATRIX, matrix);
}

void Transform::setTexture()
{
	mode = Graphics::MatrixMode::m_texture;
}





