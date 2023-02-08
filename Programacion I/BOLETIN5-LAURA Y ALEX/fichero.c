//
// Created by 34662 on 21/12/2021.
//

#include "fichero.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "meteo.h"

//Función que abre un archivo cuando le pasas el nombre por linea de comandos
//Retorna el nombre del archivo
FILE* AbrirArquivo(NombreFichero* nomefich)    //FUNCIONA BIEN
{
    FILE *file;
    int i, j;
    char* aux;   //Vector que va a guardar el Nombre del fichero
    aux = (char *) malloc(20*sizeof(char));

    for (i = 0; i < strlen(nomefich->nome); i++)   //Guardamos nombre
    {
        aux[i] = nomefich->nome[i];
        //printf("%c", nomefich->nome[i]);

    }
    if (strlen(nomefich->extension) > 0)      //Para saber si tiene extensión o no y añadirle el punto
    {
        aux[i] = '.';
        i++;
    }
    for (j = 0; j < strlen(nomefich->extension); j++)      //Guardamos extension
    {
        aux[i] = nomefich->extension[j];
        //printf("%c",nomefich->extension[j]);
        i++;
    }
    aux[i] = '\0';
    //printf("%s\n", aux);

    //Abrimos el fichero
    file = fopen(aux, "rt");
    rewind(file);
    return file;

}

//Función que cambia de un .csv a un .txt
FILE* cambioCsvaTxt(FILE* file, NombreFichero* nomefich)
{
    //Declaración de variables
    char c;
    int i;
    char *nombreTxt;   //Vector que va a guardar el NombreTxt del fichero
    nombreTxt = (char *) malloc(20 * sizeof(char));

    for (i = 0; i < strlen(nomefich->nome); i++)   //Guardamos nombreTxt
    {
        nombreTxt[i] = nomefich->nome[i];
        //printf("%c\n", nomefich->nome[i]);
    }
    nombreTxt[i] = '.';
    nombreTxt[i + 1] = 't';
    nombreTxt[i + 2] = 'x';
    nombreTxt[i + 3] = 't';
    nombreTxt[i + 4] = '\0';

    //printf("%s\n",nombre);
    FILE *file2;
    file2 = fopen(nombreTxt, "wt"); //Abrimos el fichero txt
    if (file) {
        //Creamos el segundo fichero
        if (file2) {
            do {
                fscanf(file, "%c", &c);  //para eliminar la primera linea
            } while (c != '\n');
            while (!feof(file)) {
                fscanf(file, "%c", &c); //Recorriendo caracter a caracter

                if (c != '"' && c != ',' && c != '/') //Si es un caracter de estos no lo imprime
                {
                    fprintf(file2, "%c", c); //Imprime el resto
                } else {
                    c = ' ';
                    fprintf(file2, "%c", c); //Cuando se encuentre con " , / imprima un espacio
                }
            }
            fclose(file2);
        }

    }
    rewind(file);
    file2 = fopen(nombreTxt, "rt"); //Abrimos el fichero txt
    rewind(file2);
    return file2;
}

//Función que cuenta el nº de lineas de un fichero
int cuentaLineas(FILE* file)
{
    int c=0,num_lineas=0;
    while((c = fgetc(file)) != EOF){
        if( c == '\n')
            num_lineas++;
        putchar(c);
    }
    rewind(file);
    return num_lineas;
}



