/*
    Autor : Laura Silva
    Data : 18/11/2021
    Ejercicio : 1
        Escribir un programa que declare e inicie (con calquera valor que queirades) tres variables: unha de
    tipo float, outra de tipo int, e outra de tipo char. O voso programa entón terá que imprimir o enderezo
    asociado a cada variable e o valor almacenado en cada unha deles. Utilizar o especificador de formato
    "%p" para imprimir os enderezos en notación hexadecimal (veredes enderezos do tipo: 0xbfe55918,
    onde os caracteres iniciais 0x indican notación hexadecimal e o resto dos díxitos dan o enderezo en
    base 16). É posible distinguir o tipo de dato a partires do valor do enderezo impreso? Se lle sumamos
    1 a eses enderezos de memoria, que resultados obtemos e por que?

    Os punteiros son variables que almacenan enderezos de memoria. Creade agora dous punteriro de
    tipo int* e float*. Asignádelle ao punteiro int* o enderezo de memoria da variable int, e ao float* o
    enderezo da variable de tipo float, e imprimede con printf o valores accedidos mediante eses
    punteiros. Repetide agora a operación pero agora asignando a int* o enderezo da variable tipo float,
    a float* o enderezo da variable tipo int. Por que se obteñen valores distintos aos anteriores?

*/

#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    //Declaración de variables
    float f = 1.25;
    int i = 1;
    char c = 'A';
    //Imprimir direcciones de memoria
    printf("Direcciones de memoria:\n");
    printf("\t%p\n",&f);
    printf("\t%p\n",&i);
    printf("\t%p\n",&c);

    float* pf;
    int* pi;

    pf = &f;
    pi = &i;
    printf("Lo que contienenen esas direcciones de memoria:\n");
    printf("\t%f\n",*pf);
    printf("\t%d\n",*pi);

    pf = &i;
    pi = &f;

    printf("Esto es porque no es del mismo tipo de variable:%f\n",*pf);
    printf("Esto es porque no es del mismo tipo de variable:%d\n",*pi);


    return EXIT_SUCCESS;
}