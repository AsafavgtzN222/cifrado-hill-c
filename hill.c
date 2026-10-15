#include <stdio.h>

#define N   2    /* tamaño de la clave (2x2) */
#define MOD 26   /* letras del alfabeto */
int  letraANumero(char c);
char numeroALetra(int n);

int main(void)
{
    printf("=== Cifrado de Hill ===\n");
    printf("H = %d\n", letraANumero('H'));   /* debe dar 7 */
printf("8 = %c\n", numeroALetra(8));     /* debe dar I */

    return 0;
}

int letraANumero(char c)
{
    return c - 'A';    /* 'A' -> 0, 'B' -> 1 ... 'Z' -> 25 */
}

char numeroALetra(int n)
{
    return 'A' + n;    /* 0 -> 'A', 1 -> 'B' ... 25 -> 'Z' */
}