/*
    Autora : Laura Silva Loureiro
    Data :  31/03/2022
    Ejercicio : Practica 2 -> VACUNODROMO
*/
#include "TAD/cola.h"
#include "TAD/lista.h"
#include "vacunodromo.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Funciones que ayudan a a las principales
void destruir_paciente(TIPOELEMENTOCOLA *paciente);
void imprimir_vacuna(TLISTA vacuna);
void imprimir_paciente(TCOLA paciente);



///Función que crea la estructura vacunódromo
///Inicializa la cola de pacientes, el nº de pacientes en cola y el nombre del vacunódromo
void crear_vacunodromo(VACUNODROMO *v)
{
    crearCola(&v->colaPacientes);
    v->numeroPacientes = 0;

    printf("Introduce el nombre del vacunódromo: ");
    scanf(" %[^\r\n]", v->nombreVacunodromo);

    //printf("Nombre vacunodromo:%s\n", v->nombreVacunodromo);
    //printf("NumPacientes: %d\n", v->numeroPacientes);
    //printf("%d\n", v->colaPacientes);
}

///Función que destruye el vacunodromo creado
void destruir_vacunodromo(VACUNODROMO *v)
{
    TIPOELEMENTOCOLA pac;
    //TPOSICION pos;
    //if(!esColaVacia(v->colaPacientes)) {
    while (!esColaVacia(v->colaPacientes)) {
        consultarPrimerElementoCola(v->colaPacientes, &pac);
        destruir_paciente(&pac);
        suprimirElementoCola(&v->colaPacientes);
    }
    //memset(v->nombreVacunodromo,0,30);  //Libera los chars, pero al ser estático el vector al acabar de ejecutarse ya lo hace solo
    v->numeroPacientes = 0;
    //v->colaPacientes = NULL;
    //v = NULL;
}

///FUNCION que destruye un paciente
void destruir_paciente(TIPOELEMENTOCOLA *paciente)
{
    TPOSICION pos;
    //memset(paciente->nombrePaciente, 0, 30);  //Funcion que libera todos los chars del vector, como es estática
    // la variable no es estrictamente necesario llamarla
    pos = primeroLista(paciente->listaVacunas);
    while (!esListaVacia(paciente->listaVacunas)) {
        suprimirElementoLista(&paciente->listaVacunas, pos);
        //pos = siguienteLista(pac.listaVacunas, pos);  //suprimir ya recorre el bucle solo
    }
    destruirLista(paciente->listaVacunas);
    //paciente->listaVacunas = NULL;
    //paciente = NULL;
}

///FUNCION que imprime todos los datos del vacunodromo
void imprimir_vacunodromo(VACUNODROMO v)
{
    if(v.numeroPacientes > 0) {
        printf("Vacunodromo: %s\n", v.nombreVacunodromo);
        printf("Pacientes en la cola: %d\n", v.numeroPacientes);
        imprimir_paciente(v.colaPacientes);
    }
    else
    {
        printf("Vacunodromo: %s\n", v.nombreVacunodromo);
        printf("\tNo hay pacientes en la cola.");
    }
}

///FUNCION que imprime el numero de dosis administradas de cada vacuna
void imprimir_vacuna(TLISTA vacuna)
{
    int cont=0;
    TPOSICION posicion;
    TIPOELEMENTOLISTA vacunaMostrada;
    printf("\tLista de vacunas :\n");
    posicion = primeroLista(vacuna);
    while(cont != longitudLista(vacuna))
    {
        recuperarElementoLista(vacuna, posicion, &vacunaMostrada);
        posicion = siguienteLista(vacuna, posicion);
        cont++;
        printf("\t\t %s : %d de %d dosis administradas\n", vacunaMostrada.nombreVacuna,
               vacunaMostrada.numerosDosisPuestas, vacunaMostrada.numeroMaxDosis);
    }
}

///FUNCION que imprime los datos del paciente con sus vacunas correspondientes
void imprimir_paciente(TCOLA paciente)
{
    TIPOELEMENTOCOLA pacienteAmostrar;
    consultarPrimerElementoCola(paciente, &pacienteAmostrar);
    printf("Paciente actual: %s \n", pacienteAmostrar.nombrePaciente);
    imprimir_vacuna(pacienteAmostrar.listaVacunas);

}

