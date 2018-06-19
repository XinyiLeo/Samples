#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <cuda.h>
#include <cuda_runtime.h>

#ifndef M_PI
	#define M_PI 3.1415926535897932384626433832795
#endif

const int threadsPerBlock = 256;

__device__ static int dev_N;
__device__ static double dev_omega;
__device__ static int dev_gridN;
__device__ static double dev_dx;
texture<int2, cudaTextureType1D, cudaReadModeElementType> tex_u;
texture<int2, cudaTextureType1D, cudaReadModeElementType> tex_g;

__global__ void diff(double* u, double* du, int* row);
__global__ void diffb(double* u, double* du, int* row);

// Sorry for no time to add comment, the update is a combination of red black and rows

int main(int argc, char* argv[]) {
	clock_t start = clock();
	int N = atoi(argv[1]);
	double omega = atof(argv[2]);
	double tol = atof(argv[3]);
	int gridN = N * (2*N-1);
  	const int blocksPerGrid = gridN/threadsPerBlock + (gridN %threadsPerBlock > 0 ? 1 : 0);
  	double* u = (double*)malloc(gridN*sizeof(double));
	double* g = (double*)malloc(gridN*sizeof(double));
  	double* du = (double*)malloc(gridN*sizeof(double));
	double lambda = 100.0;
	double dx = 2.0 / (N-1);
	double maxresid = 0;
	int row = 6;

  	double* dev_u;
	double* dev_g;
  	double* dev_du;
	int* dev_row;

  	cudaMalloc((void**)&dev_u, gridN*sizeof(double));
	cudaMalloc((void**)&dev_g, gridN*sizeof(double));
  	cudaMalloc((void**)&dev_du, gridN*sizeof(double));
	cudaMalloc((void**)&dev_row, sizeof(int));

	// Initialize grid
  	for (int x=0; x<2*N-1; x++) {
		for (int y=0; y<N; y++) {
    			u[x * N + y] = 0;
			g[x * N + y] = 10.0 * lambda / sqrt(M_PI) * (exp(-lambda * lambda * ((-3+dx*x)*(-3+dx*x)+(-1+dx*y)*(-1+dx*y))) \
				- exp(-lambda * lambda * ((-1+dx*x)*(-1+dx*x)+(-1+dx*y)*(-1+dx*y))));  
		}
	}

	// Start Loop
	int iter = 0;
	while(iter < 1000) {
		for(int i = 0; i < gridN; i++) {
			du[i] = 0;
		}
		for(row = 0; row < 2*N-1; row ++) {
			cudaMemcpyToSymbol(dev_N, &N, sizeof(int));
		  	cudaMemcpyToSymbol(dev_gridN, &gridN, sizeof(int));
			cudaMemcpyToSymbol(dev_omega, &omega, sizeof(double));
		  	cudaMemcpyToSymbol(dev_dx, &dx, sizeof(double));
			cudaMemcpy(dev_row, &row, sizeof(int), cudaMemcpyHostToDevice);
		  	cudaMemcpy(dev_u, u, gridN*sizeof(double), cudaMemcpyHostToDevice);
			cudaMemcpy(dev_g, g, gridN*sizeof(double), cudaMemcpyHostToDevice);

		  	cudaBindTexture(NULL, tex_u, dev_u, gridN*sizeof(double));
			cudaBindTexture(NULL, tex_g, dev_g, gridN*sizeof(double));

		  	diff<<<blocksPerGrid, threadsPerBlock>>>(dev_u, dev_du, dev_row);

		  	cudaMemcpy(u, dev_u, gridN*sizeof(double), cudaMemcpyDeviceToHost);
			cudaMemcpy(du, dev_du, gridN*sizeof(double), cudaMemcpyDeviceToHost);
			cudaUnbindTexture(tex_u);
			cudaUnbindTexture(tex_g);

			cudaMemcpyToSymbol(dev_N, &N, sizeof(int));
		  	cudaMemcpyToSymbol(dev_gridN, &gridN, sizeof(int));
			cudaMemcpyToSymbol(dev_omega, &omega, sizeof(double));
		  	cudaMemcpyToSymbol(dev_dx, &dx, sizeof(double));
			cudaMemcpy(dev_row, &row, sizeof(int), cudaMemcpyHostToDevice);
		  	cudaMemcpy(dev_u, u, gridN*sizeof(double), cudaMemcpyHostToDevice);
			cudaMemcpy(dev_g, g, gridN*sizeof(double), cudaMemcpyHostToDevice);

		  	cudaBindTexture(NULL, tex_u, dev_u, gridN*sizeof(double));
			cudaBindTexture(NULL, tex_g, dev_g, gridN*sizeof(double));

		  	diffb<<<blocksPerGrid, threadsPerBlock>>>(dev_u, dev_du, dev_row);

		  	cudaMemcpy(u, dev_u, gridN*sizeof(double), cudaMemcpyDeviceToHost);
			cudaMemcpy(du, dev_du, gridN*sizeof(double), cudaMemcpyDeviceToHost);
			cudaUnbindTexture(tex_u);
			cudaUnbindTexture(tex_g);
		}
		
		maxresid = 0;
		for(int i = 0; i < gridN; i++) { 
	 		maxresid = maxresid > du[i] ? maxresid : du[i];
		}
		if(maxresid < tol)
			break;
		iter ++;
	}
	printf("The final round is: %d", iter);
	// End

  	cudaFree(dev_u);
	cudaFree(dev_g);
  	cudaFree(dev_du);
  	free(u);
	free(g);
  	free(du);
	printf("Elapsed time: %g\n", (float) (clock()-start)/CLOCKS_PER_SEC);
  	return 0;
}

