/*
    Autor : Laura Silva
    Data : 04/11/2021
    Ejercicio : 7
        Consideremos o arquivo weatherdata-420-72.csv (abrídeo co Bloc de Notas) que contén
    información meteorolóxica en formato .cvs, onde os datos van entre aspas (“ “) e separados por
    comas. Os datos corresponden aos parámetros que se indican na primeira fila do arquivo: Data de
    recollida de datos, Ubicación da estación meteorolóxica, Temperatura (ºC), Precipitación (mm),
    Velocidade do vento (m/s), Humidade relativa, Radiación solar (MJ/m²).
    Escribide un programa que a partires dese arquivo xere outro co mesmo nome e extension .txt,
    onde non aparezan os datos da primeira fila, e se eliminen os 3 carateres “ , /.

*/

#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    //Declaración de variables
    FILE *file;
    char c;
    //Abrimos el fichero
    file = fopen("weatherdata-420-72.csv", "rt");

    if (file)
    {

        //Creamos el segundo fichero
        FILE *file2;
        file2 = fopen("weatherdata-420-72.txt", "wt");

        if (file2)
        {
            do {
                fscanf(file, "%c", &c);  //para eliminar la primera linea
            }while(c != '\n');

            while (!feof(file))
            {
                fscanf(file, "%c", &c); //Recorriendo caracter a caracter

                if (c != '"' && c != ',' && c != '/') //Si es un caracter de estos no lo imprime
                {
                    fprintf(file2, "%c", c); //Imprime el resto
                }
                else
                {
                    c =' ';
                    fprintf(file2, "%c", c); //Cuando se encuentre con " , / imprima un espacio
                }

            }
            fclose(file2);
        }
        else
        {
            printf("Erro na abertura do arquivo.\n");
            exit(1);
        }

        fclose(file);
    }
    else
    {
        printf("Erro na abertura do arquivo.\n");
        exit(1);
    }

    return EXIT_SUCCESS;
}