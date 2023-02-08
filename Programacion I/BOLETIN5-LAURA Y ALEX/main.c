/*
    Autores : Laura Silva Loureiro y Alejandro Rúa Mosquera
    Data : 13/12/2021

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "meteo.h"
#include "fecha.h"
#include "fichero.h"

int main(int argc, char *argv[])
{
    //Declaración de variables
    NombreFichero* fich;
    fich = (NombreFichero*) malloc(sizeof(NombreFichero));
    //Reservamos memoria para los punteros
    fich->nome = (char*)malloc(60*sizeof(char));
    fich->extension = (char*)malloc(10*sizeof(char));
    int i,j;

    //Creamos los ficheros para pasar de csv a dat y operar con ellos
    FILE *file, *file2;
    if(argc == 2)
    {
        i=0;
        while(argv[1][i] != '.' && argv[1][i] != '\0')   //Mientras que el nombre del archivo sea distinto a '.'//'\0
        {
            fich->nome[i] = argv[1][i];
            i++;
        }
        fich->nome[i] = '\0';    //Todos los string tiene que acabar en /0
        if(argv[1][i] == '.')       //Si el archivo tiene extension
        {
            i++;    //Saltar la posicion del punto
            j=0;
            while(argv[1][i] != '\0')
            {
                fich->extension[j] = argv[1][i];
                i++;
                j++;
            }
            fich->extension[j] = '\0';   //Todos los string tiene que acabar en /0
        }

    }
    else
    {
        printf("Error\n");
    }
    file = AbrirArquivo(fich);
    int num_Archivos = cuentaLineas(file);
    //Liberamos memoria;
    //free(fich->nome);
    //free(fich->extension);
    /*
    file2 = fopen("weatherdata-439-922.txt","rt");
    printf("%d", cuentaLineas(file2));
    file = fopen("archivos.txt","rt");
*/
    //Llamamos a la función 3 para crear la 'base de todos los datos de todos los archivos'
    WeatherStation **weatherStation;
    weatherStation = creaWeatherStationArchivo(file);

    int menu=0;
    Date fecha1,fecha2;
    do {
        //Creación del menu con las distintas opciones
        printf("Pulsa 1 dadas dos fechas obtener la Temp_Max y Temp_Min y la estación\n");
        printf("Pulsa 2 para obtener la media de las precipitaciones de una fecha en todas las estaciones\n");
        printf("Pulsa 0 para salir\n");
        scanf("%d", &menu);

        switch (menu)
        {
            case 1:
                printf("Fecha inicial:\n");
                fecha1 = Ler();
                printf("Fecha final:\n");
                fecha2 = Ler();

                Temperatura* results;
                results = TempMax_TempMin(fecha1,fecha2,weatherStation, num_Archivos, 12988);
                printf("TempMin: %f |Estación: %s\n", results->temperatura_minima, results->nombreTempMin);
                printf("TempMax: %f |Estación: %s\n", results->temperatura_maxima, results->nombreTempMax);
                free(results);
                break;
            case 2: printf("Fecha:\n");
                fecha1 = Ler();

                float *Temps;
                Temps = Media_TempMax_TempMin(fecha1,weatherStation, num_Archivos);
                printf("La media de TempMax es: %f\n", Temps[0]);
                printf("La media de TempMin es: %f\n", Temps[1]);
                free(Temps);
                break;
            case 0: break;
            default: printf("Opcion no soportada\n");   //En el caso de que el usuario introduzca un nº incorrecto
        }

    }while(menu);
    free(weatherStation);
    fclose(file);


    //printf(" Archivos : %d\n",cuentaLineas(file));
    //printf(" File 2: %d\n",cuentaLineas(file2));

/*
    int i = cuentaLineas(file2)-1;
        printf("longitud:%f| latitud:%f| elevacion:%f|\n", weatherStation->station.cordenadasStation.longitude,
               weatherStation->station.cordenadasStation.latitude,
               weatherStation->station.cordenadasStation.elevation);
        printf("%s\n", weatherStation->station.nombre);

        printf("mes:%d| dia:%d| anho:%d| "
               "t.max:%f| t.min:%f| precip:%f| viento:%f| hum.rel:%f| sol:%f",
               weatherStation->weatherData[i].date.mes,
               weatherStation->weatherData[i].date.dia, weatherStation->weatherData[i].date.anho,
               weatherStation->weatherData[i].max_temperature,
               weatherStation->weatherData[i].min_temperature,
               weatherStation->weatherData[i].precipitacion, weatherStation->weatherData[i].wind,
               weatherStation->weatherData[i].relative_humidity, weatherStation->weatherData[i].solar);
        printf("\n");
*/
   // free(weatherStation);

    return 0;
}