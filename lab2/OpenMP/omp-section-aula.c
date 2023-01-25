#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void compute(int index, int N, int* data )  {
    int i_start, i_end, i ;
    i_start = index*N/4+1;
    i_end  = (index+1)*N/4;
    printf("Working on data[%d, %d]\n", i_start,i_end);
    for (i=i_start; i<i_end;i++)
		data[i] = i*i;
}


int main (int argc, char *argv[]) {
int tid = 17;
int N = 10000;
int i=0;
int data[N];

for (i=0 ; i<N ; i++) data[i] = i;

#pragma omp parallel num_threads(4) private(tid)
  {
  tid = omp_get_thread_num();
#pragma omp sections 
    {
    #pragma omp section
      { compute(0,N,data) ; }
    #pragma omp section
      { compute(1,N,data) ; }
    #pragma omp section
      { compute(2,N,data) ; }
    #pragma omp section
      { compute(3,N,data) ; }
    }  /* Fim das sections */
  }  /* Fim do bloco paralelo */
}
