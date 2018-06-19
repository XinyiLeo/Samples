#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include <magma.h>
#include <magma_types.h>
#include <magma_lapack.h>
#include "cusparse.h" 

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

/*
	Xinyi Wu

	Start: 2018/6/12	
		
	This is the cuda version of Linear Euler Equation. I will implement the ADI method here. 
	There is only two input N, M. N is the length of the grid, M is the step of the time.
	To make things simple, I will express the grid as 1D array A[x * N + y]. x is the number of column
	y number of row. 

	after set up I will simply loop. 
	use magma for solving linear equations and cusparse for matrix operation
*/


const int threadsPerBlock = 256;

__device__ static int dev_N;
__device__ static double dev_gamma;
__device__ static double dev_dx;
texture<int2, cudaTextureType1D, cudaReadModeElementType> tex_rho;
texture<int2, cudaTextureType1D, cudaReadModeElementType> tex_u;
texture<int2, cudaTextureType1D, cudaReadModeElementType> tex_v;
texture<int2, cudaTextureType1D, cudaReadModeElementType> tex_p;
texture<int2, cudaTextureType1D, cudaReadModeElementType> tex_mulD;

__global__ void plusrhox(double* rho);
__global__ void pluspx(double* p);
__global__ void plusux(double* u);
__global__ void plusrhoy(double* rho);
__global__ void pluspy(double* p);
__global__ void plusvy(double* v);


