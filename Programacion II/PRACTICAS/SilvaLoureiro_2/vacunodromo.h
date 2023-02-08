/*
    Autora : Laura Silva Loureiro
    Data :  31/03/2022
    Ejercicio : Practica 2 -> VACUNODROMO
*/
#ifndef P2_V2_VACUNODROMO_H
#define P2_V2_VACUNODROMO_H

#include <stdio.h>
#include "TAD/cola.h"

//Estructura del VACUNODROMO
typedef struct{
    char nombreVacunodromo[MAX_NAME_LENGTH];
    int numeroPacientes;
    TCOLA colaPacientes;
} VACUNODROMO;

//FUNCIONES VACUNODROMO
///Funcion que Crea el vacunodromo
void crear_vacunodromo(VACUNODROMO *v);
///Funcion que Libera memoria
void destruir_vacunodromo(VACUNODROMO *v);
/// Funcion que imprime
void imprimir_vacunodromo(VACUNODROMO v);
///Funcion que añade un paciente a la cola con su correspondiente lista de vacunas
void anadir_vacunodromo(VACUNODROMO *v);
///Funcion que vacuna al primer paciente de la cola
void vacunar_vacunodromo(VACUNODROMO *v);
/// Funcion que añade a los pacientes del fichero si argc >= 2
void anadir_vacunodromo_fichero(VACUNODROMO *v, FILE* file);

#endif //P2_V2_VACUNODROMO_H
