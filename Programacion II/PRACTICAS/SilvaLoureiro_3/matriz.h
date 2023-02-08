//
// Created by 34662 on 31/03/2022.
//

#ifndef P3_V1_MATRIZ_H
#define P3_V1_MATRIZ_H

//Tipo de datos de los elementos del vector
typedef long TELEMENTO;
//Tipo opaco, los detalles de implementacion estan ocultos al usuario
typedef void *matrizD;


void crearMatriz(matrizD* m,long tamanho);
matrizD producto(matrizD M1, matrizD M2);
matrizD suma(matrizD M1, matrizD M2);
long obtenerElemento(int fila, int columna, matrizD *M);
void destruirMatriz(matrizD *M);

void imprimirMatriz(matrizD M);
#endif //P3_V1_MATRIZ_H
