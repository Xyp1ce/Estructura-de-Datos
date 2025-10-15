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
  int len = final - inicio + 1;

  // calculamos la mitad
  int mitad = len / 2;

  ordenar[*indice] = inicio[mitad];
  (*indice)++;

  // Izquierda
  ordenarRaices(ordenar, inicio, inicio + (mitad - 1), indice);
  // Derecha
  ordenarRaices(ordenar, inicio + (mitad + 1), final, indice);
}

void compararArboles(Arbol arbolA, Arbol arbolB, int *estructura, int *datos) {
  // Hacemos una verificacion recursiva bajando por todas las ramas
  // del arbol hasta encontrar una diferencia en los datos
  // Si ambas raices son NULL entonces hacemos return
  // Si solamente una de ellas es NULL y la otra si tiene un dato
  // ponemos estructura como 0 (falso)

  if(!arbolA.raiz || !arbolB.raiz) {
    // Uno o ambos arboles estan vacios
    printf("No es posible realizar esta accion\n");
    *estructura = 0;
    *datos = 0;
    return;
  }

  compararRaices(arbolA.raiz, arbolB.raiz, estructura);

  int indice = 0;

  void **datosArbolA = calloc(arbolA.cantidad, sizeof(void *));
  void **datosArbolB = calloc(arbolB.cantidad, sizeof(void *));
  extraccionDatos(arbolA.raiz, datosArbolA, &indice);
  indice = 0;
  extraccionDatos(arbolB.raiz, datosArbolB, &indice);
  // Ordenamos ambos arreglos menor a mayor
  bubbleSort(datosArbolA, arbolA.cantidad);
  bubbleSort(datosArbolB, arbolB.cantidad);
  for(int i = 0; i < arbolA.cantidad; i++)
    printf("%d ", (*((int*)(datosArbolA[i]))));
  printf("\n");
  for(int j = 0; j < arbolB.cantidad; j++)
    printf("%d ", (*((int*)(datosArbolB[j]))));
  printf("\n");
  for(int k = 0; k < arbolB.cantidad; k++) {
    int *a = (int*)(datosArbolA[k]);
    int *b = (int*)(datosArbolB[k]);
    if(*a != *b) {
      printf("%d != %d? %c\n", *a, *b, (*a!=*b)?'S':'N');
      *datos = 0;

    }
  }
  free(datosArbolA);
  free(datosArbolB);
}

void compararRaices(NodoA *raizA, NodoA *raizB, int *comparar) {
  if(!raizA && !raizB) return; // Estamos en las hojas por lo cual no hay nada
  if(!raizA || !raizB) *comparar = 0;

  if(*comparar != 0) {
    compararRaices(raizA->izq, raizB->izq, comparar);
    compararRaices(raizA->dch, raizB->dch, comparar);
  }
}

void swap_ptr(void **a, void **b) {
  void *tmp = *a;
  *a = *b;
  *b = tmp;
}

void bubbleSort(void **datos, int n) {
  int i, j;
  int swapped;
  for (i = 0; i < n - 1; i++)
  {
    swapped = 0;
    for (j = 0; j < n - 1; j++)
    {
      if (datos[j] && datos[j + 1]) {
        int a = *((int *)datos[j]);
        int b = *((int *)datos[j + 1]);
        if (a > b) {
          swap_ptr(&datos[j], &datos[j + 1]);
          swapped = 1;
        }
      } else if (datos[j] > datos[j + 1]) {
        swap_ptr(&datos[j], &datos[j + 1]);
        swapped = 1;
      }
    }
    if (!swapped) break;
  }
}

void eliminarArbol(Arbol *arbol) {
  eliminar_NodosA(arbol->raiz, arbol->liberar);
  arbol->raiz = NULL;
  arbol->cantidad = 0;
}

void eliminar_NodosA(NodoA *raiz, void (*liberar)(void *)) {
  if (!raiz)
    return;
  eliminar_NodosA(raiz->izq, liberar);
  eliminar_NodosA(raiz->dch, liberar);
  // LIBERAR
  if (liberar)
    liberar(raiz->dato);
  free(raiz);
}

