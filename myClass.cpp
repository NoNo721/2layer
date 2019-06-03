#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>

#include "nrutil.h"

#include "Integ.h"

using std::cin;
using std::cout;
using std::endl;

class layer1
//Normal Metal.
{
private:

public:
	const char *name;
	int numPoint;
	double x_down, x_up;
	double *x, *w, *fb, *j, *S, **Fak;

	layer1(const char *namep, int ap=0, int bp=1, int nump=100)
	//initialize the layer
	{
		name=namep;
		x_down = ap;
		x_up = bp;
		numPoint = nump;
		
		x = dvector(1, numPoint);
		w = dvector(1, numPoint);

		fb = dvector(1, numPoint);
		j = dvector(1, numPoint);

		S = dvector(1, numPoint);

		gauleg(x_down, x_up, x, w, numPoint);	
		//Gauss-Legendre quadrature formula to discretize [a,b]
		
		char filename1[100], filename2[100];
		
		strcpy(filename1, name);
		strcat(filename1, "_x.txt");
		
		strcpy(filename2, name);
		strcat(filename2, "_w.txt");

		std::ofstream fout_x(filename1);
		std::ofstream fout_w(filename2);
		
		for(int i = 1; i <= numPoint; i++)
		{
			fout_x<<x[i]<<endl;
			fout_w<<w[i]<<endl;
		}

		fout_x.close();
		fout_w.close();

		cout<<name<<" <x> done..."<<endl;
	}

	void S_vector()
	{
		for(int i = 1; i <= numPoint; i++)
			S[i]=0.0;
	}

	double **Fak_matrix_flup()
	{
		double **m;
		m = dmatrix(1, numPoint, 1, numPoint);
		return m;
	}

	double **Fak_matrix_fldown()
	{
		double **m;
		m = dmatrix(1, numPoint, 1, numPoint);
		return m;
	}

	double **Fak_matrix_nm()
	{
		double **m;
		m = dmatrix(1, numPoint, 1, numPoint);
		return m;
	}

	void Fak_matrix()
	{	
		double **m1, **m2, **m3;

		m1 = Fak_matrix_flup();
		m2 = Fak_matrix_fldown();
		m3 = Fak_matrix_nm();

		Fak = dmatrix(1, numPoint, 1, 3*numPoint);

		for(int i = 1; i <= numPoint; i++)
		{
			for(int j=1; j <= numPoint; j++)
				Fak[i][j] = m1[i][j];

			for(int j=1; j <= numPoint; j++)
				Fak[i][j+numPoint] = m2[i][j];

			for(int j=1; j <= numPoint; j++)
				Fak[i][j+2*numPoint] = m3[i][j];
		}	
	}
};

class layer2
//Ferromagnetic Insulator
{
private:

public:
	const char *name;
	int numPoint;
	double x_down, x_up;
	double *x, *w, *nmb, *j, *S, **Fak;

	layer2(const char *namep, int ap=0, int bp=1, int nump=100)
	//initialize the layer
	{
		name=namep;
		x_down = ap;
		x_up = bp;
		numPoint = nump;
		
		x = dvector(1, numPoint);
		w = dvector(1, numPoint);

		nmb = dvector(1, numPoint);
		j = dvector(1, numPoint);

		S = dvector(1, numPoint);

		gauleg(x_down, x_up, x, w, numPoint);	
		//Gauss-Legendre quadrature formula to discretize [a,b]
		
		char filename1[100], filename2[100];
		
		strcpy(filename1, name);
		strcat(filename1, "_x.txt");
		
		strcpy(filename2, name);
		strcat(filename2, "_w.txt");

		std::ofstream fout_x(filename1);
		std::ofstream fout_w(filename2);
		
		for(int i = 1; i <= numPoint; i++)
		{
			fout_x<<x[i]<<endl;
			fout_w<<w[i]<<endl;
		}

		fout_x.close();
		fout_w.close();

		cout<<name<<" <x> done..."<<endl;
	}

	void S_vector()
	{
		for(int i = 1; i <= numPoint; i++)
			S[i]=0.0;
	}

	double **Fak_matrix_flup()
	{
		double **m;
		m = dmatrix(1, numPoint, 1, numPoint);
		return m;
	}

	double **Fak_matrix_fldown()
	{
		double **m;
		m = dmatrix(1, numPoint, 1, numPoint);
		return m;
	}

	double **Fak_matrix_nm()
	{
		double **m;
		m = dmatrix(1, numPoint, 1, numPoint);
		return m;
	}

	void Fak_matrix()
	{	
		double **m1, **m2, **m3;

		m1 = Fak_matrix_flup();
		m2 = Fak_matrix_fldown();
		m3 = Fak_matrix_nm();

		Fak = dmatrix(1, numPoint, 1, 3*numPoint);

		for(int i = 1; i <= numPoint; i++)
		{
			for(int j=1; j <= numPoint; j++)
				Fak[i][j] = m1[i][j];

			for(int j=1; j <= numPoint; j++)
				Fak[i][j+numPoint] = m2[i][j];

			for(int j=1; j <= numPoint; j++)
				Fak[i][j+2*numPoint] = m3[i][j];
		}	
	}
};


















