#include <iostream>
#include "TWindow.h"

using namespace std;

int main(int argc, char *argv[]){
	TWindow w;
	int c;
	w.openSFML(false);
	//w.display();
	w.openSFML(false);
	//w.display();
	cin >> c;
	cout << "Leido: " << c << endl;
	w.close();
	w.openSFML(300,10,false);
	//w.display();
	cin >> c;
	w.close();
	w.openSFML(800,600);
	//w.display();
	while(w.isOpen()){
		//w.display();
	}
	return 0;
}
