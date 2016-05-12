/************************************************************
* Title:  Matrix Multiplication with Single Pointer         *
* Date:   2016/05/11                                        *
************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <cblas.h>

void MxM(double *, double *, double *, int);
void dgemm_row(double *, double *, double *, int);
double err(double *, double *, int);
void print_matrix(double *, int);

int main(){
	double *A, *B, *C, *D;
	int i, N;
	double t1, t2, t3, t4;

	printf("\n Enter N = ");
	scanf("%d",&N);
	A = (double *)malloc(N*N*sizeof(double));
	B = (double *)malloc(N*N*sizeof(double));
	C = (double *)malloc(N*N*sizeof(double));
	D = (double *)malloc(N*N*sizeof(double));

	for(i=0;i<N*N;i++){	// input A B
		A[i] = i+1;
		B[i] = N*N-i;
	}

	t1 = clock();
	MxM(A, B, C, N);
	t2 = clock();

	t3 = clock();
	dgemm_row(A, B, D, N);
	t4 = clock();

	printf("\n Time = %f s\n",(t2-t1)/CLOCKS_PER_SEC);
	printf(" Time_blas = %f s\n",(t4-t3)/CLOCKS_PER_SEC);
	printf(" error = %e\n\n",err(C, D, N));
/*
	printf(" C =\n");
	print_matrix(C, N);
	printf(" D =\n");
	print_matrix(D, N);
*/
	return 0;
}

void MxM(double *x, double *y, double *z, int N){
	int i, j, k;

	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			for(k=0;k<N;k++)
				z[N*i+j] = z[N*i+j]+x[N*i+k]*y[j+N*k];
		}
	}

	return;
}

void dgemm_row(double *A, double *B, double *C, int N){
	double alpha, beta;
	alpha = 1.0;
	beta = 0.0;

	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, alpha, A, N, B, N, beta, C, N);

	return;
}

double err(double *x, double *y, int N){
	int i;
	double e = 0.0;

	for(i=0;i<N*N;i++){
		if(fabs(x[i]-y[i])>e)	e = fabs(x[i]-y[i]);
	}

	return e;
}

void print_matrix(double *x, int N){
	int i;

	for(i=0;i<N*N;i++){
		printf(" %.4f  ",x[i]);
		if((i+1)%N==0)	printf("\n");
	}

	return;
}