int main(int argc, char* argv[]) {
	// Initialization: Basic Parameters
	int N = atoi(argv[1]);
	int M = atoi(argv[2]);
	double gamma = 1.4;
	double dx = 2.0 / N;
	double dt = 2.0 / M;
	double dd = dt / (4*dx);
	int baseidx = 0;
	
	const int blocksPerGrid = N/threadsPerBlock + (N%threadsPerBlock > 0 ? 1 : 0);

	// Initialization: Grids
	double* rho = (double*)malloc(N*N*sizeof(double));
	double* u = (double*)malloc(N*N*sizeof(double));
	double* v = (double*)malloc(N*N*sizeof(double));
	double* p = (double*)malloc(N*N*sizeof(double));
	double* mulD = (double*)malloc(N*N*sizeof(double)); // The temporary result after a matrix multiplies D

	double* dev_rho;
	double* dev_u;
	double* dev_v;
	double* dev_p;
	double* dev_mulD;

  	double* Aval = (double*)malloc(2*N*sizeof(double));  // MulD Prepare
  	int* Arowptr = (int*)malloc((N+1)*sizeof(int));
  	int* Acolind = (int*)malloc(2*N*sizeof(int));
  	double* xval = (double*)malloc(N*sizeof(double));
  	int* xind = (int*)malloc(N*sizeof(int));
  	double* y = (double*)malloc(N*sizeof(double));
	
	double* dev_Aval;
  	int* dev_Arowptr;
  	int* dev_Acolind;
  	double* dev_xval;
  	int* dev_xind;
  	double* dev_x;
  	double* dev_y;

  	cudaMalloc((void**)&dev_Aval, 2*N*sizeof(double));
  	cudaMalloc((void**)&dev_Arowptr, (N+1)*sizeof(int));
  	cudaMalloc((void**)&dev_Acolind, 2*N*sizeof(int));
  	cudaMalloc((void**)&dev_xval, N*sizeof(double));
  	cudaMalloc((void**)&dev_xind, N*sizeof(int));
  	cudaMalloc((void**)&dev_x, N*sizeof(double));
  	cudaMalloc((void**)&dev_y, N*sizeof(double));

	cudaMalloc((void**)&dev_rho, N*N*sizeof(double));
	cudaMalloc((void**)&dev_u, N*N*sizeof(double));
	cudaMalloc((void**)&dev_v, N*N*sizeof(double));
	cudaMalloc((void**)&dev_p, N*N*sizeof(double));
	cudaMalloc((void**)&dev_mulD, N*N*sizeof(double));

	cudaBindTexture(NULL, tex_rho, dev_rho, N*N*sizeof(double));
	cudaBindTexture(NULL, tex_u, dev_u, N*N*sizeof(double));
	cudaBindTexture(NULL, tex_v, dev_v, N*N*sizeof(double));
	cudaBindTexture(NULL, tex_p, dev_p, N*N*sizeof(double));
	cudaBindTexture(NULL, tex_mulD, dev_mulD, N*N*sizeof(double));

	// Build D
 	for(int i = 0; i < N; i++) {
		Aval[2*i] = -dd;
		Aval[2*i+1] = dd;
		Arowptr[i] = 2*i;
		Acolind[2*i] = i-1;
		Acolind[2*i+1] = i+1;
	}
	Acolind[0] = 1;
	Acolind[1] = N-1;
	Acolind[2*N-2] = 0;
	Acolind[2*N-1] = N-2;
	Arowptr[N] = 2*N;
	Aval[0] = dd;
	Aval[1] = -dd;
	Aval[2*N-2] = dd;
	Aval[2*N-1] = -dd;
  	int nnz = 2 * N;

	// Initialize the grid
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			rho[x*N+y] = 2.0 / gamma * exp(-100*((-1+x*dx)*(-1+x*dx)+(-1+y*dx)*(-1+y*dx)));
			u[x*N+y] = 0;
			v[x*N+y] = 0;
			p[x*N+y] = 2.0 * exp(-100*((-1+x*dx)*(-1+x*dx)+(-1+y*dx)*(-1+y*dx)));
		}
	}

	// Start For loop
	for(int loop = 0; loop < 1; loop++) {
		// Explicit in x
		// Updating rho
		// u * D
		for(int k = 0; k < N; k++) {
			for(int i = 0; i < N; i++) {
				xind[i] = i;
				xval[i] = u[k * N + i];
			}

		  	cudaMemcpy(dev_Aval, Aval, 2*N*sizeof(double), cudaMemcpyHostToDevice);
		  	cudaMemcpy(dev_Arowptr, Arowptr, (N+1)*sizeof(int), cudaMemcpyHostToDevice);
		  	cudaMemcpy(dev_Acolind, Acolind, 2*N*sizeof(int), cudaMemcpyHostToDevice);
		  	cudaMemcpy(dev_xval, xval, N*sizeof(double), cudaMemcpyHostToDevice);
		  	cudaMemcpy(dev_xind, xind, N*sizeof(int), cudaMemcpyHostToDevice);

		  	cusparseHandle_t handle = NULL;
		  	cusparseCreate(&handle);
		  	cusparseMatDescr_t descr = NULL; 
		  	cusparseCreateMatDescr(&descr);
		  	cusparseSetMatType(descr, CUSPARSE_MATRIX_TYPE_GENERAL);
		  	cusparseSetMatIndexBase(descr,CUSPARSE_INDEX_BASE_ZERO);
		  	cusparseDsctr(handle, N, dev_xval, dev_xind, dev_x, CUSPARSE_INDEX_BASE_ZERO);
		  	double one = 1.;
		  	double zero = 0.;
		  	cusparseDcsrmv(handle, CUSPARSE_OPERATION_NON_TRANSPOSE, N, N, nnz, &one, descr, \
				dev_Aval, dev_Arowptr, dev_Acolind, dev_x, &zero, dev_y);
		  	cudaDeviceSynchronize();
		  	cudaMemcpy(y, dev_y, N*sizeof(double), cudaMemcpyDeviceToHost);

			for(int i = 0; i < N; i++) {
				 mulD[k * N + i] = y[i];
			}
		}
		
		// Rho linear algebra update
		cudaMemcpyToSymbol(dev_N, &N, sizeof(int));
		cudaMemcpyToSymbol(dev_dx, &dx, sizeof(double));
		cudaMemcpy(dev_rho, rho, N*N*sizeof(double), cudaMemcpyHostToDevice);
		cudaMemcpy(dev_mulD, mulD, N*N*sizeof(double), cudaMemcpyHostToDevice);
		plusrhox<<<blocksPerGrid, threadsPerBlock>>>(dev_rho);
		cudaMemcpy(rho, dev_rho, N*N*sizeof(double), cudaMemcpyDeviceToHost);


		// Updating p
		// p linear algebra update
		cudaMemcpyToSymbol(dev_N, &N, sizeof(int));
		cudaMemcpyToSymbol(dev_dx, &dx, sizeof(double));
		cudaMemcpyToSymbol(dev_gamma, &gamma, sizeof(double));
		cudaMemcpy(dev_p, p, N*N*sizeof(double), cudaMemcpyHostToDevice);
		cudaMemcpy(dev_mulD, mulD, N*N*sizeof(double), cudaMemcpyHostToDevice);
		pluspx<<<blocksPerGrid, threadsPerBlock>>>(dev_p);
		cudaMemcpy(p, dev_p, N*N*sizeof(double), cudaMemcpyDeviceToHost);
		
		// Updating u
		// p * D
		for(int k = 0; k < N; k++) {
			for(int i = 0; i < N; i++) {
				xind[i] = i;
				xval[i] = p[k * N + i];
			}

		  	cudaMemcpy(dev_Aval, Aval, 2*N*sizeof(double), cudaMemcpyHostToDevice);
		  	cudaMemcpy(dev_Arowptr, Arowptr, (N+1)*sizeof(int), cudaMemcpyHostToDevice);
		  	cudaMemcpy(dev_Acolind, Acolind, 2*N*sizeof(int), cudaMemcpyHostToDevice);
		  	cudaMemcpy(dev_xval, xval, N*sizeof(double), cudaMemcpyHostToDevice);
		  	cudaMemcpy(dev_xind, xind, N*sizeof(int), cudaMemcpyHostToDevice);

		  	cusparseHandle_t handle = NULL;
		  	cusparseCreate(&handle);
		  	cusparseMatDescr_t descr = NULL; 
		  	cusparseCreateMatDescr(&descr);
		  	cusparseSetMatType(descr, CUSPARSE_MATRIX_TYPE_GENERAL);
		  	cusparseSetMatIndexBase(descr,CUSPARSE_INDEX_BASE_ZERO);
		  	cusparseDsctr(handle, N, dev_xval, dev_xind, dev_x, CUSPARSE_INDEX_BASE_ZERO);
		  	double one = 1.;
		  	double zero = 0.;
		  	cusparseDcsrmv(handle, CUSPARSE_OPERATION_NON_TRANSPOSE, N, N, nnz, &one, descr, \
				dev_Aval, dev_Arowptr, dev_Acolind, dev_x, &zero, dev_y);
		  	cudaDeviceSynchronize();
		  	cudaMemcpy(y, dev_y, N*sizeof(double), cudaMemcpyDeviceToHost);

			for(int i = 0; i < N; i++) {
				 mulD[k * N + i] = y[i];
			}
		}
		// u linear algebra update
		cudaMemcpyToSymbol(dev_N, &N, sizeof(int));
		cudaMemcpyToSymbol(dev_dx, &dx, sizeof(double));
		cudaMemcpyToSymbol(dev_gamma, &gamma, sizeof(double));
		cudaMemcpy(dev_u, u, N*N*sizeof(double), cudaMemcpyHostToDevice);
		cudaMemcpy(dev_mulD, mulD, N*N*sizeof(double), cudaMemcpyHostToDevice);
		plusux<<<blocksPerGrid, threadsPerBlock>>>(dev_u);
		cudaMemcpy(u, dev_u, N*N*sizeof(double), cudaMemcpyDeviceToHost);

		// Implicit in y
  		magma_init();
  		magma_int_t *piv, info;
  		double* A;
  		double* b;
  		magma_dmalloc_pinned(&A, 16*N*N);
  		magma_dmalloc_pinned(&b, 4*N*N);
  		piv = (magma_int_t*)malloc(4*N*sizeof(magma_int_t));

	  	for(int i = 0; i < 4*N; i++) {
			A[(4*N+1)*i] = 1.0;
		}
		baseidx = 8*N*N;
		for(int i = 0; i < N; i++) {
			A[baseidx + i*4*N + (i+1)%N] = -dd;
			A[baseidx + i*4*N + (i-1+N)%N] = dd;
		}
		baseidx = 8*N*N + 3*N;
		for(int i = 0; i < N; i++) {
			A[baseidx + i*4*N + (i+1)%N] = -gamma*dd;
			A[baseidx + i*4*N + (i-1+N)%N] = gamma*dd;
		}
		baseidx = 12*N*N + 2*N;
		for(int i = 0; i < N; i++) {
			A[baseidx + i*4*N + (i+1)%N] = -dd;
			A[baseidx + i*4*N + (i-1+N)%N] = dd;
		}

		for(int x = 0; x < N; x++) {
			for(int y = 0; y < N; y++) {
				b[x*4*N+y] = rho[x*N+y];
				b[x*4*N+N+y] = u[x*N+y];
				b[x*4*N+2*N+y] = v[x*N+y];
				b[x*4*N+3*N+y] = p[x*N+y];
			}
		}
  		magma_dgesv(4*N, N, A, 4*N, piv, b, 4*N, &info);
		for(int x = 0; x < N; x++) {
			for(int y = 0; y < N; y++) {
				rho[x*N+y] = b[x*4*N+y];
				u[x*N+y] = b[x*4*N+N+y];
				v[x*N+y] = b[x*4*N+2*N+y];
				p[x*N+y] = b[x*4*N+3*N+y];
			}
		}
		
		// Explicit in y
		// Updating rho
		// v * D
		for(int k = 0; k < N; k++) {
			for(int i = 0; i < N; i++) {
				xind[i] = i;
				xval[i] = v[k * N + i];
			}

		  	cudaMemcpy(dev_Aval, Aval, 2*N*sizeof(double), cudaMemcpyHostToDevice);
		  	cudaMemcpy(dev_Arowptr, Arowptr, (N+1)*sizeof(int), cudaMemcpyHostToDevice);
		  	cudaMemcpy(dev_Acolind, Acolind, 2*N*sizeof(int), cudaMemcpyHostToDevice);
		  	cudaMemcpy(dev_xval, xval, N*sizeof(double), cudaMemcpyHostToDevice);
		  	cudaMemcpy(dev_xind, xind, N*sizeof(int), cudaMemcpyHostToDevice);

		  	cusparseHandle_t handle = NULL;
		  	cusparseCreate(&handle);
		  	cusparseMatDescr_t descr = NULL; 
		  	cusparseCreateMatDescr(&descr);
		  	cusparseSetMatType(descr, CUSPARSE_MATRIX_TYPE_GENERAL);
		  	cusparseSetMatIndexBase(descr,CUSPARSE_INDEX_BASE_ZERO);
		  	cusparseDsctr(handle, N, dev_xval, dev_xind, dev_x, CUSPARSE_INDEX_BASE_ZERO);
		  	double one = 1.;
		  	double zero = 0.;
		  	cusparseDcsrmv(handle, CUSPARSE_OPERATION_NON_TRANSPOSE, N, N, nnz, &one, descr, \
				dev_Aval, dev_Arowptr, dev_Acolind, dev_x, &zero, dev_y);
		  	cudaDeviceSynchronize();
		  	cudaMemcpy(y, dev_y, N*sizeof(double), cudaMemcpyDeviceToHost);

			for(int i = 0; i < N; i++) {
				 mulD[k * N + i] = y[i];
			}
		}
		
		// Rho linear algebra update
		cudaMemcpyToSymbol(dev_N, &N, sizeof(int));
		cudaMemcpyToSymbol(dev_dx, &dx, sizeof(double));
		cudaMemcpy(dev_rho, rho, N*N*sizeof(double), cudaMemcpyHostToDevice);
		cudaMemcpy(dev_mulD, mulD, N*N*sizeof(double), cudaMemcpyHostToDevice);
		plusrhoy<<<blocksPerGrid, threadsPerBlock>>>(dev_rho);
		cudaMemcpy(rho, dev_rho, N*N*sizeof(double), cudaMemcpyDeviceToHost);

		// Updating p
		// p linear algebra update
		cudaMemcpyToSymbol(dev_N, &N, sizeof(int));
		cudaMemcpyToSymbol(dev_dx, &dx, sizeof(double));
		cudaMemcpyToSymbol(dev_gamma, &gamma, sizeof(double));
		cudaMemcpy(dev_p, p, N*N*sizeof(double), cudaMemcpyHostToDevice);
		cudaMemcpy(dev_mulD, mulD, N*N*sizeof(double), cudaMemcpyHostToDevice);
		pluspy<<<blocksPerGrid, threadsPerBlock>>>(dev_p);
		cudaMemcpy(p, dev_p, N*N*sizeof(double), cudaMemcpyDeviceToHost);
	
		// Updating v
		// p * D
		for(int k = 0; k < N; k++) {
			for(int i = 0; i < N; i++) {
				xind[i] = i;
				xval[i] = p[k * N + i];
			}

		  	cudaMemcpy(dev_Aval, Aval, 2*N*sizeof(double), cudaMemcpyHostToDevice);
		  	cudaMemcpy(dev_Arowptr, Arowptr, (N+1)*sizeof(int), cudaMemcpyHostToDevice);
		  	cudaMemcpy(dev_Acolind, Acolind, 2*N*sizeof(int), cudaMemcpyHostToDevice);
		  	cudaMemcpy(dev_xval, xval, N*sizeof(double), cudaMemcpyHostToDevice);
		  	cudaMemcpy(dev_xind, xind, N*sizeof(int), cudaMemcpyHostToDevice);

		  	cusparseHandle_t handle = NULL;
		  	cusparseCreate(&handle);
		  	cusparseMatDescr_t descr = NULL; 
		  	cusparseCreateMatDescr(&descr);
		  	cusparseSetMatType(descr, CUSPARSE_MATRIX_TYPE_GENERAL);
		  	cusparseSetMatIndexBase(descr,CUSPARSE_INDEX_BASE_ZERO);
		  	cusparseDsctr(handle, N, dev_xval, dev_xind, dev_x, CUSPARSE_INDEX_BASE_ZERO);
		  	double one = 1.;
		  	double zero = 0.;
		  	cusparseDcsrmv(handle, CUSPARSE_OPERATION_NON_TRANSPOSE, N, N, nnz, &one, descr, \
				dev_Aval, dev_Arowptr, dev_Acolind, dev_x, &zero, dev_y);
		  	cudaDeviceSynchronize();
		  	cudaMemcpy(y, dev_y, N*sizeof(double), cudaMemcpyDeviceToHost);

			for(int i = 0; i < N; i++) {
				 mulD[k * N + i] = y[i];
			}
		}
		// v linear algebra update
		cudaMemcpyToSymbol(dev_N, &N, sizeof(int));
		cudaMemcpyToSymbol(dev_dx, &dx, sizeof(double));
		cudaMemcpyToSymbol(dev_gamma, &gamma, sizeof(double));
		cudaMemcpy(dev_v, v, N*N*sizeof(double), cudaMemcpyHostToDevice);
		cudaMemcpy(dev_mulD, mulD, N*N*sizeof(double), cudaMemcpyHostToDevice);
		plusvy<<<blocksPerGrid, threadsPerBlock>>>(dev_v);
		cudaMemcpy(v, dev_v, N*N*sizeof(double), cudaMemcpyDeviceToHost);

		// Implicit in x
  		magma_init();
  		magma_int_t *piv, info;
  		double* A;
  		double* b;
  		magma_dmalloc_pinned(&A, 16*N*N);
  		magma_dmalloc_pinned(&b, 4*N*N);
  		piv = (magma_int_t*)malloc(4*N*sizeof(magma_int_t));

	  	for(int i = 0; i < 4*N; i++) {
			A[(4*N+1)*i] = 1.0;
		}
		baseidx = 4*N*N;
		for(int i = 0; i < N; i++) {
			A[baseidx + i*4*N + (i+1)%N] = -dd;
			A[baseidx + i*4*N + (i-1+N)%N] = dd;
		}
		baseidx = 4*N*N + 3*N;
		for(int i = 0; i < N; i++) {
			A[baseidx + i*4*N + (i+1)%N] = -gamma*dd;
			A[baseidx + i*4*N + (i-1+N)%N] = gamma*dd;
		}
		baseidx = 12*N*N + N;
		for(int i = 0; i < N; i++) {
			A[baseidx + i*4*N + (i+1)%N] = -dd;
			A[baseidx + i*4*N + (i-1+N)%N] = dd;
		}

		for(int x = 0; x < N; x++) {
			for(int y = 0; y < N; y++) {
				b[x*4*N+y] = rho[x*N+y];
				b[x*4*N+N+y] = u[x*N+y];
				b[x*4*N+2*N+y] = v[x*N+y];
				b[x*4*N+3*N+y] = p[x*N+y];
			}
		}
  		magma_dgesv(4*N, N, A, 4*N, piv, b, 4*N, &info);
		for(int x = 0; x < N; x++) {
			for(int y = 0; y < N; y++) {
				rho[x*N+y] = b[x*4*N+y];
				u[x*N+y] = b[x*4*N+N+y];
				v[x*N+y] = b[x*4*N+2*N+y];
				p[x*N+y] = b[x*4*N+3*N+y];
			}
		}
		
  		magma_free_pinned(A);
  		magma_free_pinned(b);
  		free(piv);
  		magma_finalize();
	}

	// End
	cudaUnbindTexture(tex_rho);
	cudaUnbindTexture(tex_u);
	cudaUnbindTexture(tex_v);
	cudaUnbindTexture(tex_p);
	cudaUnbindTexture(tex_mulD);
	cudaFree(dev_rho); 
	cudaFree(dev_u); 
	cudaFree(dev_v); 
	cudaFree(dev_p); 
	cudaFree(dev_mulD); 
	free(rho);
	free(u);
	free(v);
	free(p);
  	free(Aval);
  	free(Arowptr);
  	free(Acolind);
  	free(xval);
  	free(xind);
  	free(y);
	free(mulD);
	return 0;
}