__global__ void diff(double* u, double* du, int* row) {
	// Note up is uu
  	int g_i = (threadIdx.x + blockIdx.x * blockDim.x) % dev_gridN;
		int g_y = g_i % dev_N;
		int g_x = (g_i - g_y) / dev_N;
	  	int g_iu = g_i-dev_N;
	  	int g_id = g_i+dev_N;
	  	int g_il = g_i-1;
	  	int g_ir = g_i+1;
		double resid;
		int2 m_int2 = tex1Dfetch(tex_u, g_i);
	  	double m = __hiloint2double(m_int2.y, m_int2.x);
		int2 gm_int2 = tex1Dfetch(tex_g, g_i);	
		double gm = __hiloint2double(gm_int2.y, gm_int2.x);
		if(g_x == *row && g_i % 2==0) {
			if(g_y != 0 and g_y != dev_N-1) {
				int2 r_int2 = tex1Dfetch(tex_u, g_ir);
				int2 l_int2 = tex1Dfetch(tex_u, g_il);
		  		double r = __hiloint2double(r_int2.y, r_int2.x);
		  		double l = __hiloint2double(l_int2.y, l_int2.x);
				if(g_x == 0) {
					int2 d_int2 = tex1Dfetch(tex_u, g_id);
		  			double d = __hiloint2double(d_int2.y, d_int2.x);
					resid = 0.25*(l+r+d-3*m)-dev_dx*dev_dx/4*gm;
					u[g_i] += dev_omega * resid;
				}
				else if(g_x == 2*dev_N-1) {
					int2 uu_int2 = tex1Dfetch(tex_u, g_iu);
		  			double uu = __hiloint2double(uu_int2.y, uu_int2.x);
					resid = 0.25*(l+r+uu-3*m)-dev_dx*dev_dx/4*gm;
					u[g_i] += dev_omega * resid;
				}
				else {
					int2 uu_int2 = tex1Dfetch(tex_u, g_iu);
		  			double uu = __hiloint2double(uu_int2.y, uu_int2.x);
					int2 d_int2 = tex1Dfetch(tex_u, g_id);
		  			double d = __hiloint2double(d_int2.y, d_int2.x);
					resid = 0.25*(l+r+uu+d-4*m)-dev_dx*dev_dx/4*gm;
					u[g_i] += dev_omega * resid;	
				}
				du[g_i] = resid;			
			}
			else {
				du[g_i] = 0;
			}
		}
}


__global__ void diffb(double* u, double* du, int* row) {
	// Note up is uu
  	int g_i = (threadIdx.x + blockIdx.x * blockDim.x) % dev_gridN;
		int g_y = g_i % dev_N;
		int g_x = (g_i - g_y) / dev_N;
	  	int g_iu = g_i-dev_N;
	  	int g_id = g_i+dev_N;
	  	int g_il = g_i-1;
	  	int g_ir = g_i+1;
		double resid;
		int2 m_int2 = tex1Dfetch(tex_u, g_i);
	  	double m = __hiloint2double(m_int2.y, m_int2.x);
		int2 gm_int2 = tex1Dfetch(tex_g, g_i);	
		double gm = __hiloint2double(gm_int2.y, gm_int2.x);
		if(g_x == *row && g_i % 2==1) {
			if(g_y != 0 and g_y != dev_N-1) {
				int2 r_int2 = tex1Dfetch(tex_u, g_ir);
				int2 l_int2 = tex1Dfetch(tex_u, g_il);
		  		double r = __hiloint2double(r_int2.y, r_int2.x);
		  		double l = __hiloint2double(l_int2.y, l_int2.x);
				if(g_x == 0) {
					int2 d_int2 = tex1Dfetch(tex_u, g_id);
		  			double d = __hiloint2double(d_int2.y, d_int2.x);
					resid = 0.25*(l+r+d-3*m)-dev_dx*dev_dx/4*gm;
					u[g_i] += dev_omega * resid;
				}
				else if(g_x == 2*dev_N-1) {
					int2 uu_int2 = tex1Dfetch(tex_u, g_iu);
		  			double uu = __hiloint2double(uu_int2.y, uu_int2.x);
					resid = 0.25*(l+r+uu-3*m)-dev_dx*dev_dx/4*gm;
					u[g_i] += dev_omega * resid;
				}
				else {
					int2 uu_int2 = tex1Dfetch(tex_u, g_iu);
		  			double uu = __hiloint2double(uu_int2.y, uu_int2.x);
					int2 d_int2 = tex1Dfetch(tex_u, g_id);
		  			double d = __hiloint2double(d_int2.y, d_int2.x);
					resid = 0.25*(l+r+uu+d-4*m)-dev_dx*dev_dx/4*gm;
					u[g_i] += dev_omega * resid;	
				}
				du[g_i] = resid;			
			}
			else {
				du[g_i] = 0;
			}
		}
}






