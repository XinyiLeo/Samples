module load mpi
module load mpi/openmpi-1.10.5-gcc-4.8.3
module load fftw/3.3.3-gcc
mpicc -std=gnu99 -c -I/software/FFTW/3.3.3-RH7/include main.c
mpicc -std=gnu99 -o main -L/software/FFTW/3.3.3-RH7/lib main.o -lfftw3_mpi -lfftw3 -lm
mpirun -np 4 main 8 1.5 0.25 1000  