__global__ void plusrhox(double* rho) {
  	int g_i = (threadIdx.x + blockIdx.x * blockDim.x) % (dev_N * dev_N);
	int2 rhoval_int2 = tex1Dfetch(tex_rho, g_i);
	int2 mulDval_int2 = tex1Dfetch(tex_mulD, g_i);
  	double rhoval = __hiloint2double(rhoval_int2.y, rhoval_int2.x);
	double mulDval = __hiloint2double(mulDval_int2.y, mulDval_int2.x);
	rho[g_i] -= mulDval; 
}

__global__ void pluspx(double* p) {
  	int g_i = (threadIdx.x + blockIdx.x * blockDim.x) % (dev_N * dev_N);
	int2 pval_int2 = tex1Dfetch(tex_p, g_i);
	int2 mulDval_int2 = tex1Dfetch(tex_mulD, g_i);
  	double pval = __hiloint2double(pval_int2.y, pval_int2.x);
	double mulDval = __hiloint2double(mulDval_int2.y, mulDval_int2.x);
	p[g_i] -= dev_gamma * mulDval; 
}

__global__ void plusux(double* u) {
  	int g_i = (threadIdx.x + blockIdx.x * blockDim.x) % (dev_N * dev_N);
	int2 uval_int2 = tex1Dfetch(tex_u, g_i);
	int2 mulDval_int2 = tex1Dfetch(tex_mulD, g_i);
  	double uval = __hiloint2double(uval_int2.y, uval_int2.x);
	double mulDval = __hiloint2double(mulDval_int2.y, mulDval_int2.x);
	u[g_i] -= mulDval; 
}

