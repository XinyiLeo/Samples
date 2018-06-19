module load mpi
mpicc -c main.c
mpicc -o main main.o
mpirun -np 4 /home/xwi4888/SourceSink/main 200 1.95 0.00001
