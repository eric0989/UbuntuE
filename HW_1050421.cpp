/************************************************************
*Title:  Dynamic Array, Dot, Norm, Translation              *
*Date:   2016/04/21                                         *
************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(){
  double *A, *B, *C, dot=0, normA=0, normB=0;
  int N;

  printf("Enter N = ");
  scanf("%d",&N);
  A = (double *)malloc(N*sizeof(double));
  B = (double *)malloc(N*sizeof(double));
  C = (double *)malloc(N*sizeof(double));

  for(int i=0;i<N;i++){
    A[i] = sin(i);
    B[i] = cos(i);
    dot = dot + A[i]*B[i];
    normA = normA + A[i]*A[i];
    normB = normB + B[i]*B[i];
    C[i] =  A[i] - B[i];
  }

  normA = sqrt(normA);
  normB = sqrt(normB);
  printf("A[i] = sin(i), i=1,2,...,%d\n",N);
  printf("B[i] = cos(i), i=1,2,...,%d\n",N);
  printf("(1) A*B = %f\n",dot);
  printf("(2) normA = %f\n",normA);
  printf("    normB = %f\n",normB);
  printf("(3) A-B =\n");
  for(int i=0;i<N;i++){
    printf("\t%f\n",C[i]);
  }
  return 0;
}
