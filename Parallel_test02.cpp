/************************************************************
* Title:  Parallel Test : Norm                              *
* Date:   2016/05/24                                        *
************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void initial(double *, int);

int main(){
	double *A;
	int N, i;
	double normA, t1, t2;

	printf("\n Enter N = ");
	scanf("%d",&N);
	A = (double *)malloc(N*sizeof(double));

	initial(A, N);
/**************************************************/
	normA = 0;
	t1 = clock();
	for(i=0;i<N;i++)
		normA = normA + A[i]*A[i];
	t2 = clock();
	normA = sqrt(normA);
	printf("\n No  Parallel: %.8f s\n",(t2-t1)/CLOCKS_PER_SEC);
/**************************************************/
	normA = 0;
	t1 = clock();
	#pragma acc data copyin(A[0:N]) copyout(normA)
	{
	#pragma acc parallel loop
	for(i=0;i<N;i++)
		normA = normA + A[i]*A[i];
	}
	t2 = clock();
	normA = sqrt(normA);
	printf("\n Use parallel: %.8f s\n",(t2-t1)/CLOCKS_PER_SEC);
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
