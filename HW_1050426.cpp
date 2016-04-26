/************************************************************
*Title:  matrix multiplication                              *
*Date:   2016/04/26                                         *
************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(){
  int **A, **B, **C, *data;
  int N;

  printf("Enter N = ");
  scanf("%d",&N);
  A = (int **)malloc(N*sizeof(int *));
  data = (int*)malloc(N*N*sizeof(int));
  for(int i=0;i<N;i++,data+=N){
    A[i] = data;
  }
  for(int i=0;i<N;i++){
  printf("%d",A[i]);
  }


  return 0;
}
