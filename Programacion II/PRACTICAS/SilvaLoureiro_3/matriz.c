//
// Created by 34662 on 31/03/2022.
//

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

//tipo de datos que contiene la matriz
typedef long TELEMENTO;

//Implementacion del TAD matriz
typedef struct {
    TELEMENTO *datos;
    long filas, columnas;
}STMATRIZ;


typedef STMATRIZ* matrizD; //puntero a estructura

//Funciones de manipulación de datos
void crearMatriz(matrizD *m, long tamanho)
{
    long i;
    srand (time(NULL)); // [Instrucción que inicializa el generador de números aleatorios]

    *m = (matrizD)malloc(sizeof(STMATRIZ));
    (*m)->filas = tamanho;
    (*m)->columnas = tamanho;
    (*m)->datos = (TELEMENTO*)malloc(tamanho*tamanho * sizeof(TELEMENTO));
    for (i = 0; i < tamanho * tamanho; i++) {        //Tambien ponia f en vez de c
        *(((*m)->datos) + i) = rand();
    }
}

matrizD suma(matrizD M1, matrizD M2)
{
    matrizD aux = 0;
    long i, k;

    if (M1 != 0 && M2 != 0) {
        if ((M1)->filas != (M2)->filas || (M1)->columnas != (M2)->columnas) {
            printf("El numero de filas y columnas deben ser iguales\n");
            return aux;
        }
        crearMatriz(&aux,(M1)->filas);
        for (i = 0; i < (aux)->filas; i++)
            for (k = 0; k < (aux)->columnas; k++) { (//aux)->filas
                *((aux)->datos + i * (aux)->columnas + k) = *((M1)->datos + i * (M1)->columnas + k) + *((M2)->datos + i * (M2)->columnas + k));
            }
        return aux;
    } else {
        printf("Alguna de las matrices no existe\n");
        return 0;
    }
}

matrizD producto(matrizD M1, matrizD M2)
{
    matrizD aux = 0;
    long i, k, l;
    if ((M1) != 0 && (M2) != 0) {
        if ((M2)->filas != (M1)->columnas) //(M1)->filas != (M2)->columnas
        {
            printf("El numero de columnas de la primera matriz y de filas de la segunda deben ser iguales\n");
            return aux;
        }

        crearMatriz(&aux, (M1) ->filas);
        for (i = 0; i < (M1)->filas; i++)
            for (k = 0; k < (M2)->columnas; k++) {
                *((aux)->datos + i * (M2)->columnas + k) = 0;
                for (l = 0; l < (M1)->columnas; l++) {
                    *((aux)->datos + i * (M2)->columnas + k) += *((M1)->datos + i * (M1)->columnas + l) * *((M2)->datos + l * (M2)->columnas + k);
                }
            }
        return aux;
    } else {
        printf("Alguna de las matrices no existe\n");
        return 0;
    }

}

void destruirMatriz(matrizD *M)
{
    if (*M != 0) {
        free((*M)->datos);
        free(*M);
    }
    else
    {
        printf("La matriz no existe \n");
    }
}


long obtenerElemento(int fila, int columna, matrizD M)
{
    long x;  //int

    if (M != 0) {
        if ((fila <= 0 || fila > M->filas) || (columna <= 0 || columna > M->columnas))  //Faltaban los iguales

        {
            printf("Ese elemento no existe\n");
            return 0;
        }
        //x = *((M->datos) + fila * M->columnas + columna);
        x = *((M->datos) + (fila-1) * M->columnas + (columna-1));
        return x;
    } else {
        printf("La matriz no existe\n");
        return 0;
    }
}

/*
void imprimirMatriz(matrizD M) {
    int i, k;

    if (M != 0) {
        for (i = 0; i < (*M).filas; i++) {
            for (k = 0; k < (*M).columnas; k++)
                printf("%ld ", *(((*M).datos) + i * (*M).columnas + k));   //M->filas
            printf("\n");
        }
        printf("\n");
    } else
        printf("La matriz no existe\n");
}*/

void imprimirMatriz(matrizD M) {
    long i, k;

    if (M != 0) {
        for (i = 0; i < M->filas; i++) {
            for (k = 0; k < M->columnas; k++)
                printf("%ld ", *((M->datos) + i * M->columnas + k));   //M->filas
            printf("\n");
        }
        printf("\n");
    } else
        printf("La matriz no existe\n");
}



