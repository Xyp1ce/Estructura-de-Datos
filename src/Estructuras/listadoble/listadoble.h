#ifndef LISTA_DOBLE_H
#define LISTA_DOBLE_H

#include "../nodos/nododoble.h"

typedef struct lista_doble {
    NodoD *inicio;
    NodoD *fin;
    int cant;
    int (*comparar)(void *datoA, void *dataB);
    void (*imprimir)(void *datoA);
} ListaD;

ListaD inicializarListaD(void);
void mostrarListaD(ListaD lista, int opc);
void borrarLista(ListaD *lista);
void borrarDato(ListaD *lista,void* dato, int (*comparar)(void*, void*));
void* buscarDato(ListaD lista, void *dato, int (*comparar)(void*, void*));
void insertarOrdenado(ListaD *lista, void* dato);
void insertarFinal(ListaD *lista, void* dato);
void insertarInicio(ListaD *lista, void* dato);
void insertarEnPosicion(ListaD *lista, void* dato, int pos);
void eliminarEnPosicion(ListaD *lista, int pos);
void reordenar(ListaD *listaOrigen, int (*comparar)(void*, void*));

#endif
