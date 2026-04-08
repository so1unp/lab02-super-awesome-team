[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/L2yJMqlF)
# Laboratorio 2 - Llamadas al Sistema

Las respuestas a las preguntas planteadas en los ejercicios deben ser completadas en el campus.

## Punto 1

Completar el programa `hola.c` para que imprima un saludo de la siguiente manera: 

```
$ bin/hola francisco
hola francisco
```

Usar la función de biblioteca [`printf()`](https://www.man7.org/linux/man-pages/man3/printf.3.html) para imprimir el mensaje por la salida estándar. 

Analizar la ejecución del comando mediante `strace` e identificar y describir la llamada al sistema que invoca `printf()`.

## Punto 2

El programa `bin/fail` falla. Sólo disponen del binario y no tienen acceso al código fuente. Pero pueden analizar que llamadas al sistema invoca. Descubrir cual es el error y solucionarlo.

## Punto 3 

Implementar el programa `mycopy.c` para copiar un archivo en otro. Debe funcionar de la siguiente manera:
```
$ bin/mycopy [s|f] archivo-origen archivo-destino
```

- Si se indica el parámetro `s`, debe utilizar las llamadas al sistema [`open()`](http://man7.org/linux/man-pages/man2/open.2.html), [`write()`](http://man7.org/linux/man-pages/man2/write.2.html), [`read()`](http://man7.org/linux/man-pages/man2/read.2.html), [`close()`](http://man7.org/linux/man-pages/man2/close.2.html).
- Si se indica el parámetro `f`, emplea las funciones de biblioteca [`fopen()`](https://man7.org/linux/man-pages/man3/fopen.3.html), [`fwrite()`](https://man7.org/linux/man-pages/man3/fwrite.3.html), [`fread()`](https://man7.org/linux/man-pages/man3/fwrite.3.html), [`fclose()`](https://man7.org/linux/man-pages/man3/fclose.3.html).
- Si el archivo destino existe, debe fallar indicando el error mediante [`perror()`](https://man7.org/linux/man-pages/man3/perror.3.html).
- Si el archivo origen no existe, debe fallar indicando el error mediante [`perror()`](https://man7.org/linux/man-pages/man3/perror.3.html).

Comparar la ejecución de ambos mediante `strace` usando la opción `-c`, que genera un reporte, al copiar un archivo con un tamaño mayor a un **1 MiB**. 

¿Que diferencias observan?

---

¡Fin del Laboratorio 2!
