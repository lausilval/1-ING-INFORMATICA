/*
    Autor : Laura Silva
    Data :  25/11/2021
    Ejercicio : 4
        . Creade un programa que lea un nome de arquivo e o almacene nunha estrutura con (só) dous
    campos: un para o nome base, e outro para a extensión. O nome do arquivo debe pasarse por liña
    de comandos, e a estrutura debe pasárselle como argumento a unha función que abra ese arquivo
    e imprima o seu contido por pantalla. A función ten que manexar os casos de nomes con extensión e
    sen ela.

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//Definimos la estructura
typedef struct
{
    char* nome;
    char* extension;

}Fichero;
//Función pedida por el ejercicio
void AbrirArquivo(Fichero fich);
//Función principal
int main(int argc, char *argv[])
{
    //Declaración de variables
    Fichero fich;
    //Reservamos memoria para los punteros
    fich.nome = (char*)malloc(60*sizeof(char));
    fich.extension = (char*)malloc(10*sizeof(char));
    int i,j;

    if(argc == 2)
    {
        i=0;
        while(argv[1][i] != '.' && argv[1][i] != '\0')      //Mientras que el nombre del archivo sea distinto a '.'//'\0
        {
            fich.nome[i] = argv[1][i];
            i++;
        }
        fich.nome[i] = '\0';    //Todos los string tiene que acabar en /0
        if(argv[1][i] == '.')       //Si el archivo tiene extension
        {
            i++;    //Saltar la posicion del punto
            j=0;
            while(argv[1][i] != '\0')
            {
                fich.extension[j] = argv[1][i];
                i++;
                j++;
            }
            fich.extension[j] = '\0';   //Todos los string tiene que acabar en /0
        }
        AbrirArquivo(fich);
    }
    else
    {
        printf("Error\n");
    }

    free(fich.nome);
    free(fich.extension);

    return EXIT_SUCCESS;
}
//Función que abre un archivo cuando le pasas el nombre por linea de comandos
void AbrirArquivo(Fichero fich)
{
    FILE *file;
    int i, j;
    char aux[70];   //Vector que va a guardar el Nombre del fichero

    for(i = 0; i < strlen(fich.nome);i++)   //Guardamos nombre
    {
        aux[i] = fich.nome[i];
        //printf("%c", fich.nome[i]);

    }
    if(strlen(fich.extension) > 0)      //Para saber si tiene extensión o no y añadirle el punto
    {
        aux[i] = '.';
        i++;
    }
    for(j = 0; j < strlen(fich.extension);j++)      //Guardamos extension
    {
        aux[i] = fich.extension[j];
        //printf("%c",fich.extension[j]);
        i++;
    }
    aux[i] = '\0';
    //printf("%s\n", aux);

    //Abrimos el fichero
    file = fopen(aux,"r");

    if(!file) //Error si no se puede abrir
    {
        printf("Error al abrir el fichero\n");
        exit(1);
    }
    else
    {
        char c;
        while(!feof(file)) //Mientras no se termine el fichero
        {
            fscanf(file, "%c", &c); //Imprimimos caracteres
            printf("%c", c);
        }
    }
    //Cerramos el archivo
    fclose(file);

}