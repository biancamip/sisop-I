#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define NB_FILOSOFOS 5

pthread_t filosofo[NB_FILOSOFOS];
pthread_mutex_t palito[NB_FILOSOFOS];

void *atividade_filo(void* n) {
   int id_filo;
   int sec_pensando, sec_comendo;
   int pensando = 0;
   id_filo = (int) *((int*)n);

   srand(time(NULL));   // Initialization, should only be called once.
   sec_pensando = rand() % NB_FILOSOFOS;
   sec_comendo  = rand() % NB_FILOSOFOS;

   printf ("Filosofo %d pensando por %d sec...\n",id_filo, sec_pensando);
   sleep( sec_pensando );
   /* Agora o filosofo esta pronto para comer. Primeiro pega o palito id_filo
    * e logo depois pega o palito id_filo+1 % NB_FILOSOFOS.
    * Cada palito é protegido por um mutex.
    */
   pthread_mutex_lock(&palito[id_filo]);
   pthread_mutex_lock(&palito[(id_filo+1)%NB_FILOSOFOS]);
   printf ("Filosofo %d comendo por %d sec...\n",id_filo, sec_comendo);
   /* Leva um certo tempo a comer...*/
   sleep( sec_comendo );
   /* Libera os palitos */
   printf ("Filosofo %d acabou de comer.\n",id_filo);
   pthread_mutex_unlock(&palito[(id_filo+1)%NB_FILOSOFOS]);
   pthread_mutex_unlock(&palito[id_filo]);


   /* Observacao: esta implementacao pode levar a deadlock. */
   return(NULL);
}

int main() {
   int filo_ids[NB_FILOSOFOS];
   int filo_id;

   for(filo_id=0 ; filo_id<NB_FILOSOFOS; filo_id++)
      pthread_mutex_init(&palito[filo_id], NULL);

   for(filo_id=0 ; filo_id<NB_FILOSOFOS; filo_id++) {
      filo_ids[filo_id] = filo_id;
      pthread_create(&filosofo[filo_id], NULL, atividade_filo, &filo_ids[filo_id]);
   }

   for(filo_id=0 ; filo_id<NB_FILOSOFOS; filo_id++)
      pthread_join(filosofo[filo_id], NULL);

   for(filo_id=0 ; filo_id<NB_FILOSOFOS; filo_id++)
      pthread_mutex_destroy(&palito[filo_id]);

   return 0;
   }
