//
// Created by 34662 on 21/12/2021.
//

#include <stdio.h>

#ifndef BOLETIN5_2_FICHERO_H
#define BOLETIN5_2_FICHERO_H
//Definimos la estructura
typedef struct
{
    char* nome;
    char* extension;
}NombreFichero;


//Función que abre un archivo cuando le pasa el nombre
FILE* AbrirArquivo(NombreFichero* fich);

//Función que cambia de un .csv a un .txt
FILE* cambioCsvaTxt(FILE* file, NombreFichero* nomefich);

//Función que cuenta el nº de lineas de un fichero
int cuentaLineas(FILE* file);


#endif //BOLETIN5_2_FICHERO_H
