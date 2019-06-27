#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

using namespace std;

void S_layer1_up(double S[])
{
	char fileName[100];
	sprintf(fileName,"./Gx/xxx.txt");

	ifstream fin_gx(fileName);
	if(!(fin_gx))
	{
		printf("the %s is set up.\n",fileName);

		ofstream fout_gx(fileName);

		double *sum,*d_x;
    	double dt;
    	int n_steps = 1e5;

    	cudaMallocManaged(&sum, n * n_steps * sizeof(double));
    	cudaMalloc((void **)&d_x, (n + 1) * sizeof(double));

    	cudaMemcpyAsync(d_x, x, (n + 1) * sizeof(double), cudaMemcpyHostToDevice);

    	dt=(Up-Low)/n_steps;
    
    	int blockSize = 256;
    	int numBlock = (n * n_steps + blockSize - 1) / blockSize;

    	S_integrand<<<numBlock, blockSize>>>(n, n_steps, g_A, Low, dt, sum, d_x, R, injectionmode);
        
    	cudaDeviceSynchronize();
    
    	
    	for(int i = 1; i <= n; i++)
    	{
    		S[i]=0.0;
        	for(int j=0; j < n_steps; j++)
				S[i] += sum[(i - 1) * n_steps + j];
			S[i] = S[i]/cq;
			fout_gx<<S[i]<<endl;
			procBar(i*100/n);
		}
		cout<<endl;
		
    	cudaFree(sum);
    	cudaFree(d_x);

    	fout_gx.close();
	}
	else
	{
		for(int i=1; i<=n; i++)
			fin_gx>>S[i];
		fin_gx.close();
	}
	cout<<"<S> done...\n"<<endl;
}