/************************************************************
*Title:  matrix multiplication                              *
*Date:   2016/04/26                                         *
************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(){
  double **A, **B, **C;
  double *rowA, *rowB, *tem;
  int i, j, k, N;

  printf("Enter N = ");
  scanf("%d",&N);
  A = (double **)malloc(N*sizeof(double *));
  B = (double **)malloc(N*sizeof(double *));
  C = (double **)malloc(N*sizeof(double *));
  rowA = (double *)malloc(N*N*sizeof(double));
  rowB = (double *)malloc(N*N*sizeof(double));
  tem = (double *)malloc(N*N*sizeof(double));
  for(i=0;i<N;i++){
    rowA[i] = i;
    A[i] = rowA;
  }
  for(i=0;i<N;i++){
    rowB[i] = 1;
    B[i] = rowB;
  }
  for(i=0;i<N;i++){
    tem[i] = 0;
    C[i] = tem;
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
      printf("%f  ",A[i][j]);
    }
    printf("\n");
  }

  printf("B =\n");
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      printf("%f  ",B[i][j]);
    }
    printf("\n");
  }

  printf("A*B =\n");
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      printf("%f  ",C[i][j]);
    }
    printf("\n");
  }

  return 0;
}
