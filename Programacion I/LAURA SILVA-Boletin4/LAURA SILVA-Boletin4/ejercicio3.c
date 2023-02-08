/*
    Autor : Laura Silva
    Data :  25/11/2021
    Ejercicio : 3
        Consideremos un arquivo tipo weatherdata-420-72.dat (creado no boletín anterior) que contén
    información meteorolóxica en formato binario. Escribide un programa cunha función que lea todos os
    datos dese arquivo binario, entre dúas datas concretas pasadas como argumentos, os garde nun
    vector de estruturas WeatherData e devolva o punteiro a ese vector de estruturas. Facede reserva
    dinámica de memoria para ese vector (tamaño axustado ao número de entradas entre as datas
    indicadas). Imprimide os datos da primeira e última entrada dende a función main(), e finalmente
    liberade a memoria. Tede en conta que ademais dos datos é necesario saber cantos elementos ten o
    vector de estruturas.

*/

#include <stdio.h>
#include <stdlib.h>

//Definimos la estructura fecha
typedef struct {
    int dia;
    int mes;
    int anho;
} Date;
//Definimos la estructura WeatherData
typedef struct {
    Date date;
    float longitude;
    float latitude;
    float elevation;
    float max_temperature;
    float min_temperature;
    float precipitacion;
    float wind;
    float relative_humidity;
    float solar;
} WeatherData;

//Declaración de funciones
Date Ler(); //Funcion que le pide una fecha al usuario
int CalcularDistancia(Date fecha1, Date fecha2);    //Calcula la distancia en dias entre dos fechas
int esBisiesto(int anho);   //Devuelve 1 si el año es bisiesto o 0 si no lo es
int ordinal(Date d);    //Calcula el valor ordinal en dias de una fecha
void MostrarInfo(WeatherData* registros,int distancia);
//Función pedida por el ejercicio
WeatherData* LeerDatos(FILE* file, Date fecha1,Date fecha2,int distancia);

//Programa principal
int main(void)
{
    //Declaración de variables
    FILE *file;
    WeatherData *registros; //Puntero de estructuras donde guardaremos todos los datos de esas dos fechas
    registros = (WeatherData*)malloc(sizeof(WeatherData));
    Date fecha1;
    Date fecha2;
    int distancia;  //Distancia entre las fechas

    //Abrimos el fichero
    file = fopen("weatherdata-420-72.dat", "rb");
    if(!file) //Error si no se puede abrir
    {
        printf("Error al abrir el fichero\n");
        exit(1);
    }
    else {

        //Pedir fechas al usuario
        fecha1 = Ler();
        fecha2 = Ler();

        distancia = CalcularDistancia(fecha1, fecha2);   //Constante que utilizaremos varias vece
        registros = LeerDatos(file, fecha1, fecha2, distancia);

        //Imprimimos por pantalla los datos de las dos fechas
        MostrarInfo(registros, distancia);
        //Liberamos la memoria reservada par
        free(registros);

    }
    fclose(file);
    return EXIT_SUCCESS;

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
void Mostrar(Date date, char f[])
{
    //f=”1”: dia/mes/ano; f=”2”: mes/dia/ano
    if(f[0] == '1')
    {
        printf("La fecha en formato tipo 1 es: %d/%d/%d\n", date.dia, date.mes, date.anho);
    }
    else if(f[0] == '2')
    {
        printf("La fecha en formato tipo 2 es: %d/%d/%d\n", date.mes, date.dia, date.anho);
    }
    else
    {
        printf("ERROR");
    }
}
//Función que lea todos os datos dese arquivo binario, entre dúas datas concretas pasadas
// como argumentos, os garde nun vector de estruturas WeatherData e devolva o punteiro a ese vector de estruturas
WeatherData* LeerDatos(FILE* file, Date fecha1, Date fecha2,int distancia)
{
    WeatherData primeraFecha;   //Guardar datos de la primera fecha del ficheron en este caso 1/1/2000
    WeatherData *registros;     //Guardar todos los datos comprendidos entre las dos fechas
    registros = (WeatherData*) malloc(distancia*sizeof(WeatherData));       //Reservar memoria


    fread(&primeraFecha, sizeof(WeatherData), 1, file);     //Leemos primera linea
    fseek(file, sizeof(WeatherData) * CalcularDistancia(primeraFecha.date, fecha1), SEEK_SET);  //Saltamos hasta la linea de la primera fecha
    fread(registros, sizeof(WeatherData), distancia+1, file);   //Leemos todos los datos entre las dos fechas
    rewind(file);   //Rebobinamos el fichero

    return registros;
}
//Muestra la información de las dos fechas pedidas por el usuario
void MostrarInfo(WeatherData* registros,int distancia)
{
    printf("->Fecha inicial: %d/%d/%d\n longitud:%f\n latitud:%f\n elevacion:%f\n "
           "t.max:%f\n t.min:%f\n precip:%f\n viento:%f\n hum.rel:%f\n sol:%f\n", registros[0].date.dia,
           registros[0].date.mes,registros[0].date.anho,
           registros[0].longitude, registros[0].latitude, registros[0].elevation, registros[0].max_temperature,
           registros[0].min_temperature,
           registros[0].precipitacion, registros[0].wind, registros[0].relative_humidity, registros[0].solar);
    printf("->Fecha final: %d/%d/%d\n longitud:%f\n latitud:%f\n elevacion:%f\n "
           "t.max:%f\n t.min:%f\n precip:%f\n viento:%f\n hum.rel:%f\n sol:%f\n", registros[distancia].date.dia,
           registros[distancia].date.mes, registros[distancia].date.anho,
           registros[distancia].longitude, registros[distancia].latitude, registros[distancia].elevation,
           registros[distancia].max_temperature, registros[distancia].min_temperature,
           registros[distancia].precipitacion, registros[distancia].wind, registros[distancia].relative_humidity,
           registros[distancia].solar);
}