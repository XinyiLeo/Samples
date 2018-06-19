/*
  Source and Sink Equation 

  Editing History:

  6/5/18: Initial draft
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <complex.h>
#include "mpi.h"  

#ifndef M_PI
	const double M_PI = 4.0 * atan(1.0);
#endif
/*

	Source and Sink

	Input: N, omega, tol 
        Output: The grid of its final version

	Description: The grid has [-2,2] * [-1,1] range, 
			it's divided into N * (2N - 1) grids.
			The idea in MPI is to evenly divide into (N/d) * (2N-1) strips
	Use gather to gather all information

	Initial Setup: The middle strip have two extra rows, one up and one down.
			The bottommost and upmost row has one extra row
		

*/

int main(int argc, char* argv[])
{
	
	MPI_Init(&argc, &argv); 

	int rank;
  	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  	int size;
  	MPI_Comm_size(MPI_COMM_WORLD, &size);

	// Start clock for a single pass
	if(rank == 0) 
		clock_t start = clock();

	// Initialization
	int N = atoi(argv[1]); 
	double omega = atof(argv[2]); 
	double tol = atof(argv[3]);

	/* 
	   allocate memory.  Each core should have roughly (N/size+2)*(2N-1) grid points, but if N is not
  	   evenly divisible by size, give one extra grid point to the low ranks to make up the
  	   difference.  Also, the rank=0 and rank=size-1 processes do not have to store boundary
 	   data for a neighbor.

	   Express the grid as y*(2N-1)+x , x in [0, 2N-2], y in [0, N-1], local y in grid [N/size*rank, N/size*(rank+1)-1]
	   Every strip is divided into checkertboard type, update the red point, then update black point, and then gather them all.
	*/

	double dx = 2. / (N - 1);
	int localN = N/size + (N%size > rank ? 1 : 0);
	
  	double* localu = (double*)malloc(localN * (2 * N - 1) * sizeof(double));  
	double* u = (double*)malloc(N * (2 * N - 1) * sizeof(double)); 
	double* g = (double*)malloc(N * (2 * N - 1) * sizeof(double)); 
	double* maxresidset = (double*)malloc(size * sizeof(double)); 

	// Initialize the data
	double lambda = 100.;
  	int i, j;
	int g_x, g_y;
	double maxresid = 1 + tol;
	int iter = 0;
	double resid;
	int baseidx; // Baseline index for reference
	int W = 2*N-1; // column number

	// Assign value for g(x,y)
	for (i=0; i < N * W; ++i) {
		g_x = i % W;
		g_y = (i - g_x) / W;
		g[i] = 10. * lambda / sqrt(M_PI) * (exp(-lambda * lambda * ((-3+dx*g_x)*(-3+dx*g_x)+(-1+dx*g_y)*(-1+dx*g_y))) \
			- exp(-lambda * lambda * ((-1+dx*g_x)*(-1+dx*g_x)+(-1+dx*g_y)*(-1+dx*g_y))));  
		u[i] = 0.;
	}

	// Start update in loop
	while(iter < 10000 && maxresid > tol) {
		maxresid = 0;
		baseidx = rank*N/size*W;

		// Update the red: i % 2 == 0, then black
		for(j = 0; j < 2; j++) {
			for(i = 0; i < localN * W; ++i) {
				if(i % 2 == j) {
					g_x = i % W;
					g_y = (i - g_x) / W;

					// Consider three different cases
					if(!(rank == 0 && g_y ==0) && !(rank==size-1 && g_y==N/size-1)) {
						if(g_x == 0) {
							resid = 0.25*(u[baseidx+g_x+W*(g_y+1)]+u[baseidx+g_x+W*(g_y-1)] \
								+u[baseidx+(g_x+1)+W*g_y]-3*u[baseidx+g_x+W*g_y])-dx*dx/4*g[baseidx+g_x+W*g_y]; 
						}
						else if(g_x == W - 1) {
							resid = 0.25*(u[baseidx+g_x+W*(g_y+1)]+u[baseidx+g_x+W*(g_y-1)] \
								+u[baseidx+(g_x-1)+W*g_y]-3*u[baseidx+g_x+W*g_y])-dx*dx/4*g[baseidx+g_x+W*g_y]; 
						}
						else {
							resid = 0.25*(u[baseidx+g_x+W*(g_y+1)]+u[baseidx+g_x+W*(g_y-1)]+u[baseidx+(g_x-1)+W*g_y] \
								+u[baseidx+(g_x+1)+W*g_y]-4*u[baseidx+g_x+W*g_y])-dx*dx/4*g[baseidx+g_x+W*g_y]; 
						}
						if(resid > 10)
							printf("%lf\n", resid);
						maxresid = maxresid > resid ? maxresid : resid;
						localu[i] = localu[i] + omega * resid;
						u[baseidx+g_x+W*g_y] = u[baseidx+g_x+W*g_y] + omega * resid;
					}
				}
			}
		}
		// Gather all together
		MPI_Allgather(localu , localN*W, MPI_DOUBLE, u, localN*W, MPI_DOUBLE, MPI_COMM_WORLD);
		MPI_Allgather(&maxresid , 1, MPI_DOUBLE, maxresidset, 1, MPI_DOUBLE, MPI_COMM_WORLD); // Find the maximum tolerance

		double tmp = 0;
		for(i = 0; i < size; i++) {
			tmp = tmp > maxresidset[i] ? tmp : maxresidset[i];
		}
		maxresid = tmp;
		iter = iter + 1;
	}

	if(rank == 0)
		printf("final round = %d\n", iter);

	free(localu);
	free(u);
	free(g);
	free(maxresidset); 
	
	// End Clock
	if(rank == 0)
		printf("Elapsed time for a single pass: %g\n", (float) (clock()-start)/CLOCKS_PER_SEC);
	
	MPI_Finalize();
  	return 0;
}


























