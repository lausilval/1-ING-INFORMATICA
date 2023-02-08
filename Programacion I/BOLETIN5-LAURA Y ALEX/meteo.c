//
// Created by 34662 on 21/12/2021.
//

#include "meteo.h"
#include "fichero.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Funcion 1: Lee los datos de un archivo y los almacena de un weatherData
WeatherData* LeerDatoArchivo(FILE* file, int num_lineas)
{
    WeatherData *registroArchivo;
    registroArchivo = (WeatherData*) malloc(num_lineas*sizeof(WeatherData));       //Reservar memoria

    int i = 0;
    while (!feof(file) && (i < num_lineas))
    {
        fscanf(file, "%d %d %d %f %f %f %f %f %f %f %f %f", &registroArchivo[i].date.mes, &registroArchivo[i].date.dia,
               &registroArchivo[i].date.anho, &registroArchivo[i].coordenadas.longitude, &registroArchivo[i].coordenadas.latitude,
               &registroArchivo[i].coordenadas.elevation, &registroArchivo[i].max_temperature,&registroArchivo[i].min_temperature,
               &registroArchivo[i].precipitacion,&registroArchivo[i].wind, &registroArchivo[i].relative_humidity, &registroArchivo[i].solar);
        i++;
    }
    rewind(file);
    //fclose(file);
    return registroArchivo;
}

//Función 2: crea un WeatherStation a partir del nombre del archivo y de la función 1
WeatherStation* creaWeatherStation(WeatherData* registroArchivo,NombreFichero* nomeFich, int num_lineas)
{
    WeatherStation *registroStation;
    registroStation = (WeatherStation*) malloc(sizeof(WeatherStation));
    int i;
    registroStation->weatherData = (WeatherData*) malloc(num_lineas*sizeof(WeatherData));  //Reservamos memoria para todos los weatherData

    for(i=0;i<num_lineas;i++)
    {
            registroStation->weatherData[i].date.mes = registroArchivo[i].date.mes;
            registroStation->weatherData[i].date.dia = registroArchivo[i].date.dia;
            registroStation->weatherData[i].date.anho = registroArchivo[i].date.anho;
            registroStation->weatherData[i].max_temperature = registroArchivo[i].max_temperature;
            registroStation->weatherData[i].min_temperature = registroArchivo[i].min_temperature;
            registroStation->weatherData[i].precipitacion = registroArchivo[i].precipitacion;
            registroStation->weatherData[i].wind = registroArchivo[i].wind;
            registroStation->weatherData[i].relative_humidity = registroArchivo[i].relative_humidity;
            registroStation->weatherData[i].solar = registroArchivo[i].solar;

        //printf("%d, %d, %d\n",registroStation->weatherData[i].date.mes ,registroStation->weatherData[i].date.dia,
        //registroStation->weatherData[i].date.anho );
    }

    registroStation->station.cordenadasStation.longitude = registroArchivo->coordenadas.longitude;
    registroStation->station.cordenadasStation.latitude = registroArchivo->coordenadas.latitude;
    registroStation->station.cordenadasStation.elevation = registroArchivo->coordenadas.elevation;

    registroStation->station.nombre = nomeFich->nome;

    return registroStation;
}

