/************************************************************
* Title:  QR Decomposition with Householder                 *
* Date:   2016/05/11                                        *
************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void QR_R(double *, double *, double *, double *, double *, double *, double *, int);
void QR_Q(double *, double *, double *, double *, double *, int);
double dot(double *, double *, int, int);
void print_matrix(double *, int, int);
void v_A(double *, double *, double *, int, int);
void vv_A(double *, double *, double *, int, int);
void MxM(double *, double *, double *, int);
double err(double *, double *, int);
double sign(double *, int);
void output(double *, double *, double *, double *, int);

int main(){
	double *A, *Q, *R, *X, *v, *tmpV, *tmp1, *tmp2, *e1, *B;
	int i, j, k, N;

	printf("\n Enter N = ");
	scanf("%d",&N);
	A = (double *)malloc(N*N*sizeof(double));
	Q = (double *)malloc(N*N*sizeof(double));
	R = (double *)malloc(N*N*sizeof(double));
	X = (double *)malloc(N*sizeof(double));
	v = (double *)malloc(N*sizeof(double));
	tmpV = (double *)malloc(N*N*sizeof(double));
	tmp1 = (double *)malloc(N*sizeof(double));
	tmp2 = (double *)malloc(N*N*sizeof(double));
	e1 = (double *)malloc(N*sizeof(double));
	B = (double *)malloc(N*N*sizeof(double));

	for(i=0;i<N*N;i++){	// input A and copy A to R
		A[i] = i+1;
		R[i] = A[i];
	}

	QR_R(R, X, v, tmpV, tmp1, tmp2, e1, N);	// complete R
	QR_Q(Q, v, tmpV, tmp1, tmp2, N);	// complete Q
	MxM(Q, R, B, N);	// Q*R=B
	output(A, Q, R, B, N);

	return 0;
}

void QR_R(double *R, double *X, double *v, double *tmpV, double *tmp1, double *tmp2, double *e1, int N){
	int k, i, j;
	double tmp;

	for(k=0;k<N;k++){
		e1[k] = 1;
		for(i=k;i<N;i++)        // take column
			X[i] = R[k+N*i];

		for(i=k;i<N;i++)
			v[i] = sign(X, k)*sqrt(dot(X, X, k, N))*e1[i]+X[i];

		tmp = sqrt(dot(v, v, k, N));    // take norm(v)
		for(i=k;i<N;i++)        // normalize v
			v[i] = v[i]/tmp;

		v_A(v, R, tmp1, N, k);
		vv_A(v, tmp1, tmp2, N, k);
		for(i=k;i<N;i++)
			for(j=k;j<N;j++)
				R[N*i+j] = R[N*i+j] - 2*tmp2[N*i+j];

		for(i=k;i<N;i++)        // store v into tmpV
			tmpV[k+N*i] = v[i];
	}

	return;
}

void QR_Q(double *Q, double *v, double *tmpV, double *tmp1, double *tmp2, int N){
	int k, i, j;

	for(i=0;i<N;i++)	// identity Q
		Q[N*i+i] = 1;

	for(k=N-1;k>=0;k--){
		for(i=k;i<N;i++)
			v[i] = tmpV[k+N*i];
		v_A(v, Q, tmp1, N, k);
		vv_A(v, tmp1, tmp2, N, k);
		for(i=k;i<N;i++)
			for(j=k;j<N;j++)
				Q[N*i+j] = Q[N*i+j] - 2*tmp2[N*i+j];
	}

	return;
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

void v_A(double *x, double *y, double *z, int N, int k){
	int i, j;

	for(i=0;i<N;i++)	// clear tmp1
		z[i] = 0;
	for(i=k;i<N;i++)
		for(j=k;j<N;j++)
			z[i] = z[i] + x[j]*y[i+N*j];

	return;
}

void vv_A(double *x, double *y, double *z, int N, int k){
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

void output(double *A, double *Q, double *R, double *B, int N){
	printf("\n A =\n");
	print_matrix(A, N, N);
	printf("\n Q =\n");
	print_matrix(Q, N, N);
	printf("\n R =\n");
	print_matrix(R, N, N);
	printf("\n Q*R =\n");
	print_matrix(B, N, N);
	printf("\n error = %e\n\n",err(A, B, N));

	return;
}
