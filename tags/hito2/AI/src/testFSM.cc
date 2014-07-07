#include <FSM.h>
#include <cstdlib>

void menu();
void mostrarEstados(FSM fsm);

int main(int argc, char *argv[]) {

	int opc;
	string sName = "";
	vector<FSMState> estados;
	FSM fsm;

	if (argc == 2) {
		fsm.loadData(argv[1]);
	}

	int id;
	int idOri, idDes, input;
	int eActual;
	bool res;
	ofstream fout;
	vector<FSMState>::iterator iIter;
	vector<pair<int, int> > trans;
	vector<pair<int, int> >::iterator tIter;

	do{
			menu();

			char ch;

			cin >> opc;

			while ((ch = cin.get()) != '\n' && ch != EOF);

			cout<< endl;

			switch (opc) {
			case 1:
				cout<< "\tNombre: ";
				cin >> sName;
				id = fsm.addState(sName);
				cout<< "\tAñadido: " << sName << " (" << id << ")" << endl;
				break;

			case 2:

				mostrarEstados(fsm);

				cout<< endl;

				cout<< "\tEstado a eliminar: ";
				cin >> id;

				if(fsm.removeState(id)){
					cout<< "\tEstado eliminado co exito" << endl;
				}else{
					cout<< "\t## Error al eliminar el estado ##" << endl;
				}

				break;

			case 3:
				cout<< "\tEstado inicial: ";
				cin >> idOri;
				cout<< "\tEstado destino: ";
				cin >> idDes;
				cout<< "\tValor de transicion: ";
				cin >> input;
				res = fsm.addTransition(idOri, idDes, input);
				if (res) {
					cout<< "\tAñadido: " << idOri << " ---[" << input << "]---> "
							<< idDes << endl;
				} else {
					cout<< "\t## Error al añadir la transicion ##" << endl;
				}
				break;

			case 4:
				cout<< "\tEstado inicial: ";
				cin >> idOri;
				cout<< "\tEstado destino: ";
				cin >> idDes;

				if(fsm.removeTransition(idOri, idDes)){
					cout<< "\tTransicion eliminada con exito" << endl;
				}else{
					cout<< "\t## Error al eliminar la transicion ##" << endl;
				}

				break;

			case 5:
				cout<< "\tEstado de inicio: ";
				cin >> id;
				res = fsm.makeCurrent(id);
				if (res)
					cout<< "\tEstado de inicio cambiado" << endl;
				else
					cout<< "\t## Error al cambiar el estado de inicio ##" << endl;
				break;

			case 6:
				eActual = fsm.getCurrentI();
				estados = fsm.getStates();
				cout<< "\t-- Estados --" << endl;
				for (iIter = estados.begin(); iIter != estados.end(); iIter++) {
					cout<< "\t" << (*iIter).getName() << " (" << (*iIter).getId()
							<< ")";
					if ((*iIter).getId() == eActual)
						cout<< " #" << endl;
					else
						cout<< endl;

					trans = (*iIter).getTransitions();
					for (tIter = trans.begin(); tIter != trans.end(); tIter++) {
						cout<< "\t\t" << "---[" << (*tIter).first << "]---> "
								<< (*tIter).second << endl;
					}
				}

				break;

			case 7:

				cout<< "\tNombre del archivo: ";

				cin >> sName;

				fout.open(sName.c_str(), ios::out);

				if(fout.is_open()){

					estados = fsm.getStates();
					for (iIter = estados.begin(); iIter != estados.end(); iIter++) {
						fout << "e " << (*iIter).getName() << endl;
					}

					for (iIter = estados.begin(); iIter != estados.end(); iIter++) {

						trans = (*iIter).getTransitions();

						for (tIter = trans.begin(); tIter != trans.end(); tIter++) {

							fout << "t " << (*iIter).getName() << " " << (*tIter).first << " " << fsm.getName((*tIter).second) << endl;

						}
					}

					fout << "i " << fsm.getCurrentS() << endl;

					fout.close();

					cout<< "\tArchivo generado" << endl;


				}else{
					cout<< "\t## Error al abrir el archivo " << sName << " ##" << endl;
				}


				break;

			case 8:

				cout<< "\tNombre del archivo: ";

				cin >> sName;

				if(fsm.loadData(sName)){
					cout<< "\tDatos cargados" << endl;
				}else{
					cout<< "\t## Error al cargar los datos ##" << endl;
				}

				break;

			case 9:

				break;

			default:
				cout<< "## " << opc << " no es una opcion valida ##" << endl;
				break;
			}

			cout<< endl;

		}while(opc != 9);

	return 0;
}

void menu(){

	cout<< "¿Que deseas realizar?" << endl;

	cout<< "[1] Añadir estado" << endl;
	cout<< "[2] Eliminar estado" << endl;
	cout<< "[3] Añadir transicion" << endl;
	cout<< "[4] Eliminar transicion" << endl;
	cout<< "[5] Cambiar el estado inicial" << endl;
	cout<< "[6] Ver la maquina actual" << endl;
	cout<< "[7] Generar el archivo" << endl;
	cout<< "[8] Cargar un archivo" << endl;
	cout<< "[9] Salir" << endl;

	cout<< "Opcion: ";

}

void mostrarEstados(FSM fsm){
	int eActual = fsm.getCurrentI();
	vector<FSMState> estados = fsm.getStates();
	vector<FSMState>::iterator iIter;

	cout<< "\t-- Estados --" << endl;
	for (iIter = estados.begin(); iIter != estados.end(); iIter++) {
		cout<< "\t" << (*iIter).getName() << " (" << (*iIter).getId()
				<< ")";
		if ((*iIter).getId() == eActual)
			cout<< " #" << endl;
		else
			cout<< endl;
	}
}