//Funcion 3: Crea WeatherStation de una lista de archivos
WeatherStation** creaWeatherStationArchivo(FILE* archivos)
{
    int cuentaArchivos,i;    //Contamos las líneas para saber cuantos archivos hay
    cuentaArchivos = cuentaLineas(archivos);

    char **nombreArchivo;   //Guardamos el nombre del archivo
    nombreArchivo = (char**)malloc(cuentaArchivos*sizeof(char*));

    WeatherStation **weatherStationArchivos;  //Creamos el WeatherStation de cada archivo
    weatherStationArchivos = (WeatherStation**) malloc(cuentaArchivos*sizeof(WeatherStation*));

    for(i=0; i< cuentaArchivos;i++)
    {
        //printf("%d\n",cuentaArchivos);
        size_t n;  //Para el getline

        nombreArchivo[i] = (char*) malloc(20*sizeof(char));  //Creamos matriz para almacenar los nombres
        getline(&nombreArchivo[i], &n, archivos);  //Vamos cogiendo linea a linea

        if (i == cuentaArchivos)
        {
            nombreArchivo[i][strlen(nombreArchivo[i])+1]='\0';
        }
        else
        {
            nombreArchivo[i][strlen(nombreArchivo[i])-1]='\0';  //Como coge el \n se lo quitamos y le añadimos \0
        }
        //printf("%s\n",nombreArchivo[i]);
        NombreFichero* Archivo;   //Creamos una estructura tipo fichero para guardar el nombre
        Archivo = (NombreFichero*) malloc(sizeof(NombreFichero));
        Archivo->nome = nombreArchivo[i];
        Archivo->extension = "csv";

        FILE *file,*file2;    //Creamos y abrimos los ficheros correspondientes
        //Creamos y abrimos los ficheros correpondientes
        file = AbrirArquivo(Archivo);
        file2 = cambioCsvaTxt(file,Archivo);

        int num_lineas_archivo;  //Cuenta las lineas del archivo
        num_lineas_archivo = cuentaLineas(file2);

        WeatherData *weatherDataArchivo;    //Creamos el WeatherData del archivo
        weatherDataArchivo = LeerDatoArchivo(file2,num_lineas_archivo);

        weatherStationArchivos[i] = (WeatherStation*) malloc(num_lineas_archivo*sizeof(WeatherStation));
        //Vamos creando WeatherStation y los vamos almacenando
        weatherStationArchivos[i] = creaWeatherStation(weatherDataArchivo,Archivo,num_lineas_archivo);
        //printf(" %d\n",i);

    }
    /*printf("longitud:%f| latitud:%f| elevacion:%f|\n", weatherStationArchivos[1]->station.cordenadasStation.longitude,
           weatherStationArchivos[1]->station.cordenadasStation.latitude,weatherStationArchivos[1]->station.cordenadasStation.elevation);
    printf("%s\n", weatherStationArchivos[1]->station.nombre);

    //int i = cuentaLineas(file2)-1;
    printf("mes:%d| dia:%d| anho:%d| "
           "t.max:%f| t.min:%f| precip:%f| viento:%f| hum.rel:%f| sol:%f", weatherStationArchivos[1]->weatherData[3].date.mes,
           weatherStationArchivos[1]->weatherData[3].date.dia, weatherStationArchivos[1]->weatherData[3].date.anho,
           weatherStationArchivos[1]->weatherData[3].max_temperature,
           weatherStationArchivos[1]->weatherData[3].min_temperature,
           weatherStationArchivos[1]->weatherData[3].precipitacion, weatherStationArchivos[1]->weatherData[3].wind,
           weatherStationArchivos[1]->weatherData[3].relative_humidity, weatherStationArchivos[1]->weatherData[3].solar);
    printf("\n");*/

    return weatherStationArchivos;
}

