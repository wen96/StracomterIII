#include "Map.h"
#include "Point.h"
#include "GraphUD.h"

int main(void){

	Map mapa1;

	mapa1.setMap("map_01.txt");
/*
	GraphUD<Node> grafoMapa = mapa1.getGraph();

	cout << grafoMapa << endl;
*/
	std::vector<Point> pointList = mapa1.getVertex();

	cout << pointList.size() << endl ;

	std::vector<Point>::iterator iter;

	for(iter = pointList.begin(); iter != pointList.end(); iter++){
		cout << *iter << endl;
	}
	return 0;
}
