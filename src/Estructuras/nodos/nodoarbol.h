#ifndef 
#define NODOARBOL_H
#include <stdlib.h>

typedef struct nodo {
  struct nodo *izq;
  struct nodo *dch;
  void *dato;
}NodoA;

NodoA* crearNodoA(void *dato);

#endif
