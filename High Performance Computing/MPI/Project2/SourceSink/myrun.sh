#!/bin/bash
#MSUB -N main
#MSUB -A e30514
#MSUB -m e
#MSUB -l nodes=1:ppn=4
#MSUB -l walltime=00:05:00
#MSUB -q short
cd $PBS_O_WORKDIR
module load mpi
mpirun -np 1 /home/xwi4888/SourceSink/main 100 1.5 0.00001
