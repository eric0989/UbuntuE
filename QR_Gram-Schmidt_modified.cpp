/************************************************************
* Title:  QR Factorize with Gram-Schmidt                    *
* Date:   2016/05/03                                        *
************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double dot(double *, double *, int, int, int);
void print_matrix(double *, int);
void MxM(double *, double *, double *, int);
double matrix_err(double *, double *, int);

int main(){
	double *A, *Q, *R, *tmpQ, *B;
	int i, j, k, N;
	double err;

	printf("\n Enter N = ");
	scanf("%d",&N);
	A = (double *)malloc(N*N*sizeof(double));
	Q = (double *)malloc(N*N*sizeof(double));
	R = (double *)malloc(N*N*sizeof(double));
	tmpQ = (double *)malloc(N*N*sizeof(double));
	B = (double *)malloc(N*N*sizeof(double));

	for(i=0;i<N*N;i++){  // input A and initial B
		A[i] = i;
		B[i] = 0;
	}
	// QR-dcomposition
	for(i=0;i<N*N;i++)
		tmpQ[i] = A[i];
	for(i=0;i<N;i++){
		R[i*N+i] = sqrt(dot(tmpQ, tmpQ, N, i, i));
		for(k=0;k<N;k++)
			Q[i+N*k] = tmpQ[i+N*k]/R[i*N+i];
		for(j=i+1;j<N;j++){
			R[N*i+j] = dot(Q, tmpQ, N, i, j);
			for(k=0;k<N;k++)
				tmpQ[j+N*k] = tmpQ[j+N*k]-R[N*i+j]*Q[i+N*k];
		}
	}
	MxM(Q,R,B,N);	// Q*R=B
	err = matrix_err(A, B, N);

	printf("\n A =\n");
	print_matrix(A, N);
	printf("\n Q =\n");
	print_matrix(Q, N);
	printf("\n R =\n");
	print_matrix(R, N);
	printf("\n Q*R =\n");
	print_matrix(B, N);
	printf("\n error = %e\n\n",err);

	return 0;
}

double dot(double *x, double *y, int N, int i1, int i2){
	int i;
	double dot = 0;

	for(i=0;i<N;i++)
		dot = dot + x[i*N+i1]*y[i*N+i2];

	return dot;
}

void print_matrix(double *x, int N){
	int i;

	printf("\n");
	for(i=0;i<N*N;i++){
		printf(" %.4f  ",x[i]);
		if((i+1)%N==0)	printf("\n");
	}

	return;
}

void MxM(double *x, double *y, double *z, int N){
	int i, j, k;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			for(k=0;k<N;k++)
				z[N*i+j] = z[N*i+j] + x[N*i+k]*y[j+N*k];
		}
	}

	return;
}

double matrix_err(double *x, double *y, int N){
	int i;
	double err = 0.0;

	for(i=0;i<N*N;i++)
		if(fabs(x[i]-y[i])>err)	err = fabs(x[i]-y[i]);

	return err;
}