void eliminarNodoA(Arbol *arbol, void((*liberar)(void *)), void *dato, int(*comparar)(void*, void*)) {
  if (!arbol || !arbol->raiz) return;

  NodoA *raiz = arbol->raiz;
  // Auxiliar buscar nodo por comparación 
  NodoA *find = raiz;
  while (find) {
    int cmp = comparar(dato, find->dato);
    if (cmp == 0) break;
    if (cmp > 0) 
      find = find->dch; 
    else 
      find = find->izq;
  }
  if (!find) {
    // no encontrado 
    return;
  }

  NodoA *padre = buscarPadre(raiz, dato, comparar);

  /* 
   Si el nodo a eliminar es la raíz: la nueva raíz será el subárbol izquierdo.
   El subárbol derecho del nodo eliminado se acopla al extremo derecho del subárbol izquierdo.
   Si el nodo no es la raíz: el subárbol izquierdo toma la posición del nodo eliminado y
   el subárbol derecho del nodo eliminado se acopla al extremo derecho del subárbol izquierdo.
  */

  // El nodo es la raiz 
  if (padre == NULL && comparar(find->dato, raiz->dato) == 0) {
    NodoA *left = find->izq;
    NodoA *right = find->dch;
    if (left) {
      NodoA *ext = extremoDch(left);
      if (ext) ext->dch = right;
      arbol->raiz = left;
    } else {
      /* si no hay left, la nueva raiz será right (o NULL) */
      arbol->raiz = right;
    }
    if (liberar && find->dato) liberar(find->dato);
    free(find);
    arbol->cantidad--;
    return;
  }

  /* Nodo no raiz */
  NodoA *left = find->izq;
  NodoA *right = find->dch;
  if (left) {
    // enlazar left en la posición del nodo a eliminar 
    if (padre->izq == find) 
      padre->izq = left; 
    else if (padre->dch == find) 
      padre->dch = left;
    NodoA *ext = extremoDch(left);
    if (ext) 
      ext->dch = right;
    if (liberar && find->dato) 
      liberar(find->dato);
    free(find);
    arbol->cantidad--;
    return;
  } else {
    // no hay left simplemente reemplazar por right 
    if (padre->izq == find) padre->izq = right; else if (padre->dch == find) padre->dch = right;
    if (liberar && find->dato) liberar(find->dato);
    free(find);
    arbol->cantidad--;
    return;
  }
}

void buscarEnArbol(NodoA *raiz, void *dato, NodoA *encontrado, int(*comparar)(void*,void*)) {
  if (encontrado->dato == NULL) {
    if (!raiz)
      return;
    printf("\nComparando con %d", (*(int *)(raiz->dato)));
    if (comparar(dato, raiz->dato) == 0) {
      encontrado->dato = raiz->dato;
      encontrado->izq = raiz->izq;
      encontrado->dch = raiz->dch;
    }

    if (comparar(dato, raiz->dato) == 1)
      buscarEnArbol(raiz->dch, dato, encontrado, comparar);
    else
      buscarEnArbol(raiz->izq, dato, encontrado, comparar);
    return;
  }
}

// Buscar padre busca al padre del valor ingresado
NodoA* buscarPadre(NodoA *raiz, void* dato, int(*comparar)(void*,void*)) {
  if (!raiz || !dato) return NULL;

  /* Si alguno de los hijos es el nodo buscado, la raiz actual es el padre */
  if ((raiz->izq && comparar(dato, raiz->izq->dato) == 0) ||
      (raiz->dch && comparar(dato, raiz->dch->dato) == 0)) {
    return raiz;
  }

  /* Si la raiz misma contiene el dato, no tiene padre */
  if (comparar(raiz->dato, dato) == 0) return NULL;

  /* Recursión según dirección */
  if (raiz->izq && comparar(dato, raiz->dato) < 0)
    return buscarPadre(raiz->izq, dato, comparar);
  if (raiz->dch && comparar(dato, raiz->dato) > 0)
    return buscarPadre(raiz->dch, dato, comparar);

  return NULL;
}

NodoA* extremoDch(NodoA *raiz){
  if (!raiz) return NULL;
  while (raiz->dch) {
    raiz = raiz->dch;
  }
  return raiz;
}

NodoA* extremoIzq(NodoA *raiz){
  if (!raiz) return NULL;
  while (raiz->izq) {
    raiz = raiz->izq;
  }
  return raiz;
}
