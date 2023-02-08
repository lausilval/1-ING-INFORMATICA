

#include <stdlib.h>

float potencia(int base, int exponente)
{
    float valor = 1;
    int  i;
    for(i=1; i <= abs(exponente); i++)
    {
        valor = valor * base;
    }
    return (exponente < 0) ? 1 / valor : valor;
}