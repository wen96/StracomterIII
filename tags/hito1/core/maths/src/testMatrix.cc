#include <iostream>
using namespace std;

#include "Matrix.h"
#include "Rational.h"
#include "ctime"
#include "cstdlib"

const int TAM=4;

int main() {
	float e;
	/*Matrix mat1(2,3);
	Matrix mat2(3,2);
	Matrix mat3x3(3,3);
	Matrix matI(3,3);
	Matrix matI2(3,3);

	for(int n=1;n <= 2;n++)
	{
		
		for(int m=1; m <= 3;m++)
		{
			cout<<"JA"<<n<<" "<<m<<endl;
			mat1(n,m) = Rational(n+m);
			cout<<"SALE"<<endl;
		}
	}

	for(int n=1;n <= 3;n++)
	{
		for(int m=1; m <= 2;m++)
		{
			mat2(n,m) = Rational(n+m);
		}
	}
	for(int n=1;n <= 3;n++)
	{
		for(int m=1; m <= 3;m++)
		{
			mat3x3(n,m) = Rational(n+m);
		}
	}
	cout<<"HOLA"<<endl;
	mat3x3(1,3)=8;
		cout<<"HOLA"<<endl;
	cout<<"Matriz identidad:\n"<<matI<<endl;
	cout<<"Mat1:\n"<<mat1<<endl;
	cout<<"Mat2:\n"<<mat2<<endl;
	cout<<"MULT:\n"<<mat1*mat2<<endl;
	Matrix mat3=mat1*mat2;
	cout<<"Mat3(1,2): "<<mat3(1,2)<<endl;
	cout<< "\nCambio la posicion (1,2) de Mat3 por 33: \n";
	mat3(1,2)=33;
	cout<<mat3<<endl;
	cout<<"Mat3 * 2:\n";
	cout<<mat3 * 2<<endl;
	cout<<"Mat3 / 2:\n";
	cout<<mat3 / 2<<endl;
	cout<<"Traspuesta Mat3:\n";
	cout<<mat3.transpose()<<endl;
	cout<<"Matriz mat3x3:\n"<<mat3x3<<endl;
	cout<<"Su determinante es: "<<mat3x3.determinant()<<endl;
	cout<<"Inversa de mat3x3 es:\n"<<mat3x3.inverse()<<endl;
	cout<<"A mat1 de tamaño 2x3, le asigno el 33 en la posicion (4,4)"<<endl;
	mat1(4,4)=33;
	cout<<mat1<<endl;*/
	
	srand(time(NULL));
	cout<<"Esta prueba se realiza con una matriz de float"<<endl;
	Matrix<float> mat3x3(TAM,TAM);
	Matrix<float> inversa(TAM,TAM);
		for(int n=1;n <= TAM;n++)
			for(int m=1; m <= TAM;m++)
			{
				cout<<n<<","<<m<<": ";
				cin>>e;
				mat3x3(n,m) = e;
				//mat3x3(n,m) = rand()%10;
			}
	cout<<"Matriz 3x3:\n"<<mat3x3<<endl;
//	cout<<"Determinante Matriz 3x3:\n"<<mat3x3.determinant()<<endl;
//	cout<<"Inversa por Determinante de Matriz 3x3:\n"<<mat3x3.inverseDet()<<endl;
	inversa = mat3x3.inverse();
	cout<<"Inversa por Gauss-Jordan de Matriz 3x3:\n"<<inversa<<endl;
	/*for(int i = 1; i <= TAM; i++)
	{
		for(int j = 1; j <= TAM; j++)
			cout << inversa(i,j).getValor() << "\t";
		cout << endl;
	}*/
	
		

	return 0;
}



/*	//PRUEBAS DE OPERATOR==
 * 	if(matI2 == matI)
	{
		cout<<"Como matI y matI2 somos iguales,";
	}else
	{
		cout<<"Como matI y matI2 no somos iguales, ";
	}
	if(matI2 != matI)
	{
		cout<<"somos distintas!\n";
	}else
	{
		cout<<"no somos distintas!\n";
	}

	if(matI.isIdentity() && !(mat3x3.isIdentity()))
	{
		cout<<"MatI es la Identidad, pero Mat3x3 no lo es.\n";
	}
	mat3x3.identity();
	if(mat3x3.isIdentity())
	{
			cout<<"Ahora Mat3x3 tambien es Identidad.\n";
	}
	int vec[7];
	vec[0] = 1;
	vec[1] = 2;
	vec[2] = 3;
	vec[3] = 4;
	vec[4] = 5;
	vec[5] = 6;
	vec[6] = 7;
	matI2.fill(vec,7);
	cout<<"relleno MatI2;\n"<<matI2<<endl;
*/
