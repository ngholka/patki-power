#!/bin/bash
# $1 = number of nodes desired
# $2 = number of CPU cores desired
set -x

export BMARK_STRING=sweep.$2

name=`date +%Y_%m_%d_%H_%M_%S_%N`
mkdir $name
cd $name
env >> env
hostname >> info
echo $name >> info
uname -a >> info
srun --nodes=1 --ntasks=1 -ppbatch cat /proc/cpuinfo | grep MHz >> info
echo 'cores: '$2 >> info
echo 'nodes: '$1 >> info

echo $1 
echo $name

#Copy the right input file
cp ../../../input/input-$2 ./input


sh ~/local/src/power/setcpufreq.sh 1200000 0 15

srun --nodes=$1 --ntasks=$2 -ppbatch -e sweep.err -o out.dat --auto-affinity=start=0,verbose,cpt=1 ../sweepCL.sh $2

#Reset all cores back to original freq which is 2600000 after the run
#sh ../../../../../setcpufreq.sh 2600000 0 15
sh ~/local/src/power/setcpufreq.sh 2600000 0 15


#srun --nodes=$1 --ntasks=$2 -ppbatch -e sweep.err -o sweep.dat --cpu_bind=sockets sh ../sweepCL.sh