///Funcion que añade un paciente al vacunodromo
void anadir_vacunodromo(VACUNODROMO *v)
{
    TIPOELEMENTOCOLA nuevoPaciente;
    TIPOELEMENTOLISTA tipoVacuna;

    printf("Nombre del paciente: ");
    scanf(" %[^\r\n]", nuevoPaciente.nombrePaciente);
    crearLista(&nuevoPaciente.listaVacunas);                   //Creamos la lista de vacunas del nuevoPaciente

    do {
        printf("\tNombre vacuna (fin para finalizar) : ");
        scanf(" %[^\r\n]", tipoVacuna.nombreVacuna);                     //Nombre de la vacuna

        if(strcmp(tipoVacuna.nombreVacuna, "fin") != 0)
        {
            do {
                printf("\tNumero de dosis maximas: ");
                scanf("%d", &tipoVacuna.numeroMaxDosis);   //Numero Maximo Dosis
            } while(tipoVacuna.numeroMaxDosis < 1);         //Comprobacion dosis Max es un numero mayor que 0
            tipoVacuna.numerosDosisPuestas = 0;             //Inicializamos nº de dosis a 0

            if(esListaVacia(nuevoPaciente.listaVacunas))  //Metemos en la lista el 1er elemento
            {
            insertarElementoLista(&nuevoPaciente.listaVacunas, finLista(nuevoPaciente.listaVacunas),
                                  tipoVacuna);    //Volcamos todos los datos
            }
            else {  ///Compara si el nombre de la vacuna introducida ya estaba y le suma dosis en tal caso
                TPOSICION tposicion, posicionModifica;
                TIPOELEMENTOLISTA vacuna2;
                int cont=0, modifica=0, salir=-1;
                tposicion = primeroLista(nuevoPaciente.listaVacunas);
                while(cont < (longitudLista(nuevoPaciente.listaVacunas)) && (salir == -1))
                {
                    recuperarElementoLista(nuevoPaciente.listaVacunas, tposicion,&vacuna2);
                    if(strcmp(tipoVacuna.nombreVacuna, vacuna2.nombreVacuna) != 0)
                    {
                        tposicion = siguienteLista(nuevoPaciente.listaVacunas, tposicion);   //Recorre la lista
                    }
                    else
                    {       //Si son iguales...
                        posicionModifica = tposicion;
                        vacuna2.numeroMaxDosis = vacuna2.numeroMaxDosis + tipoVacuna.numeroMaxDosis;
                        insertarElementoLista(&nuevoPaciente.listaVacunas, finLista(nuevoPaciente.listaVacunas), vacuna2);
                        modifica++;
                        tposicion = siguienteLista(nuevoPaciente.listaVacunas, tposicion);
                    }
                    cont++;
                    if (modifica>0)
                    {
                        //Suprimimos el anterior para añadirlo al final con el nº de dosis nuevo
                        suprimirElementoLista(&nuevoPaciente.listaVacunas, posicionModifica);
                        salir++;
                    }
                }
                if(modifica == 0)  //Si no encuentra ninguna coincidencia lo inserta
                {
                    insertarElementoLista(&nuevoPaciente.listaVacunas, tposicion, tipoVacuna);
                }
            }
        }
    } while(strcmp(tipoVacuna.nombreVacuna , "fin") != 0);   //Utilizar funcion para comparar
    if(!esListaVacia(nuevoPaciente.listaVacunas))
    {
        v->numeroPacientes++;                   //Le sumamos 1 al número de pacientes
        anadirElementoCola(&v->colaPacientes, nuevoPaciente);   //Añadimos el nuevo Paciente a la cola
    }
    //imprimir_paciente(v->colaPacientes);
}

