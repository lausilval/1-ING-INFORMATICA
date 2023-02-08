/*
    Autora : Laura Silva Loureiro
    Data :  31/03/2022
    Ejercicio : Practica 2 -> VACUNODROMO
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vacunodromo.h"


int main(int argc, char *argv[])
{
    VACUNODROMO vacunodromo;
    crear_vacunodromo(&vacunodromo);
    //Codigo reutilizado de un ejercicio de programacion I:
    if (argc >= 2 && strcmp(argv[1], "-f")==0) {
        //Declaración de variables
        FILE *file;
        file = fopen(argv[2], "rt");
        anadir_vacunodromo_fichero(&vacunodromo, file);
        printf("Se añadieron los pacientes del fichero. \n");
    }
        //MENU PRINCIPAL
        char opcion;
        do {
            printf("\n------------------%s-------------------", vacunodromo.nombreVacunodromo);
            printf("\n1. Imprimir vacunodromo");
            printf("\n2. Vacunar siguiente paciente ");
            printf("\n3. Nuevo paciente: ");
            printf("\n0. Salir");
            printf("\nSeleccione una opcion: ");
            scanf(" %c", &opcion);
            switch (opcion) {
                case '1': //Imprimir vacunodromo
                    imprimir_vacunodromo(vacunodromo);
                    break;
                case '2': //Vacunar siguiente paciente
                    vacunar_vacunodromo(&vacunodromo);
                    break;
                case '3': //Nuevo paciente
                    anadir_vacunodromo(&vacunodromo);
                    break;
                case '0':
                    destruir_vacunodromo(&vacunodromo);
                    printf("Saliendo del programa... \n");
                    break;//Salir
                default:
                    printf("Opcion incorrecta\n");
            }
        } while (opcion != '0');
    return(EXIT_SUCCESS);
}

