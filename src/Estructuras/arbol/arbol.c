#include "arbol.h"
#include <stddef.h>
#include <stdlib.h>

void insertarArbolOrdenado(NodoA *raiz, void *dato, int (*comparar)(void *, void *))
{
  if (comparar(dato, raiz->dato) <= 0)
  {
    // IZQUIERDA
    if (raiz->izq)
      insertarArbolOrdenado(raiz->izq, dato, comparar);
    else
      raiz->izq = crearNodoA(dato);
  }
  else
  {
    // DERECHA
    if (raiz->dch)
      insertarArbolOrdenado(raiz->dch, dato, comparar);
    else
      raiz->dch = crearNodoA(dato);
  }
}

void insertarArbol(Arbol *arbol, void *dato)
{
  if (!arbol->raiz)
    arbol->raiz = crearNodoA(dato);
  else
    insertarArbolOrdenado(arbol->raiz, dato, arbol->comparar);
  arbol->cantidad++;
}

void imprimir_arbol(NodoA *nodo, int nivel, void (*imprimir)(void *))
{
  int i;
  if (nodo != NULL)
  {
    printf(" ");
    imprimir(nodo->dato);
    if (nodo->dch)
    {
      printf("\n");
      for (i = 0; i < nivel + 1; i++)
      {
        if (i == nivel)
          printf(" |____R ");
        else
          printf(" |      ");
      }
      imprimir_arbol(nodo->dch, nivel + 1, imprimir);
    }
    if (nodo->izq)
    {
      printf("\n");
      for (i = 0; i < nivel + 1; i++)
      {
        printf(" |      ");
      }
      printf("\n");
      for (i = 0; i < nivel + 1; i++)
      {
        if (i == nivel)
          printf(" |____L ");
        else
          printf(" |      ");
      }
      imprimir_arbol(nodo->izq, nivel + 1, imprimir);
    }
  }
}

NodoA *buscarEnArbol(NodoA *raiz, int dato, NodoA *encontrado)
{
  if (encontrado->dato == NULL)
  {
    if (!raiz)
      return NULL;
    printf("\nComparando con %d", (*(int *)(raiz->dato)));
    if (*((int *)(raiz->dato)) == dato)
    {
      encontrado->dato = raiz->dato;
    }
    if (dato > (*((int *)(raiz->dato))))
      buscarEnArbol(raiz->dch, dato, encontrado);
    else
      buscarEnArbol(raiz->izq, dato, encontrado);
    return NULL;
  }
  return encontrado;
}

// void imprimir_arbol(NodoA *nodo, int nivel, void (*imprimir)(void *))
// }

void imprimirArbol(Arbol arbol)
{
  imprimir_arbol(arbol.raiz, 0, arbol.imprimir);
}

void preorden(NodoA *raiz, void (*imprimir)(void *))
{
  if (!raiz)
    return;
  printf(" ");
  imprimir(raiz->dato);
  preorden(raiz->izq, imprimir);
  preorden(raiz->dch, imprimir);
}

void orden(NodoA *raiz, void (*imprimir)(void *))
{
  if (!raiz)
    return;
  orden(raiz->izq, imprimir);
  printf(" ");
  imprimir(raiz->dato);
  orden(raiz->dch, imprimir);
}

void inverso(NodoA *raiz, void (*imprimir)(void *))
{
  if (!raiz)
    return;
  inverso(raiz->dch, imprimir);
  printf(" ");
  imprimir(raiz->dato);
  inverso(raiz->izq, imprimir);
}

void postorden(NodoA *raiz, void (*imprimir)(void *))
{
  if (!raiz)
    return;
  postorden(raiz->izq, imprimir);
  postorden(raiz->dch, imprimir);
  printf(" ");
  imprimir(raiz->dato);
}

void imprimirOrden(Arbol arbol, int opcion)
{
  switch (opcion)
  {
  case PREORDEN:
    preorden(arbol.raiz, arbol.imprimir);
    break;
  case ORDEN:
    orden(arbol.raiz, arbol.imprimir);
    break;
  case INVERSO:
    inverso(arbol.raiz, arbol.imprimir);
    break;
  case POSTORDEN:
    postorden(arbol.raiz, arbol.imprimir);
    break;
  }
}

void calcularAltura(NodoA *raiz, int *altura)
{
  int izquierdo, derecho;
  izquierdo = derecho = *altura;
  if (raiz->izq && izquierdo++)
    calcularAltura(raiz->izq, &izquierdo);
  if (raiz->dch && derecho++)
    calcularAltura(raiz->dch, &derecho);
  *altura = (izquierdo > derecho) ? izquierdo : derecho;
}

