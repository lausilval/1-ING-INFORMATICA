//
// Created by 34662 on 21/12/2021.
//

#include "fecha.h"

//Función que guarda los valores de una fecha dada por el usuario
Date Ler()
{
    Date date;
    do {
        printf("Introduce el día:");
        scanf("%d", &date.dia);
    } while (date.dia < 1 || date.dia > 31);
    do {
        printf("Introduce el mes:");
        scanf("%d", &date.mes);
    } while (date.mes < 1 || date.mes > 12);
    printf("Introduce el año:");
    scanf("%d", &date.anho);

    return date;
}
//Función que calcula la distancia entre dos fechas
int CalcularDistancia(Date fecha1, Date fecha2)
{
    int anho, distancia;

    if(fecha1.anho == fecha2.anho) distancia=0;
    else
    {
        distancia = 365;
        if(esBisiesto(fecha1.anho)) distancia++;
    }
    distancia = distancia - ordinal(fecha1);
    for(anho = fecha1.anho +1; anho<fecha2.anho;anho++)
    {
        distancia = distancia +365;
        if (esBisiesto(anho)) distancia++;
    }
    distancia = distancia + ordinal(fecha2);

    return abs(distancia);
}
//Función que calcula si un año es Bisiesto
int esBisiesto(int anho)
{
    return (anho%4==0 && anho%100!=0 || anho%400==0)? 1:0;
}
//Función que muestra una fecha en distintos formatos
void Mostrar(Date date, char f[]) {
    //f=”1”: dia/mes/ano; f=”2”: mes/dia/ano
    if (f[0] == '1') {
        printf("La fecha en formato tipo 1 es: %d/%d/%d\n", date.dia, date.mes, date.anho);
    } else if (f[0] == '2') {
        printf("La fecha en formato tipo 2 es: %d/%d/%d\n", date.mes, date.dia, date.anho);
    } else {
        printf("ERROR");
    }
}

//Función que calcula el valor ordinal de una fecha
int ordinal(Date date)
{
    int diasMes[12] = {31, 28+esBisiesto(date.anho), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int i, ordinal=0;

    if(date.dia <= diasMes[date.mes-1])
    {
        for(i=0; i < date.mes-1; i++)
        {
            ordinal += diasMes[i];
        }
        ordinal += date.dia;
    }

    return ordinal;
}