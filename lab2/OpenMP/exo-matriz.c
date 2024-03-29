#include <stdio.h>
#include <stdlib.h>

#define NRA 62                 /* numero de linhas em A */
#define NCA 15                 /* numero de colunas em A */
#define NCB 7                  /* numero de colunas em B */

int main (int argc, char *argv[]) {
int	tid, nthreads, i, j, k, chunk;
double	a[NRA][NCA],           /* A  */
	b[NCA][NCB],           /* B  */
	c[NRA][NCB];           /* C (resultado de A x B) */

  /* Inicializações */
  
  for (i=0; i<NRA; i++)
    for (j=0; j<NCA; j++)
      a[i][j]= i+j;
 
  for (i=0; i<NCA; i++)
    for (j=0; j<NCB; j++)
      b[i][j]= i*j;

  for (i=0; i<NRA; i++)
    for (j=0; j<NCB; j++)
      c[i][j]= 0;

  /* Calculo */
  for (i=0; i<NRA; i++)    {
    for(j=0; j<NCB; j++)       
      for (k=0; k<NCA; k++)
        c[i][j] += a[i][k] * b[k][j];
  }

/*** Imprime os resultados ***/
printf("******************************************************\n");
printf("Resultado:\n");
for (i=0; i<NRA; i++)
  {
  for (j=0; j<NCB; j++) 
    printf("%6.2f   ", c[i][j]);
  printf("\n"); 
  }
printf("******************************************************\n");
printf ("Acabou.\n");

}
