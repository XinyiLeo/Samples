all: main runmain sparsetest sparse runsparse runs
main: main.cu
	nvcc -g -G -o main main.cu -lcusparse

runmain: main
	qsub myrun.sh

sparsetest: sparsetest.c
	gcc -DADD_ -DHAVE_CUBLAS -I/usr/local/cuda/include -I/usr/local/magma/include -g -o sparsetest sparsetest.c -L/usr/local/magma/lib -lmagma -L/usr/local/cuda/lib64 -llapack -lcublas -lcudart -lm -lgfortran

runsparse: sparsetest
	qsub sparserun.sh

sparse: sparse.cu
	nvcc -g -G -o sparse sparse.cu -lcusparse

runs: sparse
	qsub srun.sh	
	
