/*
 * PROGRAMA PARA REALIZAR OPERACIONES BÁSICAS CON UNA MATRIZ DINÁMICA
 *
 * OBJETIVO: DEPURAR USANDO LAS HERRAMIENTAS DE NETBEANS. EL PROGRAMA TIENE COMO MÍNIMO SEIS ERRORES
 * DOCUMENTAR LAS CORRECCIONES INTRODUCIDAS, PONIENDO UN COMENTARIO CON LA SENTENCIA INCORRECTA AL
 * LADO DE LA SENTENCIA CORREGIDA
 *
 * PRUEBAS:
 * - número de filas o columnas: 0
 * - acceder a un dato con índices negativos
 * - verificar todas las operaciones, para matrices pequeñas (2,3 filas/cols)
 *      - número de filas y columnas distintos en las dos matrices
 *      - número de filas igual y de columnas distinto
 *      - número de columnas igual y de filas distinto
 */

/*  RESPUESTA AL APARTADO B):
 * No se está liberando memoria adecuadamente en todos los casos.
 * En el case 7 'Eliminar las matrices' se libera memoria pero el puntero sigue apuntando
 * a la misma dirección de memoria, esto se soluciona igualandolas a NULL.
 * En el case 0 debemos liberar memoria tambn ya que estamos saliendo del programa y lo correcto
 * sería eliminar los datos al salir del programa, sin esta liberacion de memoria no estamos haciendo un buen uso de la liberacion
 * ya que en el único sitio donde liberamos memoria es en destruirMatriz y si no llamamos a esta funcion no se libera memoria,
 * para evitar esto incluimos esta liberacion al salir del programa.
 * */
#include "matriz.h"

int main(int argc, char** argv) {
    int f, c;  //i, k no se utilizan
    float valor;
    matriz *a = 0 , *b = 0 , *aux= 0;
    char resp, opcion;


    do {
        printf("---------------------Libreria matrices---------------------\n\n");
        printf("1-Crear matrices\n");
        printf("2-Asignar elementos\n");
        printf("3-Obtener elemento\n");
        printf("4-Imprimir matrices\n");
        printf("5-Sumar matrices\n");
        printf("6-Producto de matrices\n");
        printf("7-Eliminar matrices\n");
        printf("0-Salir\n");
        printf("Opcion: ");
        scanf(" %c", &opcion);   //&

        switch (opcion) {
            case '0':
                destruirMatriz(a);
                destruirMatriz(b);
                a = NULL;
                b = NULL;
                printf("Saliendo del programa\n");
                break;
            case '1':
                printf("Introduzca el numero de filas de la matriz 'a': ");
                scanf("%d", &f); //"%f"
                printf("Introduzca el numero de columnas de la matriz 'a': ");
                scanf("%d", &c);
                a = crearMatriz(f, c);

                printf("Introduzca el numero de filas de la matriz 'b': ");
                scanf("%d", &f); //"%f"
                printf("Introduzca el numero de columnas de la matriz 'b': ");
                scanf("%d", &c);
                b = crearMatriz(f, c);

                break;
            case '2':
                if (a != NULL  && b != NULL) {  //Si no existe alguna de ellas que vuelva al menu
                    printf("Matriz A\n");
                    for (f = 0; f < a->filas; f++)
                        for (c = 0; c < a->columnas; c++) {
                            printf("Introduzca el valor de la posicion %dx%d: ", f + 1, c + 1);
                            scanf("%f", &valor);
                            asignarElemento(f, c, valor, a); //Ponia matriz b
                        }

                    printf("Matriz B\n");
                    for (f = 0; f < b->filas; f++)
                        for (c = 0; c < b->columnas; c++) {
                            printf("Introduzca el valor de la posicion %dx%d: ", f + 1, c + 1);
                            scanf("%f", &valor);
                            asignarElemento(f, c, valor, b); //Ponia matriz a
                        }
                }
                break;
            case '3':
                do {
                    printf("De que matriz quieres ver un elemento? (a/b): ");
                    scanf(" %c", &resp);
                } while (resp != 'a' && resp != 'b');
                printf("Introduce fila y columna (fila columna): ");
                scanf("%d %d", &f, &c);
                if (resp == 'a') {
                    valor = obtenerElemento(f, c, a);  //Ponia matriz b
                    printf("El valor de la fila y columna seleccionada es: %f\n", valor);
                } else if (resp == 'b') {
                    valor = obtenerElemento(f, c, b);   //Ponia matriz a
                    printf("El valor de la fila y columna seleccionada es: %f\n", valor);
                }
                break;
            case '4':
                printf("Matriz A\n");
                imprimirMatriz(a);
                printf("Matriz B\n");
                imprimirMatriz(b);
                break;
            case '5':
                aux = suma(a, b);
                imprimirMatriz(aux);
                destruirMatriz(aux);
                break;
            case '6':
                aux = producto(a, b);
                imprimirMatriz(aux);
                destruirMatriz(aux);
                //destruirMatriz(aux);
                break;
            case '7':
                destruirMatriz(a);
                a = NULL;      //Para liberar la direccion de memoria
                destruirMatriz(b);
                b = NULL;
                printf("Matrices eliminadas...\n");
                break;
            default:
                printf("Opcion incorrecta\n");
                break;
        }
    } while (opcion != '0');


    return (EXIT_SUCCESS);
}