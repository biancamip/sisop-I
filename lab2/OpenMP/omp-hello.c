#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main (int argc, char *argv[]) {
int nprocs = -1;
#pragma omp parallel 
  {
     nprocs = omp_get_num_threads();
     printf("Oi mundo! (Executando com %d fluxos)\n", 
                                              nprocs);
  }  /* Sincronizacao */
  printf("Isso eh impresso por apenas uma thread.\n");
}

