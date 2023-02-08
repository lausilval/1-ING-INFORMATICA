//
// Created by 34662 on 21/12/2021.
//

#ifndef BOLETIN5_2_FECHA_H
#define BOLETIN5_2_FECHA_H

#include <stdlib.h>
#include <stdio.h>

// Estructura de fecha
typedef struct {
    int dia;
    int mes;
    int anho;
} Date;

//Declaración de funciones

//Función que guarda los valores de una fecha dada
Date Ler();

//Función que calcula la distancia entre dos fechas
int CalcularDistancia(Date fecha1, Date fecha2);

//Función que muestra una fecha en distintos formatos
void Mostrar(Date d, char f[]);

//Función que calcula si un año es Bisiesto
int esBisiesto(int anho);

//Función que calcula el valor de una fecha en ordinal
int ordinal(Date date);
#endif //BOLETIN5_2_FECHA_H
