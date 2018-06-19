#! /bin/bash
#PBS -N sparse
##PBS -m abe
#PBS -M xinyiwu2019@u.northwestern.edu
#PBS -l walltime=00:01:00
#PBS -q batch
cd $PBS_O_WORKDIR
./sparse 
