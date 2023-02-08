//
// Created by 34662 on 21/12/2021.
//

#ifndef BOLETIN5_2_METEO_H
#define BOLETIN5_2_METEO_H

#include <stdio.h>
#include "fecha.h"
#include "fichero.h"


typedef struct{
    float longitude;
    float latitude;
    float elevation;
} Coordenadas;
//Estructura de WeatherData
typedef struct {
    Date date;
    Coordenadas coordenadas;
    float max_temperature;
    float min_temperature;
    float precipitacion;
    float wind;
    float relative_humidity;
    float solar;
}WeatherData;
//Definimos la estructura Station
typedef struct {
    char *nombre;
    Coordenadas cordenadasStation;
} Station;
//Definimos la estructura WheatherStation
typedef struct {
    WeatherData *weatherData;
    Station station;
}WeatherStation;

typedef struct {
    float temperatura_maxima;
    float temperatura_minima;
    char* nombreTempMax;
    char* nombreTempMin;
}Temperatura;


//Funcion 1: Lee los datos de un archivo y los almacena de un weatherData
WeatherData* LeerDatoArchivo(FILE* file, int num_lineas);

//Función que crea un WeatherStation a partir del nombre del archivo y de la función 1
WeatherStation* creaWeatherStation(WeatherData* registroArchivo,NombreFichero* nomeFich, int num_lineas);

//Funcion 3: Crea WeatherStation de una lista de archivos
WeatherStation** creaWeatherStationArchivo(FILE* archivos);

//Funcion 4: Dadas dos fechas y la lista de estaciones devuelva temp_max y temp_min y el nombre de la estación donde se registro
Temperatura* TempMax_TempMin(Date fecha1, Date fecha2, WeatherStation** weatherStationArchivos, int numArchivos, int numLineas);

//Función5: Dada una fecha y una lista estaciones devuelva la media de TempMax y TempMin
float* Media_TempMax_TempMin(Date fecha, WeatherStation** weatherStationArchivos,int numArchivos);
#endif //BOLETIN5_2_METEO_H