//Funcion 4: Dadas dos fechas y la lista de estaciones devuelva temp_max y temp_min y el nombre de la estación donde se registro
Temperatura* TempMax_TempMin(Date fecha1, Date fecha2, WeatherStation** weatherStationArchivos, int numArchivos, int numLineas)
{
    float *temp_max, *temp_min, valortemp_max = -1000, valortemp_min = 1000;
    char *nombreStationTempMax, *nombreStationTempMin;
    int i=0,j,k=0, saltolinea=0, distanciaFechas=0;
    //Reservamos memoria
    temp_max = (float*) malloc(numArchivos*numLineas*sizeof(float*));
    temp_min = (float*) malloc(numArchivos*numLineas*sizeof(float*));
    nombreStationTempMax = (char*) malloc(20*sizeof (char));
    nombreStationTempMin = (char*) malloc(20*sizeof (char));

    Date primerafecha; //primera fecha de cada archivo
    Temperatura *resultado; //Donde se va a almacenar el resultado de la funcion
    resultado = (Temperatura*) malloc(sizeof(Temperatura));

    for(i=0; i< numArchivos;i++)
    {
        primerafecha = weatherStationArchivos[i]->weatherData[0].date;  //primera fecha de cada archivo
        saltolinea = CalcularDistancia(primerafecha,fecha1);  //Calculamos la distancia para acceder a la posicion de fecha1
        distanciaFechas = CalcularDistancia(fecha1, fecha2);

        if(saltolinea>distanciaFechas)
        {
            for(k=saltolinea+distanciaFechas; k>distanciaFechas ;k--) //Para que vaya contando hacia atras
            {
                temp_max[i] = weatherStationArchivos[i]->weatherData[k].max_temperature;
                temp_min[i] = weatherStationArchivos[i]->weatherData[k].min_temperature;

                if(temp_max[i] >= valortemp_max)
                {
                    valortemp_max = temp_max[i];
                    nombreStationTempMax = weatherStationArchivos[i]->station.nombre;
                }
                if(temp_min[i] <= valortemp_min)
                {
                    valortemp_min = temp_min[i];
                    nombreStationTempMin = weatherStationArchivos[i]->station.nombre;
                }

            }
        }
        else {
            for (k = saltolinea; k < distanciaFechas; k++) //Para que vaya incrementando
            {
                temp_max[i] = weatherStationArchivos[i]->weatherData[k].max_temperature;
                temp_min[i] = weatherStationArchivos[i]->weatherData[k].min_temperature;

                if (temp_max[i] >= valortemp_max) {
                    valortemp_max = temp_max[i];
                    nombreStationTempMax = weatherStationArchivos[i]->station.nombre;
                }
                if (temp_min[i] <= valortemp_min) {
                    valortemp_min = temp_min[i];
                    nombreStationTempMin = weatherStationArchivos[i]->station.nombre;
                }

            }
        }

    }
    resultado->temperatura_maxima = valortemp_max;
    resultado->temperatura_minima = valortemp_min;
    resultado->nombreTempMax = nombreStationTempMax;
    resultado->nombreTempMin = nombreStationTempMin;

    free(temp_max);
    free(temp_min);
    //free(nombreStationTempMin);
    //free(nombreStationTempMax);

    return resultado;
}

//Función5: Dada una fecha y una lista estaciones devuelva la media de TempMax y TempMin
float* Media_TempMax_TempMin(Date fecha, WeatherStation** weatherStationArchivos,int numArchivos)
{
    int i=0,j,k=0, saltolinea=0, distanciaFechas=0;
    Date primerafecha; //primera fecha de cada archivo
    primerafecha = weatherStationArchivos[i]->weatherData[0].date;  //primera fecha de cada archivo
    saltolinea = CalcularDistancia(primerafecha,fecha);  //Calculamos la distancia para acceder a la posicion de fecha1

    float *temp_max, *temp_min,sumaMax=0, sumaMin=0, mediaMax=0, mediaMin=0, *resultado;
    temp_max = (float*) malloc(numArchivos*sizeof(float*));
    temp_min = (float*) malloc(numArchivos*sizeof(float*));
    resultado = (float*) malloc(2*sizeof(float));

    for(i=0;i<numArchivos;i++)
    {
        temp_max[i] = weatherStationArchivos[i]->weatherData[saltolinea].max_temperature;
        temp_min[i] = weatherStationArchivos[i]->weatherData[saltolinea].min_temperature;

        sumaMax = sumaMax + temp_max[i];
        sumaMin = sumaMin + temp_min[i];
    }

    mediaMax = sumaMax/numArchivos;
    mediaMin = sumaMin/numArchivos;

    resultado[0] = mediaMax;
    resultado[1] = mediaMin;

    return resultado;
}
