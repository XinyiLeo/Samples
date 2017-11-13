#!/bin/bash
#Input Format: ./CPU.sh CommandName logfilename pid

grep ${1} ${2} | grep ${3} | awk -F ' ' '{print $3;}'|awk 'BEGIN{max=-1.0;min=101;avg=0.0;}{max=($1>max?$1:max);min=($1<min?$1:min);avg+=$1;}END{printf "%f\t%f\t%f\t",max,min,avg/NR}'
