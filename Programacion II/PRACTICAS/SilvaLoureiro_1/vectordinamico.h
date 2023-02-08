//
// Created by 34662 on 17/02/2022.
//

#ifndef P1_V0_VECTORDINAMICO_H
#define P1_V0_VECTORDINAMICO_H
//Tipo de datos de los elementos del vector
typedef float TELEMENTO;
//Tipo opaco, los detalles de implementacion estan ocultos al usuario
typedef void * vectorD;

/*Funcion crear: asigna memoria y devuelve la asignacion al vector. Recibe
 * v por referencia para devolver al programa principal la direccion de memoria
 * reservada por este procedimiento*/
void crear(vectorD *v, short longitud);
/*Funcion asignar: Llena una posicion del vector con un valor. Recibe una copia
 * de la direccion de memoria reservada para el vector v */
void asignar(vectorD *v, short posicion, TELEMENTO valor);
//Función liberar: libera la memoria del vector
void liberar(vectorD *v);

//Funcion recuperar: recibe como argumentos el vector y posicion y devuelve el TELEMENTO de esa posicion
TELEMENTO recuperar(vectorD v, short posicion);

//Funcion longitudVector(): devuelve la longitud del vector
short longitudVector(vectorD v);

#endif //P1_V0_VECTORDINAMICO_H
