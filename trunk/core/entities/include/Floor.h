
#ifndef FLOOR_H_
#define FLOOR_H_


#include "Entity.h"

class Floor: public Entity {
	friend ostream& operator<<(ostream &os, const Floor& obj);
public:
	Floor();
	Floor(ResourceManager *r);
	Floor(const unsigned int idG, const Point, float, ResourceManager *r, Color<float> color_, vector<Point> vP);
	Floor(const Floor&);
	virtual ~Floor();
	Floor& operator=(const Floor&);
	vector<Point> getPoints();
	void generateCollision();
    vector<Point> getPerimetro() const;
    void setPerimetro(vector<Point> perimetro);

private:

	vector<Point> perimetro;
};

#endif