__global__ void plusrhoy(double* rho) {
  	int g_i = (threadIdx.x + blockIdx.x * blockDim.x) % (dev_N * dev_N);
	int2 rhoval_int2 = tex1Dfetch(tex_rho, g_i);
	int2 mulDval_int2 = tex1Dfetch(tex_mulD, g_i);
  	double rhoval = __hiloint2double(rhoval_int2.y, rhoval_int2.x);
	double mulDval = __hiloint2double(mulDval_int2.y, mulDval_int2.x);
	rho[g_i] -= mulDval; 
}

__global__ void pluspy(double* p) {
  	int g_i = (threadIdx.x + blockIdx.x * blockDim.x) % (dev_N * dev_N);
	int2 pval_int2 = tex1Dfetch(tex_p, g_i);
	int2 mulDval_int2 = tex1Dfetch(tex_mulD, g_i);
  	double pval = __hiloint2double(pval_int2.y, pval_int2.x);
	double mulDval = __hiloint2double(mulDval_int2.y, mulDval_int2.x);
	p[g_i] -= dev_gamma * mulDval; 
}

__global__ void plusvy(double* v) {
  	int g_i = (threadIdx.x + blockIdx.x * blockDim.x) % (dev_N * dev_N);
	int2 vval_int2 = tex1Dfetch(tex_v, g_i);
	int2 mulDval_int2 = tex1Dfetch(tex_mulD, g_i);
  	double vval = __hiloint2double(vval_int2.y, vval_int2.x);
	double mulDval = __hiloint2double(mulDval_int2.y, mulDval_int2.x);
	v[g_i] -= mulDval; 
}



