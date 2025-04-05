/*
	Name: Lab#2
	Copyright: 2021-22
	Author: Prof. Joao Costa
	Date: 06/04/22 17:24
	Description: 
		Parallelizing an inner loop with dependences
	
			for (iter=0; iter<numiter; iter++) {
				for (i=0; i<size-1; i++) {
					V[i] = f( V[i], V[i+1] );
				}
			}
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define TOTALSIZE 1000
#define NUMITER 200

/*
* DUMMY FUNCTION
*/
#define f(x,y) ((x + y) / 2.0)

int main(int argc, char *argv[]) {
  int i, iter;

  // Alocação dos vetores
  double *V1 = (double *)malloc(TOTALSIZE * sizeof(double));
  double *V2 = (double *)malloc(TOTALSIZE * sizeof(double));

  // Inicialização do vetor V1
  for(i = 0; i < TOTALSIZE; i++) {
    V1[i] = 0.0 + i;
  }

  // Laço de iterações
  for(iter = 0; iter < NUMITER; iter++) {

    // Processamento paralelo dos elementos
    #pragma omp parallel for
    for(i = 0; i < TOTALSIZE - 1; i++) {
      V2[i] = f(V1[i], V1[i+1]);
    }

    // Troca de ponteiros
    double *temp = V1;
    V1 = V2;
    V2 = temp;
  }

  // Saída dos valores finais
  printf("Output:\n");
  for(i = 0; i < TOTALSIZE; i++) {
    printf("%4d %f\n", i, V1[i]);
  }

  // Liberação de memória
  free(V1);
  free(V2);

  return 0;
}
