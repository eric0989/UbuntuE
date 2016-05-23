#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void print_matrix(int X[], int, int);

int main(){
	int i, j, k, p, q, r;
	p = 2;
	q = 3;
	r = 4;
	int A[6] = {1, 2, 0, -2, 3, 2};
	int B[12] = {4, 0, 1, 1, 1, -2, -3, 1, -1, 3, 0, 3};
	int C[8] ={0};

	for(i=0;i<p;i++){
		for(j=0;j<r;j++){
			for(k=0;k<q;k++)
				C[r*i+j] = C[r*i+j]+A[q*i+k]*B[j+r*k];
		}
	}
	printf("\n A =\n");
	print_matrix(A, p, q);
	printf("\n B =\n");
	print_matrix(B, q, r);
	printf("\n C =\n");
	print_matrix(C, p, r);
	printf("\n");

	return 0;
}

void print_matrix(int X[], int m, int n){
	int i;

	for(i=0;i<m*n;i++){
		printf("   %d",X[i]);
		if((i+1)%n==0)	printf("\n");
	}

	return;
}