///FUNCION que vacuna al primer paciente de la cola del vacunodromo
void vacunar_vacunodromo(VACUNODROMO *v)
{
    if (v->numeroPacientes > 0 ) {
        TIPOELEMENTOCOLA paciente;
        TIPOELEMENTOLISTA vacuna;
        consultarPrimerElementoCola(v->colaPacientes, &paciente);   //Consultamos el paciente que nos toca

        TPOSICION tposicion;
        tposicion = primeroLista(paciente.listaVacunas);               //Posicion en la cola del paciente (primera)
        printf("Vacunando al paciente %s: \n", paciente.nombrePaciente);
        int longitud = longitudLista(paciente.listaVacunas);
        //Recorremos toda la lista de vacunas y le sumamos una dosis a cada una y eliminamos si dosisPuestas==dosisMax
        for (int i = 0; i < longitud; i++)     //Ir recorriendo la vacunas pendientes
        {
            recuperarElementoLista(paciente.listaVacunas, tposicion, &vacuna);     //Vacuna a poner
            vacuna.numerosDosisPuestas++;      //Añadimos una dosis
            printf("\tVacunando a %s con %s (%d de %d dosis administradas)\n", paciente.nombrePaciente, vacuna.nombreVacuna,
                   vacuna.numerosDosisPuestas, vacuna.numeroMaxDosis);
            //Si el nº de dosis puestas es nº max eliminamos vacuna
            if (vacuna.numerosDosisPuestas == vacuna.numeroMaxDosis) {
                suprimirElementoLista(&paciente.listaVacunas, tposicion);   //Eliminación vacuna completada
            }
            else
            {
                modificarElementoLista(&paciente.listaVacunas, tposicion, vacuna); //Modificamos la vacuna
                tposicion = siguienteLista(paciente.listaVacunas, tposicion);   //Recorremos la lista
            }
        }
        //Si el paciente no tiene más vacunas se le elimina de la cola
        if (esListaVacia(paciente.listaVacunas)) {
            destruirLista(&paciente.listaVacunas);  //Libera la memoria de la lista
            suprimirElementoCola(&v->colaPacientes);
            v->numeroPacientes--;
            printf("\n\tSe ha completado la pauta completa de todas sus vacunas\n");
            printf("\tEliminando al paciente %s de la cola...\n", paciente.nombrePaciente);
        }
        //Se le vuelve a colocar en la cola si aun tiene vacunas pendientes
        else {
            suprimirElementoCola(&v->colaPacientes);
            anadirElementoCola(&v->colaPacientes, paciente);
        }
    }
    else{
        printf("\tNo hay pacientes pendientes de vacunar en la cola.");
    }
}

///Funcion que en el caso de haber un fichero agrega a los pacientes que hay en el
void anadir_vacunodromo_fichero(VACUNODROMO *v, FILE* file)
{
    //Variables relacionadas con la extracion de datos del fichero
    char *contenido, *separadores, numeroDosis[3];
    contenido = (char*)malloc(500* sizeof(char));
    //Variables en las cuales volcaremos el contenido
    TIPOELEMENTOCOLA paciente;
    TIPOELEMENTOLISTA vacuna;

    while(!feof(file))
    {
        fgets(contenido, 500, file); //Cogemos todo el contenido del fichero
        separadores = strtok(contenido, "|");  //Cogemos el nombre
        strcpy(paciente.nombrePaciente, separadores);
        //printf("%s\n", nombre);
        v->numeroPacientes++;
        crearLista(&paciente.listaVacunas);

        separadores = strtok(NULL, "|;\n"); // Volvemos a recortar
        while(separadores != NULL)  //Bucle para las vacunas
        {
            strcpy(vacuna.nombreVacuna, separadores);  //Copia lo que recopila strtok en el nombre (igualacion de strings)
            //printf("%s\n", nombreV);
            separadores = strtok(NULL, "|;\n");
            strcpy(numeroDosis, separadores);
            vacuna.numeroMaxDosis = atoi(numeroDosis);   //atoi pasa de char a ints
            //printf("%d\n", num);
            vacuna.numerosDosisPuestas = 0;             //inicializamos las dosis de las vacunas
            insertarElementoLista(&paciente.listaVacunas, finLista(paciente.listaVacunas),vacuna);
            separadores = strtok(NULL, "|;\n"); //Para que llegue al final
        }
        anadirElementoCola(&v->colaPacientes,paciente);
    }
    free(contenido);    //Liberamos memoria del puntero que hemos utilizado para coger el contenido
}

