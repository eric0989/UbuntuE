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
double err(double *, double *, int);
double sign(double *, int);

int main(){
	double *A, *Q, *R, *X, *V, *tmp1, *tmp2, *e1 ,*B;
	int i, j, k, N;
	double tmp;

	printf("\n Enter N = ");
	scanf("%d",&N);
	A = (double *)malloc(N*N*sizeof(double));
	Q = (double *)malloc(N*N*sizeof(double));
	R = (double *)malloc(N*N*sizeof(double));
	X = (double *)malloc(N*sizeof(double));
	V = (double *)malloc(N*sizeof(double));
	tmp1 = (double *)malloc(N*sizeof(double));
	tmp2 = (double *)malloc(N*N*sizeof(double));
	e1 = (double *)malloc(N*sizeof(double));
	B = (double *)malloc(N*N*sizeof(double));

	for(i=0;i<N*N;i++){  // input A, copy A to R, and initial B
		A[i] = i;
		R[i] = i;
		B[i] = 0;
	}
	// QR-dcomposition
	for(k=0;k<N;k++){	//printf("\n\n For k = %d\n\n",k);
		e1[k] = 1;	//printf("\n X =\n");
		for(i=k;i<N;i++)/**/{
			X[i] = R[k+N*i];	//printf(" %.3f ",X[i]);
		}	//printf("\n V =\n");
		for(i=k;i<N;i++)/**/{
			V[i] = sign(X, k)*sqrt(dot(X, X, k, N))*e1[i]+X[i];
//printf(" %.3f ",V[i]);
		}	//printf("\n normal V =\n");
		tmp = sqrt(dot(V, V, k, N));
		for(i=k;i<N;i++)/**/{
			V[i] = V[i]/tmp;	//printf(" %.3f ",V[i]);
		}
		V_A(V, R, tmp1, N, k);		//printf("\n\n tmp1 =\n");	//print_matrix(tmp1, 1, N-k);
		VV_A(V, tmp1, tmp2, N, k);	//printf("\n tmp2 =\n");	//print_matrix(tmp2, N-k, N-k);
		for(i=k;i<N;i++)/**/{
			for(j=0;j<N-k;j++)/**/{
				R[k+N*i+j] = R[k+N*i+j] - 2*tmp2[k+N*i+j];
			}
		}
//printf("\n R =\n");	//print_matrix(R, N-k, N-k);	//printf("====================");
	}
//	MxM(Q, R, B, N, N, N);	// Q*R=B

	printf("\n A =\n");
	print_matrix(A, N, N);
//	printf("\n Q =\n");
//	print_matrix(Q, N, N);
	printf("\n R =\n");
	print_matrix(R, N, N);
/*	printf("\n Q*R =\n");
	print_matrix(B, N, N);
	printf("\n error = %e\n\n",err(A, B, N));
*/
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

	for(i=0;i<N;i++)	// initial tmp1
		z[i] = 0;
	for(i=k;i<N;i++)
		for(j=k;j<N;j++)
			z[i] = z[i] + x[j]*y[i+N*j];

	return;
}

void VV_A(double *x, double *y, double *z, int N, int k){
	int i, j;

	for(i=0;i<N*N;i++)	// initial tmp2
		z[i] = 0;
	for(i=k;i<N;i++)
		for(j=k;j<N;j++)
			z[N*i+j] = x[i]*y[j];

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
