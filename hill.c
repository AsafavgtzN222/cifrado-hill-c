#include <stdio.h>
#include <ctype.h>//biblioteca de manejo de y clasificacion de caracteres

#define N   2    /* tamaño de la clave (2x2) */
#define MOD 26   /* letras del alfabeto */
int  letraANumero(char c);
char numeroALetra(int n);
void limpiarTexto(char *texto);
void multiplicarMatrizVector(int K[N][N], int v[N], int resultado[N]);
int mcd(int a, int b);
int determinante(int K[N][N]);
int inversoModular(int a, int m);
int calcularInversa(int K[N][N], int Kinv[N][N]);
void cifrar(int K[N][N], const char *mensaje, char *resultado);

int main(void)//Funcion principal
{
    printf("=== Cifrado de Hill ===\n");
    printf("H = %d\n", letraANumero('H'));   /* debe dar 7 */
printf("8 = %c\n", numeroALetra(8));     /* debe dar I */

char msg[100] = "Asaf Avila Gutierrez";
limpiarTexto(msg);
printf("Limpio: %s\n", msg);   /* debe dar  ASAFAVILAGUTIERREZ */

//prueba de funcion matriz por vector
int K[N][N];
int v[N], r[N];
char a, b;

printf("Clave (4 numeros: fila1 fila2): ");
scanf("%d %d %d %d", &K[0][0], &K[0][1], &K[1][0], &K[1][1]);

printf("Dos letras en MAYUSCULA: ");
scanf(" %c %c", &a, &b);

v[0] = letraANumero(a);
v[1] = letraANumero(b);
multiplicarMatrizVector(K, v, r);
printf("Resultado: %c%c\n", numeroALetra(r[0]), numeroALetra(r[1]));

//Prueba del descifrado
    int det = determinante(K);
printf("Determinante: %d\n", det);
printf("mcd(det, 26) = %d\n", mcd(det, MOD));
printf("Inverso de det: %d\n", inversoModular(det, MOD));

//Prueba calculando la matriz inversa
int Kinv[N][N];
if (calcularInversa(K, Kinv))
    printf("Inversa: %d %d / %d %d\n", Kinv[0][0], Kinv[0][1], Kinv[1][0], Kinv[1][1]);
else
    printf("Esa clave no tiene inversa\n");

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

void multiplicarMatrizVector(int K[N][N], int v[N], int resultado[N])
{
    for (int i = 0; i < N; i++) {                     /* una vuelta por cada fila de K */
        resultado[i] = 0;                             /* empieza la suma en cero */
        for (int j = 0; j < N; j++)                   /* recorre las columnas de esa fila */
            resultado[i] += K[i][j] * v[j];           /* suma fila × vector */
        resultado[i] = ((resultado[i] % MOD) + MOD) % MOD;   /* dejalo entre 0 y 25 */
    }
}

int mcd(int a, int b)//Algoritmo de Euclides (mcd)
{
    while (b != 0) {         
        int temp = b;        
        b = a % b;           
        a = temp;             
    }
    return a;                 
}

int determinante(int K[N][N])//funcion para el determinante
{
    int det = K[0][0] * K[1][1] - K[0][1] * K[1][0];   
    return ((det % MOD) + MOD) % MOD;                  
}

int inversoModular(int a, int m)//funcion del inverso modular (encuentra el número que necesitamos para calcular la matriz inversa.)
{
    for (int x = 1; x < m; x++)      
        if ((a * x) % m == 1)         
            return x;                 
    return -1;                    
}

int calcularInversa(int K[N][N], int Kinv[N][N])//funcion para calcular la matriz inversa
{
    int det = determinante(K);             
    if (mcd(det, MOD) != 1)                
        return 0;                           
    int detInv = inversoModular(det, MOD);  
        Kinv[0][0] =  K[1][1];                  
    Kinv[0][1] = -K[0][1];                
    Kinv[1][0] = -K[1][0];
    Kinv[1][1] =  K[0][0];

    for (int i = 0; i < N; i++)             
        for (int j = 0; j < N; j++)
            Kinv[i][j] = (((Kinv[i][j] * detInv) % MOD) + MOD) % MOD;
    return 1;                               
}
void cifrar(int K[N][N], const char *mensaje, char *resultado)
{
    int v[N], r[N];
    int largo = strlen(mensaje);

    for (int i = 0; i < largo; i += N) {          /* de 2 en 2 letras */
        for (int j = 0; j < N; j++)
            v[j] = letraANumero(mensaje[i + j]);  /* arma el vector */
        multiplicarMatrizVector(K, v, r);         /* r = K * v (mod 26) */
        for (int j = 0; j < N; j++)
            resultado[i + j] = numeroALetra(r[j]);
    }
    resultado[largo] = '\0';
}