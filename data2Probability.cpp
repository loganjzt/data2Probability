
#include <stdio.h>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#include <math.h>
#include <fstream>
#include <malloc.h>
#include <cstdio>

using namespace std;

int main(int argc, char *argv[]){

	if(argc < 2){
		printf("Need the name of input file (*.dat)...\n");
		return 1;
	}
	printf("you can input: name of file, nCut, nBin\n");
	/* variables for reading PvN data */
    char *fileName;
	char f[40];
    FILE *data;
    int i,j;

	int nCut = 5000;
	if(argc >=3 ) nCut = atoi(argv[2]);

    double time,x1,x2;

	int nbin = 20;
	if(argc >=4 ) nCut = atoi(argv[3]);

	double p[nbin];
	double dx;	
	double sum;

	double max,min;
	double mean,squareMean;

	fileName = argv[1];
	printf("# Reading file %s ...\n",fileName);
	data = fopen(fileName,"r");
    for(int i =0;i<nCut;i++) fgets(f,100,data);

	int size = 0;
	while(!feof(data)){
		fscanf(data,"%lf %lf %lf\n",&time,&x1,&x2);
		//x1 = sqrt(x1*x1+x2*x2);
		if(size == 0 ){
			max = x1;
			min = x1;
		}
		else{
			if( max < x1) max = x1;
			if( min > x1) min = x1;
		}
		
		size++;

		mean += x1; 
		squareMean += x1*x1;

	}
	fclose(data);

	mean = mean/double(size);
	squareMean = squareMean/double(size);
	
	printf("# mean = %e\n# var = %e\n",mean,squareMean-mean*mean);
	printf("# number of frame counted = %d\n",size);

	dx = (max-min)/double(nbin-1);

	printf("# second loop %s ...\n",fileName);
	data = fopen(fileName,"r");
    //fgets(f,100,data);
	for(int i =0;i<nCut;i++) fgets(f,100,data);

	while(!feof(data)){
		fscanf(data,"%lf %lf %lf\n",&time,&x1,&x2);
		x1 = x2;
		p[int((x1-min)/dx+0.5) ] += 1.0;
	}
	fclose(data);

	for(i=0;i<nbin - 1;i++) sum += dx*(p[i]+p[i+1])/2.0;
	for(i=0;i<nbin;i++){
		printf("%.2f\t%e\t%e\n",i*dx+min,p[i]/sum,-log(p[i]/sum));
	}

    return 0;
}
