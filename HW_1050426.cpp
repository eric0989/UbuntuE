/************************************************************
*Title:  matrix multiplication                              *
*Date:   2016/04/26                                         *
************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(){
  int **A, **B, **C;
  int *data;
  int N;

  printf("Enter N = ");
  scanf("%d",&N);
  A = (int **)malloc(N*sizeof(int *));
  B = (int **)malloc(N*sizeof(int *));
  data = (int*)malloc(N*N*sizeof(int));
  for(int i=0;i<N;i++){
    data[i] = 1;
    A[i] = data;
  }
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      printf("%d",A[i][j]);
    }
    printf("\n");
  }

  return 0;
}
