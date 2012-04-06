#!/bin/bash
#MSUB -l nodes=2
#MSUB -q pbatch
#MSUB -l walltime=00:40:00

export PKG_MINW_MINS=0x38198
export PP0_MINW_MINS=0x38198
export DRAM_MINW_MINS=0x38078
export MSR_PKG_POWER_LIMIT=0x38198
export MSR_PP0_POWER_LIMIT=0x0
export MSR_DRAM_POWER_LIMIT=0x0
export MSR_RANK_MOD=16
export BLR_BENCHMARK=../bin/cg.D.16
#LD_LIB_PATH should not be needed, ideally
#export LD_LIBRARY_PATH=$(HOME)/local/src/power/rapl/libmsr/lib:LD_LIBRARY_PATH

#Run 16 tasks with CG.D to see whether the min power is more than 51W
#Also test what happens to power if you have two nodes
sh ./runCG.sh 1 1 16 16
sh ./runCG.sh 2 2 8 8

