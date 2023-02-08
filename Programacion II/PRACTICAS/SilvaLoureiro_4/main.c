/*
 * PRÁCTICA 4 PROGRAMACION II   -->>  ALGORITMO VORAZ
 *
 * - AUTORA: LAURA SILVA LOUREIRO
 *  - FECHA: 05/05/2022
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "vectordinamico.h"

//Funcion que devuelve el cambio con billetes/monedas ilimitadas
int cambio(float x, vectorD billetes, vectorD* solucion);
//Funcion que inicializa los vectores según el tipo de moneda que queramos utilizar
void iniciaBilletes(FILE* file, char* usuarioMoneda, vectorD* vectorCantidades, vectorD* vectorStock);
//Funcion que devuelve el cambio con monedas/billetes limitados por un stock
int cambioLimitado(float x, vectorD billetes, vectorD* solucion, vectorD* stock);
//Funcion que aumenta el stock
void aumentaStock(vectorD cantidades, vectorD *stock);
//Funciones que imprimen
void imprimeIlimitado(vectorD vectorCantidades, vectorD vectorSoluciones, char* tipomoneda);
void imprimeLimitado(vectorD vectorCantidades, vectorD vectorSoluciones, vectorD vectorStock, char* tipomoneda);
void imprimeStock(vectorD vectorCantidades, vectorD vectorStock, char* tipomoneda);
//Función que modifica la linea que queremos
void modificaFichero(FILE* file,FILE* file2, char* usuarioMoneda, vectorD vecCant, vectorD vecStock);
void modificaT(FILE* file,FILE* file2, char opcion2[30] , vectorD vecCant, vectorD vecStock);


int main(int argc, char **argv)
{
    vectorD vectorCantidades = NULL, vectorSoluciones = NULL, vectorStock = NULL;
    float cantidad;
    ///Obtener las monedas y los billetes por fichero
    vectorD V1, V2;


    char opcion, opcion2[30], opcion3;
    do {
        FILE *file;
        file = fopen("dinero.txt", "rt");
        FILE* file2;
        file2 = fopen("dinero2.txt", "w+");
        printf("\n-------------------------------");
        printf("\n1) monedas/billetes infinitos");
        printf("\n2) monedas/billetes limitados ");
        printf("\n0) Salir");
        printf("\n-------------------------------");
        printf("\nOpcion: ");
        scanf(" %c", &opcion);
        switch (opcion) {
            case '1': ///ILIMITADOS
                printf("\tCon qué moneda quieres trabajar? ");
                scanf(" %[^\r\n]", opcion2);

                iniciaBilletes(file, opcion2, &vectorCantidades,
                                       &vectorStock);  //Funcion que lee del fichero las monedas
                printf("- Introduce las cantidades en euros a devolver: [ej: 20.75] (introduce un 0 para acabar) ");
                do {
                    scanf(" %f", &cantidad);
                    cantidad = roundf(cantidad * 100) / 100;
                    if (cantidad <= 0) {
                        break;
                    } else
                    {
                        crear(&vectorSoluciones, longitudVector(vectorCantidades));  //Creamos el vector donde almacenamos las soluciones
                        cambio(cantidad, vectorCantidades, &vectorSoluciones);   //Devolvemos el cambio
                        imprimeIlimitado(vectorCantidades, vectorSoluciones, opcion2);   //Imprimimos
                        liberar(&vectorSoluciones);  //Liberamos memoria reservada para la solucion
                    }
                } while (cantidad > 0);
            break;
///---------------------------------------------------------------------------------------------------------------------------------------------------
            case '2':  ///LIMITADOS
                printf("\tCon qué moneda quieres trabajar? ");
                scanf(" %[^\r\n]", opcion2);
                char op[30];

                    printf("\ta) devolver cambio\n");
                    printf("\tb) aumentar stock\n");
                    scanf(" %c", &opcion3);
                if(strcmp(opcion2, op)!=0){
                    if (opcion3 == 'a') //devolver cambio
                    {

                        rewind(file);
                        iniciaBilletes(file, opcion2, &vectorCantidades, &vectorStock);
                        printf("-Introduce las cantidades en %s a devolver: (introduce un 0 para acabar) ", opcion2);
                        do {
                            scanf(" %f", &cantidad);
                            if ( cantidad > 0)
                            {
                                //Imprimimos solo si se ha podido realizar el cambio
                                if (cambioLimitado(cantidad, vectorCantidades, &vectorSoluciones, &vectorStock) == 1) {
                                    imprimeLimitado(vectorCantidades, vectorSoluciones, vectorStock, opcion2);
                                   // modificaT(file,file2, opcion2, vectorCantidades, vectorStock);
                                } else {
                                    printf("No se ha podido realizar el cambio debido a que no hay stock disponible\n");
                                }
                                liberar(&vectorSoluciones);
                            }
                        } while ((cantidad > 0 && cantidad !=0 )|| cantidad < 0);
                        //break;

                    } else if (opcion3 == 'b') //aumentar el stock
                    {
                        iniciaBilletes(file, opcion2, &vectorCantidades, &vectorStock);
                        //Funcion que aumenta el stock
                        aumentaStock(vectorCantidades, &vectorStock);
                        imprimeStock(vectorCantidades, vectorStock, opcion2);
                    }
                    else
                    {
                        printf("Opcion incorrecta \n");
                    }
                }
                else{
                    if(opcion3 == 'a')
                    {
                        printf("-Introduce las cantidades en %s a devolver: (introduce un 0 para acabar) ", opcion2);
                        do {
                            scanf(" %f", &cantidad);
                            if ( cantidad > 0)
                            {
                                //Imprimimos solo si se ha podido realizar el cambio
                                if (cambioLimitado(cantidad, V1, &vectorSoluciones, &V2) == 1) {
                                    imprimeLimitado(V1, vectorSoluciones, V2, opcion2);
                                    // modificaT(file,file2, opcion2, V1, V2);
                                } else {
                                    printf("No se ha podido realizar el cambio debido a que no hay stock disponible\n");
                                }
                                liberar(&vectorSoluciones);
                            }
                        } while ((cantidad > 0 && cantidad !=0 )|| cantidad < 0);
                    } else if (opcion3 == 'b') //aumentar el stock
                    {
                        //iniciaBilletes(file, opcion2, &V1, &V2);
                        //Funcion que aumenta el stock
                        aumentaStock(V1, &V2);
                        imprimeStock(V1, V2, opcion2);
                    }
                    else
                    {
                        printf("Opcion incorrecta \n");
                    }
                }

                    V1 = vectorCantidades;
                    V2 = vectorStock;
                    strcpy(op, opcion2);
                    //modificaT(file,file2, opcion2, vectorCantidades, vectorStock);
            break;

            case '0':
                /*modificaFichero(file, file2,  opcion2,vectorCantidades, vectorStock);
                fclose(file);
                fclose(file2);
                remove("dinero.txt");
                rename("dinero2.txt", "dinero.txt");*/
                modificaT(file,file2, opcion2, vectorCantidades, vectorStock);
                //fseek(file, 5, SEEK_END);
                //fprintf(file , "\n");
                liberar(&vectorCantidades);
                liberar(&vectorStock);
                printf("Saliendo del programa\n");
                break;
            default:
                printf("Opcion incorrecta\n");
        }

    } while (opcion != '0');
    return (EXIT_SUCCESS);

}


