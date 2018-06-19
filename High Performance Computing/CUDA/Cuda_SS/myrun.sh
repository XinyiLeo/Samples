#!/bin/bash
#PBS -N main
#PBS -m abe
#PBS -M xinyiwu.2019@u.northwestern.edu
#PBS -l walltime=00:03:00
#PBS -q batch
cd $PBS_O_WORKDIR
./main 100 1.5 0.00001
