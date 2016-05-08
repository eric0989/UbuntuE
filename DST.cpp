/************************************************************
*Title:  Discrete Sine Transform (DST)                      *
*Date:   2016/05/03                                         *
************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fftw3.h>

void fft(fftw_complex *x, fftw_complex *y, int N);
void extend(fftw_complex *x, int N);
void print_complex_vector(fftw_complex *x, int N);

int main(){
	int i, N;
	fftw_complex *in, *out;
	double *dst;

	printf("\n Enter N = ");
	scanf("%d",&N);
	in = (fftw_complex *)fftw_malloc((2*N+2)*sizeof(fftw_complex));
	out = (fftw_complex *)fftw_malloc((2*N+2)*sizeof(fftw_complex));
	dst = (double *)malloc(N*sizeof(double));

	fft(in, out, N);
	printf("\n FFT in :\n");
	print_complex_vector(in, N);
	printf(" FFT out :\n");
	print_complex_vector(out, N);
	printf(" DST out :\n");
	for(i=0;i<N;i++){
		dst[i] = out[i+1][1]/(-2);
		printf(" [%d] %f\n",i,dst[i]);
	}
	printf("\n");

	return 0;
}

void fft(fftw_complex *x, fftw_complex *y, int N){
	fftw_plan plan;

	extend(x, N);
	plan = fftw_plan_dft_1d(2*N+2, x, y, FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(plan);
	fftw_destroy_plan(plan);

	return;
}

void extend(fftw_complex *x, int N){
	int i;

	x[0][0] = 0.0;
	x[N+1][0] = 0.0;
	for(i=1;i<N+1;i++)
		x[i][0] = (i-1)*1.0;
	for(i=N+2;i<2*N+2;i++)
		x[i][0] = (2*N+1-i)*(-1.0);
	for(i=0;i<2*N+2;i++)
		x[i][1] = 0.0;

	return;
}

void print_complex_vector(fftw_complex *x, int N){
	int i;

	for(i=0;i<2*N+2;i++){
		if(x[i][1]>=0.0)
			printf(" [%d] %f +%fi\n",i,x[i][0],x[i][1]);
		else
			printf(" [%d] %f %fi\n",i,x[i][0],x[i][1]);
	}
	printf("\n");

	return;
}
