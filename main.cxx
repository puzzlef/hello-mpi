#include <random>
#include <cstdio>
#include <iostream>
#include <mpi.h>

using namespace std;




// Fixed config
#ifndef REPEAT_METHOD
#define REPEAT_METHOD 1
#endif




// PERFORM EXPERIMENT
// ------------------

void runExperiment(int p, int P) {
  random_device dev;
  default_random_engine rnd(dev());
  int repeat = REPEAT_METHOD;
  printf("%d: Hello MPI\n", p);
}


int main(int argc, char **argv) {
  int p = 0, P = 0;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &P);
  MPI_Comm_rank(MPI_COMM_WORLD, &p);
  runExperiment(p, P);
  MPI_Finalize();
  return 0;
}
