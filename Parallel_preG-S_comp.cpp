/***********************************************************
* Title:  Parallel test : pre-Gram-Schmidt                 *
* Date:   2016/06/02                                       *
***********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void initial(double *, double *, int);

int main(){
	double *x, *y;
	int i, N;
	double norm=0, dot=0, t1, t2;

	printf("\n Enter N = ");
	scanf("%d",&N);
	x = (double *)malloc(N*sizeof(double));
	y = (double *)malloc(N*sizeof(double));
	initial(x, y, N);

	t1 = clock();

	// normalize x[]
	for(i=0;i<N;i++)
		norm = norm + x[i]*x[i];
	norm = sqrt(norm);
	for(i=0;i<N;i++)
		x[i] = x[i]/norm;

	// x[] dot y[]
	for(i=0;i<N;i++)
		dot = dot + x[i]*y[i];

	// SAXPY
	for(i=0;i<N;i++)
		y[i] = y[i] - dot*x[i];

	t2 = clock();
	printf(" Time = %.8f s\n\n",(t2-t1)/CLOCKS_PER_SEC);

	return 0;
}

void initial(double *x, double *y, int N){
	for(int i=0;i<N;i++){
		x[i] = i+1;
		y[i] = 1;
	}

	return;
}
