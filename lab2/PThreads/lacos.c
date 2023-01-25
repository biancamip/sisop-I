#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

#define NBTHREADS 5
int N = 50;  
int* buffer;

struct limites {
   int inf;
   int sup;
};

int um_resultado(int arg) { // Função exemplo. Poderia calcular qq coisa.
   return (arg*2 + 1);
}

void* compute(void* param) {
   struct limites * l;
   l = (struct limites *) param;
   for (int i=l->inf ; i<l->sup ; i++)
      buffer[i] = um_resultado(i);
   printf("A thread calculou iterações indo de %d a %d.\n", l->inf, l->sup-1);
   return(0);
}

int main(void)
{
	pid_t   pid;
   pthread_t thread[NBTHREADS];
   struct limites * lim;
   int i;
   int res;

   buffer = (int*) malloc(N * sizeof(int));
   // Quer-se paralelizar com NTHREADS um laço como:
   // for (i=0 ; i<N ; i++) buffer[i] = um_resultado(i);
   for (i=0 ; i<NBTHREADS ; i++) {
      lim = (struct limites *)malloc(sizeof(struct limites));
      lim->inf = i * (N/NBTHREADS);
      lim->sup = (i+1) * (N/NBTHREADS) ; 
      pthread_create( &thread[i], NULL, compute, lim );
   }

   for (i=0 ; i<NBTHREADS ; i++) 
      pthread_join(thread[i], NULL);
   return(0);
}
