#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>

#include "nrutil.h"
#include "Integ.h"
#include "myClass.h"
#include "utility.h"

using std::cin;
using std::cout;
using std::endl;

//CLASS layer1
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

layer1::layer1(const char *namep, double ap, double bp, int nump)
//initialize the layer
{
	layer1::name=namep;
	layer1::x_down = ap;
	layer1::x_up = bp;
	layer1::numPoint = nump;
	
	//malloc space
	layer1::x = dvector(1, layer1::numPoint);
	layer1::w = dvector(1, layer1::numPoint);

	layer1::fb = dvector(1, layer1::numPoint);
	layer1::j = dvector(1, layer1::numPoint);

	layer1::S = dvector(1, layer1::numPoint);

	layer1::m1 = dmatrix(1, layer1::numPoint, 1, layer1::numPoint);
	layer1::m2 = dmatrix(1, layer1::numPoint, 1, layer1::numPoint);
	layer1::m3 = dmatrix(1, layer1::numPoint, 1, layer1::numPoint);

	layer1::Fak = dmatrix(1, layer1::numPoint, 1, 3*layer1::numPoint);

	gauleg(layer1::x_down, layer1::x_up, layer1::x, layer1::w, layer1::numPoint);	
	//Gauss-Legendre quadrature formula to discretize [a,b]
	
	char filename1[100], filename2[100];
	
	strcpy(filename1, layer1::name);
	strcat(filename1, "_x.txt");
	
	strcpy(filename2, layer1::name);
	strcat(filename2, "_w.txt");

	std::ofstream fout_x(filename1);
	std::ofstream fout_w(filename2);
	
	for(int i = 1; i <= layer1::numPoint; i++)
	{
		fout_x<<layer1::x[i]<<endl;
		fout_w<<layer1::w[i]<<endl;
	}

	fout_x.close();
	fout_w.close();

	cout<<layer1::name<<" <x> done..."<<endl;
}


void layer1::freeLayer()
//free space
{
	free_dvector(layer1::x, 1, layer1::numPoint);
	free_dvector(layer1::w, 1, layer1::numPoint);

	free_dvector(layer1::fb, 1, layer1::numPoint);
	free_dvector(layer1::j, 1, layer1::numPoint);

	free_dvector(layer1::S, 1, layer1::numPoint);

	free_dmatrix(layer1::m1, 1, layer1::numPoint, 1, layer1::numPoint);
	free_dmatrix(layer1::m2, 1, layer1::numPoint, 1, layer1::numPoint);
	free_dmatrix(layer1::m3, 1, layer1::numPoint, 1, layer1::numPoint);

	free_dmatrix(layer1::Fak, 1, layer1::numPoint, 1, 3*layer1::numPoint);
}

void layer1::S_vector()
{

/*
	1.判断S文件是否存在，若存在，则直接读取，不存在继续
	2.执行外接函数double S
			S被积函数 __device__
			kernal函数：调用S被积函数，GPU并行求值 __global__
			double S：调用kernal然后累加
	3.赋值给layer::S，并输出文件
*/

//1
	cout<<"<S>"<<endl;
	char path[100];
	
	sprintf(path, "./Gx");
	myMkdir(path);
//2
	S()


	for(int i = 1; i <= layer1::numPoint; i++)
		layer1::S[i]=0.0;
}

void layer1::Fak_matrix_flup()
{
	
}

void layer1::Fak_matrix_fldown()
{
	
}

void layer1::Fak_matrix_nm()
{
	
}

void layer1::Fak_matrix()
{	
	layer1::Fak_matrix_flup();
	layer1::Fak_matrix_fldown();
	layer1::Fak_matrix_nm();

	for(int i = 1; i <= layer1::numPoint; i++)
	{
		for(int j=1; j <= layer1::numPoint; j++)
			layer1::Fak[i][j] = layer1::m1[i][j];

		for(int j=1; j <= layer1::numPoint; j++)
			layer1::Fak[i][j+layer1::numPoint] = layer1::m2[i][j];

		for(int j=1; j <= layer1::numPoint; j++)
			layer1::Fak[i][j+2*layer1::numPoint] = layer1::m3[i][j];
	}	
}


