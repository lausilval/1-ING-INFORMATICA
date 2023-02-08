/*
    Autor : Laura Silva
    Data : 04/11/2021
    Ejercicio : 8
        Repetide o exercicio pero agora almacenando todos os datos nun vector de estruturas. A estrutura
    WeatherData debe ter un campo por cada parámetro, e así almacenar os datos recollidos nunha
    data concreta (almacenar a data nunha estrutura Date). Gardar finalmente todos os datos en
    formato binario nun arquivo .dat

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definimos la estructura fecha
typedef struct Date {
    int dia;
    int mes;
    int anho;
} date;
//Definimos la estructura WeatherData
typedef struct {
    date date;
    float longitude;
    float latitude;
    float elevation;
    float max_temperature;
    float min_temperature;
    float precipitacion;
    float wind;
    float relative_humidity;
    float solar;
}WeatherData;


//Programa principal
int main(void)
{
    //Abrimos el fichero
    FILE *file;
    file = fopen("weatherdata-420-72.txt", "rt");
    WeatherData weather[5000];
    int i=0;

    //Creamos el segundo fichero
    FILE *file2;
    file2 = fopen("weatherdata-420-72.dat", "wb");

    if(file2)
    {
        if(file)
        {
            while(!feof(file))
            {

                fscanf(file,"%d %d %d %f %f %f %f %f %f %f %f %f", &weather[i].date.mes, &weather[i].date.dia, &weather[i].date.anho,
                       &weather[i].longitude,&weather[i].latitude, &weather[i].elevation, &weather[i].max_temperature,&weather[i].min_temperature,
                       &weather[i].precipitacion, &weather[i].wind, &weather[i].relative_humidity, &weather[i].solar);
                printf("mes:%d| dia:%d| anho:%d| longitud:%f| latitud:%f| elevacion:%f| "
                       "t.max:%f| t.min:%f| precip:%f| viento:%f| hum.rel:%f| sol:%f", weather[i].date.mes, weather[i].date.dia, weather[i].date.anho,
                       weather[i].longitude,weather[i].latitude, weather[i].elevation, weather[i].max_temperature,weather[i].min_temperature,
                       weather[i].precipitacion, weather[i].wind, weather[i].relative_humidity, weather[i].solar);
                printf(" \n");
                i++;

            }

        }
        else
        {
            printf("Erro na abertura do arquivo.\n");
            exit(1);
        }
        fclose(file);   //cerramos el fichero
        fwrite(&weather, sizeof(WeatherData), 5000, file2); //Escribimos en binario

    }
    else
    {
        printf("Erro na abertura do arquivo.\n");
        exit(1);
    }
    fclose(file2);  //Cerramos el fichero

    return EXIT_SUCCESS;
}