#!/bin/bash
#MSUB -N main
#MSUB -A e30514
#MSUB -m e
#MSUB -l nodes=1:ppn=8
#MSUB -l walltime=00:10:00
#MSUB -q short
cd $PBS_O_WORKDIR
module load mpi/openmpi-1.10.5-gcc-4.8.3
module load fftw/3.3.3-gcc
mpirun -np 8 /home/xwi4888/Cgl/main 128 1.5 0.25 10000