///FUNCIONES -------------------------------------------------------------------------------------------------------------

///MONEDAS/BILLETES ILIMITADOS
int cambio(float x, vectorD billetes, vectorD* solucion)
{
    int longitud = longitudVector(billetes);
    int i=0;
    float suma = 0;
    while((float)suma < (float)x  &&  i < longitud)
    {
        if((float)suma + (float)recuperar(billetes, i) <= (float)x)
        {
            TELEMENTO cant = recuperar(*solucion, i);
            asignar(solucion, i, (float)cant+1);
            suma += (float)recuperar(billetes, i);
        }
        else
        {
            i++;
        }
    }
    if((float)suma == x)
    {
        return 1;
    }
    else
    {
        for( i=0; i<longitud; i++)
        {
            asignar(solucion, i, 0);
        }
        // liberar(solucion);
        return 0;
    }

}

//Función que almacena los valores de las monedas deseadas
void iniciaBilletes(FILE* file, char* usuarioMoneda, vectorD* vectorCantidades, vectorD* vectorStock)
{
    //Variables relacionadas con la extracion de datos del fichero
    char *contenido, *separadores, ntamanho[3], nombre[30], billete[10], stockmoneda[4];
    contenido = (char*)malloc(500* sizeof(char));
    int tamanho, ciframoneda, i=0;
    TELEMENTO  cifraBillete;

    rewind(file);
    while(!feof(file))
    {
        fgets(contenido, 500, file); //Cogemos todo el contenido del fichero
        separadores = strtok(contenido, "|");  //Cogemos el nombre
        strcpy(nombre, separadores);

        if (strcmp(nombre, usuarioMoneda) == 0)
        {
            separadores = strtok(NULL, "|\n");
            strcpy(ntamanho, separadores);  //Copia lo que recopila strtok en el nombre (igualacion de strings)
            tamanho = atoi(ntamanho);
            crear(vectorCantidades, tamanho);   //Creamos el vector de la moneda que vamos a utilizar
            crear(vectorStock, tamanho);     //Su correspondiente stock
            separadores = strtok(NULL, ","); // Volvemos a recortar
            while (separadores != NULL)  //Bucle para las vacunas
            {
                strcpy(billete, separadores);
                cifraBillete = atoff(billete);
                asignar(vectorCantidades, i, (TELEMENTO) cifraBillete);
                separadores = strtok(NULL, ";\n");
                strcpy(stockmoneda, separadores);
                ciframoneda = atoi(stockmoneda);   //atoi pasa de char a float/TELEMENTO
                asignar(vectorStock, i, (TELEMENTO) ciframoneda);
                separadores = strtok(NULL, ",\n"); //Para que llegue al final
                i++;
            }
        }
    }
    free(contenido);    //Liberamos memoria del puntero que hemos utilizado para coger el contenido
}
///MONEDAS/BILLETES LIMITADOS
int cambioLimitado(float x, vectorD billetes, vectorD* solucion, vectorD* stock)
{
    vectorD auxstock;
    int longitud = longitudVector(billetes);
    crear(solucion, longitud);
    crear (&auxstock, longitud);
    for (int i=0; i<longitud ; i++)
    {
        asignar(&auxstock, i, recuperar(*stock, i));
    }
    int i=0;
    float suma = 0;
    while(suma < x  &&  i < longitud)
    {
        if(suma + recuperar(billetes, i) <= x && recuperar(*stock, i) != 0)
        {
            TELEMENTO cant = recuperar(*solucion, i);
            asignar(solucion, i, cant+1);
            TELEMENTO billetemenos = recuperar(*stock, i);
            asignar(stock, i, billetemenos - 1);
            suma += recuperar(billetes, i);
        }
        else
        {
            i++;
        }
    }
    if(suma == x){
        return 1;
    }
    else
    {
        // printf("No se puede realizar el cambio debido a que no hay stock disponible");
        for( i=0; i<longitud; i++)
        {
            asignar(stock, i, recuperar(auxstock, i));
        }
        liberar(&auxstock);
        return 0;
    }
}

