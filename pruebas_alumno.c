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
	int  enteros[]={2,8,4,6,9,4};
	int* valor1 = &enteros[0];
	int* valor2 = &enteros[1];
	int* valor3 = &enteros[2];
	int* valor4 = &enteros[3];
	int* valor5 = &enteros[4];
	int* valor6 = &enteros[5];
	heap_t * heap = heap_crear(intcmp);
	
	printf("INICIO DE PRUEBAS CON ENTEROS\n");
    print_test("crear heap", heap);
    
    /* Guardo y borro datos */
    print_test("encolar 2", heap_encolar(heap, valor1));
    print_test("encolar 8", heap_encolar(heap, valor2));
    print_test("la cantidad de elementos es 2", heap_cantidad(heap) == 2);
    print_test("ver máximo es 8", heap_ver_max(heap) == valor2);
    print_test("encolar 4", heap_encolar(heap, valor3));
    print_test("encolar 6", heap_encolar(heap, valor4));
    print_test("encolar 9", heap_encolar(heap, valor5));
    print_test("encolar 4", heap_encolar(heap, valor6));
    print_test("la cantidad de elementos es 6", heap_cantidad(heap) == 6);
    print_test("ver máximo es 9", heap_ver_max(heap) == valor5);
    print_test("desencolar dato es 9", heap_desencolar(heap) == valor5);
    print_test("ver máximo es 8", heap_ver_max(heap) == valor2);
    print_test("desencolar dato es 8", heap_desencolar(heap) == valor2);
    print_test("el heap no está vacío", !heap_esta_vacio(heap));
    print_test("ver máximo es 6", heap_ver_max(heap) == valor4);
    print_test("desencolar dato es 6", heap_desencolar(heap) == valor4);
    print_test("desencolar dato es 4", heap_desencolar(heap) == valor6);
    print_test("desencolar dato es 4", heap_desencolar(heap) == valor3);
    print_test("desencolar dato es 2", heap_desencolar(heap) == valor1);

    /* Ahora está vacío */
    print_test("el heap está vacío", heap_esta_vacio(heap));

    /* Destruyo el heap */
    heap_destruir(heap, NULL);
    print_test("el heap fue destruido", true);
}
    
static void pruebas_heap_dinamica()
{
	int* valor1 = malloc(sizeof(int));
	int* valor2 = malloc(sizeof(int));
	int* valor3 = malloc(sizeof(int));
	int* valor4 = malloc(sizeof(int));
	
	*valor1 = 10;
	*valor2 = 5;
	*valor3 = 35;
	*valor4 = 7;
	
	heap_t * heap = heap_crear(intcmp);
	printf("INICIO DE PRUEBAS CON MEMORIA DINAMICA\n");
    print_test("crear heap", heap);
	
	/* Guardo y borro datos */
	print_test("encolar 10",heap_encolar(heap, valor1));
	print_test("encolar 5",heap_encolar(heap, valor2));
	print_test("encolar 35",heap_encolar(heap, valor3));
	print_test("encolar 7",heap_encolar(heap, valor4));
	print_test("el heap no está vacío", !heap_esta_vacio(heap));
	print_test("ver máximo es 35", heap_ver_max(heap) == valor3);
	
    
    /* Destruyo el heap */
    heap_destruir(heap, free);
    print_test("el heap fue destruido", true);
}

static void pruebas_heapsort()
{
	char * arreglo[] = {"Juan", "Pepe", "Jose", "Fulano","Mengano"};
	char * arreglo_ordenado[] = {"Fulano", "Jose", "Juan", "Mengano", "Pepe"};
	heap_sort((void**)arreglo,5,comparar_strings);
	printf("Arreglo pos 0: %s\n",arreglo[0]);
	printf("Arreglo pos 1: %s\n",arreglo[1]);
	printf("Arreglo pos 2: %s\n",arreglo[2]);
	printf("Arreglo pos 3: %s\n",arreglo[3]);
	printf("Arreglo pos 4: %s\n",arreglo[4]);
	
	printf("INICIO DE PRUEBAS CON HEAPSORT\n");
	
	bool ok = true;
	int i;
	for (i = 0; i<5 ; i++)
	{
		if (comparar_strings(arreglo[i],arreglo_ordenado[i])!=0)
		{
			ok = false;
			break;
		}
	}
	print_test("Se ordeno el arreglo",ok);
	print_test("El primero elemento es Fulano",comparar_strings(arreglo[0],arreglo_ordenado[0])==0);
	print_test("El segundo elemento es Jose",comparar_strings(arreglo[1],arreglo_ordenado[1])==0);
	print_test("El tercer elemento es Juan",comparar_strings(arreglo[2],arreglo_ordenado[2])==0);
	print_test("El cuarto elemento es Mengano",comparar_strings(arreglo[3],arreglo_ordenado[3])==0);
	print_test("El quinto elemento es Pepe",comparar_strings(arreglo[4],arreglo_ordenado[4])==0);
}
  
static void pruebas_heap_muchos_elementos(int volumen)
{
	heap_t * heap = heap_crear(intcmp);
	printf("INICIO DE PRUEBAS MASIVAS\n");
	print_test("crear heap", heap);
	int i;
	bool ok = true;
	for (i=0; i<volumen ; i++)
	{
		ok = heap_encolar(heap,&i);
		if (!ok) {
			break;
		}
	}
    print_test("Se encolaron todos los datos",ok);
    print_test("El heap no esta vacio",!heap_esta_vacio(heap));
	print_test("la cantidad de elementos es 5000", heap_cantidad(heap) == volumen);
	print_test("ver máximo es 5000", heap_ver_max(heap) == &i);
    
    /* borro los elementos */
    ok = true;
    for (i=0 ; i<=volumen ; i++){
		heap_desencolar(heap);
	}
	print_test("Se desencolaron todos los datos",ok);
	print_test("El heap esta vacio",heap_esta_vacio(heap));
	print_test("el heap tiene 0 elementos",heap_cantidad(heap) == 0);
	/* Destruyo el heap */
    heap_destruir(heap, NULL);
    print_test("el heap fue destruido", true);
}
	
    
void pruebas_heap_alumno()
{
    pruebas_heap_vacio();
    pruebas_heap_algunos_elementos();
    pruebas_heap_enteros();
    pruebas_heap_dinamica();
    pruebas_heapsort();
    pruebas_heap_muchos_elementos(5000);
}
