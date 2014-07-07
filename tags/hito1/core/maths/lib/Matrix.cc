/*
 * Matrix.cc
 *
 *  Created on: 03/11/2011
 *      Author: Chutaos Team
 */
/*
#include "Matrix.h"

Matrix::Matrix(int nf, int nc) {
	if (nf > 0 && nc > 0) {

		matrix = new Rational*[nf];
		for(int i = 0; i < nf; i++)
			matrix[i] = new Rational[nc];
		c = nc;
		f = nf;
	}
}

Matrix::~Matrix()
{
	for(int y = 0; y < f ; y++)
	{
		delete[] matrix[y];
	}
	delete[] matrix;
}

Matrix::Matrix(const Matrix & mat)
{
	int af = mat.getF();
	int ac = mat.getC();

	matrix = new Rational*[af];
	for(int i = 0; i < af; i++)
	{
		matrix[i] = new Rational[ac];
	}
	c = ac;
	f = af;

	for (int n = 0; n < af; n++)
		for (int m = 0; m < ac; m++)
		{
			matrix[n][m] = mat.matrix[n][m];
			//setNM(n, m, mat.getNM(n, m));
		}
}

int
Matrix::getC(void)const
{
	return c;
}

int
Matrix::getF(void)const
{
	return f;
}
Rational
Matrix::getNM(const int n, const int m)const
{
	return matrix[n][m];
}

void
Matrix::setNM(const int n, const int m, const Rational dato)
{
	matrix[n][m] = dato;
}

Matrix&
Matrix::operator=(const Matrix & mat)
{
	if(this != &mat)
	{
		int af = mat.getF();
		int ac = mat.getC();

		this->~Matrix();

		matrix = new Rational*[af];
		for(int i = 0; i < af; i++)
		{
			matrix[i] = new Rational[ac];
		}
		c = ac;
		f = af;


		for (int n = 0; n < af; n++)
			for (int m = 0; m < ac; m++)
			{
				//this->setXY(x, y, mat.getXY(x, y));
				matrix[n][m] = mat.matrix[n][m];
			}
	}
	return *this;
}

Matrix
Matrix::operator+(const Matrix &mat) const
{
	Matrix tmp(f,c);
	if(c==mat.c && f==mat.f)
	{
		for(int n=0; n < f; n++)
			for(int m=0; m < c; m++)
			{
				tmp.matrix[n][m] = (matrix[n][m] + mat.matrix[n][m]);
			}
	}
	return tmp;
}

Matrix
Matrix::operator *(const Matrix& mat) const
{
	Matrix tmp(f,mat.c);
	if(c==mat.f)
	{
		for(int n=0; n < f; n++)
			for(int m=0; m < mat.c; m++)
			{
				tmp.matrix[n][m]=0;
				for(int z=0; z < c; z++)
					tmp.matrix[n][m]= tmp.matrix[n][m] + (matrix[n][z]*mat.matrix[z][m]);
			}
	}
	return tmp;
}

Matrix
Matrix::operator*(const Rational& rat) const
{
	Matrix tmp(f,c);

	for(int n=0; n < f; n++)
		for(int m=0; m < c; m++)
			tmp.matrix[n][m] = (matrix[n][m] * rat);

	return tmp;
}

Matrix
Matrix::operator/(const Rational& rat) const
{

	return operator *(rat.inversa());

}
Rational &
Matrix::operator()(const int n, const int m)
{
	if(n > 0 && m > 0)
	{
		if(n <= f && m <= c)
		{
			return matrix[n-1][m-1];
		}else
		{
			int nf=n,nc=m;
			if(f>n)
				nf=f;
			else
				nf=n;
			if(c>m)
				nc=c;
			else
				nc=m;
			*this = chaMatrix(nf,nc);
			return matrix[n-1][m-1];
		}
	}else
	{
		return error;
	}
}

Rational
Matrix::operator()(const int n, const int m) const
{
	if((n>0 && n <= f) && (m>0 && m<= c))
		return matrix[n-1][m-1];
	else
		return Rational();
}

bool
Matrix::operator== (const Matrix &mat)
{
	bool iguales=false;
	if(f==mat.f && c==mat.c)
	{
		iguales=true;
		for(int n=0; n<f && iguales; n++)
			for(int m=0; m<c && iguales; m++)
				if(matrix[n][m]!=mat.matrix[n][m])
					iguales=false;

	}
	return iguales;
}

bool
Matrix::operator!= (const Matrix &mat)
{
	return (!operator==(mat));
}


ostream&
operator<<(ostream &os, const Matrix &mat) {

	for(int n=0; n<mat.f; n++)
	{
		for(int m=0; m<mat.c; m++)
		{
			os << mat.matrix[n][m] << "\t";
		}
		os<<endl;
	}
	return os;
}

Matrix
Matrix::chaMatrix(int n, int m)const
{
	Matrix tmp(n,m);

	if(n>f)
		n=f;
	if(m>c)
		m=c;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			tmp.matrix[i][j] = matrix[i][j];

	return tmp;
}

Matrix
Matrix::subMatrix(int ni,int mi, int nf, int mf)const
{
	if(ni>0 && mi>0)
	{
		if(nf>f)
			nf=f;
		if(mf>c)
			mf=c;
		int n=nf-ni+1;
		int m=mf-mi+1;
		Matrix tmp(n,m);

		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
			{
				tmp.matrix[i][j] = matrix[i+ni-1][j+mi-1];
			}

		return tmp;
	}else
	{
		return *this;
	}
}

Matrix
Matrix::conMatrix(const Matrix &mat) const
{
	if(f==mat.f)
	{
		Matrix tmp(f,c+mat.c);

		for (int i = 0; i < f; i++)
		{
			for (int j = 0; j < c; j++)
				tmp.matrix[i][j] = matrix[i][j];
			for (int j2 = 0; j2 < mat.c; j2++)
				tmp.matrix[i][j2+c] = mat.matrix[i][j2];
		}

		return tmp;
	}else
		return *this;
}



Matrix &
Matrix::fill(const Rational vec[],const int tam)
{
	int i=0,n=0,m;
	while(i<tam && n<f)
	{
		m=0;
		while(i<tam && m<c)
		{
				matrix[n][m]=vec[i];
				m++;
				i++;
		}
		n++;
	}

	return *this;
}

bool
Matrix::isSquare(void)const
{
	return (c==f);
}

bool
Matrix::isIdentity(void)
{
	bool ident =false;
	if(f==c)
	{
		Matrix aux(f,c);
		aux.setIdentity();
		if(*this==aux)
			ident=true;
	}
	return ident;
}

void
Matrix::setIdentity(void)
{
	if(isSquare())
	{
		for(int n=0; n<f; n++)
		{
			matrix[n][n]=1;
			for(int m=0; m<n; m++)
			{
				matrix[m][n]=0;
				matrix[n][m]=0;
			}
		}
	}
}

Rational
Matrix::determinant(void)const
{
	int aux;
	Rational det(0,1);
	Rational mult(0,0);
	if(isSquare())
	{
		if(f==1)
		{
			det= matrix[0][0];
		}else if(f==2)
		{
			det= matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
		}else
		{
			for(int n=0; n<f; n++)
			{
				mult=1;
				for(int m=0; m<c; m++)
				{
					mult= mult * matrix[(m+n)%f][m];
				}
				det= det + mult;
			//}for(int n=f-1; n>=0; n--){
				mult=1;
				for(int m=0; m<c; m++)
				{
					aux=f-1-n-m;//f-1: ya que usamos la misma n, si eliminamos f-1 hay que descomentar el for.
					if(aux<0)
					{
						aux+=f;
					}
					mult= mult * matrix[aux][m];
				}
				det= det - mult;
			}
		}
	}
	return det;
}


Matrix
Matrix::transpose(void)const
{
	Matrix tmp(f,c);

	if(isSquare())
	{
		for(int n=0; n<f; n++)
		{
			tmp.matrix[n][n]=matrix[n][n];
			for(int m=0; m<n; m++)
			{
				tmp.matrix[m][n]=matrix[n][m];
				tmp.matrix[n][m]=matrix[m][n];
			}
		}
	}
	return tmp;
}

Matrix
Matrix::cofactors(void)const
{
	int i,i1,ii,j,j1,jj;
	Rational det;
	Matrix aux(f,c);
	Matrix tmp(f,c);
	if(isSquare())
	{
		for (j=0;j<f;j++)//Recorre para cada Mij
		{
			for (i=0;i<f;i++)
			{
				i1 = 0;
				for (ii=0;ii<f;ii++)//Todos los aij, para crear la matrix aux.
				{
					if (ii != i)//los elementos de mi fila, no lo cojo.
					{
						j1 = 0;
						for (jj=0;jj<f;jj++)
						{
						   if (jj != j)//si el elemento es de mi columna, no lo cojo.
						   {
							   aux.matrix[i1][j1] = matrix[ii][jj];
						   	   j1++;
						   }
						 }
						i1++;
						}
				 }
				 det = aux.chaMatrix(f-1,c-1).determinant();
				 if( ((i+j+2) % 2) != 0)
					 det = det * -1;
				 tmp.matrix[i][j] = det;
		  }
	    }
	}
	return tmp;
}

Matrix
Matrix::adjoint(void)const
{
	return cofactors().transpose();
}

Matrix
Matrix::inverseDet(void)const
{
	return adjoint()/determinant();
}

Matrix&
Matrix::operatorFF(const int n1,const char op, const int n2)
{
	if(op=='-')
	{
		for(int m=0; m<c; m++)//Restamos la fila i y la fila n para conseguir el cero;
		{
			matrix[n1][m]=matrix[n1][m]-matrix[n2][m];
		}
	}else if(op=='+')
	{
		for(int m=0; m<c; m++)//Restamos la fila i y la fila n para conseguir el cero;
		{
			matrix[n1][m]=matrix[n1][m]+matrix[n2][m];
		}
	}
	return *this;
}

Matrix&
Matrix::operatorFFR(const int n1,const char op, const int n2,const Rational rat)
{
	if(op=='-')
	{
		for(int m=0; m<c; m++)//Restamos la fila i y la fila n para conseguir el cero;
		{
			matrix[n1][m]=matrix[n1][m]-(matrix[n2][m]*rat);
		}
	}else if(op=='+')
	{
		for(int m=0; m<c; m++)//Restamos la fila i y la fila n para conseguir el cero;
		{
			matrix[n1][m]=matrix[n1][m]+(matrix[n2][m]/rat);
		}
	}
	return *this;
}

Matrix&
Matrix::operatorFR(const int n,const char op, const Rational rat)
{
	if(op=='/')
	{
		for(int m=0; m<c; m++)//consigue el 1 en (i,i) y aplica a toda slas columas
		{
			matrix[n][m]=matrix[n][m]/rat;
		}
	}else if(op=='*')
	{
		for(int m=0; m<c; m++)//consigue el 1 en (i,i) y aplica a toda slas columas
		{
			matrix[n][m]=matrix[n][m]*rat;
		}
	}
	return *this;
}
Matrix&
Matrix::operatorCF(const Matrix mat,const int n)
{
	if(f==mat.f && c==mat.c)
	{
		for(int m=0; m<c; m++)//consigue el 1 en (i,i) y aplica a toda slas columas
		{
			matrix[n][m]=mat.matrix[n][m];
		}
	}
	return *this;
}

bool
Matrix::colZeros(const int col)
{
	bool zeros=true;
	Rational zero(0);

	if(col<c)
		for(int n=0; n<f; n++)
			if(matrix[n][col]!=zero)
				zeros=false;

	return zeros;
}

int
Matrix::filPivot(const int fil,const int col)
{
	int piv=0;
	Rational zero(0);
	if(fil<f && col<c)
	{
		for(int n=0; n<f; n++)
		{
			if(n!=fil)
				if(matrix[n][col]!=zero)
					piv=n;
		}
	}
	return piv;
}

Matrix
Matrix::inverse(void)const//Opera mal, y divide por 0, tenerlo en cuenta
{
	if(isSquare())
	{
		Matrix tmp(f,c),ident(f,c),aux(f,c*2);
		ident.setIdentity();
		tmp=*this;
		tmp=tmp.conMatrix(ident);
		Rational den(0);
		int a;

		for(int i=0; i<f; i++)//repeticion pora cada 1
		{
			if(!tmp.colZeros(i))
			{
				den=tmp.matrix[i][i];
				if(den!=0)
					tmp.operatorFR(i,'/',den);//consigue el 1 en (i,i) y aplica a toda slas columas
				else
				{
					a=tmp.filPivot(i,i);//busco cualquier elemento distitno de 0 en la columna i que no sea el elemento (i,i)
					den=tmp.matrix[a][i];//uso ese elemento (a,1) para poder generar el 1 en el elemento (i,i)
					//aux=tmp;//version ineficiente
					//aux.operatorFR(a,'/',den);
					//aux.operatorFF(i,'+',a);
					//tmp.operatorCF(aux,i);
					tmp.operatorFFR(i,'+',a,den);
				}
				for(int n=0; n<f; n++)//conseigue el 0 en las filas de esa columna
				{
					if(i!=n)//Si no soy la fila del 1
					{
						den=tmp.matrix[n][i];
						if(den!=0)//si ya es 0 no hace falta hacer nada
						{
							//aux=tmp; //version ineficiente
							//aux.operatorFR(i,'*',den);//consigue el 1 en (m,i) y aplica a toda slas columas
							//aux.operatorFF(n,'-',i);//Restamos la fila i y la fila n para conseguir el cero;
							//tmp.operatorCF(aux,n);
							tmp.operatorFFR(n,'-',i,den);
						}
					}
				}
			}
		}
		cout<<"Resultado:\n"<<tmp<<endl;
		if(tmp.subMatrix(1,1,f,c).isIdentity())
			return tmp.subMatrix(1,c+1,f,c*2);
	}
	return *this;
}
*/
