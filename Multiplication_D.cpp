/************************************************************
*Title:  Matrix Multiplication with Double Index            *
*Date:   2016/04/26                                         *
************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main(){
  double **A, **B, **C;
  int i, j, k, N;
  double t1, t2;

  t1 = clock();

  printf("Enter N = ");
  scanf("%d",&N);
  A = (double **)malloc(N*sizeof(double *));
  B = (double **)malloc(N*sizeof(double *));
  C = (double **)malloc(N*sizeof(double *));
  for(i=0;i<N;i++){
    A[i] = (double *)malloc(N*sizeof(double));
    B[i] = (double *)malloc(N*sizeof(double));
    C[i] = (double *)malloc(N*sizeof(double));
  }

  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      A[i][j] = N*i+j+1;
      B[i][j] = 2*N*N-(i+1)*(2*j+1)+1;
      C[i][j] = 0;
    }
  }
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      for(k=0;k<N;k++)
        C[i][j] = C[i][j]+A[i][k]*B[k][j];
    }
  }

  printf("\nA =\n");
  for(i=0;i<N;i++){
    for(j=0;j<N;j++)
      printf("%.2f  ",A[i][j]);
    printf("\n");
  }
  printf("\nB =\n");
  for(i=0;i<N;i++){
    for(j=0;j<N;j++)
      printf("%.2f  ",B[i][j]);
    printf("\n");
  }
  printf("\nA*B =\n");
  for(i=0;i<N;i++){
    for(j=0;j<N;j++)
      printf("%.2f  ",C[i][j]);
    printf("\n");
  }

  t2 = clock();
  printf("\nTime = %f s\n",(t2-t1)/CLOCKS_PER_SEC);

  return 0;
}
