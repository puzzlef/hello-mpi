#include <cstdio>
#include "inc/main.hxx"

using namespace std;




#pragma region CONFIGURATION
#ifndef MAX_THREADS
/** Maximum number of threads to use. */
#define MAX_THREADS 32
#endif
#ifndef REPEAT_METHOD
/** Number of times to repeat each method. */
#define REPEAT_METHOD 1
#endif
#pragma endregion




#pragma region METHODS
#pragma region PERFORM EXPERIMENT
/**
 * Perform the experiment.
 * @param p process rank (current process id)
 * @param P number of processes
 */
void runExperiment(int p, int P) {
  #pragma omp parallel
  {
    int t = omp_get_thread_num();
    printf("P%02d.T%02d: Hello MPI\n", p, t);
  }
}


/**
 * Main function.
 * @param argc argument count
 * @param argv argument values
 * @returns zero on success, non-zero on failure
 */
int main(int argc, char **argv) {
  char pname[MPI_MAX_PROCESSOR_NAME];
  int p = 0, P = 0, lpname = 0;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &P);
  MPI_Comm_rank(MPI_COMM_WORLD, &p);
  MPI_Get_processor_name(pname, &lpname);
  omp_set_num_threads(MAX_THREADS);
  printf("P%02d: NAME=%s\n", p, pname);
  printf("P%02d: OMP_NUM_THREADS=%d\n", p, MAX_THREADS);
  MPI_Barrier(MPI_COMM_WORLD);
  runExperiment(p, P);
  MPI_Finalize();
  return 0;
}
#pragma endregion
