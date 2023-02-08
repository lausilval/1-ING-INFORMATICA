/*
    Autor : Laura Silva
    Data : 18/11/2021
    Ejercicio : 2
        Repetide o último exercicio do boletín anterior, pero agora considerando estes novos prototipos de
funcións:
    WeatherData* Consulta_por data(FILE* file, Date *d) A esta función pásaselle unha data e devolve
    unha estrutura cos datos recollidos dese día

    float Consulta_precip_media(File* file, Date *d1, Date *d2) A esta función pásaselle dúas datas
    e devolve a precipitación media

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
void Mostrar(Date d, char f[]); //Muestra fechas en el formato indicado
int esBisiesto(int anho);   //Devuelve 1 si el año es bisiesto o 0 si no lo es
int ordinal(Date d);    //Calcula el valor ordinal en dias de una fecha
int datecmp(Date d1, Date d2);  //Comprueba que fecha es mayor

//Funciones pedidas
WeatherData* Consulta_por_data(FILE* file, Date *d);
float Consulta_precip_media(FILE* file, Date *d1, Date *d2);

//Programa principal
int main(void)
{
    //Definición de variables
    FILE *file;
    WeatherData*  registro; //para guardar los datos del fichero
    registro = (WeatherData*) malloc(sizeof(WeatherData));  //reservamos memoria para ese registro
    int menu;   //para que el usuario elija que opción quiere
    Date fecha1, fecha2;

    //Abrimos el fichero
    file = fopen("weatherdata-420-72.dat", "rb");
    if(!file) //Error si no se puede abrir
    {
        printf("Error al abrir el fichero\n");
        exit(1);
    }

    do {
        //Creación del menu con las distintas opciones
        printf("Pulsa 1 para consultar datos de una fecha concreta\n");
        printf("Pulsa 2 para obtener la media de las precipitaciones entre dos fechas\n");
        printf("Pulsa 0 para salir\n");
        scanf("%d", &menu);

        switch (menu)
        {
            case 1:
                printf("Escriba la fecha de la cual quiere el registro:\n");
                fecha1 = Ler(); //Pedimos fecha al usuario
                registro = Consulta_por_data(file,&fecha1);
                Mostrar(registro->date, "1");
                printf(" mes:%d\n dia:%d\n anho:%d\n longitud:%f\n latitud:%f\n elevacion:%f\n "
                       "t.max:%f\n t.min:%f\n precip:%f\n viento:%f\n hum.rel:%f\n sol:%f\n", registro->date.mes, registro->date.dia, registro->date.anho,
                       registro->longitude,registro->latitude, registro->elevation,registro->max_temperature,registro->min_temperature,registro->precipitacion,
                       registro->wind, registro->relative_humidity, registro->solar);
                break;
            case 2: printf("Fecha inicial:\n");
                fecha1 = Ler();
                printf("Fecha final:\n");
                fecha2 = Ler();
                printf("La media de las precipitaciones es: %f\n", Consulta_precip_media(file,&fecha1,&fecha2));
                break;
            case 0: break;
            default: printf("Opcion no soportada\n");   //En el caso de que el usuario introduzca un nº incorrecto

        }
    }while(menu);
    //Liberamos la memoria que habiamos reservado
    free(registro);
    //Cerramos el fichero
    fclose(file);

    return EXIT_SUCCESS;
}

//Función que guarda los valores de una fecha dada por el usuario
Date Ler()
{
    Date date;
    do
    {
        printf("Introduce el día:");
        scanf("%d", &date.dia);

        printf("Introduce el mes:");
        scanf("%d", &date.mes);

        printf("Introduce el año:");
        scanf("%d", &date.anho);
    } while (date.dia < 1 || date.dia > 31 || date.mes < 1 || date.mes > 12 || date.anho < 2000 || date.anho > 2010);


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
void Mostrar(Date date, char  f[])
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

//Función pásaselle unha data e devolve unha estrutura cos datos recollidos dese día
WeatherData* Consulta_por_data(FILE* file, Date *d)
{
    WeatherData *dato;
    dato = (WeatherData*) malloc(sizeof(WeatherData));

    fread(dato, sizeof(WeatherData), 1, file);
    fseek(file, sizeof(WeatherData)* CalcularDistancia((dato->date),*d), SEEK_SET);
    fread(dato, sizeof(WeatherData), 1, file);
    rewind(file);

    return dato;

}

float Consulta_precip_media(FILE* file, Date *d1, Date *d2)
{
    WeatherData registro[4018];
    WeatherData  primero;
    Date *temp;
    float media_precip=0;
    int i;

    if(datecmp(*d1,*d2)==1)
    {
        temp = d1;
        d1 = d2;
        d2 = temp;
    }

    fread(&primero, sizeof(WeatherData), 1, file);
    fseek(file, sizeof(WeatherData)* CalcularDistancia(primero.date, *d1), SEEK_SET);
    fread(registro, sizeof(WeatherData), CalcularDistancia(*d1,*d2)+1, file);
    rewind(file);

    for(i=0; i<= CalcularDistancia(*d1,*d2); i++)
    {
        media_precip += registro[i].precipitacion;
    }
    media_precip = media_precip/i;
    return media_precip;
}
//Calcula el valor ordinal en dias de una fecha
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
//Función que compara dos fechas para saber cual de ellas es mayor
int datecmp(Date d1, Date d2)
{
    int res = 0;
    if(d1.anho < d2.anho) res = -1;
    else if(d1.anho > d2.anho) res = 1;
    else    //hay que comparar los meses
    {
        if(d1.mes < d2.mes) res = -1;
        else if(d1.mes > d2.mes) res = 1;
        else    //hay que comparar los dias
        {
            if (d1.dia < d2.dia) res = -1;
            else if(d1.dia > d2.dia) res = 1;
        }
    }
    return  res; //si no se entró en ningun condicional
}
