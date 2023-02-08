/*
    Autor : Laura Silva
    Data :  03/03/2022
    Ejercicio : P1_v3

*/


#include <stdio.h>
#include <stdlib.h>
#include "vectordinamico.h"


//FUNCIONES:

//Funcion imprimir:
void imprimir(vectorD v);
//Funcion SumaEscalar:
vectorD SumaEscalar(vectorD v);

int main(int argc, char** argv)
{
    vectorD vector = NULL, vectorSuma = NULL;  //declaramos el vector
    short longitud, i, j, longitudArgc; // variables tamanho y recorrido //posicion,
    TELEMENTO valor;   //valor a introducir en el vector  //, posicionElemento
    char opcion;  //variable del menu

    //printf("%d\n", argc);
    if(argc >= 2)  //Si introducimos el vector como argumento
    {
        longitudArgc = (short)(argc-1);    //La longitud del vector será el nº de argumentos de argc -1(el nombre)
        crear(&vector, longitudArgc);
        j=0;
        while( j < longitudArgc)
        {
            asignar(&vector, j,atoff(argv[j+1]));  //Asignamos los cracteres convertidos a float
            j++;
        }
        //imprimir(vector);
    }

        do {
            printf("\n-------------------------------\n");
            printf("\na) Crear vector v");
            printf("\nb) Liberar vector: ");
            //printf("\nc) Obtener elemento: ");
            printf("\nc) Imprimir: ");
            printf("\nd) Suma Escalar a vector: ");
            printf("\ns) Salir");
            printf("\n-------------------------------\n");
            printf("\nOpcion: ");
            scanf(" %c", &opcion);   //importante el espacion antes del %c
            switch (opcion) {
                case 'a':  //Crear vector v
                    if(vector !=0)  //Opcion para introducir los argumentos por argc
                    {
                        printf("Había un vector creado, borrando vector... \n");
                        liberar(&vector);
                    }
                    do {
                        printf("Longitud del vector v: ");
                        scanf("%hd", &longitud);
                    }while(longitud <= 0);
                    crear(&vector, longitud);
                    //Asignar valores a v
                    for (i = 0; i < longitud; i++) {
                        printf("vector[%d]: ", i);
                        scanf("%f", &valor);
                        asignar(&vector, i, valor);
                    }
                    break;
                case 'b':
                    liberar(&vector);
                    break;
                    //Depuracion del programa:
                /*case 'c':
                    if (vector != 0) {
                        do {
                            printf("Introduce la posición: ");
                            scanf("%d", &posicion);
                        } while (posicion > longitud || posicion < 1);
                        posicionElemento = recuperar(vector, posicion - 1);
                        printf("El elemento que se encuentra en vector[%d] es %0.2f (POSICION %d)\n", posicion - 1,
                               posicionElemento, posicion);
                    } else printf("El vector no existe\n");
                    break;*/
                case 'c':
                    imprimir(vector);
                    break;
                case 'd':
                    if(vector != 0)
                    {
                        vectorSuma = SumaEscalar(vector);
                        printf("El vector original es: \n");
                        imprimir(vector);
                        printf("El vector con el escalar es: \n");
                        imprimir(vectorSuma);
                        liberar(&vectorSuma);
                    }
                    else {
                        printf("El vector no existe\n");
                    }
                    break;
                case 's':
                    liberar(&vector);
                    printf("Saliendo del programa\n");
                    break;
                default:
                    printf("Opcion incorrecta\n");
            }
        } while (opcion != 's');

    return (EXIT_SUCCESS);
}

//FUNCIONES:

//Funcion imprimir:
void imprimir(vectorD v)
{
    short i, tamanho;
    tamanho = longitudVector(v);

    if (v != 0)
    {
        for(i=0; i< tamanho; i++)
        {
            printf("\tvector[%d] = %0.2f\n", i, recuperar(v,i));
        }
    }
    else
    {
        printf("Error en imprimir,\n");
    }
}

//Funcion SumaEscalar:
vectorD SumaEscalar(vectorD v)
{
    if (v != 0) {
        short tamanho, i;
        float escalar;
        TELEMENTO telemento;
        vectorD nuevoVector;

        printf("Introduce el escalar: ");   //Pedimos el escalar a sumar
        scanf("%f", &escalar);

        tamanho = longitudVector(v);    //Tamanho del nuevo vector
        crear(&nuevoVector,tamanho);
        for(i=0; i< tamanho; i++)
        {
            telemento = recuperar(v,i) + escalar;    //Valores del vector que recibimos + suma
            asignar(&nuevoVector,i, telemento);  //Asignacion
        }
        return nuevoVector;
    }
    else
    {
        printf("El vector no existe\n");
        return 0;
    }
}