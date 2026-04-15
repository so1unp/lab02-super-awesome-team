#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

/*
 * mycopy: copia un archivo en otro usando llamadas al sistema o
 * funciones de biblioteca de C, según el parámetro indicado.
 *
 * Uso: bin/mycopy [s|f] archivo-origen archivo-destino
 *
 *   s  — usa open(), read(), write(), close()
 *   f  — usa fopen(), fread(), fwrite(), fclose()
 *
 * En ambos modos:
 *   - Si el archivo destino ya existe, falla con perror().
 *   - Si el archivo origen no existe, falla con perror().
 */

#define BUFFER_SIZE 4096

/* ------------------------------------------------------------------ */
/* Modo s: llamadas al sistema                                         */
/* ------------------------------------------------------------------ */
static void copy_syscall(const char *src, const char *dst)
{
    /* Abrir origen; si no existe open() devolverá -1 con errno=ENOENT */
    int fd_src = open(src, O_RDONLY);
    if (fd_src == -1) {
        perror("open: archivo origen");
        exit(EXIT_FAILURE);
    }

    /*
     * Abrir destino en modo exclusivo (O_EXCL): falla con EEXIST si
     * el archivo ya existe, sin truncarlo ni modificarlo.
     */
    int fd_dst = open(dst, O_WRONLY | O_CREAT | O_EXCL, 0644);
    if (fd_dst == -1) {
        perror("open: archivo destino");
        close(fd_src);
        exit(EXIT_FAILURE);
    }

    char buf[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(fd_src, buf, sizeof(buf))) > 0) {
        ssize_t written = 0;
        while (written < bytes_read) {
            ssize_t w = write(fd_dst, buf + written,
                              (size_t)(bytes_read - written));
            if (w == -1) {
                perror("write");
                close(fd_src);
                close(fd_dst);
                exit(EXIT_FAILURE);
            }
            written += w;
        }
    }

    if (bytes_read == -1) {
        perror("read");
        close(fd_src);
        close(fd_dst);
        exit(EXIT_FAILURE);
    }

    close(fd_src);
    close(fd_dst);
}

/* ------------------------------------------------------------------ */
/* Modo f: funciones de biblioteca                                     */
/* ------------------------------------------------------------------ */
static void copy_library(const char *src, const char *dst)
{
    /* Abrir origen en modo binario de lectura */
    FILE *fp_src = fopen(src, "rb");
    if (fp_src == NULL) {
        perror("fopen: archivo origen");
        exit(EXIT_FAILURE);
    }

    /*
     * "wbx" (C11): modo escritura binaria exclusiva.
     * fopen() falla si el archivo destino ya existe (errno=EEXIST).
     */
    FILE *fp_dst = fopen(dst, "wbx");
    if (fp_dst == NULL) {
        perror("fopen: archivo destino");
        fclose(fp_src);
        exit(EXIT_FAILURE);
    }

    char buf[BUFFER_SIZE];
    size_t bytes_read;

    while ((bytes_read = fread(buf, 1, sizeof(buf), fp_src)) > 0) {
        if (fwrite(buf, 1, bytes_read, fp_dst) != bytes_read) {
            perror("fwrite");
            fclose(fp_src);
            fclose(fp_dst);
            exit(EXIT_FAILURE);
        }
    }

    if (ferror(fp_src)) {
        perror("fread");
        fclose(fp_src);
        fclose(fp_dst);
        exit(EXIT_FAILURE);
    }

    fclose(fp_src);
    fclose(fp_dst);
}

/* ------------------------------------------------------------------ */
/* main                                                                */
/* ------------------------------------------------------------------ */
int main(int argc, char *argv[])
{
    if (argc != 4) {
        fprintf(stderr, "Uso: %s [s|f] archivo-origen archivo-destino\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    const char *mode = argv[1];
    const char *src  = argv[2];
    const char *dst  = argv[3];

    if (strcmp(mode, "s") == 0) {
        copy_syscall(src, dst);
    } else if (strcmp(mode, "f") == 0) {
        copy_library(src, dst);
    } else {
        fprintf(stderr, "Modo inválido '%s': usar 's' (syscall) o 'f' (biblioteca)\n",
                mode);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
