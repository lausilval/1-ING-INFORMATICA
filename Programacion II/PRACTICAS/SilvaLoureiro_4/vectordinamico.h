//
// Created by 34662 on 17/02/2022.
//

#ifndef P4_V0_VECTORDINAMICO_H
#define P4_V0_VECTORDINAMICO_H
//Tipo de datos de los elementos del vector
typedef float TELEMENTO;
//Tipo opaco, los detalles de implementacion estan ocultos al usuario
typedef void * vectorD;

/*Funcion crear: asigna memoria y devuelve la asignacion al vector. Recibe
 * v por referencia para devolver al programa principal la direccion de memoria
 * reservada por este procedimiento*/
void crear(vectorD *v, int longitud);
/*Funcion asignar: Llena una posicion del vector con un valor. Recibe una copia
 * de la direccion de memoria reservada para el vector v */
void asignar(vectorD *v, int posicion, TELEMENTO valor);
//Función liberar: libera la memoria del vector
void liberar(vectorD *v);

//Funcion recuperar: recibe como argumentos el vector y posicion y devuelve el TELEMENTO de esa posicion
TELEMENTO recuperar(vectorD v, int posicion);

//Funcion longitudVector(): devuelve la longitud del vector
int longitudVector(vectorD v);




#endif //P4_V0_VECTORDINAMICO_H
