#pragma once
#include <mpi.h>




// TRY
// ---
// Log error if MPI function call fails.

#ifndef TRY_MPI
void tryMpi(int err, const char* exp, const char* func, int line, const char* file) {
  char buf[MPI_MAX_ERROR_STRING]; int BUF;
  if (err == MPI_SUCCESS) return;
  MPI_Error_string(err, buf, &BUF);
  fprintf(stderr,
    "%s\n"
    "  in expression %s\n"
    "  at %s:%d in %s\n",
    buf, exp, func, line, file);
  MPI_Abort(MPI_COMM_WORLD, err);
}

#define TRY_MPI(exp)  tryMpi(exp, #exp, __func__, __LINE__, __FILE__)
#define TRY_MPIE(exp) PERFORME(TRY_MPI(exp))
#define TRY_MPIW(exp) PERFORMW(TRY_MPI(exp))
#define TRY_MPII(exp) PERFORMI(TRY_MPI(exp))
#define TRY_MPID(exp) PERFORMD(TRY_MPI(exp))
#define TRY_MPIT(exp) PERFORMT(TRY_MPI(exp))
#endif

#ifndef TRY
#define TRY(exp)  TRY_MPI(exp)
#define TRYE(exp) TRY_MPIE(exp)
#define TRYW(exp) TRY_MPIW(exp)
#define TRYI(exp) TRY_MPII(exp)
#define TRYD(exp) TRY_MPID(exp)
#define TRYT(exp) TRY_MPIT(exp)
#endif
