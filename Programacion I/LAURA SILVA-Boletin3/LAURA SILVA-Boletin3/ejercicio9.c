/*
    Autor : Laura Silva
    Data : 11/11/2021
    Ejercicio : 9
        Escribir un programa para facer consultas sobre ese arquivo binario. Tendo en conta que os datos
    están ordenados por data (01/01/2000-12/31/2010). e que polo tanto podemos precalcular a
    posición dentro do arquivo, crear estas dúas funcións de consulta:

        WeatherData Consulta_por data(File* file, Date d) A esta función pásaselle unha data e
            devolve unha estrutura cos datos recollidos dese día.
        float Consulta_precip_media(File* file, Date d1, Date d2) A esta función pásaselle dúas
            datas e devolve a precipitación media.

*/

#include <stdio.h>
#include <stdlib.h>

//Definimos la estructura fecha
typedef struct {
    int dia;
    int mes;
    int anho;
}date;
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

/* Garda o contido dun vector de puntos.
Par�metros: nome do arquivo, n�mero de
puntos no vector e o punteiro ao vector */
void salva (char* arquivo, int n, WeatherData vect[]) {
    FILE* fp = fopen(arquivo,"wb");
    if(fp==NULL) {
        printf("Erro na apertura do arquivo.\n");
        exit(1);
    }
    fwrite(vect, sizeof(WeatherData) , n, fp);
    fclose(fp);
}
//Procedementopara recuperar os datos gardados
void carga (char* arquivo, int n, WeatherData vect[]) {
    FILE* fp = fopen(arquivo,"rb");
    if(fp==NULL) {
        printf("Erro na apertura do arquivo.\n");
        exit(1);
    }
    fread(vect, sizeof(WeatherData), n, fp);
    fclose(fp);
}
//Funci�n para recuperar o i-esimopunto almacenado no arquivobinario
WeatherData lee_punto(FILE* fp, int i) {
    WeatherData p;
    fseek(fp, i*sizeof(WeatherData) , SEEK_SET);
    fread(&p, sizeof(WeatherData) , 1, fp);
    return p;
}
//A esta función pásaselle unha data e devolve unha estrutura cos datos recollidos dese día.
WeatherData Consulta_por_data(FILE *file, date d)
{
    WeatherData weatherData[5000];
    file = fopen("weatherdata-420-72.dat", "rb");

    int linea = fechaToDias(d);

    salva(file,5000,weatherData);
    carga(file,1,weatherData);
    lee_punto(file,linea);



}
//A esta función pásaselle dúas datas e devolve a precipitación media.
float Consulta_precip_media(FILE* file, date d1, date d2)
{

}


//Programa principal
int main(void)
{
    FILE *file;
    file = fopen("weatherdata-420-72.dat", "rb");
    WeatherData weatherData[5000];
    date fecha;

    int menu,i=0;
    WeatherData v[5000], u[5000], pto;




    printf("La fecha es %d? ", i+1);
    scanf("%d %d %d", &v[i].date.mes, &v[i].date.dia, &v[i].date.anho);


    salva(file, 5000, v); //vuelco todos los puntos del vector a un archivo

    carga(file, 5000, u); //cargo los datos del archivo a un vector de copias
    for (i=0; i<5000; i++)
    {
        printf("(%d, %d, %d)\n", u[i].date.mes, u[i].date.dia, u[i].date.anho);
    }

    if (file) {
        pto = lee_punto(file, 1); //obtengo una copia del segundo punto
        printf("\n\n(%d, %d, %d)\n", pto.date.mes, pto.date.dia, pto.date.anho);
        fclose(file);
    }

    //Creación del menú de opciones
    printf("Si quieres consultar los datos de una fecha pulsa 1, si quieres calcular "
           "el promedio de las precipitaciones entre dos fechas pulsa 2", menu);
    scanf("%d", &menu);
    if(menu == 1)   //Consultar los datos de una fecha
    {

        printf("Introduce el dia:",fecha.dia);
        scanf("%s", &fecha.dia);
        printf("Introduce el mes:",fecha.mes);
        scanf("%s", &fecha.mes);
        printf("Introduce el anho:",fecha.anho);
        scanf("%s", &fecha.anho);

        printf("Los datos son: ", Consulta_por_data(file, fecha));
    }
    else if (menu == 2) //Calcular media de precipitaciones de 2 fechas
    {
        date fecha2;
        printf("Introduce el dia(1):",fecha.dia);
        scanf("%s", &fecha.dia);
        printf("Introduce el mes(1):",fecha.mes);
        scanf("%s", &fecha.mes);
        printf("Introduce el anho(1):",fecha.anho);
        scanf("%s", &fecha.anho);
        printf("Introduce el dia(2):",fecha.dia);
        scanf("%s", &fecha2.dia);
        printf("Introduce el mes(2):",fecha2.mes);
        scanf("%s", &fecha2.mes);
        printf("Introduce el anho(2):",fecha2.anho);
        scanf("%s", &fecha2.anho);

        printf("El promedio de las precipitaciones es: %f", Consulta_precip_media(file, fecha, fecha2));

    }
    else
    {
        printf("ERROR");
        exit(0);
    }

    return EXIT_SUCCESS;
}
