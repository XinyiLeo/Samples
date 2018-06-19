/*
  Dot Product

  Program written by Leo Wu

  Editing History:

  4/24/18: Start
*/

#include <stdio.h>
#include <stdlib.h>
#include <cblas.h> 
#include <time.h>
#include <math.h>

float gaussrand()	
{				        
	float U1, U2, W, N1;
	// static number is Good to reuse the random number
	static float N2;
	static int flag = 0;

	if (flag) {
		N1 = N2;
		flag = 0;
	}
	else {
		do {
			U1 = 2.0 * drand48() - 1.0;
			U2 = 2.0 * drand48() - 1.0;
			W = U1 * U1 + U2 * U2;
		} while ( W >= 1.0 );

		W = sqrt( (-2.0 * log( W ) ) / W );
		N1 = U1 * W;
		N2 = U2 * W;
		flag = 1;
	}
	return N1 ;
}


int main(int argc, char* argv[]) 
{
	clock_t start = clock();
	double alpha = atof(argv[1]);
	double sigma = atof(argv[2]);
	int M = atoi(argv[3]);
	int N = atoi(argv[4]);
	double T = 10;
	double deltaT = T/M;
	long int seed = (long int)time(NULL);
	srand48(seed);
	double P[101] = {};
	int division = M / 100;

	for(int j = 0; j < N; j++ ) {
		double x = 0.1 * gaussrand();
		double y = 0, y_tmp;
		for(int i = 0; i < M + 1 ; i++) {
			if(i % division == 0) {
				if(sqrt((x+alpha) * (x+alpha) + y * y) <= 0.5) {
					P[i/division] += 1.0 / N;
				}
				if(sqrt((x-alpha) * (x-alpha) + y * y) <= 0.5) {
					P[i/division] += 1.0 / N;
				}
			}
			double gauss = gaussrand();
			y_tmp = y;
			y += ((alpha * alpha - x * x) * x - y) * deltaT + sigma * x * gauss * deltaT;
			x += y_tmp * deltaT;
		}
	}		
	
  	FILE *fileid = fopen("Xinyi_oscillator.o", "w");  
  	fwrite( P, sizeof(double), 101, fileid);
  	fclose(fileid);
  	fileid = fopen("Xinyi_oscillator.o", "r");
  	double read_P[101];
  	fread( read_P, sizeof(double), 101, fileid);
  	fclose(fileid);

	/*
	for(int j = 0; j < 101; j++ ) {
		printf("%lf\n", read_P[j]);
	}
	*/
	printf("Elapsed time: %g\n", (float) (clock()-start)/CLOCKS_PER_SEC);
	return 0;
}

























