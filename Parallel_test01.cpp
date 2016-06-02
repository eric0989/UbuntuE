/************************************************************
* Title:  Parallel Test : Copy, SAXPY                       *
* Date:   2016/05/24                                        *
************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void initial(double *, double *, int);

int main(){
	double *A1, *cpA1, *B1, *A2, *cpA2, *B2;
	int N, i;
	double t1, t2, t3, t4;

	printf("\n Enter N = ");
	scanf("%d",&N);
	A1 = (double *)malloc(N*sizeof(double));
	cpA1 = (double *)malloc(N*sizeof(double));
	B1 = (double *)malloc(N*sizeof(double));
	A2 = (double *)malloc(N*sizeof(double));
	cpA2 = (double *)malloc(N*sizeof(double));
	B2 = (double *)malloc(N*sizeof(double));

	initial(A1, B1, N);
	initial(A2, B2, N);

	t1 = clock();
	for(i=0;i<N;i++)
		cpA1[i] = A1[i];
	t2 = clock();

	t3 = clock();
	#pragma acc data copyin(A2[0:N]) copyout(cpA2[0:N])
	{
	#pragma acc parallel loop
	for(i=0;i<N;i++)
		cpA2[i] = A2[i];
	}
	t4 = clock();

	printf("\n Copy : No   parallel:  %.8f s\n",(t2-t1)/CLOCKS_PER_SEC);
	printf("\n        Use  parallel:  %.8f s\n",(t4-t3)/CLOCKS_PER_SEC);

	t1 = clock();
	for(i=0;i<N;i++)
		B1[i] = A1[i]-B1[i];
	t2 = clock();

	t3 = clock();
	#pragma acc parallel loop
	for(i=0;i<N;i++)
		B2[i] = A2[i]-B2[i];
	t4 = clock();

	printf("\n SAXPY : No   parallel:  %.8f s\n",(t2-t1)/CLOCKS_PER_SEC);
	printf("\n         Use  parallel:  %.8f s\n",(t4-t3)/CLOCKS_PER_SEC);

	printf("\n");

	return 0;
}

void initial(double *x, double *y, int N){
	int i;

	for(i=0;i<N;i++){
		x[i] = i+1;
		y[i] = 1;
	}

	return;
}
