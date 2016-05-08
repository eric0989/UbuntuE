/************************************************************
*Title:  Discrete Sine Transform (DST)                      *
*Date:   2016/05/03                                         *
************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fftw3.h>

void initial(fftw_complex *x, int N);
void print_complex_vector(fftw_complex *x, int N);

int main(){
	int N;
	fftw_complex *in, *out;
	fftw_plan plan;

	printf("\n Enter N = ");
	scanf("%d",&N);
	in = (fftw_complex *)fftw_malloc(N*sizeof(fftw_complex));
	out = (fftw_complex *)fftw_malloc(N*sizeof(fftw_complex));

	initial(in, N);
	printf(" in :\n");
	print_complex_vector(in, N);

	plan = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(plan);
	fftw_destroy_plan(plan);

	printf(" out :\n");
	print_complex_vector(out, N);

	return 0;
}

void initial(fftw_complex *x, int N){
	int i;

	for(i=0;i<N;i++){
		x[i][0] = i*1.0;
		x[i][1] = 0.0;
	}

	return;
}

void print_complex_vector(fftw_complex *x, int N){
	int i;

	for(i=0;i<N;i++){
		if(x[i][1]>=0.0)
			printf(" [%d] %f +%fi\n",i,x[i][0],x[i][1]);
		else
			printf(" [%d] %f %fi\n",i,x[i][0],x[i][1]);
	}
	printf("\n");

	return;
}
