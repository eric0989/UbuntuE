/************************************************************
* Title:  Matrix Multiplication with Single Pointer         *
* Date:   2016/04/26                                        *
************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void MxM(double *, double *, double *, int);
void print_matrix(double *, int);

int main(){
	double *A, *B, *C;
	int i, N;
	double t1, t2;

	printf("\n Enter N = ");
	scanf("%d",&N);
	A = (double *)malloc(N*N*sizeof(double));
	B = (double *)malloc(N*N*sizeof(double));
	C = (double *)malloc(N*N*sizeof(double));

	for(i=0;i<N*N;i++){	// input value in matrix A,B,C
		A[i] = i+1;
		B[i] = N*N-i;
		C[i] = 0;
	}

	t1 = clock();	//
	MxM(A, B, C, N);
	t2 = clock();	//

	printf("\n A =\n ");
	print_matrix(A, N);
	printf("\n B =\n ");
	print_matrix(B, N);
	printf("\n C =\n ");
	print_matrix(C, N);

	printf("\n matrix multiplication time = %f s\n\n",(t2-t1)/CLOCKS_PER_SEC);

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

void print_matrix(double *x, int N){
	int i;

	for(i=0;i<N*N;i++){
		printf("%.2f  ",x[i]);
		if((i+1)%N==0)
			printf("\n ");
	}

	return;
}
