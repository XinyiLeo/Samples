/*
  Example using cuSPARSE matrix library
  
  Program written by David Chopp
  
  Example of using the cuSPARSE package to do a sparse matrix vector multiplication
  
  Inputs: none
  
  Outputs: Shows the equation that is computed.
  
  Editing History:
  6/4/14: Initial draft
*/
#include <stdio.h>
#include "cusparse.h" // this is the header file for using the cuSPARSE library

/*
int main(int argc, char* argv[])

The main program takes no arguments and creates a tridiagonal matrix and
then multiplies it by a simple sparse vector.  

Inputs: none

Output: prints the expression computed in matrix format.
*/
int main(int argc, char* argv[]) {

  // Dimensions of the matrix for this example
  const int N = 9;
  
  // The data vector for compressed sparse row format
  double* Aval = (double*)malloc(3*N*sizeof(double));
  
  // The row index and column index vectors for the compressed sparse row format
  int* Arowptr = (int*)malloc((N+1)*sizeof(int));
  int* Acolind = (int*)malloc(3*N*sizeof(int));
  
  // The data vector for a sparse vector
  double* xval = (double*)malloc(N*sizeof(double));
  
  // The index vector for a sparse vector
  int* xind = (int*)malloc(N*sizeof(int));
  
  // A dense solution vector.
  double* y = (double*)malloc(N*sizeof(double));

  // build the matrix A with -2 down the diagonal and ones on the off diagonals
  // in compressed sparse row format
  int row;
  int index = 0;
  for (row=0; row<N; ++row) {
    Arowptr[row] = index;
    if (row > 0) {
      Aval[index] = 1.;
      Acolind[index++] = row-1;
    }
    Aval[index] = -2.;
    Acolind[index++] = row;
    if (row < N-1) {
      Aval[index] = 1.;
      Acolind[index++] = row+1;
    }
  }
  Arowptr[N] = index;

  for(int i = 0; i < 3*N; i++) 
    printf("Aval[%d] = %lf\n", i, Aval[i]);

  for(int i = 0; i < 1+N; i++) 
    printf("Arowptr[%d] = %d\n", i, Arowptr[i]);

  for(int i = 0; i < 3*N; i++)
    printf("Acolind[%d] = %d\n", i, Acolind[i]);


  int nnz = index;

  // build the vector x as a sparse vector with alternating 1 0 2 0 3 ...
  index = 0;
  for (row=0; row<N; row += 2) {
    xval[index] = (row/2)+1;
    xind[index++] = row;
  }
  for(int i = 0; i < 1+N; i++) 
    printf("xval[%d] = %lf\n", i, xval[i]);

  for(int i = 0; i < N; i++)
    printf("xind[%d] = %d\n", i, xind[i]);

  // All operations take place on the device, so must create versions of all the input
  // and output data on the device and copy the input data to the device.
  double* dev_Aval;
  int* dev_Arowptr;
  int* dev_Acolind;
  double* dev_xval;
  int* dev_xind;
  double* dev_x;
  double* dev_y;
  cudaMalloc((void**)&dev_Aval, 3*N*sizeof(double));
  cudaMalloc((void**)&dev_Arowptr, (N+1)*sizeof(int));
  cudaMalloc((void**)&dev_Acolind, 3*N*sizeof(int));
  cudaMalloc((void**)&dev_xval, N*sizeof(double));
  cudaMalloc((void**)&dev_xind, N*sizeof(int));
  cudaMalloc((void**)&dev_x, N*sizeof(double));
  cudaMalloc((void**)&dev_y, N*sizeof(double));

  cudaMemcpy(dev_Aval, Aval, 3*N*sizeof(double), cudaMemcpyHostToDevice);
  cudaMemcpy(dev_Arowptr, Arowptr, (N+1)*sizeof(int), cudaMemcpyHostToDevice);
  cudaMemcpy(dev_Acolind, Acolind, 3*N*sizeof(int), cudaMemcpyHostToDevice);
  cudaMemcpy(dev_xval, xval, N*sizeof(double), cudaMemcpyHostToDevice);
  cudaMemcpy(dev_xind, xind, N*sizeof(int), cudaMemcpyHostToDevice);

  // Initialize the cuSPARSE library and get the environment context
  cusparseHandle_t handle = NULL;
  cusparseCreate(&handle);

  // Create a matrix description for our sparse matrix
  cusparseMatDescr_t descr = NULL; 
  cusparseCreateMatDescr(&descr);
  cusparseSetMatType(descr, CUSPARSE_MATRIX_TYPE_GENERAL);
  cusparseSetMatIndexBase(descr,CUSPARSE_INDEX_BASE_ZERO);

  // Convert the sparse vector into a dense vector
  cusparseDsctr(handle, (N+1)/2, dev_xval, dev_xind, dev_x, CUSPARSE_INDEX_BASE_ZERO);

  // Multiple the matrix A by the vector x
  double one = 1.;
  double zero = 0.;
  cusparseDcsrmv(handle, CUSPARSE_OPERATION_NON_TRANSPOSE, N, N, nnz, &one, descr,
        dev_Aval, dev_Arowptr, dev_Acolind, dev_x, &zero, dev_y);

  // Ensure the operation is complete.
  cudaDeviceSynchronize();
  
  // Copy the results on the device back to the host
  cudaMemcpy(y, dev_y, N*sizeof(double), cudaMemcpyDeviceToHost);

  // Print the results
  int i, j, mindex = 0, vindex = 0;
  for (i=0; i<N; ++i) {
    printf("[ ");
    for (j=0; j<N; ++j) {
      if (mindex < Arowptr[i+1] && j==Acolind[mindex]) {
        printf("%5.1f", Aval[mindex++]);
      } else {
        printf("%5.1f", 0.);
      }
    }
    printf("] [");
    if (i == xind[vindex]) {
      printf("%5.1f]", xval[vindex++]);
    } else {
      printf("%5.1f]", 0.);
    }
    if (i == N/2) {
      printf(" = [");
    } else {
      printf("   [");
    }
    printf("%5.1f]\n", y[i]);
  }

  return 0;
}
