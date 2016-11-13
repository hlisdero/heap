#include <stdlib.h>
#include <string.h>
#include "heap.h"
#define TAM_INICIAL 32
#define PADRE(x)    ((x-1)/2)     // Calcula el indice del padre
#define IZQ(x)  (2*(x)+ 1)         // Calcula el indice del hijo izquierdo
#define DER(x)  (2*(x)+ 2)      // Calcula el indice del hijo derecho

/* *****************************************************************
 *            Definición de las estructuras de datos               *
 * *****************************************************************/

struct heap {
    void ** datos;
    size_t cant;
    size_t tam;
    cmp_func_t cmp;
};

/* *****************************************************************
 *                    Funciones auxiliares                         *
 * *****************************************************************/

/* Intercambiar dos punteros genéricos */
void intercambiar(void ** a, void ** b)
{
    void *aux = *a;
    *a = *b;
    *b = aux;
}

/* Downheap, basado en el pseudocódigo de MAX_HEAPIFY del Cormen */
static void downheap(heap_t * heap, size_t indice)
{
    size_t izq = IZQ(indice);
    size_t der = DER(indice);
    size_t mayor;

    if (izq <= heap->cant && heap->cmp(heap->datos[izq], heap->datos[indice]) > 0) {
        mayor = izq;
    } else {
        mayor = indice;
    }
    if (der <= heap->cant && heap->cmp(heap->datos[der], heap->datos[mayor]) > 0) {
        mayor = der;
    }
    if (mayor != indice) {
        intercambiar(heap->datos + indice, heap->datos + mayor);
        downheap(heap, mayor);
    }
}

/* Función de heapsort genérica. Esta función ordena mediante heap_sort
 * un arreglo de punteros opacos, para lo cual requiere que se
 * le pase una función de comparación. Modifica el arreglo "in-place".
 * Nótese que esta función NO es formalmente parte del TAD Heap.
 */
/* Basada sobre el pseudocódigo del Cormen */
void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp)
{
    size_t i;
    heap_t * heap = heap_crear_arr(elementos, cant, cmp);

    if (!heap) {
        return;
    }
    for (i = heap->cant; i > 2; i--) {
        intercambiar(heap->datos[1], heap->datos[i]);
        --(heap->cant);
        downheap(heap, 1);
    }
    heap_destruir(heap, NULL);
}

/* *****************************************************************
 *                    Primitivas del Heap                          *
 * *****************************************************************/

/* Crea un heap. Recibe como único parámetro la función de comparación a
 * utilizar. Devuelve un puntero al heap, el cual debe ser destruido con
 * heap_destruir().
 */
heap_t *heap_crear(cmp_func_t cmp)
{
    heap_t * nuevo = malloc(sizeof(heap_t));

    if (!nuevo) {
        return NULL;
    }
    nuevo->datos = malloc(sizeof(void *)*TAM_INICIAL);
    if (!(nuevo->datos)) {
        free(nuevo);
        return NULL;
    }
    nuevo->cant = 0;
    nuevo->tam = TAM_INICIAL;
    nuevo->cmp = cmp;
    return nuevo;
}

/*
 * Constructor alternativo del heap. Además de la función de comparación,
 * recibe un arreglo de valores con que inicializar el heap. Complejidad
 * O(n).
 *
 * Excepto por la complejidad, es equivalente a crear un heap vacío y encolar
 * los valores de uno en uno
*/
heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp)
{
    size_t i;
    heap_t * nuevo = malloc(sizeof(heap_t));

    if (!nuevo) {
        return NULL;
    }
    nuevo->datos = malloc(sizeof(void*)*n);
    if (!(nuevo->datos)) {
        free(nuevo);
        return NULL;
    }
    memcpy(nuevo->datos, arreglo, n*sizeof(void *));
    nuevo->cant = n;
    nuevo->tam = n;
    nuevo->cmp = cmp;

    for (i = (n-1)/2; i > 0; i--) {
        downheap(nuevo, i);
    }
    downheap(nuevo, 0);
    return nuevo;
}

/* Elimina el heap, llamando a la función dada para cada elemento del mismo.
 * El puntero a la función puede ser NULL, en cuyo caso no se llamará.
 * Post: se llamó a la función indicada con cada elemento del heap. El heap
 * dejó de ser válido. */
void heap_destruir(heap_t *heap, void destruir_elemento(void *e))
{
    size_t i;

    if (destruir_elemento) {
        for (i = 0; i < heap->cant; i++) {
            destruir_elemento(heap->datos[i]);
        }
    }
    free(heap->datos);
    free(heap);
}

/* Devuelve la cantidad de elementos que hay en el heap. */
size_t heap_cantidad(const heap_t *heap)
{
    return heap->cant;
}

/* Devuelve true si la cantidad de elementos que hay en el heap es 0, false en
 * caso contrario. */
bool heap_esta_vacio(const heap_t *heap)
{
    return (heap->cant == 0);
}

/* Agrega un elemento al heap. El elemento no puede ser NULL.
 * Devuelve true si fue una operación exitosa, o false en caso de error.
 * Pre: el heap fue creado.
 * Post: se agregó un nuevo elemento al heap.
 */
bool heap_encolar(heap_t *heap, void *elem);

/* Devuelve el elemento con máxima prioridad. Si el heap esta vacío, devuelve
 * NULL.
 * Pre: el heap fue creado.
 */
void *heap_ver_max(const heap_t *heap)
{
    if (heap_esta_vacio(heap))
        return NULL;
    else
        return heap->datos[0];
}

/* Elimina el elemento con máxima prioridad, y lo devuelve.
 * Si el heap esta vacío, devuelve NULL.
 * Pre: el heap fue creado.
 * Post: el elemento desencolado ya no se encuentra en el heap.
 */
void *heap_desencolar(heap_t *heap);
