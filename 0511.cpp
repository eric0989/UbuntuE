/************************************************************
* Title:  Matrix Multiplication with Single Pointer         *
* Date:   2016/05/11                                        *
************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <cblas.h>

void dgemm_row(double *, double *, double *, int);

int main(){
	double *A, *B, *C, *D;
	int i, j, k, N;
	double t1, t2, t3, t4, err=0.0;

	printf("\n Enter N = ");
	scanf("%d",&N);
	A = (double *)malloc(N*N*sizeof(double));
	B = (double *)malloc(N*N*sizeof(double));
	C = (double *)malloc(N*N*sizeof(double));
	D = (double *)malloc(N*N*sizeof(double));

	for(i=0;i<N*N;i++){
		A[i] = i+1;
		B[i] = N*N-i;
		C[i] = 0;
	}

	t1 = clock();

	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			for(k=0;k<N;k++)
				C[N*i+j] = C[N*i+j]+A[N*i+k]*B[j+N*k];
		}
	}

	t2 = clock();

	t3 = clock();

	dgemm_row(A,B,D,N);

	t4 = clock();

	for(i=0;i<N*N;i++)
		if(fabs(D[i]-C[i])>err)	err = fabs(D[i]-C[i]);

	printf("\n Time = %f s\n",(t2-t1)/CLOCKS_PER_SEC);
	printf(" Time_blas = %f s\n",(t4-t3)/CLOCKS_PER_SEC);
	printf(" err = %e\n\n",err);

	return 0;
}

void dgemm_row(double *A, double *B, double *C, int N){
	double alpha, beta;
	alpha = 1.0;
	beta = 0.0;

	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, alpha, A, N, B, N, beta, C, N);

	return;
}
