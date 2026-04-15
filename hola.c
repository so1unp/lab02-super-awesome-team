#include <stdio.h>
#include <stdlib.h>

/*
 * saludar: imprime un saludo al nombre recibido por argumento.
 *
 * Uso: bin/saludar <nombre>
 *
 * printf() es una función de biblioteca de C que internamente invoca
 * la llamada al sistema write(2) para escribir en la salida estándar
 * (file descriptor 1).  Con strace se puede observar dicha syscall:
 *
 *   write(1, "hola francisco\n", 15)  = 15
 */
int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <nombre>\n", argv[0]);
        return EXIT_FAILURE;
    }

    printf("hola %s\n", argv[1]);

    return EXIT_SUCCESS;
}
