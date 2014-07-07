#include <iostream>
#include "GraphUD.h"
#include "Point.h"
#include "Node.h"
#include "NavGraph.h"
#include "ASNode.h"

using namespace std;

int main(){
	NavGraph ng;
	int id = -1;
	vector<int> ids;
	for (int i = 0; i < 6; i++){
		id = ng.addNode(ASNode(Point(0,0)));
		ids.push_back(id);
	}
	int primero = ids[0];
	cout << "##IDs insertados en Node" << primero << endl;
	for (unsigned int i = 0; i < ids.size(); i++){
		if (ng.addEdge(primero,ids[i])){
			cout << ids[i] << endl;
		}else{
			cout << "No insertado: "<< ids[i] << endl;
		}

	}
	cout << "Tras la insercion: " << ng.getNode(primero);

	cout << ng;


	//cout << ng << endl;
	NavGraph ng2;
	ng2 = ng;
	//cout << ng2 << endl;
	NavGraph * ng3 = NULL;
	ng3 = new NavGraph(ng2);

	cout << "##########Adyacencia de primero" << endl;
	vector<ASNode> ady = ng3->getAdyacence(primero);
	for (unsigned int i = 0; i < ady.size(); i++){
		cout << ady[i] << endl;
	}

	delete ng3;

	/*cout << "NumNodos: " << ng.nodes.size() << endl;
	vector<ASNode*>  ady = ng.getAdyacence(0);
	cout << "Adyacencia de 0" << endl;
	for (unsigned int i = 0; i < ady.size(); i++){
		cout << ady[i]->getId() << ": " << ady[i]->getG();
		cout << " + " << ady[i]->getH() << " = "<< ady[i]->getF() << endl;
	}
	cout << "Adyacencia de 1" << endl;
	ady = ng.getAdyacence(1);
	for (unsigned int i = 0; i < ady.size(); i++){
		cout << ady[i]->getId() << ": " << ady[i]->getG();
		cout << " + " << ady[i]->getH() << " = "<< ady[i]->getF() << endl;
	}
	ng.removeEdge(0,1);
	cout << "NumNodos: " << ng.nodes.size() << endl;
	ady = ng.getAdyacence(0);
	cout << ady.size() << endl;*/

	/*GraphUD grafo1;
	Point p;
	p.setX(1);
	p.setY(2);

	cout << p << endl;
	Node d(p);
	cout << d << endl;

	grafo1.addNode(p);
	grafo1.addNode(p);
	grafo1.addNode(p);
	grafo1.insertArist(1,2);
	grafo1.insertArist(0,1);
	cout << grafo1.existsNode(0);
	cout << grafo1.existsNode(1);
	cout << grafo1.existsNode(2);
	cout << grafo1.existsNode(3);
	cout << endl;
	cout << grafo1;
	grafo1.removeNode(0);
	grafo1.addNode(p);
	cout << grafo1.existsNode(0);
	cout << grafo1.existsNode(1);
	cout << grafo1.existsNode(2);
	cout << grafo1.existsNode(3);
	cout << endl;
	cout << grafo1;


	cout << "Fin" << endl;*/

	return 0;
}
