/************************************************************
* Title:  Matrix Multiplication with Single Index           *
* Date:   2016/04/26                                        *
************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main(){
	double *A, *B, *C;
	int i, j, k, N;
	double t1, t2;

	t1 = clock();

	printf("\n Enter N = ");
	scanf("%d",&N);
	A = (double *)malloc(N*N*sizeof(double));
	B = (double *)malloc(N*N*sizeof(double));
	C = (double *)malloc(N*N*sizeof(double));

	for(i=0;i<N*N;i++){
		A[i] = i+1;
		B[i] = N*N-i;
		C[i] = 0;
	}
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			for(k=0;k<N;k++)
				C[N*i+j] = C[N*i+j]+A[N*i+k]*B[j+N*k];
		}
		}

	printf("\n A =\n ");
	for(i=0;i<N*N;i++){
		printf("%.2f  ",A[i]);
		if((i+1)%N==0)
			printf("\n ");
	}
	printf("\n B =\n ");
	for(i=0;i<N*N;i++){
		printf("%.2f  ",B[i]);
		if((i+1)%N==0)
			printf("\n ");
	}
	printf("\n C =\n ");
	for(i=0;i<N*N;i++){
		printf("%.2f  ",C[i]);
		if((i+1)%N==0)
			printf("\n ");
	}

	t2 = clock();
	printf("\n Time = %f s\n\n",(t2-t1)/CLOCKS_PER_SEC);

	return 0;
}
