/*
  Dot Product

  Program written by Leo Wu

  Editing History:

  5/1/18: Start
*/

#include <stdio.h>
#include <stdlib.h>
#include <cblas.h> 
#include <time.h>
#include <math.h>
#include <lapacke.h>  
void dgemm_(char *,char *,int *,int *,int *,double *,double *,int *,double *,int *,double *,double *,int *);


int main(int argc, char* argv[]) 
{
	clock_t start = clock();
	int N = atoi(argv[1]);
	int M = atoi(argv[2]);
	double T = 2;
	double deltaT = T / M;
	double gridlen = 2.0 / N;
	double gamma = 1.4;
	double x = 0, y = 0;

	// construct matrix rho = f(x_j, y_k, t_n)
  	double (*rho)[N][M + 1] = malloc(sizeof * rho * N);
  	double (*ux)[N][M + 1] = malloc(sizeof * ux * N);
  	double (*uy)[N][M + 1] = malloc(sizeof * uy * N);
  	double (*p)[N][M + 1] = malloc(sizeof * p * N);
	double (*tmpA)[4 * N] = malloc(sizeof * tmpA * 4 * N);
	double (*tmpb)[4 * N] = malloc(sizeof * tmpA * N); // 4N columns, N rows
	double (*rhotmp)[N] = malloc(sizeof * rhotmp * N);
	double (*uxtmp)[N] = malloc(sizeof * uxtmp * N);
	double (*uytmp)[N] = malloc(sizeof * uytmp * N);
	double (*ptmp)[N] = malloc(sizeof * ptmp * N);

     	for (int n=0; n < M + 1; n++) {
		if(n == 0) {
			for (int j=0; j<N; j++) {
    				for (int k=0; k<N; k++) {
					x = -1 + j * gridlen;
					y = -1 + k * gridlen;
					rho[j][k][n] = (2.0/gamma) * exp(-100.0 * (x * x + y * y)) ;
					ux[j][k][n] = 0;
					uy[j][k][n] = 0;
					p[j][k][n] = 2.0 * exp(-100.0 * (x * x + y * y));
					//printf("rho[%d][%d][%d] = %lf\n", j, k, n, rho[j][k][n]);
				}
			}
		}
		else {
			// ADI calculation
			// First Step
			for(int i = 0; i < 4 * N; i++) {
				for(int j = 0; j < 4 * N; j++) {
					tmpA[i][j] = 0;
				}
			}
			for(int i = 0; i < 4 * N; i++) {
				for(int j = 0; j < N; j++) {
					tmpb[j][i] = 0;
				}	
			}

			for(int k = 0; k < N; k++) {
				for(int j = 0; j < N; j++) {
					rhotmp[j][k] = rho[j][k][n-1] - (deltaT / (4 * gridlen)) * (ux[(j+1)%N][k][n-1] - ux[(j+N-1)%N][k][n-1]);	
					uxtmp[j][k] = ux[j][k][n-1] - (deltaT / (4 * gridlen)) * (p[(j+1)%N][k][n-1] - p[(j+N-1)%N][k][n-1]);	
					uytmp[j][k] = uy[j][k][n-1];
					ptmp[j][k] = p[j][k][n-1] - gamma * (deltaT / (4 * gridlen)) * (ux[(j+1)%N][k][n-1] - ux[(j+N-1)%N][k][n-1]);	
					//printf("uxtmp[%d][%d] = %lf\n", j, k, uxtmp[j][k]);
				}						
			}
			// Second Step
			// Create matrix A (i and j are reversed), b 
			for(int i = 0; i < 4 * N; i++) {
				tmpA[i][i] = 1;
			}
			for(int i = 0; i < N; i++) {
				tmpA[2 * N + i][( i - 1 + N ) % N] = deltaT / (4 * gridlen);
				tmpA[2 * N + i][( i + 1 ) % N] = - deltaT / (4 * gridlen);
				tmpA[3 * N + i][2 * N + ( i - 1 + N ) % N] = deltaT / (4 * gridlen);
				tmpA[3 * N + i][2 * N + ( i + 1 ) % N] = - deltaT / (4 * gridlen);
				tmpA[2 * N + i][3 * N + ( i - 1 + N ) % N] = gamma * deltaT / (4 * gridlen);
				tmpA[2 * N + i][3 * N + ( i + 1 ) % N] = - gamma * deltaT / (4 * gridlen);
			}
			/* This print tmpA
			for(int i = 0; i < 4 * N; i++) {
				for(int j = 0; j < 4 * N; j++) {
					printf("%4.1f", tmpA[j][i]);
				}	
				printf("\n");	
			}
			*/
			
			for(int k = 0; k < N; k++) {
				for(int j = 0; j < N; j++) {
					tmpb[k][j] = rhotmp[k][j];
					tmpb[k][N + j] = uxtmp[k][j];
					tmpb[k][2 * N + j] = uytmp[k][j];
					tmpb[k][3 * N + j] = ptmp[k][j];
				}		
			}	
			/*
			for(int i = 0; i < 4 * N; i++) {
				for(int j = 0; j < N; j++) {
					printf("%6.3f", tmpb[j][i]);
				}	
				printf("\n");	
			}	
			*/
			char TRANS = 'N';
			int INFO= 0;
			int LDA = 4 * N;
			int LDB = 4 * N;
			int NN = 4 * N;
			int NRHS = N;
			int IPIV[4 * N];
			double* a = &(tmpA[0][0]);
			double* b = &(tmpb[0][0]);
			LAPACK_dgetrf(&NN,&NN,a,&LDA,IPIV,&INFO);
			dgetrs_(&TRANS,&NN,&NRHS,a,&LDA,IPIV,b,&LDB,&INFO);
			
			/*
			if(n == 2) {
			for(int i = 0; i < 4 * N; i++) {
				for(int j = 0; j < N; j++) {
					printf("%6.3f", tmpb[j][i]);
				}	
				printf("\n");	
			}
			}
			*/

			// Third Step
			for(int k = 0; k < N; k++) {
				for(int j = 0; j < N; j++) {
					rhotmp[j][k] = tmpb[k][j] - (deltaT / (4 * gridlen)) * (tmpb[k][2 * N + (j+1)%N]- tmpb[k][2 * N + (j+N-1)%N]);
					uxtmp[j][k] = tmpb[k][j + N];	
					uytmp[j][k] = tmpb[k][j + 2 * N] - (deltaT / (4 * gridlen)) * (tmpb[k][3 * N + (j+1)%N] - tmpb[k][3 * N + (j+N-1)%N]);
					ptmp[j][k] = tmpb[k][j + 3 * N] - gamma * (deltaT / (4 * gridlen)) * (tmpb[k][2 * N + (j+1)%N]- tmpb[k][2 * N + (j+N-1)%N]);	
					//printf("uytmp[%d][%d] = %lf\n", j, k, uytmp[j][k]);
				}						
			}

			// Fourth Step
			// Create matrix A (i and j are reversed), b 
			for(int i = 0; i < 4 * N; i++) {
				for(int j = 0; j < 4 * N; j++) {
					tmpA[i][j] = 0;
				}
			}
			for(int i = 0; i < 4 * N; i++) {
				for(int j = 0; j < N; j++) {
					tmpb[j][i] = 0;
				}	
			}

			for(int i = 0; i < 4 * N; i++) {
				tmpA[i][i] = 1;
			}
			for(int i = 0; i < N; i++) {
				tmpA[N + i][( i - 1 + N ) % N] = deltaT / (4 * gridlen);
				tmpA[N + i][( i + 1 ) % N] = - deltaT / (4 * gridlen);
				tmpA[3 * N + i][N + ( i - 1 + N ) % N] = deltaT / (4 * gridlen);
				tmpA[3 * N + i][N + ( i + 1 ) % N] = - deltaT / (4 * gridlen);
				tmpA[N + i][3 * N + ( i - 1 + N ) % N] = gamma * deltaT / (4 * gridlen);
				tmpA[N + i][3 * N + ( i + 1 ) % N] = - gamma * deltaT / (4 * gridlen);
			}
			/*
			for(int i = 0; i < 4 * N; i++) {
				for(int j = 0; j < 4 * N; j++) {
					printf("%4.1f", tmpA[j][i]);
				}	
				printf("\n");	
			}
			*/
			
			for(int k = 0; k < N; k++) {
				for(int j = 0; j < N; j++) {
					tmpb[k][j] = rhotmp[k][j];
					tmpb[k][N + j] = uxtmp[k][j];
					tmpb[k][2 * N + j] = uytmp[k][j];
					tmpb[k][3 * N + j] = ptmp[k][j];
				}		
			}	
			LAPACK_dgetrf(&NN,&NN,a,&LDA,IPIV,&INFO);
			dgetrs_(&TRANS,&NN,&NRHS,a,&LDA,IPIV,b,&LDB,&INFO);
			
			for(int j = 0; j < N; j++) {
				for(int k = 0; k < N; k++) {
					rho[j][k][n] = tmpb[k][j];
					ux[j][k][n] = tmpb[k][j + N];
					uy[j][k][n] = tmpb[k][j + 2 * N];
					p[j][k][n] = tmpb[k][j + 3 * N];
				}	
			}	
			
    		}
  	}
	printf("Elapsed time: %g\n", (float) (clock()-start)/CLOCKS_PER_SEC);



	FILE* pFile;  
	pFile = fopen("EulerR.out" , "w"); 
	for(int i = 0; i < N; i++) {
    		fwrite(rho[i], sizeof(double), N, pFile);
	}
    	fclose(pFile);
	
	pFile = fopen("EulerU.out" , "w"); 
	for(int i = 0; i < N; i++) {
    		fwrite(ux[i], sizeof(double), N, pFile);
	}
    	fclose(pFile);

	pFile = fopen("EulerV.out" , "w"); 
	for(int i = 0; i < N; i++) {
    		fwrite(uy[i], sizeof(double), N, pFile);
	}
    	fclose(pFile);
	
	pFile = fopen("EulerP.out" , "w"); 
	for(int i = 0; i < N; i++) {
    		fwrite(p[i], sizeof(double), N, pFile);
	}
    	fclose(pFile);

/*
	pFile = fopen("EulerR.out" , "r");  
    	double (*ttt)[N] = malloc(sizeof * uxtmp * N);
	for(int i = 0; i < N; i++) {
    		fread(ttt[i],  sizeof(double), N, pFile);
	}
    	fclose(pFile);
	for(int i = 0; i < N; i++) {
    		for(int j = 0; j < N; j++) {
    			printf("%9.3f ", ttt[i][j]);
		}	
		printf("\n");	
	}
*/

/*



	printf("rho is:\n");
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			printf("%10.5f", rho[i][j][M]);
		}
		printf("\n");	
	}

	printf("ux is:\n");
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			printf("%10.5f", ux[i][j][M]);
		}
		printf("\n");	
	}

	printf("uy is:\n");
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			printf("%10.5f", uy[i][j][M]);
		}
		printf("\n");	
	}

	printf("p is:\n");
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			printf("%10.5f", p[i][j][M]);
		}
		printf("\n");	
	}

*/
	free(tmpA);
	free(tmpb);
  	free(rho); 
  	free(ux); 
  	free(uy); 
  	free(p); 
	free(rhotmp); 
  	free(uxtmp); 
  	free(uytmp); 
  	free(ptmp); 
	return 0;
}

























