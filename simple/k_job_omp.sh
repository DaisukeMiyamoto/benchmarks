#!/bin/bash -x

#PJM --rsc-list "node=1"
#PJM --rsc-list "elapse=00:10:00"
#PJM --stg-transfiles all
#PJM --mpi "use-rankdir"
#PJM --stgin "/home/hp120263/k00634/benchmarks/simple/simple_bench_fcc.out ./"
#PJM --stgout "rank=* %r:./prof_stat1/* /data/hp120263/k00634/result/prof/bench/%j_stat1/"
#PJM --stgout "rank=* %r:./prof_stat2/* /data/hp120263/k00634/result/prof/bench/%j_stat2/"
#PJM --stgout "rank=* %r:./prof_stat4/* /data/hp120263/k00634/result/prof/bench/%j_stat4/"
#PJM --stgout "rank=* %r:./prof_stat8/* /data/hp120263/k00634/result/prof/bench/%j_stat8/"
#PJM -s

. /work/system/Env_base

PROF_STAT_OMP1="fapp -C -d ./prof_stat1 -Ihwm -Hevent=Statistics -L1"
PROF_STAT_OMP2="fapp -C -d ./prof_stat2 -Ihwm -Hevent=Statistics -L1"
PROF_STAT_OMP4="fapp -C -d ./prof_stat4 -Ihwm -Hevent=Statistics -L1"
PROF_STAT_OMP8="fapp -C -d ./prof_stat8 -Ihwm -Hevent=Statistics -L1"

MPIEXEC="mpiexec"

echo "OMP1"
export OMP_NUM_THREADS=1
time ${PROF_STAT_OMP1} ${MPIEXEC} ./simple_bench_fcc.out

echo "OMP2"
export OMP_NUM_THREADS=2
time ${PROF_STAT_OMP2} ${MPIEXEC} ./simple_bench_fcc.out

echo "OMP4"
export OMP_NUM_THREADS=4
time ${PROF_STAT_OMP4} ${MPIEXEC} ./simple_bench_fcc.out

echo "OMP8"
export OMP_NUM_THREADS=8
time ${PROF_STAT_OMP8} ${MPIEXEC} ./simple_bench_fcc.out

