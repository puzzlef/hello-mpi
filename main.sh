#!/usr/bin/env bash
#SBATCH -N 2
#SBATCH -n 32
#SBATCH --mem-per-cpu=1024
# scl enable gcc-toolset-11 bash
# module load hpcx-2.7.0/hpcx-ompi
src="hello-mpi"
out="$HOME/Logs/$src$1.log"
module load openmpi/4.1.5
ulimit -s unlimited
printf "" > "$out"

# Download program
if [[ "$DOWNLOAD" != "0" ]]; then
  rm -rf $src
  git clone https://github.com/puzzlef/$src
fi
cd $src

# Fixed config
: "${TYPE:=double}"
: "${MAX_THREADS:=32}"
: "${REPEAT_BATCH:=5}"
: "${REPEAT_METHOD:=1}"
# Define macros (dont forget to add here)
DEFINES=(""
"-DTYPE=$TYPE"
"-DMAX_THREADS=$MAX_THREADS"
"-DREPEAT_BATCH=$REPEAT_BATCH"
"-DREPEAT_METHOD=$REPEAT_METHOD"
)

# Run
mpic++ ${DEFINES[*]} -std=c++17 -O3 -fopenmp main.cxx -o "a$1.out"
stdbuf --output=L mpiexec -np 2 --map-by node ./"a$1.out" 2>&1 | tee -a "$out"
