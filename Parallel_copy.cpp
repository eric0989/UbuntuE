/************************************************************
* Title:  Parallel Test : Copy                              *
* Date:   2016/05/24                                        *
************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void initial(double *, int);

int main(){
	double *A, *cpA1, *cpA2, *cpA3;
	int N, i;
	double t1, t2;

	printf("\n Enter N = ");
	scanf("%d",&N);
	A = (double *)malloc(N*sizeof(double));
	cpA1 = (double *)malloc(N*sizeof(double));
	cpA2 = (double *)malloc(N*sizeof(double));
	cpA3 = (double *)malloc(N*sizeof(double));

	initial(A, N);
/**************************************************/
	t1 = clock();
	for(i=0;i<N;i++)
		cpA1[i] = A[i];
	t2 = clock();
	printf(" No  parallel: %.8f s\n",(t2-t1)/CLOCKS_PER_SEC);
/**************************************************/
	t1 = clock();
	#pragma acc data copyin(A[0:N]) copyout(cpA2[0:N])
	{
	#pragma acc parallel loop
	for(i=0;i<N;i++)
		cpA2[i] = A[i];
	}
	t2 = clock();
	printf(" Use parallel: %.8f s\n",(t2-t1)/CLOCKS_PER_SEC);
/**************************************************/
	t1 = clock();
	#pragma acc parallel loop
	for(i=0;i<N;i++)
		cpA3[i] = A[i];
	t2 = clock();
	printf(" No data copy: %.8f s\n",(t2-t1)/CLOCKS_PER_SEC);
/**************************************************/
	printf("\n");

	return 0;
}

void initial(double *x, int N){
	int i;

	for(i=0;i<N;i++)
		x[i] = i+1;

	return;
}
