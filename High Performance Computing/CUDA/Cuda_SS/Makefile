all: main runmain
main: main.cu
	nvcc -g -G -o main main.cu

runmain: main
	qsub myrun.sh
