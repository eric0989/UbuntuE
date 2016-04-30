/************************************************************
*Title:  matrix multiplication                              *
*Date:   2016/04/26                                         *
************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(){
  double **A, **B, **C;
  int i, j, k, N;

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
      B[i][j] = N*(i+1)-j;
      C[i][j] = 0;
    }
  }
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      for(k=0;k<N;k++){
        C[i][j] = C[i][j]+A[i][k]*B[k][j];
      }
    }
  }

  printf("A =\n");
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      printf("%.2f  ",A[i][j]);
    }
    printf("\n");
  }

  printf("B =\n");
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      printf("%.2f  ",B[i][j]);
    }
    printf("\n");
  }

  printf("A*B =\n");
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      printf("%.2f  ",C[i][j]);
    }
    printf("\n");
  }

  return 0;
}
