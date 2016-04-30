# include <stdio.h>
# include <math.h>
# include <stdlib.h>

int main(){
  int A[3][3] = {{0,1,2},{0,1,2},{0,1,2}};
  int B[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
  int C[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      for(int k=0;k<3;k++){
        C[i][j] = C[i][j]+A[i][k]*B[k][j];
      }
      printf("%d ",C[i][j]);
    }
  printf("\n");
  }


  return 0;
}