//Funcion que aumenta el stock
void aumentaStock(vectorD cantidades, vectorD *stock)
{
    TELEMENTO antesStock;
    for(int i=0; i < longitudVector(cantidades); i++)
    {
        antesStock = recuperar(*stock, i);
        asignar(stock, i, antesStock + 10 );
    }
}


//Funcion que imprime para cambio ilimitado
void imprimeIlimitado(vectorD vectorCantidades, vectorD vectorSoluciones, char* tipomoneda)
{
    for (int k = 0; k < longitudVector(vectorCantidades); k++) {
        if (recuperar(vectorSoluciones, k) != 0)
        {
                printf("\t%0.0f de  %0.2f %s\n", recuperar(vectorSoluciones, k), recuperar(vectorCantidades, k), tipomoneda);

        }
    }
}

//Funcion que imprime para cambio limitado
void imprimeLimitado(vectorD vectorCantidades, vectorD vectorSoluciones, vectorD vectorStock, char* tipomoneda)
{
    printf("\t STOCK    |      CANTIDAD      |        %s\n", tipomoneda);
    for (int k = 0; k < longitudVector(vectorCantidades); k++)
    {
        printf("  %10.0f      |%10.0f          |    %0.2f\n", recuperar(vectorStock, k),
               recuperar(vectorSoluciones, k), recuperar(vectorCantidades, k));

    }
}

void imprimeStock(vectorD vectorCantidades, vectorD vectorStock, char* tipomoneda)
{
    printf("Este es su nuevo stock:\n");
    printf("\t\t STOCK | %s\n", tipomoneda);
    for (int k = 0; k < longitudVector(vectorCantidades); k++)
    {
        printf("\t  %10.0f   | %0.2f\n", recuperar(vectorStock, k),
               recuperar(vectorCantidades, k));
    }
}

//Función que modifica la linea que queremos
void modificaFichero(FILE* file,FILE* file2, char* usuarioMoneda, vectorD vecCant, vectorD vecStock)
{ //Variables relacionadas con la extracion de datos del fichero
    char *contenido, *separadores, nombre[30], cont[500];
    contenido = (char*)malloc(500* sizeof(char));
    int j=-1;
    rewind(file);
    do
    {
        fgets(contenido, 500, file); //Cogemos todo el contenido del fichero
        strcpy(cont, contenido);
        separadores = strtok(contenido, "|\n");  //Cogemos el nombre
        strcpy(nombre, separadores);

        if (strcmp(nombre, usuarioMoneda) == 0 && j == -1)
        {
            separadores = NULL;
            fprintf(file2, "%s|%d|", usuarioMoneda, longitudVector(vecCant));
            for (int i = 0; i < longitudVector(vecStock); ++i)
            {
                fprintf(file2, " %0.2f,%0.0f;", recuperar(vecCant,i), recuperar(vecStock,i));
            }
            fprintf(file2, "\n");
            j++;
        }
        else
        {
            fputs(cont, file2);
        }
    }while(!feof(file) && strcmp(contenido, "\n") !=0);
    free(contenido);
}


void modificaT(FILE* file,FILE* file2, char opcion2[30] , vectorD vecCant, vectorD vecStock)
{
    modificaFichero(file, file2,  opcion2,vecCant, vecStock);
    fclose(file);
    //fprintf(file2, "\n");
    fclose(file2);
    remove("dinero.txt");
    rename("dinero2.txt", "dinero.txt");
}
