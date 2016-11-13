#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "heap.h"
#include "testing.h"

/* Función auxiliar para comparar ints */
int intcmp(const void * a, const void * b)
{
    return *(const int *)a - *(const int *)b;
}

/* Funcion wrapper para strcmp para evitar punteros incompatibles */
int comparar_strings(const void * a, const void * b)
{
    return strcmp((const char *) a, (const char *) b);
}

/* Pruebas para un heap vacio */
static void pruebas_heap_vacio()
{
    heap_t* heap = heap_crear(intcmp);

    printf("INICIO DE PRUEBAS CON HEAP VACIO\n");
    print_test("crear heap", heap);

    /* Inicio de pruebas */
    print_test("la cantidad de elementos es cero", heap_cantidad(heap) == 0);
    print_test("el heap está vacío", heap_esta_vacio(heap));
    print_test("ver máximo devuelve NULL", !heap_ver_max(heap));
    print_test("desencolar devuelve NULL", !heap_desencolar(heap));

    /* Destruyo el heap */
    heap_destruir(heap, NULL);
    print_test("el heap fue destruido", true);
}

static void pruebas_heap_algunos_elementos()
{
    int i;
    char * s[] = {"Spam", "Eggs", "Monty", "Python"};
    heap_t * heap = heap_crear(comparar_strings);

    printf("INICIO DE PRUEBAS CON ALGUNOS ELEMENTOS\n");
    print_test("crear heap", heap);

    /* Guardo y borro datos */
    print_test("encolar Spam", heap_encolar(heap, s[0]));
    print_test("encolar Eggs", heap_encolar(heap, s[1]));
    print_test("la cantidad de elementos es 2", heap_cantidad(heap) == 2);
    print_test("ver máximo es Spam", heap_ver_max(heap) == s[0]);
    print_test("desencolar dato es Spam", heap_desencolar(heap) == s[0]);
    print_test("la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("ver máximo es Eggs", heap_ver_max(heap) == s[1]);
    print_test("desencolar dato es Eggs", heap_desencolar(heap) == s[1]);

    /* Ahora está vacío */
    print_test("el heap está vacío", heap_esta_vacio(heap));

    /* Guardo cuatro elementos y destruyo el heap */
    for (i = 0; i < 4; i++) {
        heap_encolar(heap, s[i]);
    }
    print_test("la cantidad de elementos es 4", heap_cantidad(heap) == 4);
    print_test("ver máximo es Spam", heap_ver_max(heap) == s[0]);

    /* Destruyo el heap */
    heap_destruir(heap, NULL);
    print_test("el heap fue destruido", true);
}

void pruebas_heap_alumno()
{
    pruebas_heap_vacio();
    pruebas_heap_algunos_elementos();
}
