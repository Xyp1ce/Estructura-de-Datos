#ifndef NODOARBOL_H
#define NODOARBOL_H
#include <stdlib.h>

typedef struct nodoArbol {
  struct nodoArbol *izq;
  struct nodoArbol *dch;
  void *dato;
}NodoA;

NodoA* crearNodoA(void *dato);

#endif
