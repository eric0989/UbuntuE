/************************************************************
* Title:  QR Factorize with Householder                     *
* Date:   2016/05/11                                        *
************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double dot(double *, double *, int, int);
void print_matrix(double *, int, int);
void V_A(double *, double *, double *, int, int);
void VV_A(double *, double *, double *, int, int);
void MxM(double *, double *, double *, int);
double err(double *, double *, int);
double sign(double *, int);

int main(){
	double *A, *Q, *tmpQ, *R, *X, *V, *tmp1, *tmp2, *e1 ,*B;
	int i, j, k, N;
	double tmp;

	printf("\n Enter N = ");
	scanf("%d",&N);
	A = (double *)malloc(N*N*sizeof(double));
	Q = (double *)malloc(N*N*sizeof(double));
	tmpQ = (double *)malloc(N*N*sizeof(double));
	R = (double *)malloc(N*N*sizeof(double));
	X = (double *)malloc(N*sizeof(double));
	V = (double *)malloc(N*sizeof(double));
	tmp1 = (double *)malloc(N*sizeof(double));
	tmp2 = (double *)malloc(N*N*sizeof(double));
	e1 = (double *)malloc(N*sizeof(double));
	B = (double *)malloc(N*N*sizeof(double));

	for(i=0;i<N*N;i++){  // input A, copy A to R, and initial B
		A[i] = i+1;
		R[i] = A[i];
		tmpQ[i] = 0;
		B[i] = 0;
	}
	for(i=0;i<N;i++)
		tmpQ[N*i+i] = 1;
	// QR-dcomposition
	for(k=0;k<N;k++){
		e1[k] = 1;
		for(i=k;i<N;i++)	// take column
			X[i] = R[k+N*i];

		for(i=k;i<N;i++)
			V[i] = sign(X, k)*sqrt(dot(X, X, k, N))*e1[i]+X[i];

		tmp = sqrt(dot(V, V, k, N));
		for(i=k;i<N;i++)	// normalize V
			V[i] = V[i]/tmp;

		V_A(V, R, tmp1, N, k);
		VV_A(V, tmp1, tmp2, N, k);
		for(i=k;i<N;i++)
			for(j=0;j<N-k;j++)
				R[k+N*i+j] = R[k+N*i+j] - 2*tmp2[k+N*i+j];

		V_A(V, tmpQ, tmp1, N, k);
		VV_A(V, tmp1, tmp2, N, k);
		for(i=k;i<N;i++)
			for(j=k;j<N;j++)
				tmpQ[N*i+j] = tmpQ[N*i+j] - 2*tmp2[N*i+j];
	}
	for(i=0;i<N;i++)	// transpose
		for(j=0;j<N;j++)
			Q[N*i+j] = tmpQ[i+N*j];

	MxM(Q, R, B, N);	// Q*R=B

	printf("\n A =\n");
	print_matrix(A, N, N);
	printf("\n Q =\n");
	print_matrix(Q, N, N);
	printf("\n R =\n");
	print_matrix(R, N, N);
	printf("\n Q*R =\n");
	print_matrix(B, N, N);
	printf("\n error = %e\n\n",err(A, B, N));

	return 0;
}

double dot(double *x, double *y, int k, int N){
	int i;
	double dot = 0.0;

	for(i=k;i<N;i++)
		dot = dot + x[i]*y[i];

	return dot;
}

void print_matrix(double *x, int m, int n){
	int i;

	printf("\n");
	for(i=0;i<m*n;i++){
		printf(" %.3f  ",x[i]);
		if((i+1)%n==0)	printf("\n");
	}

	return;
}

void V_A(double *x, double *y, double *z, int N, int k){
	int i, j;

	for(i=0;i<N;i++)	// clear tmp1
		z[i] = 0;
	for(i=k;i<N;i++)
		for(j=k;j<N;j++)
			z[i] = z[i] + x[j]*y[i+N*j];

	return;
}

void VV_A(double *x, double *y, double *z, int N, int k){
	int i, j;

	for(i=0;i<N*N;i++)	// clear tmp2
		z[i] = 0;
	for(i=k;i<N;i++)
		for(j=k;j<N;j++)
			z[N*i+j] = x[i]*y[j];

	return;
}

void MxM(double *x, double *y, double *z, int N){
	int i, j, k;

	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
			for(k=0;k<N;k++)
				z[N*i+j] = z[N*i+j] + x[N*i+k]*y[j+N*k];

	return;
}

double err(double *x, double *y, int N){
	int i;
	double e = 0.0;

	for(i=0;i<N*N;i++)
		if(fabs(x[i]-y[i])>e)	e = fabs(x[i]-y[i]);

	return e;
}

double sign(double *x, int k){
	if(x[k]>=0)	return 1.0;
	else		return -1.0;
}
