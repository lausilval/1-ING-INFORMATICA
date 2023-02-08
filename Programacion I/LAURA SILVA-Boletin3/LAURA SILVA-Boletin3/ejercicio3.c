/*
    Autor : Laura Silva
    Data : 26/10/2021
    Ejercicio : 3
        Escribir unha función Ordenar que teña un vector de enteiros e o seu tamaño como parámetros
    formais, e que ordene os valores dentro do vector de menor a maior. Para o ordenamento
    empregade o método da burbulla. Este método percorre un vector varias veces ata que se completa
    unha iteración completa sen facer cambios. En cada iteración do bucle vaise comparando cada
    elemento do vector co seguinte, e cando ese par de elementos non están ordenados
    intercámbianse. Deste xeito os valores máis pequenos iranse desprazando cara as posicións máis
    baixas do vector cun desprazamento en cada iteración, ata que atopan o lugar que lles
    corresponde.
*/

#include <stdio.h>
#include <stdlib.h>

#define N 8

//Función que muestra el vector
void aMostrar(int vec[])
{
    int j;
    printf("\t -vector: ");
    for(j=0;j<N;j++)
        printf("%i, ", vec[j]);
}

//Función que ordena un vector de menor a mayor (metodo burbuja)
 void ordenar(int vec[],int tamaño)
{
    int i, j, x;
    for(i=0; i < tamaño; i++)
    {
        for(j=0; j < (tamaño-1); j++)
        {
            if(vec[j] > vec[j+1])
            {
                x = vec[j];
                vec[j] = vec[j+1];
                vec[j+1] = x;
            }
        }

    }
    aMostrar(vec);
}

//Programa principal
int main(void)
{
    //Declaración de variables
    int i,vec[N];
    //Lectura de datos dada por el usuario
    for(i=0; i<N; i++)
    {
        printf("Valor de vec[%d]:", i);
        scanf("%d", &vec[i]);    //Guarda el valor en el elemento i del vector
    }

    //Resolución del problema con la función ordenar

    //Mostramos el vector original
    printf("El vector original es: \n");
    aMostrar(vec);
    //Salto de linea
    printf(" \n");
    //Muestra el resultado del vector ordenado
    printf("EL vector ordenado es: \n");
    ordenar(vec,N);

    return EXIT_SUCCESS;

}