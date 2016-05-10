/************************************************************
* Title:  Matrix Multiplication (wrong)                     *
* Date:   2016/04/26                                        *
************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(){
	double **A, **B, **C;
	double *rowA, *rowB, *tmp;
	int i, j, k, N;

	printf("\n Enter N = ");
	scanf("%d",&N);
	A = (double **)malloc(N*sizeof(double *));
	B = (double **)malloc(N*sizeof(double *));
	C = (double **)malloc(N*sizeof(double *));
	rowA = (double *)malloc(N*N*sizeof(double));
	rowB = (double *)malloc(N*N*sizeof(double));
	tmp = (double *)malloc(N*N*sizeof(double));

	for(i=0;i<N*N;i++){
		rowA[i] = i+1;
		rowB[i] = (N*N-i)*2-1;
		tmp[i] = 0;
	}
	for(i=0;i<N;i++){
		A[i] = rowA;
		rowA = rowA + N;  //rowA is a memory
	}
	for(i=0;i<N;i++){
		B[i] = rowB;
		rowB = rowB + N;
	}
	for(i=0;i<N;i++)  //initial C
		C[i] = tmp;
	printf("\n ");   //
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			C[i][j] = 0;  //reset
			for(k=0;k<N;k++)
				C[i][j] = C[i][j]+A[i][k]*B[k][j];
			printf("%.2f  ",C[i][j]);  //
		}
		printf("\n ");  //
	}

	printf("\n A =\n ");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++)
			printf("%.2f  ",A[i][j]);
		printf("\n ");
	}
	printf("\n B =\n ");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++)
			printf("%.2f  ",B[i][j]);
		printf("\n ");
	}
	printf("\n A*B =\n ");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++)
			printf("%.2f  ",C[i][j]);
		printf("\n ");
	}
	printf("\n");

	return 0;
}
