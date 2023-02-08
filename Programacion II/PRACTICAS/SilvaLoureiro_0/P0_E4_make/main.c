/*EJERCICIO 4:
 Implementa un programa para elevar a la potencia b cada uno de los elementos de un array a:
 c=[a[0]^b, a[1]^b, a[2]^b, a[3]^b] siendo a y b y c las variables siguientes: int a[4], c[4], b;
 de modo que cada componente del vector c se calcule mediante una funcion potencia(). Puedes usar como base l
 la función potencia utilizada en el ejercicio 3.
 Ejecuta paso a paso el programa, visualizando en todo momento las variables,y observando como se modifican
 las componentes de los arrays.
 */
/*
    a) Utilizando el botón "Watches", visualiza las siguientes expresiones, que indican la direccion de memoria
      de los respectivos elementos del array: &a[0] &a[1] &a[2] &a[3].

      Al principio las variables &a[0] &a[1] &a[2] &a[3] tienen direcciones de memoria del tipo 0xffffcbe0, 0xffffcbe4, 0xffffcbe8 y
      0xffffcbec, respectivamente. Podemos observar que todas están juntas en la misma direccion de memoria pero al ser enteros se separan por 4 bytes de
      memoria.
      En sus respectivos punteros tenemos los valores asignados a esas direcciones de memoria, al principio son valores random, en este caso:
      -13088, 0, -13232 y  0 respectivamente. En el siguiente paso, al pedirle los valores al usuario, estos ya son actualizados por los introducidos
      por el usuario.

    b) Calcula la diferencia entre las direcciones de dos elementos consecutivos. Trata de justificar los
      resultados.

      La diferencia entre las distintas direcciones de memorias es de 4 bytes en todos los casos, para calcular esto vemos el ultimo byte de
      las direcciones de memoria ya que al tratarse de enteros van a ocupar 4 bytes y por tanto no es necesario fijarse en el resto de bytes. Ademas,
      al manejar solo 4 datos no es necesario fijarse en mas.
      La memoria en este caso es estática ya que inicializamos los vectores con su tamaño y este nunca es modificado, por tanto no es coherente
      hablar de memoria dinámica.

*/


#include <stdio.h>
#include "operaciones.h"

int main(int argc, char** argv) {

    int a[4], b, i;
    float  c[4];

    printf("Introduce los 4 nºs enteros del array: ");
    scanf("%d %d %d %d", &a[0], &a[1], &a[2], &a[3]);

    printf("Introduce la potencia a la cual vas a elevar los elementos del array: ");
    scanf("%d", &b);

    printf("El array original es: %d %d %d %d\n", a[0], a[1], a[2], a[3]);
    printf("El nuevo array es: ");
    for(i = 0; i < 4; i++)
    {
        c[i] = potencia(a[i], b);
        printf("%0.2f ", c[i]);
    }

}
