/*
    Autor : Laura Silva
    Data : 04/11/2021
    Ejercicio : 5
        Escribide un programa que realice as operacións indicadas a continuación sobre unha secuencia de
    enteiros almacenada nun arquivo. O programa deber ler os datos do arquivo e gardalos nun vector.
    Facede a lectura ata chegar ao final do arquivo (empregade o valor devolto pola función de lectura
    para detectalo). Implementade 3 funcións para: cálculo de máximo, mínimo e media. Estes valores
    deben imprimirse dende a función main().

*/

#include<stdio.h>
#include <stdlib.h>

//Calcula el maximo elemento en el vector
int maximo(int vector[])
{
    int maximo,i;
    maximo = vector[0];
    for(i=1; i<10; i++)
    {
        if (maximo < vector[i])
        {
            maximo = vector[i];
        }
    }
    return maximo;
}
//Calcula el minimo elemento en el vector
int minimo(int vector[])
{
    int minimo,i;
    minimo = vector[0];
    for(i=1; i<10; i++)
    {
        if (minimo > vector[i])
        {
            minimo = vector[i];
        }
    }
    return minimo;
}
// Retorna la suma de los elementos de un vector
float Sumador(int vector[])
{
    int i=0, suma=0;
    while(i < 10)
    {
        suma = suma + vector[i];
        i++;
    }
    return suma;
}
//Función que calcula la media de los elementoe de un vector
float media(int vector[])
{
    float  media;
    media = Sumador(vector) / 10;

    return media;
}
//Programa principal
int main(void) {
    //Declaración de variables
    FILE *file;
    int i = 0;
    int vector[10];

    //Abrimos el fichero
    file = fopen("ej5.txt", "rt");

    if(file)
    {
        while(!feof(file)) //Mientras no se termine el fichero
        {
            fscanf(file, "%d", &vector[i]); //Guardamos los datos en el vector
            i++;
        }
        printf("El vector es: \n");
        for (int j=0; j<10; j++)  //Imprimimos el vector
        {
            printf("\t%d\n", vector[j]);
        }
        printf("\n");
    }
    else
    {
        printf("Erro na abertura do arquivo.\n");
        exit(1);
    }
    //Imprimimos resultados
    printf("El valor minimo es: %d\n", minimo(vector));
    printf("El valor maximo es: %d\n", maximo(vector));
    printf("La media es: %0.2f\n", media(vector));

    fclose(file); //Cerramos el fichero

    return EXIT_SUCCESS;
}

