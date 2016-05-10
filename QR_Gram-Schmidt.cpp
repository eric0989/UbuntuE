/************************************************************
* Title:  QR Factorize with Gram-Schmidt                    *
* Date:   2016/05/03                                        *
************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void print_tr2D(double **, int);
double dot(double **, double **, int, int, int);

int main(){
	double *A, **Q, **tmpQ, *R, **col;
	int i, j, k, N;

	printf("\n Enter N = ");
	scanf("%d",&N);
	A = (double *)malloc(N*N*sizeof(double));
	Q = (double **)malloc(N*sizeof(double *));
	tmpQ = (double **)malloc(N*sizeof(double *));
	R = (double *)malloc(N*N*sizeof(double));
	col = (double **)malloc(N*sizeof(double *));
	for(i=0;i<N;i++){
		Q[i] = (double *)malloc(N*sizeof(double));
		tmpQ[i] = (double *)malloc(N*sizeof(double));
		col[i] = (double *)malloc(N*sizeof(double));
	}

	for(i=0;i<N*N;i++)
		A[i] = i+1;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++)
			col[i][j] = A[N*j+i];
	}
	printf("\n transpose col =\n");
	print_tr2D(col,N);
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			Q[i][j] = col[i][j];
		}
	}
	for(i=1;i<N;i++){
		for(j=0;j<N;j++){
			for(k=0;k<i;k++)
Q[i][j] = Q[i][j]-dot(col,Q,N,i,k)/dot(Q,Q,N,k,k)*Q[k][j];
		}
	}
	for(i=0;i<N;i++){
		for(j=0;j<N;j++)
tmpQ[i][j] = Q[i][j]/sqrt(dot(Q,Q,N,i,i));
	}

	printf("\n Q =\n");
	print_tr2D(tmpQ,N);

	printf("\n");
	return 0;
}

void print_tr2D(double **x, int N){
	int i, j;

	printf("\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++)
			printf(" %.4f   ",x[j][i]);
		printf("\n");
	}

	return;
}

double dot(double **x,double **y, int N, int i1, int i2){
	int j;
	double dot = 0;

	for(j=0;j<N;j++)
		dot = dot+x[i1][j]*y[i2][j];

	return dot;
}
