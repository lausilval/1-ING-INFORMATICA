#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "matriz.h"

int main(int argc, char **argv) {
    if(argc == 5) { /*comprobar que el programa reciba todos los argumentos de entrada*/
        long tamanho = atol(argv[1]); /*tamanho del vector en cada iteracion*/
        long tamMax = atol(argv[2]); /*tamanho maximo del vector*/
        long paso = atol(argv[3]); /*paso que se incrementa en cada iteracion*/
        //unsigned char busqueda = atoi(argv[3]); /*numero de busquedas*/
        char *opcion = argv[4]; /*Tipo de busqueda que se va a realizar*/

        FILE *fp;
        if (strcmp(opcion, "suma") == 0) {

            fp = fopen("tiemposSumaMatrices.txt", "w");
        } else if (strcmp(opcion, "producto") == 0) {

            fp = fopen("tiemposProductoMatrices.txt", "w");
        } else {

            printf("La opcion de tipo de busqueda es incorrecta. Debe ser suma o producto");
            return -1;
        }
        
        for (tamanho = 1; tamanho <= tamMax; tamanho += paso) {
            //crear e inicializar las matrices
            matrizD m1, m2, aux;
            crearMatriz(&m1, tamanho);
            // inicializar(&m1);
            //imprimirMatriz(m1);
            crearMatriz(&m2, tamanho);
            //inicializar(&m2);
            crearMatriz(&aux, tamanho);

            clock_t start = clock();

            if (strcmp(opcion, "suma") == 0) {
                aux = suma(m1, m2);
            } else if (strcmp(opcion, "producto") == 0) {
                producto(m1, m2);
            } else {

                printf("La opcion de tipo de busqueda es incorrecta. Debe ser a o b");
                return -1;
            }
            clock_t end = clock();

            fprintf(fp, "%ld\t%4lf\n", tamanho, (end - start) / (double) CLOCKS_PER_SEC);
            printf("tamanho: %lu\t\tini.:%d\tfin:%d\t\ttiempo:%.4lf\n", tamanho, (int) start, (int) end,
                   (end - start) / (double) CLOCKS_PER_SEC);
            //liberar matrices
            destruirMatriz(&m1);
            destruirMatriz(&m2);
            destruirMatriz(&aux);

        }
        fclose(fp);
    }
    return (EXIT_SUCCESS);
}