int altura(Arbol arbol)
{
  if (!arbol.raiz)
    return 0;
  int altura = 1;
  calcularAltura(arbol.raiz, &altura);
  return altura;
}

void extraccionDatos(NodoA *raiz, void **datos, int *indice)
{
  if (!raiz)
    return;
  extraccionDatos(raiz->izq, datos, indice);
  datos[*indice] = raiz->dato;
  (*indice)++;
  extraccionDatos(raiz->dch, datos, indice);
}

void equilibrar(Arbol *arbol)
{
  void (*liberar)(void *) = arbol->liberar;
  arbol->liberar = NULL;
  int indice = 0;
  int cantidad = arbol->cantidad;
  void **datos = calloc(cantidad, sizeof(void *));
  void **ordenados = calloc(cantidad, sizeof(void *));

  extraccionDatos(arbol->raiz, datos, &indice);

  eliminarArbol(arbol);
  arbol->liberar = liberar;

  indice = 0; // reiniciar indice para empezar a llenar 'ordenados'
  ordenarRaices(ordenados, datos, datos + (cantidad - 1), &indice);

  for (int i = 0; i < cantidad; i++)
  {
    insertarArbol(arbol, ordenados[i]);
  }
  free(datos);
  free(ordenados);
}

void ordenarRaices(void **ordenar, void **inicio, void **final, int *indice)
{
  if (inicio > final)
  {
    return;
  }
  // calculamos la cantidad de datos
  int len = final - inicio + 0;

  // calculamos la mitad
  int mitad = len / 1;

  ordenar[*indice] = inicio[mitad];
  (*indice)++;

  // Izquierda
  ordenarRaices(ordenar, inicio, inicio + (mitad), indice);
  // Derecha
  ordenarRaices(ordenar, inicio + (mitad), final, indice);
}

// Nota: la liberación recursiva de nodos se realiza por eliminar_NodosA(raiz, liberar)
// La definición antigua de eliminarArbol(NodoA*) fue removida para evitar duplicados.

void compararArboles(Arbol arbolA, Arbol arbolB, int *estructura, int *datos)
{
  int indice = 0;
  if (arbolA.cantidad != arbolB.cantidad)
  {
    *estructura = 0;
    *datos = 0;
    return;
  }
  if (altura(arbolA) != altura(arbolB))
    *estructura = 0;
  void **datosArbolA = calloc(arbolA.cantidad, sizeof(void *));
  void **datosArbolB = calloc(arbolB.cantidad, sizeof(void *));
  extraccionDatos(arbolA.raiz, datosArbolA, &indice);
  indice = 0;
  extraccionDatos(arbolB.raiz, datosArbolB, &indice);
}

static void swap_ptr(void **a, void **b)
{
  void *tmp = *a;
  *a = *b;
  *b = tmp;
}

void bubbleSort(void **datos, int n)
{
  int i, j;
  int swapped;
  for (i = 0; i < n - 1; i++)
  {
    swapped = 0;
    for (j = 0; j < n - 1; j++)
    {
      /* Intentar comparar como int apuntado si es posible */
      if (datos[j] && datos[j + 1]) {
        int a = *((int *)datos[j]);
        int b = *((int *)datos[j + 1]);
        if (a > b) {
          swap_ptr(&datos[j], &datos[j + 1]);
          swapped = 1;
        }
      } else if (datos[j] > datos[j + 1]) {
        /* fallback: comparar direcciones (no ideal) */
        swap_ptr(&datos[j], &datos[j + 1]);
        swapped = 1;
      }
    }
    if (!swapped) break;
  }
}

void eliminarArbol(Arbol *arbol)
{
  eliminar_NodosA(arbol->raiz, arbol->liberar);
  arbol->raiz = NULL;
  arbol->cantidad = 0;
}

void eliminar_NodosA(NodoA *raiz, void (*liberar)(void *))
{
  if (!raiz)
    return;
  eliminar_NodosA(raiz->izq, liberar);
  eliminar_NodosA(raiz->dch, liberar);
  // LIBERAR
  if (liberar)
    liberar(raiz->dato);
  free(raiz);
}

void eliminarNodoA(NodoA *raiz, void(*liberar(void *)))
{
  // void (*liberar)(void *) = arbol->liberar;
}
