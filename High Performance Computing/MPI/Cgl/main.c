#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"
#include "fftw3-mpi.h"
#include <time.h>
#include <stdbool.h>
#ifndef M_PI
	const double M_PI = 4.0 * atan(1.0);
#endif

double magic_function(double a);

int main (int argc , char *argv[]) {
	// Initialize MPI 
	MPI_Init(&argc, &argv);
	// Start clock
	clock_t start = clock();

	fftw_mpi_init();

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank );

  	int size;
  	MPI_Comm_size(MPI_COMM_WORLD, &size);

	srand48((long int)time(NULL));
	fftw_plan pf, pb;

	double c1 = atoi(argv[2]);
	double c3 = atoi(argv[3]);
	double M = atoi(argv[4]);
	double L = 128.0 * M_PI;
	double T = 10000;
	double dt = T/M;
	int Tdt = (int)T/dt;

	// Allocate memory
	const ptrdiff_t N = atoi(argv[1]);
	ptrdiff_t localN, local0;	
	ptrdiff_t alloc_local = fftw_mpi_local_size_2d(N, N, MPI_COMM_WORLD, &localN , &local0);
	fftw_complex * A = fftw_alloc_complex(alloc_local);
	fftw_complex * A1 = fftw_alloc_complex(alloc_local);
	fftw_complex * A2 = fftw_alloc_complex(alloc_local);
	double* full = (double*) malloc (2*N*N* sizeof(double));   // Full Matrix	


	// Setup the initial data on the local allocation
	double dx = 2 * M_PI/N;

	for(int i = 0; i < localN; ++i) {
		double x = dx * (local0 + i);
		for(int j = 0; j < N; ++j ) {
			double y = dx * j;
			A[i * N + j][0] = 3 * drand48() - 1.5;
			// This is magic, it gives a required random number and make the MPI function work.
			A[i * N + j][1] = 3 * magic_function(drand48()+x*y) - 1.5;  
		}
	}

	for(int i = 0; i < Tdt; i++) {
		if(rank == 0)
			printf("i = %d\n", i);
		// Forward FFT
		pf = fftw_mpi_plan_dft_2d(N, N, A, A1, MPI_COMM_WORLD, FFTW_FORWARD, FFTW_ESTIMATE);
		fftw_execute(pf);
		MPI_Allgather(A1 , 2*localN*N, MPI_DOUBLE, full , 2*localN*N, MPI_DOUBLE, MPI_COMM_WORLD);


		// 2D FFT shift
		for(int i = 0; i < localN; i++) {
			for(int j = 0; j < N; j++) {
				A1[i * N + j][0] = full[(i+local0 + (local0 < N/2 ? N/2 : -N/2))*2*N+2*(j + (j < N/2 ? N/2 : -N/2))];
				A1[i * N + j][1] = full[(i+local0 + (local0 < N/2 ? N/2 : -N/2))*2*N+2*(j + (j < N/2 ? N/2 : -N/2))+1];
			}
		}

		// Update Coefficient (divide N^2, compensate for inverse FFT)
		for(int i = 0; i < localN; i++) {
			for(int j = 0; j < N; j++) {
				A1[i * N + j][0] = -A1[i * N + j][0] * ((4-i-local0) * (4-i-local0) + (4-j) * (4-j)) / (N*N);
				A1[i * N + j][1] = -A1[i * N + j][1] * ((4-i-local0) * (4-i-local0) + (4-j) * (4-j)) / (N*N);
			}
		}

		// 2D FFT shift
		MPI_Allgather(A1 , 2*localN*N, MPI_DOUBLE, full , 2*localN*N, MPI_DOUBLE, MPI_COMM_WORLD);
		for(int i = 0; i < localN; i++) {
			for(int j = 0; j < N; j++) {
				A1[i * N + j][0] = full[(i+local0 + (local0 < N/2 ? N/2 : -N/2))*2*N+2*(j + (j < N/2 ? N/2 : -N/2))];
				A1[i * N + j][1] = full[(i+local0 + (local0 < N/2 ? N/2 : -N/2))*2*N+2*(j + (j < N/2 ? N/2 : -N/2))+1];
			}
		}

		// Backward FFT
		pb = fftw_mpi_plan_dft_2d(N, N, A1, A1, MPI_COMM_WORLD, FFTW_BACKWARD, FFTW_ESTIMATE);
		fftw_execute(pb);

		// Calculate Final A1
		for(int i = 0; i < localN; i++) {
			for(int j = 0; j < N; j++) {
				A1[i*N+j][0]=A[i*N+j][0]+dt/4*(A[i*N+j][0]+((A1[i*N+j][0]-c1*A1[i*N+j][1])*(2*M_PI/L)*(2*M_PI/L))-\
					(A[i*N+j][0]*A[i*N+j][0]+A[i*N+j][1]*A[i*N+j][1])*(A[i*N+j][0]+c3*A[i*N+j][1]));
				A1[i*N+j][1]=A[i*N+j][1]+dt/4*(A[i*N+j][1]+((A1[i*N+j][1]+c1*A1[i*N+j][0])*(2*M_PI/L)*(2*M_PI/L))-\
					(A[i*N+j][0]*A[i*N+j][0]+A[i*N+j][1]*A[i*N+j][1])*(A[i*N+j][1]-c3*A[i*N+j][0]));
			}
		}	

		// Do the same thing for A1 to A2
		// Forward FFT
		pf = fftw_mpi_plan_dft_2d(N, N, A1, A2, MPI_COMM_WORLD, FFTW_FORWARD, FFTW_ESTIMATE);
		fftw_execute(pf);
		MPI_Allgather(A2 , 2*localN*N, MPI_DOUBLE, full , 2*localN*N, MPI_DOUBLE, MPI_COMM_WORLD);


		// 2D FFT shift
		for(int i = 0; i < localN; i++) {
			for(int j = 0; j < N; j++) {
				A2[i * N + j][0] = full[(i+local0 + (local0 < N/2 ? N/2 : -N/2))*2*N+2*(j + (j < N/2 ? N/2 : -N/2))];
				A2[i * N + j][1] = full[(i+local0 + (local0 < N/2 ? N/2 : -N/2))*2*N+2*(j + (j < N/2 ? N/2 : -N/2))+1];
			}
		}

		// Update Coefficient (divide N^2, compensate for inverse FFT)
		for(int i = 0; i < localN; i++) {
			for(int j = 0; j < N; j++) {
				A2[i * N + j][0] = -A2[i * N + j][0] * ((4-i-local0) * (4-i-local0) + (4-j) * (4-j)) / (N*N);
				A2[i * N + j][1] = -A2[i * N + j][1] * ((4-i-local0) * (4-i-local0) + (4-j) * (4-j)) / (N*N);
			}
		}

		// 2D FFT shift
		MPI_Allgather(A2 , 2*localN*N, MPI_DOUBLE, full , 2*localN*N, MPI_DOUBLE, MPI_COMM_WORLD);
		for(int i = 0; i < localN; i++) {
			for(int j = 0; j < N; j++) {
				A2[i * N + j][0] = full[(i+local0 + (local0 < N/2 ? N/2 : -N/2))*2*N+2*(j + (j < N/2 ? N/2 : -N/2))];
				A2[i * N + j][1] = full[(i+local0 + (local0 < N/2 ? N/2 : -N/2))*2*N+2*(j + (j < N/2 ? N/2 : -N/2))+1];
			}
		}

		// Backward FFT
		pb = fftw_mpi_plan_dft_2d(N, N, A2, A2, MPI_COMM_WORLD, FFTW_BACKWARD, FFTW_ESTIMATE);
		fftw_execute(pb);

		// Calculate Final A2
		for(int i = 0; i < localN; i++) {
			for(int j = 0; j < N; j++) {
				A2[i*N+j][0]=A[i*N+j][0]+dt/3*(A1[i*N+j][0]+((A2[i*N+j][0]-c1*A2[i*N+j][1])*(2*M_PI/L)*(2*M_PI/L))-\
					(A1[i*N+j][0]*A1[i*N+j][0]+A1[i*N+j][1]*A1[i*N+j][1])*(A1[i*N+j][0]+c3*A1[i*N+j][1]));
				A2[i*N+j][1]=A[i*N+j][1]+dt/3*(A1[i*N+j][1]+((A2[i*N+j][1]+c1*A2[i*N+j][0])*(2*M_PI/L)*(2*M_PI/L))-\
					(A1[i*N+j][0]*A1[i*N+j][0]+A1[i*N+j][1]*A1[i*N+j][1])*(A1[i*N+j][1]-c3*A1[i*N+j][0]));
			}
		}	

		// Do the same thing for A2 to A1
		// Forward FFT
		pf = fftw_mpi_plan_dft_2d(N, N, A2, A1, MPI_COMM_WORLD, FFTW_FORWARD, FFTW_ESTIMATE);
		fftw_execute(pf);
		MPI_Allgather(A1 , 2*localN*N, MPI_DOUBLE, full , 2*localN*N, MPI_DOUBLE, MPI_COMM_WORLD);


		// 2D FFT shift
		for(int i = 0; i < localN; i++) {
			for(int j = 0; j < N; j++) {
				A1[i * N + j][0] = full[(i+local0 + (local0 < N/2 ? N/2 : -N/2))*2*N+2*(j + (j < N/2 ? N/2 : -N/2))];
				A1[i * N + j][1] = full[(i+local0 + (local0 < N/2 ? N/2 : -N/2))*2*N+2*(j + (j < N/2 ? N/2 : -N/2))+1];
			}
		}

		// Update Coefficient (divide N^2, compensate for inverse FFT)
		for(int i = 0; i < localN; i++) {
			for(int j = 0; j < N; j++) {
				A1[i * N + j][0] = -A1[i * N + j][0] * ((4-i-local0) * (4-i-local0) + (4-j) * (4-j)) / (N*N);
				A1[i * N + j][1] = -A1[i * N + j][1] * ((4-i-local0) * (4-i-local0) + (4-j) * (4-j)) / (N*N);
			}
		}

		// 2D FFT shift
		MPI_Allgather(A1 , 2*localN*N, MPI_DOUBLE, full , 2*localN*N, MPI_DOUBLE, MPI_COMM_WORLD);
		for(int i = 0; i < localN; i++) {
			for(int j = 0; j < N; j++) {
				A1[i * N + j][0] = full[(i+local0 + (local0 < N/2 ? N/2 : -N/2))*2*N+2*(j + (j < N/2 ? N/2 : -N/2))];
				A1[i * N + j][1] = full[(i+local0 + (local0 < N/2 ? N/2 : -N/2))*2*N+2*(j + (j < N/2 ? N/2 : -N/2))+1];
			}
		}

		// Backward FFT
		pb = fftw_mpi_plan_dft_2d(N, N, A1, A1, MPI_COMM_WORLD, FFTW_BACKWARD, FFTW_ESTIMATE);
		fftw_execute(pb);

		// Calculate Final A1
		for(int i = 0; i < localN; i++) {
			for(int j = 0; j < N; j++) {
				A1[i*N+j][0]=A[i*N+j][0]+dt/2*(A2[i*N+j][0]+((A1[i*N+j][0]-c1*A1[i*N+j][1])*(2*M_PI/L)*(2*M_PI/L))-\
					(A2[i*N+j][0]*A2[i*N+j][0]+A2[i*N+j][1]*A2[i*N+j][1])*(A2[i*N+j][0]+c3*A2[i*N+j][1]));
				A1[i*N+j][1]=A[i*N+j][1]+dt/2*(A2[i*N+j][1]+((A1[i*N+j][1]+c1*A1[i*N+j][0])*(2*M_PI/L)*(2*M_PI/L))-\
					(A2[i*N+j][0]*A2[i*N+j][0]+A2[i*N+j][1]*A2[i*N+j][1])*(A2[i*N+j][1]-c3*A2[i*N+j][0]));
			}
		}	
		
		// Do the same thing for A1 to A
		// This is very important!!! I use A2 as a temporary storage for A, 
		// because A will be updated and the original A is rushed
		for(int i = 0; i < localN; i++) {
			for(int j = 0; j < N; j++) {
				A2[i * N + j][0] = A[i * N + j][0];
				A2[i * N + j][1] = A[i * N + j][1];
			}
		}


		// Forward FFT
		pf = fftw_mpi_plan_dft_2d(N, N, A1, A, MPI_COMM_WORLD, FFTW_FORWARD, FFTW_ESTIMATE);
		fftw_execute(pf);
		MPI_Allgather(A , 2*localN*N, MPI_DOUBLE, full , 2*localN*N, MPI_DOUBLE, MPI_COMM_WORLD);


		// 2D FFT shift
		for(int i = 0; i < localN; i++) {
			for(int j = 0; j < N; j++) {
				A[i * N + j][0] = full[(i+local0 + (local0 < N/2 ? N/2 : -N/2))*2*N+2*(j + (j < N/2 ? N/2 : -N/2))];
				A[i * N + j][1] = full[(i+local0 + (local0 < N/2 ? N/2 : -N/2))*2*N+2*(j + (j < N/2 ? N/2 : -N/2))+1];
			}
		}

		// Update Coefficient (divide N^2, compensate for inverse FFT)
		for(int i = 0; i < localN; i++) {
			for(int j = 0; j < N; j++) {
				A[i * N + j][0] = -A[i * N + j][0] * ((4-i-local0) * (4-i-local0) + (4-j) * (4-j)) / (N*N);
				A[i * N + j][1] = -A[i * N + j][1] * ((4-i-local0) * (4-i-local0) + (4-j) * (4-j)) / (N*N);
			}
		}

		// 2D FFT shift
		MPI_Allgather(A , 2*localN*N, MPI_DOUBLE, full , 2*localN*N, MPI_DOUBLE, MPI_COMM_WORLD);
		for(int i = 0; i < localN; i++) {
			for(int j = 0; j < N; j++) {
				A[i * N + j][0] = full[(i+local0 + (local0 < N/2 ? N/2 : -N/2))*2*N+2*(j + (j < N/2 ? N/2 : -N/2))];
				A[i * N + j][1] = full[(i+local0 + (local0 < N/2 ? N/2 : -N/2))*2*N+2*(j + (j < N/2 ? N/2 : -N/2))+1];
			}
		}

		// Backward FFT
		pb = fftw_mpi_plan_dft_2d(N, N, A, A, MPI_COMM_WORLD, FFTW_BACKWARD, FFTW_ESTIMATE);
		fftw_execute(pb);

		// Calculate Final A
		for(int i = 0; i < localN; i++) {
			for(int j = 0; j < N; j++) {
				A[i*N+j][0]=A2[i*N+j][0]+dt*(A1[i*N+j][0]+((A[i*N+j][0]-c1*A[i*N+j][1])*(2*M_PI/L)*(2*M_PI/L))-\
					(A1[i*N+j][0]*A1[i*N+j][0]+A1[i*N+j][1]*A1[i*N+j][1])*(A1[i*N+j][0]+c3*A1[i*N+j][1]));
				A[i*N+j][1]=A2[i*N+j][1]+dt*(A1[i*N+j][1]+((A[i*N+j][1]+c1*A[i*N+j][0])*(2*M_PI/L)*(2*M_PI/L))-\
					(A1[i*N+j][0]*A1[i*N+j][0]+A1[i*N+j][1]*A1[i*N+j][1])*(A1[i*N+j][1]-c3*A1[i*N+j][0]));
			}
		}	
	}

	// Print
	
	MPI_Allgather(A , 2*localN*N, MPI_DOUBLE, full , 2*localN*N, MPI_DOUBLE, MPI_COMM_WORLD);
	/* 
	if (rank == 0) {
		printf("\n");
		for (int i=0; i< N ; ++i ) {
			for ( int j =0; j<N; ++j ) {
				double real = full[i*2*N+2*j];
				double imag = full[i*2*N+2*j +1 ];
				printf("%4.2f%c%4.2fi\t ", real, imag >= 0 ? '+' : '-' ,fabs(imag));
			}
			printf("\n");
		}
	}
	*/
	
	fftw_destroy_plan(pf);
	fftw_destroy_plan(pb);
	fftw_free(A);
	fftw_free(A1);
	fftw_free(A2);
	free(full);

	if(rank == 0)
		printf("Elapsed time for a single pass: %g\n", (float) (clock()-start)/CLOCKS_PER_SEC);
	MPI_Finalize();	
}

double magic_function(double a) {
	a = a > 0 ? a : -a;
	while (a > 1) {
		a--;
	}
	return a;
}
