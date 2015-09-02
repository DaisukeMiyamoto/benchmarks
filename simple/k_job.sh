#!/bin/bash -x

#PJM --rsc-list "node=1"
#PJM --rsc-list "elapse=00:10:00"
#PJM --stg-transfiles all
#PJM --mpi "use-rankdir"
#PJM --stgin "/home/hp120263/k00634/benchmarks/simple/simple_bench_fcc.out ./"
#PJM --stgout "rank=* %r:./prof_cache/* /data/hp120263/k00634/result/prof/bench/%j_cache/"
#PJM --stgout "rank=* %r:./prof_perf/* /data/hp120263/k00634/result/prof/bench/%j_perf/"
#PJM --stgout "rank=* %r:./prof_stat/* /data/hp120263/k00634/result/prof/bench/%j_stat/"
#PJM --stgout "rank=* %r:./prof_inst/* /data/hp120263/k00634/result/prof/bench/%j_inst/"
#PJM --stgout "rank=* %r:./prof_mem/* /data/hp120263/k00634/result/prof/bench/%j_mem/"
#PJM -s

. /work/system/Env_base
PROF_CACHE="fapp -C -d ./prof_cache -Ihwm -Hevent=Cache -L1"
PROF_PERF="fapp -C -d ./prof_perf -Ihwm -Hevent=Performance -L1"
PROF_STAT="fapp -C -d ./prof_stat -Ihwm -Hevent=Statistics -L1"
PROF_INST="fapp -C -d ./prof_inst -Ihwm -Hevent=Instructions -L1"
PROF_MEM="fapp -C -d ./prof_mem -Ihwm -Hevent=MEM_access -L1"

MPIEXEC="mpiexec"

time ${PROF_CACHE} ${MPIEXEC} ./simple_bench_fcc.out
time ${PROF_PERF} ${MPIEXEC} ./simple_bench_fcc.out
time ${PROF_STAT} ${MPIEXEC} ./simple_bench_fcc.out
time ${PROF_INST} ${MPIEXEC} ./simple_bench_fcc.out
time ${PROF_MEM} ${MPIEXEC} ./simple_bench_fcc.out

