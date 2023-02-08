//
// Created by 34662 on 17/02/2022.
//


#include <stdlib.h>
#include <stdio.h>

// Se vuelve a definir el tipo de datos que contiene el vector
typedef float TELEMENTO;

//Implementacion del TAD vectorD
typedef struct{
    TELEMENTO *datos;   //valores del vector
    int  tam;         //tamanho del vector
} STVECTOR;             //definicion del tipo de datos estructura

typedef STVECTOR *vectorD; //puntero a estructura

//Funciones de manipulacion de datos
//Funcion crear: asigna memoria y devuelve la asignacion al vector
void crear(vectorD * v, int longitud)
{
    int i;
    *v = (vectorD) malloc(sizeof(STVECTOR));
    (*v)->datos = (TELEMENTO*)malloc(longitud * sizeof(TELEMENTO));
    (*v)->tam = longitud;
    for(i = 0; i < longitud; i++)   //Inicializacion a 0 de las componentes del vector
    {
        *((*v)->datos + i) = 0;
    }
}

//Funcion asignar: Asigna un valor a una posicion del vector
void asignar(vectorD * v, int posicion, TELEMENTO valor)
{
    *((*v)->datos + posicion) = valor;
}

//Funcion liberar: Libera la memoria ocupada por el vector
void liberar(vectorD *v)
{
    if (*v != 0)
    {
        free((*v)->datos);
        free(*v);
        *v = NULL;
    }
    else
    {

        printf("El vector no existe\n");
    }
}

//Funcion recuperar: recibe como argumentos el vector y posicion y devuelve el TELEMENTO de esa posicion
TELEMENTO recuperar(vectorD v, int posicion)
{
    TELEMENTO x;

    if (v != 0)
    {
        x = v->datos[posicion];
        return x;
    }
    else
    {
        printf("El vector no existe\n");
        return 0;
    }
}

//Funcion longitudVector(): devuelve la longitud del vector
int longitudVector(vectorD v)
{
    int longitud;
    if (v != 0)
    {
        longitud = v->tam;
        return longitud;
    }
    else
    {
        printf("El vector no existe\n");
        return 0;
    }
}



