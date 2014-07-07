#include "Floor.h"

Floor::Floor() {

}

Floor::Floor(ResourceManager *r) {
	setId(0);
	setType(Core::Entities::e_floor);
	setVisible(true);
	setSmall(false);
	setResource(r);
	generateCollision();
	id = 0;
}

Floor::Floor(const unsigned int idG, const Point pos, float angle,
		ResourceManager *r, Color<float> color_, vector<Point> vP) {
	setId(idG);
	setType(Core::Entities::e_floor);
	setAngle(angle);
	setCenter(pos);
	setVisible(true);
	setSmall(false);
	setResource(r);
	setColor(color_);
	perimetro = vP;
	generateCollision();
	idDisplay = r->generatePerimeter(vP);
}

Floor::Floor(const Floor &suelo) {
	setId(suelo.getId());
	setType(suelo.getType());
	setVisible(suelo.getVisible());
	setSmall(suelo.getSmall());
	setResource(suelo.getResource());
	setColor(suelo.getColor());
	generateCollision();
	id = suelo.id;
}

Floor::~Floor() {
	perimetro.clear();
}

Floor&
Floor::operator=(const Floor &suelo) {
	if (this != &suelo) {
		/*this->~Floor();
		 id=pare.id;
		 type=e_floor;
		 visible=pare.visible;
		 small=pare.small;
		 center=pare.center;
		 colision=pare.colision;*/
	}
	return *this;
}

void Floor::generateCollision() {

	Polygon pol(perimetro);

	BodyData *aux = new BodyData(pol);

	aux->setNeutral();
	World *auxWorld = getResource()->getWorld();
	body = new Body(*auxWorld, *aux);
	body->setPosition(center);
	body->setAngle(angle);
}

vector<Point> Floor::getPoints() {

	return perimetro;
}

ostream& operator<<(ostream &os, const Floor& obj) {
	os << "Entity(e_floor)";
	return os;
}

vector<Point> Floor::getPerimetro() const {
	return perimetro;
}

void Floor::setPerimetro(vector<Point> perimetro) {
	this->perimetro = perimetro;
}
