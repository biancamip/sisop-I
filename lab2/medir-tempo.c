#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>


int main (int argc, char *argv[]) {
   struct timeval  first, second, lapsed;
   struct timezone tzp;
   long int tempo_micro_sec;

   printf("Sleeping during 3 seconds....\n") ;

   gettimeofday (&first, &tzp);
   sleep(3);
   gettimeofday (&second, &tzp);

   if (first.tv_usec > second.tv_usec) {
      second.tv_usec += 1000000;
      second.tv_sec--;
   }
   lapsed.tv_usec = second.tv_usec - first.tv_usec;
   lapsed.tv_sec  = second.tv_sec  - first.tv_sec;
   tempo_micro_sec = lapsed.tv_sec*1000000+lapsed.tv_usec;
   printf("Timing gettimeofday(): %ld micro-sec...\n", tempo_micro_sec);
}
