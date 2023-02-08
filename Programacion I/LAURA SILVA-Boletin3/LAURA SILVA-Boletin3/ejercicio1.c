/*
    Autor : Laura Silva
    Data : 26/10/2021
    Ejercicio : 1
    A continuación preséntase unha función para o cálculo do promedio de dous números, xunto cun
    exemplo de invocación dende un programa principal:
    Engade outra función que devolva o máximo común divisor de dous enteiros positivos pasados
    como argumentos. Os datos pediranse dende a función main(), e nela tamén se imprimirá o
    resultado.
*/

#include <stdio.h>
#include <stdlib.h>

float encontprom(int num1, int num2)
{
    float promedio;

    promedio = (num1 + num2) / 2.0;
    return(promedio);
}

int mcd(int num1,int num2)
{
    int x;
    while(num2 != 0)
    {
        x = num2;
        num2 = num1 % num2;
        num1 = x;
    }
    return num1;
}
//Programa principal
int main(void)
{
    //Declaración variables
    int a,b, resultado2;
    float resultado;
    //Pedimos valores al usuario
    printf("Dame dous valores enteiros: ");
    scanf("%d %d",&a,&b);

    //Imprimimos resultados
    resultado = encontprom(a, b);
    printf("Promedio=%0.2f\n",resultado);

    resultado2 = mcd(a,b);
    printf("El maximo comun divisor es:%d",resultado2);

    return EXIT_SUCCESS;
}