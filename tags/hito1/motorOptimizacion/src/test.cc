#include <iostream>
#include <vector>
using namespace std;

#include <Simplex.h>

/*Ejemplo de Simplex Normal Z = 22
 const string obj = "Max z 3x1 + 4x2";
 const string r1 = "2x1 + x2 <= 8";
 const string r2 = "-x1 + 2x2 <= 6";
 const string r3 = "x1 + x2 <= 6";*/
/*Ejemplo de Simplex Penalizaciones (con Optimo) Z = 1
 const string obj = "Max z 2x1 - x2";
 const string r1 = "x1 + x2 <= 5";
 const string r2 = "-x1 + x2 >= 1";*/
/*Ejemplo de Simplex Penalizaciones (no Acotado) Z = #noHaySolucion
 const string obj = "Min z 3x1 - 2x2 + 5x3";
 const string r1 = "x1 + 2x2 + x3 >= 5";
 const string r2 = "-3x1 + x2 - x3 <= 4";*/
/*Ejemplo de Simplex Dual (directo) Z = -36
 const string obj = "Max z -4x1 - 6x2 - 18x3";
 const string r1 = "x1 + 3x3 >= 3";
 const string r2 = "x2 + 2x3 >= 5";*/
/*Ejemplo de Simplex Entero Z = 8 (Encuentra uno con el mejor valor)*/
const string obj = "Max z 2x1 + x2";
const string r1 = "4x1 + 2x2 >= 15";
const string r2 = "12x1 + 7x2 <= 55";
const string r3 = "5x1 + 2x2 <= 18";
/*Ejemplo de Simplex Entero Z = 8 (Calcula todos y elige esl mas optimo);
const string obj = "Max z 21x1 + 11x2";
const string r1 = "7x1 + 4x2 <= 13";*/


