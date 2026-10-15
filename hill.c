#include <stdio.h>
#include <ctype.h>//biblioteca de manejo de y clasificacion de caracteres

#define N   2    /* tamaño de la clave (2x2) */
#define MOD 26   /* letras del alfabeto */
int  letraANumero(char c);
char numeroALetra(int n);
void limpiarTexto(char *texto);

int main(void)//Funcion principal
{
    printf("=== Cifrado de Hill ===\n");
    printf("H = %d\n", letraANumero('H'));   /* debe dar 7 */
printf("8 = %c\n", numeroALetra(8));     /* debe dar I */

char msg[100] = "Asaf Avila Gutierrez";
limpiarTexto(msg);
printf("Limpio: %s\n", msg);   /* debe dar  ASAFAVILAGUTIERREZ */


    return 0;
}//Fin funcion principal

int letraANumero(char c)//ingresa una letra y regresa un numero segun ASCII
{
    return c - 'A';    /* 'A' -> 0, 'B' -> 1 ... 'Z' -> 25 */
}

char numeroALetra(int n)//ingresa numero y regresa letra 'A' = 65 más el numero
{
    return 'A' + n;    /* 0 -> 'A', 1 -> 'B' ... 25 -> 'Z' */
}

void limpiarTexto(char *texto)//Funcion para limpiar el texto de espacios y convertir a mayusculas
{
    int j = 0;
    for (int i = 0; texto[i] != '\0'; i++)
        if (isalpha((unsigned char)texto[i]))
            texto[j++] = toupper((unsigned char)texto[i]);
    if (j % 2 != 0)
        texto[j++] = 'X';
    texto[j] = '\0';
}