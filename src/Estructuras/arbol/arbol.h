#ifndef ARBOL_H
#define ARBOL_H

#include "../nodos/nodoarbol.h"
#include <stdio.h>

#define PREORDEN 1
#define ORDEN 2
#define POSTORDEN 3
#define INVERSO 4
typedef struct
{
	NodoA *raiz;
	int cantidad;
	void (*imprimir)(void*);
	int (*comparar)(void*,void*);
	void (*liberar)(void*);
}Arbol;

void insertarArbol(Arbol *arbol,void *dato);
void imprimirArbol(Arbol arbol);
void imprimirOrden(Arbol arbol,int opcion);
int altura(Arbol arbol);
void equilibrar(Arbol *arbol);
void ordenarRaices(void **ordenar, void **inicio, void **final, int *indice);
void eliminarArbol(Arbol *arbol);
void eliminar_NodosA(NodoA *raiz, void (*liberar)(void *));
NodoA* buscarEnArbol(NodoA *raiz, int dato, NodoA *encontrado, int dato);

#endif
