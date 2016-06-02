/************************************************************
* Title:  Parallel Test : SAXPY                             *
* Date:   2016/05/24                                        *
************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void initial(double *, double *, double *, double *, int);

int main(){
	double *A, *B1, *B2, *B3;
	int N, i;
	double t1, t2;

	printf("\n Enter N = ");
	scanf("%d",&N);
	A = (double *)malloc(N*sizeof(double));
	B1 = (double *)malloc(N*sizeof(double));
	B2 = (double *)malloc(N*sizeof(double));
	B3 = (double *)malloc(N*sizeof(double));

	initial(A, B1, B2, B3, N);
/**************************************************/
	t1 = clock();
	for(i=0;i<N;i++)
		B1[i] = A[i]-B1[i];
	t2 = clock();
	printf(" No  parallel: %.8f s\n",(t2-t1)/CLOCKS_PER_SEC);
/**************************************************/
	t1 = clock();
	#pragma acc data copyin(A[0:N]) copyout(B2[0:N])
	{
	#pragma acc parallel loop
	for(i=0;i<N;i++)
		B2[i] = A[i]-B2[i];
	}
	t2 = clock();
	printf(" Use parallel: %.8f s\n",(t2-t1)/CLOCKS_PER_SEC);
/**************************************************/
	t1 = clock();
	#pragma acc parallel loop
	for(i=0;i<N;i++)
		B3[i] = A[i]-B3[i];
	t2 = clock();
	printf(" No data copy: %.8f s\n",(t2-t1)/CLOCKS_PER_SEC);
/**************************************************/
	printf("\n");

	return 0;
}

void initial(double *w, double *x, double *y, double *z, int N){
	int i;

	for(i=0;i<N;i++){
		w[i] = i+1;
		x[i] = 1;
		y[i] = 1;
		z[i] = 1;
	}

	return;
}
