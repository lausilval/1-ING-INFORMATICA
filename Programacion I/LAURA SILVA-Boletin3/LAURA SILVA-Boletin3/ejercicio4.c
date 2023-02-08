/*
    Autor : Laura Silva
    Data : 26/10/2021
    Ejercicio : 4
        Escribir un programa que pida o valor de dúas datas (dia, mes, ano) e calcule a distancia en días
    que as separa. Debe definirse unha estrutura (Date) para almacenar as coordenadas dos puntos e
    polo menos tres funcións: Ler, Mostrar, CalcularDistancia.
        Date Ler (); // Esta función pedirá os valores de día, mes e ano, creará a estrutura para
        // representarr a data e devolveraa

        float CalcularDistancia (Date d1, Date d2); //Determina o número de días entre as dúas datas

        void Mostrar (Date d, char f[]); // Imprime a data segundo o formato que se lle indique:
        //f=”1”: dia/mes/ano; f=”2”: mes/dia/ano
*/

#include <stdio.h>
#include <stdlib.h>

//Definimos la estructura fecha
typedef struct Date
{
    int dia;
    int mes;
    int anho;
}date;

// Función que calcula si un anho es bisiesto
int esBisiesto(int anho)
{
    return (anho%4==0 && anho%100!=0 || anho%400==0)? 1:0;
}
// Función que calcula los dias del mes
int getDiasMes(date date)
{
    int dias;
    int bisiesto[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int nobisiesto[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(esBisiesto(date.anho))
    {
        dias = bisiesto[date.mes-1];
    }
    else
    {
        dias = nobisiesto[date.mes-1];
    }
    return dias;
}

//Función que le pide al usuario que introduzca su fecha
date Ler()
{
    date date;
    printf("Introduce el día:", date.dia);
    scanf("%d", &date.dia);
    printf("Introduce el mes:", date.mes);
    scanf("%d", &date.mes);
    printf("Introduce el año:", date.anho);
    scanf("%d", &date.anho);

    return date;
}
//Función que nos devuelve la cantidad de días que tiene una fecha
int fechaToDias (date date)
{
    int dias, diasanho=0, diasmes=0,anho, mes;
    int v = getDiasMes(date) - date.dia;

    // Dias del año
    anho = date.anho;
    while(anho>1)
    {
        diasanho = diasanho + 365 + esBisiesto(anho);
        anho = anho-1;
    }
    // Dias del mes
    mes =  date.mes;
    while(date.mes>0)
    {
        diasmes = diasmes + getDiasMes(date);
        date.mes = date.mes - 1;
    }
    // Sumamos todos los dias
    dias = diasanho + diasmes - v;

    return dias;
}

//Función que calcula la distancia en días entre dos fechas
int CalcularDistancia (date fecha1, date fecha2)
{
    int dias1, dias2, diferencia;
    dias1 = fechaToDias(fecha1);    //Calculamos los días de las fechas
    dias2 = fechaToDias(fecha2);

    diferencia = abs(dias1 - dias2);    //Las restamos en valor absoluto

    return diferencia;
}

//Función que muestra la fecha en formato dd/mm/aaaa y mm/dd/aaaa
void Mostrar(date date, int f)
{
    //f=”1”: dia/mes/ano; f=”2”: mes/dia/ano
    if(f == 1)
    {
        printf("La fecha en formato tipo 1 es: %d/%d/%d\n", date.dia, date.mes, date.anho);
    }
    else if(f == 2)
    {
        printf("La fecha en formato tipo 2 es: %d/%d/%d\n", date.mes, date.dia, date.anho);
    }
    else
    {
        printf("ERROR");
    }
}

//Programa principal
int main(void)
{
    int menu=0;
    //Declaración de variables fecha
    date fecha1, fecha2;
    //Lectura de datos introducida por el usuario
    fecha1 = Ler();
    fecha2 = Ler();
    //Imprimir resultado de la función que calcula la distancia de dos fechas
    printf("Los días que hay entre las dos fechas son: %d\n", CalcularDistancia(fecha1,fecha2));
    //Muestra las fechas en el formato que quieras
    printf("Pulsa 1 si quieres la fecha en formato dd/mm/aaaa o 2 si la quieres en formato mm/dd/aaaa", menu);
    scanf("%d", &menu);

    if(menu == 1 || menu==2)
    {
        Mostrar(fecha1,menu);
        Mostrar(fecha2,menu);
    }
    else
    {
        printf("Formato incorrecto");
    }

    return 0;
}