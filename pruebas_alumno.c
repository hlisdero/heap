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

static void pruebas_heap_enteros()
{
	int datos[] = {2, 8, 4, 6, 9, 4};
	heap_t * heap = heap_crear(intcmp);

	printf("INICIO DE PRUEBAS CON UN HEAP DE ENTEROS\n");
    print_test("crear heap", heap);

    /* Guardo y borro datos */
    print_test("encolar 2", heap_encolar(heap, datos+0));
    print_test("encolar 8", heap_encolar(heap, datos+1));
    print_test("la cantidad de elementos es 2", heap_cantidad(heap) == 2);
    print_test("ver máximo es 8", heap_ver_max(heap) == datos+1);
    print_test("encolar 4", heap_encolar(heap, datos+2));
    print_test("encolar 6", heap_encolar(heap, datos+3));
    print_test("encolar 9", heap_encolar(heap, datos+4));
    print_test("encolar 4", heap_encolar(heap, datos+5));
    print_test("la cantidad de elementos es 6", heap_cantidad(heap) == 6);
    print_test("ver máximo es 9", heap_ver_max(heap) == datos+4);
    print_test("desencolar dato es 9", heap_desencolar(heap) == datos+4);
    print_test("ver máximo es 8", heap_ver_max(heap) == datos+1);
    print_test("desencolar dato es 8", heap_desencolar(heap) == datos+1);
    print_test("el heap no está vacío", !heap_esta_vacio(heap));
    print_test("ver máximo es 6", heap_ver_max(heap) == datos+3);
    print_test("desencolar dato es 6", heap_desencolar(heap) == datos+3);
    print_test("desencolar dato es 4", heap_desencolar(heap) == datos+5);
    print_test("desencolar dato es 4", heap_desencolar(heap) == datos+2);
    print_test("desencolar dato es 2", heap_desencolar(heap) == datos+0);

    /* Ahora está vacío */
    print_test("el heap está vacío", heap_esta_vacio(heap));

    /* Destruyo el heap */
    heap_destruir(heap, NULL);
    print_test("el heap fue destruido", true);
}

static void pruebas_heap_crear_arr()
{
    size_t i;
    int valores[] = {10, 5, 35, 7};
    int ** arreglo = malloc(sizeof(int *)*4);
    heap_t * heap;

    if (!arreglo) {
        printf("No hay memoria suficiente para las pruebas\n");
        return;
    }
    /* Reservo cuatro enteros en memoria dinámica y les asigno valores */
    for (i = 0; i < 4; i++) {
        arreglo[i] = malloc(sizeof(int));
        if (!arreglo[i]) {
            printf("No hay memoria suficiente para las pruebas\n");
            return;
        }
        *arreglo[i] = valores[i];
    }

    heap = heap_crear_arr((void *) arreglo, 4, intcmp);

	printf("INICIO DE PRUEBAS HEAP CREADO A PARTIR DE ARREGLO\n");
    print_test("crear heap", heap);

	/* Chequeo que estén los 4 elementos */
	print_test("el heap no está vacío", !heap_esta_vacio(heap));
	print_test("la cantidad de elementos es 4", heap_cantidad(heap) == 4);
	print_test("ver máximo es 35", heap_ver_max(heap) == arreglo[2]);

    /* Destruyo el heap con sus elementos restantes */
    heap_destruir(heap, free);
    print_test("el heap fue destruido", true);

    /* Destruyo el arreglo */
    free(arreglo);
}

static void pruebas_heap_muchos_elementos(size_t volumen)
{
    size_t i;
	bool ok = true;
	heap_t * heap = heap_crear(intcmp);

	printf("INICIO DE PRUEBAS CON MUCHOS ELEMENTOS\n");
	print_test("crear heap", heap);

    /* Encolo elementos allocados en memoria dinámica */
	for (i = 0; i < volumen; i++) {
        size_t * elemento = malloc(sizeof(size_t));
        *elemento = i+1;
		ok = heap_encolar(heap, elemento);
		if (!ok) {
			break;
		}
	}

    /* Chequeo que se hayan encolado todos los elementos */
    print_test("se encolaron todos los datos", ok);
    print_test("el heap no esta vacio", !heap_esta_vacio(heap));
	print_test("la cantidad de elementos es 5000", heap_cantidad(heap) == volumen);
    print_test("ver máximo es 5000", *(size_t *)heap_ver_max(heap) == 5000);

    /* Borro la mitad de los elementos */
    for (i = 0 ; i < volumen/2; i++){
		free(heap_desencolar(heap));
	}

    /* Chequeo que se hayan borrado la mitad de los elementos */
	print_test("el heap no esta vacio", !heap_esta_vacio(heap));
	print_test("la cantidad de elementos es 2500", heap_cantidad(heap) == volumen/2);
    print_test("ver máximo es 2500", *(size_t *)heap_ver_max(heap) == 2500);

	/* Destruyo el heap */
    heap_destruir(heap, free);
    print_test("el heap fue destruido", true);
}

static void pruebas_heapsort()
{
	char * arreglo[] = {"Juan", "Pepe", "Jose", "Fulano", "Mengano"};
	char * arreglo_ordenado[] = {"Fulano", "Jose", "Juan", "Mengano", "Pepe"};
	bool ok = true;
	size_t i;

	printf("INICIO DE PRUEBAS CON HEAPSORT\n");

    /* Ordeno el arreglo */
	heap_sort((void **) arreglo, 5, comparar_strings);

    /* Comparo los strings del arreglo procesado con el arreglo ya ordenado */
	for (i = 0; i < 5; i++) {
		if (strcmp(arreglo[i], arreglo_ordenado[i])) {
			ok = false;
			break;
		}
	}
	print_test("se ordeno el arreglo", ok);
}

void pruebas_heap_alumno()
{
    pruebas_heap_vacio();
    pruebas_heap_algunos_elementos();
    pruebas_heap_enteros();
    pruebas_heap_crear_arr();
    pruebas_heap_muchos_elementos(5000);
    pruebas_heapsort();
}
