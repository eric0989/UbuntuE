/************************************************************
* Title:  Parallel Test : gemm                              *
* Date:   2016/05/24                                        *
************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void initial(double *, double *, int, int, int);

int main(){
	double *A, *B, *C1, *C2, *C3;
	int L, M, N, i, j, k;
	double t1, t2;

	printf("\n General matrix multiplication with LxM * MxN\n");
	printf(" Enter L  M  N = ");
	scanf("%d %d %d",&L,&M,&N);
	A = (double *)malloc(L*M*sizeof(double));
	B = (double *)malloc(M*N*sizeof(double));
	C1 = (double *)malloc(L*N*sizeof(double));
	C2 = (double *)malloc(L*N*sizeof(double));
	C3 = (double *)malloc(L*N*sizeof(double));

	initial(A, B, L, M, N);
/**************************************************/
	t1 = clock();
	for(i=0;i<L;i++)
		for(j=0;j<N;j++)
			for(k=0;k<M;k++)
				C1[N*i+j] = C1[N*i+j] + A[M*i+k]*B[j+N*k];
	t2 = clock();
	printf(" No  parallel: %.8f s\n",(t2-t1)/CLOCKS_PER_SEC);
/**************************************************/
	t1 = clock();
	#pragma acc data copyin(A[0:L*M], B[0:M*N]) copyout(C2[0:L*N])
	{
	#pragma acc kernels
	{
	for(i=0;i<L;i++)
		for(j=0;j<N;j++)
			for(k=0;k<M;k++)
				C2[N*i+j] = C2[N*i+j] + A[M*i+k]*B[j+N*k];
	}
	}
	t2 = clock();
	printf(" Use parallel: %.8f s\n",(t2-t1)/CLOCKS_PER_SEC);
/**************************************************/
	t1 = clock();
	#pragma acc kernels
	{
	for(i=0;i<L;i++)
		for(j=0;j<N;j++)
			for(k=0;k<M;k++)
				C3[N*i+j] = C3[N*i+j] + A[M*i+k]*B[j+N*k];
	}
	t2 = clock();
	printf(" No data copy: %.8f s\n",(t2-t1)/CLOCKS_PER_SEC);
/**************************************************/
	printf("\n");

	return 0;
}

void initial(double *x, double *y , int L, int M, int N){
	int i;

	for(i=0;i<L*M;i++)
		x[i] = i+1;
	for(i=0;i<M*N;i++)
		y[i] = 2;

	return;
}
