/************************************************************
* Title:  Discrete Sine Transform (DST)                     *
* Date:   2016/05/03                                        *
************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <fftw3.h>

void dst(fftw_complex *, fftw_complex *, int);
void initial(fftw_complex *, int);
void extend(fftw_complex *, int);
void fft(fftw_complex *, fftw_complex *, int);
void print_complex_vector(fftw_complex *, int);

int main(){
	int i, N;
	fftw_complex *in, *out;
	double t1, t2;

	t1 = clock();

	printf("\n Enter N = ");
	scanf("%d",&N);
	in = (fftw_complex *)fftw_malloc((2*N+2)*sizeof(fftw_complex));
	out = (fftw_complex *)fftw_malloc((2*N+2)*sizeof(fftw_complex));

	for(i=0;i<N;i++)
		in[i][0] = i*1.0;
	dst(in, out, N);
	printf("\n DST out :\n");
	for(i=0;i<N;i++)
		printf(" [%d] %f\n",i,in[i][0]);

	dst(in, out, N);
	printf("\n iDST out :\n");
	for(i=0;i<N;i++){
		in[i][0] = in[i][0]*(2.0/(N+1)); //N is int
		printf(" [%d] %f\n",i,in[i][0]);
	}

	t2 = clock();
	printf("\n Time = %f s\n\n",(t2-t1)/CLOCKS_PER_SEC);

	return 0;
}

void dst(fftw_complex *x, fftw_complex *y, int N){
	int i;

	initial(x, N);
	extend(x, N);
	fft(x, y, N);
/*
	printf("\n FFT in :\n");
	print_complex_vector(x, N);
	printf("\n FFT out :\n");
	print_complex_vector(y, N);
*/
	for(i=0;i<N;i++)
                x[i][0] = y[i+1][1]/(-2);

	return;
}

void initial(fftw_complex *x, int N){
	int i;

	for(i=0;i<2*N+2;i++)
		x[i][1] = 0.0;

	return;
}

void extend(fftw_complex *x, int N){
	int i;

	for(i=N;i>0;i--)
		x[i][0] = x[i-1][0];
	x[0][0] = 0.0;
	x[N+1][0] = 0.0;
	for(i=N+2;i<2*N+2;i++)
		x[i][0] = -x[2*N+2-i][0];

	return;
}

void fft(fftw_complex *x, fftw_complex *y, int N){
	fftw_plan plan;

	plan = fftw_plan_dft_1d(2*N+2, x, y, FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(plan);
	fftw_destroy_plan(plan);

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

	return;
}