int main(int argc,char *argv[]) {

	if(argc==1)
	{
		cout<<"-----------------------------------------------------------------------------------------------------------\n";
		cout<<"Tambien dispone de las siguientes opciones:\n";
		cout<<"\"Simplex demo\" o \"Simplex -d\" - Para ejecutar una demo con un problema predeterminado.\n"
				"\"Simplex help\" o \"Simplex -h\" - Para mostrar la ayuda del ejecutable.\n";
		Simplex sim;
		string obje="",rest="",opc="";
		do{
			cout<<"-----------------------------------------------------------------------------------------------------------\n";
			cout<<"Introduce el tipo de Simplex que desea calcular:\n"
				" \"Estandar\" \t \"Penalizaciones\" \t \"Dual\" \t \"Enteros\"\n";
			cout<<"-----------------------------------------------------------------------------------------------------------\n";
			getline(cin,opc);
		}while((opc!="Enteros" && opc!="Dual") && (opc!="Penalizaciones" && opc!="Estandar"));

		cout<<"Introduce la funcion objetivo:\nejemplo: Max z 21x1 + 11x2"<<endl;
		getline(cin,obje);
		do{
			cout<<"Introduce una restriccion:\nejemplo: 7x1 + 4x2 <= 13 #Si no desea introducir mas restricciones escriba: NO"<<endl;
			getline(cin,rest);
			if(rest!="NO")
				sim.addRestriccion(rest);
		}while(rest!="NO");
		sim.setObjetivo(obje);

		cout<<"-----------------------------------------------------------------------------------------------------------\n";
		cout<<"Problema introducido:\n"
				"-----------------------------------------------------------------------------------------------------------\n"<<sim<<
				"-----------------------------------------------------------------------------------------------------------\n";
		int status=-5;
		if(opc=="Enteros")
		{
			status=sim.SimplexInt();
		}else if(opc=="Penalizaciones" || opc=="Estandar")
		{
			status=sim.SimplexPenal();
		}else if(opc=="Dual")
		{
			status=sim.SimplexDual();
		}
		if (status == 0) {
			cout << "Problema resuelto.\n"
				"-----------------------------------------------------------------------------------------------------------\n" << sim <<""
				"-----------------------------------------------------------------------------------------------------------\n";
			sim.MuestraSolucion();
			cout<<"-----------------------------------------------------------------------------------------------------------\n";
		}else if(status==-1)
		{
			cout << "El problema de programacion lineal es no acotado, no tiene solucion.\n"
					"-----------------------------------------------------------------------------------------------------------\n";
		}else if(status==-2)
		{
			cout << "El problema introducido no tiene solucion.\n"
					"-----------------------------------------------------------------------------------------------------------\n";
		}

	}else if(argc==2)
	{
		string opcion=argv[1];

		if(opcion=="demo" || opcion=="-d")
		{
			Simplex par;
			par.addRestriccion(r1);
			par.addRestriccion(r2);
			par.addRestriccion(r3);
			par.setObjetivo(obj);
			cout<<"-----------------------------------------------------------------------------------------------------------\n";
			cout<<"Problema de demostracion:\n"
					"-----------------------------------------------------------------------------------------------------------\n"<<par<<
					"-----------------------------------------------------------------------------------------------------------\n";
			int status = par.SimplexInt();
			if (status == 0) {
				cout << "Problema resuelto.\n"
					"-----------------------------------------------------------------------------------------------------------\n" << par <<""
					"-----------------------------------------------------------------------------------------------------------\n";
				par.MuestraSolucion();
				cout<<"-----------------------------------------------------------------------------------------------------------\n";
			} else {
				cout << "No se pudo resolver simplex: Error " << status << endl;
			}
		}else if(opcion=="help" || opcion=="-h")
		{
			cout <<"\nSimplex tiene las siguientes tres funciones:\n"
							"\"Simplex\" - Para introducir el problema de Programacion Lineal.\n"
							"\"Simplex demo\" o \"Simplex -d\" - Para ejecutar una demo con un problema predeterminado.\n"
							"\"Simplex help\" o \"Simplex -h\" - Para mostrar la ayuda del ejecutable.\n\n"
					"\nSi seleccionas la primera opcion Simplex te permite resolver todo tipo de problemas de Programacion Lineal,\n"
					"usando sus distintos algoritmos, desde el Simplex Estandar hasta el Simplex de Enteros Puro,\n"
					"pasando por Simplex por Penalizaciones y el Dual.\n\n"
					"Simplex no es dificil de usar, pero se ruega que el usuario siga las pautas a la hora de escribir la función objetivo\n"
					"y las restricciones, asi como a la hora de elegir el algoritmo a emplear, para ello se muestran ejemplos y se proporciona\n"
					"una demo muy donde vemos como resuelve un problema. El problema que se resuelve le aparecer aqui abajo, para que asi tambien\n"
					"vea como debe de escribir los parametros de la ejecucion:\n\n";
			cout<<"-----------------------------------------------------------------------------------------------------------\n";
			cout<<"Introduce la funcion objetivo:\nejemplo: Max z 21x1 + 11x2"<<endl;
			cout<<obj<<endl;
			cout<<"Introduce una restriccion:\nejemplo: 7x1 + 4x2 <= 13 #Si no desea introducir mas restricciones escriba: NO"<<endl;
			cout<<r1<<endl;
			cout<<"Introduce una restriccion:\nejemplo: 7x1 + 4x2 <= 13 #Si no desea introducir mas restricciones escriba: NO"<<endl;
			cout<<r2<<endl;
			cout<<"Introduce una restriccion:\nejemplo: 7x1 + 4x2 <= 13 #Si no desea introducir mas restricciones escriba: NO"<<endl;
			cout<<r3<<endl;
			cout<<"-----------------------------------------------------------------------------------------------------------\n";
			cout<<"\nGracias por usar Simplex y espero que le sea de ayuda.\nUn cordial saludo de todo el equipo de \"Chutaos Team\"."<<endl;
		}
	}else
	{
		cout << "\nError en el numero de parametros. Ejecute:\n"
				"\"Simplex\" - Para introducir el problema de Programacion Lineal.\n"
				"\"Simplex demo\" o \"Simplex -d\" - Para ejecutar una demo con un problema predeterminado.\n"
				"\"Simplex help\" o \"Simplex -h\" - Para mostrar la ayuda del ejecutable.\n"<< endl;
	}

	return 0;
}
