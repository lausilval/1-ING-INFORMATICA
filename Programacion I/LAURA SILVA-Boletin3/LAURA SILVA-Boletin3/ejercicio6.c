/*
    Autor : Laura Silva
    Data : 04/11/2021
    Ejercicio : 6
        Repetide o exercicio, pero agora lendo os datos dun arquivo datos.txt, e gardando os resultaos nun
arquivo datos_ordenados.txt.

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
//Función que ordena un vector de menor a mayor (metodo burbuja)
int ordenar(int vec[],int tamaño)
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

}

//Programa principal
int main(void)
{
    FILE *file;
    int i = 0;
    int vector[10];

    //Abrimos el fichero
    file = fopen("datos.txt", "rt");

    if(file)
    {
        while(!feof(file)) //Mientras no se termine el fichero
        {
            fscanf(file, "%d", &vector[i]); //Guardamos los datos en el vector
            i++;
        }

    }
    else
    {
        printf("Erro na abertura do arquivo.\n");
        exit(1);
    }
    fclose(file); //Cerramos el fichero

    ordenar(vector,10);


    //Abrimos el 2º fichero de manera que podamos escribir
    FILE *file2;
    file2 = fopen("datos_ordenados.txt", "wt");

    if(file2)
    {
        fprintf(file2,"El vector ordenado es:\n ");
        for (int k=0; k<10; k++)  //Imprimimos el vector
        {
            fprintf(file2,"\t%d\n", vector[k]);
        }
        fprintf(file2,"EL valor minimo es: %d\n", minimo(vector));
        fprintf(file2,"El valor maximo es: %d\n", maximo(vector));
        fprintf(file2,"La media es: %0.2f\n", media(vector));
    }
    else
    {
        printf("Erro na abertura do arquivo.\n");
        exit(1);
    }
    fclose(file2);
    return EXIT_SUCCESS;
}
