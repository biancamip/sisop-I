#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

int N = 15;  // Tamanho do buffer onde se escreve/le.
int i = 0;  // Numero da entrada no buffer onde se escreveu/leu pela ultima vez.

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int um_resultado(int arg) { // Função exemplo. Poderia calcular qq coisa.
   return (arg*2 + 1);
}

void* produce(void* buffer) {
   // Armazena na entrada 'i' um resultado, e incrementa i.
   // buffer é usado como se fosse uma fila.

   // Usa um Mutex para garantir que o buffer seja inicializado
   // inteiramente antes que uma thread consumidora o leia.
   // Isso SÓ funciona porque o MESMO mutex 'lock' é usado
   // pelas threads consumidoras ao fazerem sua leitura no buffer.
   pthread_mutex_lock( &lock );
   for (int i=0 ; i<N ; i++)
      ((int*)buffer)[i] = um_resultado(i);
   pthread_mutex_unlock( &lock );
   printf("Thread produtora produziu %d dados.\n", N);
   return(0);
}

void* consume(void* buffer) {
   // Lê a entrada 'i', e incrementa i.
   // buffer é usado como se fosse uma fila.
   // Pega 'lock' antes de fazer a leitura.
   // Como 'lock' é também usado pela thread produtora, isso
   // garante que a leitura não será feita ao mesmo tempo
   // que o consumidor escreve no buffer.
   pthread_mutex_lock( &lock );
   int res = ((int*)buffer)[i];
   printf("Thread leu e obteve %d.\n", res);
   i = (i+1) % N;
   pthread_mutex_unlock( &lock );
   return(0);
}

int main(void)
{
	pid_t   pid;
   pthread_t thread_prod, thread_cons[N];
   int* the_buffer = (int*) malloc(N * sizeof(int));
   int ii;
   int res;

   pthread_create( &thread_prod, NULL, produce, the_buffer );
   pthread_join( thread_prod, NULL ) ;
   for (ii=0 ; ii<N ; ii++) 
      pthread_create( &thread_cons[ii], NULL, consume, the_buffer );

   for (ii=0 ; ii<N ; ii++) 
      pthread_join(thread_cons[ii], NULL);
   return(0);
}