//CLASS layer2
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

layer2::layer2(const char *namep, double ap, double bp, int nump)
//initialize the layer
{
	layer2::name=namep;
	layer2::x_down = ap;
	layer2::x_up = bp;
	layer2::numPoint = nump;
	
	//malloc space
	layer2::x = dvector(1, layer2::numPoint);
	layer2::w = dvector(1, layer2::numPoint);

	layer2::nmb = dvector(1, layer2::numPoint);
	layer2::j = dvector(1, layer2::numPoint);

	layer2::S = dvector(1, layer2::numPoint);

	layer2::m1 = dmatrix(1, layer2::numPoint, 1, layer2::numPoint);
	layer2::m2 = dmatrix(1, layer2::numPoint, 1, layer2::numPoint);
	layer2::m3 = dmatrix(1, layer2::numPoint, 1, layer2::numPoint);

	layer2::Fak = dmatrix(1, layer2::numPoint, 1, 3*layer2::numPoint);

	gauleg(layer2::x_down, layer2::x_up, layer2::x, layer2::w, layer2::numPoint);	
	//Gauss-Legendre quadrature formula to discretize [a,b]
	
	char filename1[100], filename2[100];
	
	strcpy(filename1, layer2::name);
	strcat(filename1, "_x.txt");
	
	strcpy(filename2, layer2::name);
	strcat(filename2, "_w.txt");

	std::ofstream fout_x(filename1);
	std::ofstream fout_w(filename2);
	
	for(int i = 1; i <= layer2::numPoint; i++)
	{
		fout_x<<layer2::x[i]<<endl;
		fout_w<<layer2::w[i]<<endl;
	}

	fout_x.close();
	fout_w.close();

	cout<<layer2::name<<" <x> done..."<<endl;
}

void layer2::freeLayer()
//free space
{
	free_dvector(layer2::x, 1, layer2::numPoint);
	free_dvector(layer2::w, 1, layer2::numPoint);

	free_dvector(layer2::nmb, 1, layer2::numPoint);
	free_dvector(layer2::j, 1, layer2::numPoint);

	free_dvector(layer2::S, 1, layer2::numPoint);

	free_dmatrix(layer2::m1, 1, layer2::numPoint, 1, layer2::numPoint);
	free_dmatrix(layer2::m2, 1, layer2::numPoint, 1, layer2::numPoint);
	free_dmatrix(layer2::m3, 1, layer2::numPoint, 1, layer2::numPoint);

	free_dmatrix(layer2::Fak, 1, layer2::numPoint, 1, 3*layer2::numPoint);
}

void layer2::S_vector()
{
	for(int i = 1; i <= layer2::numPoint; i++)
		layer2::S[i]=0.0;
}

void layer2::Fak_matrix_flup()
{
	
}

void layer2::Fak_matrix_fldown()
{
	
}

void layer2::Fak_matrix_nm()
{
	
}

void layer2::Fak_matrix()
{	
	layer2::Fak_matrix_flup();
	layer2::Fak_matrix_fldown();
	layer2::Fak_matrix_nm();

	for(int i = 1; i <= layer2::numPoint; i++)
	{
		for(int j=1; j <= layer2::numPoint; j++)
			layer2::Fak[i][j] = layer2::m1[i][j];

		for(int j=1; j <= layer2::numPoint; j++)
			layer2::Fak[i][j+layer2::numPoint] = layer2::m2[i][j];

		for(int j=1; j <= layer2::numPoint; j++)
			layer2::Fak[i][j+2*layer2::numPoint] = layer2::m3[i][j];
	}	
}



















