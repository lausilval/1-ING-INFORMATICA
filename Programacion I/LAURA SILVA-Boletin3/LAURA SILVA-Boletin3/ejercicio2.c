/*
    Autor : Laura Silva
    Data : 26/10/2021
    Ejercicio : 2
    Implementa un programa que dada unha data calquera (dd, mm, aa) nos devolva o valor ordinal do
    día (1-366) correspondente. Para iso, implementa dúas funcións: unha que a partir do dato do ano
    (parámetro formal aa), devolva un valor 0 ou 1 para indicar se é bisesto ou non; e outra función que
    invoque á anterior para determinar se o ano é bisesto ou non (cando sexa necesario) e que despois
    calcule o valor ordinal. Podedes crear un vector que conteña o número de días correspondente a
    cada mes (ao mes de febreiro podedes sumarlle o valor devolto pola primeira función para ter en
    conta se é bisesto ou non) e así facilitar o cálculo.
*/



#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Función que calcula si un anho es bisiesto
int esBisiesto(anho)
{
    return anho%4==0 && anho%100!=0 || anho%400==0? 1:0;
}

int ordinal(int dia, int mes, int anho)
{
    int suma = 0, cantdias = 0, i = 0;
    int bisiesto[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int nobisiesto[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (esBisiesto(anho) == 1)  //Si es bisiesto
    {
        if(dia > bisiesto[mes-1]) //Si los dias > diasmes
        {
            do {    //Volver a pedir datos al usuario mientras dias < diasmes
                printf("Introduce el día:", dia);
                scanf("%d", &dia);
                printf("Introduce el mes:", mes);
                scanf("%d", &mes);
                printf("Introduce el año:", anho);
                scanf("%d", &anho);
            }while(dia< bisiesto[mes-1]);
        }

        for (i = 1; i < mes; i++)
        {
            suma = suma + bisiesto[i];  //Suma los días de todos los meses
        }

        cantdias = suma + dia;  //Calcula la cantidad de días

        return cantdias;


    } else
    {
        if(dia > nobisiesto[mes-1])
        {
            do {
                printf("Introduce el día:", dia);
                scanf("%d", &dia);
                printf("Introduce el mes:", mes);
                scanf("%d", &mes);
                printf("Introduce el año:", anho);
                scanf("%d", &anho);
            }while(dia< nobisiesto[mes-1]);
        }

        for (i = 1; i < mes; i++) {
            suma = suma + nobisiesto[i];  //Suma los días de todos los meses
        }
        cantdias = suma + dia;  //Calcula la cantidad de días

        return cantdias;


    }
}

//Programa principal
int main(void)
{
    int fecha[2];

    //Lectura de datos
    printf("Introduce el día:", fecha[0]);
    scanf("%d", &fecha[0]);
    printf("Introduce el mes:", fecha[1]);
    scanf("%d", &fecha[1]);
    printf("Introduce el año:", fecha[2]);
    scanf("%d", &fecha[2]);

    printf("La cantidad de días de esta fecha es: %d", ordinal(fecha[0], fecha[1], fecha[2]));


}





