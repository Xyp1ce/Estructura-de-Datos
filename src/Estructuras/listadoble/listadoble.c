#include "listadoble.h"
#include <stdio.h>
#include <stdlib.h>

ListaD inicializarListaD(void) {
  ListaD lista;
  lista.inicio = NULL;
  lista.fin = NULL;
  lista.cant = 0;
  lista.comparar = NULL;
  lista.imprimir = NULL;
  return lista;
}

void mostrarListaD(ListaD lista, int opc) {
  NodoD *p;
  printf("\n Lista[%d]: ", lista.cant);
  if(opc == 0) {
    // Imprimir en fin a inicio
    for(p = lista.fin; p != NULL; p = p->ant) {
      printf(" ");
      lista.imprimir(p->dato);
      printf("->");
    }
  } else {
    // Imprimir de inicio a fin
    for(p = lista.inicio; p != NULL; p = p->sig) {
      printf(" ");
      lista.imprimir(p->dato);
      printf("->");
    }
  }
  printf("NULL\n");
}

void borrarLista(ListaD *lista) {
  NodoD *actual, *anterior = NULL;
  for(actual = lista->inicio; actual != NULL;) {
    anterior = actual;
    actual = actual->sig;
    free(anterior);
  }
  lista->inicio = lista->fin = NULL;
  lista->cant = 0;
}

void borrarDato(ListaD *lista, void *dato, int (*comparar)(void*, void*)) {
    NodoD *actual;
    for (actual = lista->inicio; actual != NULL; actual = actual->sig) {
        if (comparar(dato, actual->dato) == 0) {
            // Caso: eliminar primer nodo
            if (actual == lista->inicio)
                lista->inicio = actual->sig;
            else
                actual->ant->sig = actual->sig;
            // Caso: eliminar último nodo
            if (actual == lista->fin)
                lista->fin = actual->ant;
            else
                actual->sig->ant = actual->ant;
            lista->cant--;
            // Si quedó vacía
            if (lista->cant == 0) {
                lista->inicio = NULL;
                lista->fin = NULL;
            }
            free(actual);
            break;
        }
    }
}

void* buscarDato(ListaD lista, void *dato, int (*comparar)(void*, void*)) {
  NodoD *actual;
  for(actual = lista.inicio; actual != NULL; actual = actual->sig) {
    if(comparar(dato, actual->dato) == 0) {
      return actual->dato;
    }
  }    
  return NULL;
}

void insertarOrdenado(ListaD *lista, void* dato) {
  NodoD *nuevo = crearNodoD(dato);
  NodoD *actual, *anterior = NULL;

  for(actual = lista->inicio; actual != NULL; actual = actual->sig) {
    if(lista->comparar(dato, actual->dato) < 0) {
      if(anterior != NULL) {
        // INSERTO EN MEDIO
        anterior->sig = nuevo;
        nuevo->ant = anterior;
        nuevo->sig = actual;
        actual->ant = nuevo;
      } else {
        // INSERTAR EN EL INICIO
        nuevo->sig = actual;
        nuevo->ant = NULL;
        actual->ant = nuevo;
        lista->inicio = nuevo;
      }
      break;
    }
    anterior = actual;
  }        

  if(lista->inicio == NULL) {
    // Lista vacia: insertamos al inicio
    lista->inicio = nuevo;
    lista->fin = nuevo;
  } else if (anterior != NULL && actual == NULL) {
    // Recorri toda la lista: insertamos al final
    anterior->sig = nuevo;    
    nuevo->sig = NULL;
    nuevo->ant = anterior;
    lista->fin = nuevo;
  }
  lista->cant++;    
}

void insertarFinal(ListaD *lista, void* dato) {
  // CREAR NODO
  NodoD *nuevo = crearNodoD(dato);
  if(lista->inicio == NULL && lista->cant == 0) {
    // LISTA VACIA ASOCIAMOS AL INICIO
    lista->inicio = lista->fin = nuevo;
  } else {
    // RECORRER Y ENCONTRAR EL ULTIMO NODO INSERTAR
    lista->fin->sig = nuevo;
    nuevo->ant = lista->fin;
    lista->fin = nuevo;
  }
  lista->cant++;
  printf("Creado correctamente\n");
}

void insertarInicio(ListaD *lista, void* dato) {
  NodoD *nuevo = crearNodoD(dato);
  nuevo->sig = lista->inicio;
  if(lista->inicio != NULL) {
    lista->inicio->ant = nuevo;
  } else {
    lista->fin = nuevo;
  }
  lista->inicio = nuevo;    
  lista->cant++;
}

void insertarEnPosicion(ListaD *lista, void* dato, int pos) {    
  // VALIDAR
  if(pos < 0 || pos > lista->cant) {
    return; // Posición inválida
  }

  if(pos == 0) {
    insertarInicio(lista, dato);
    return;
  }

  if(pos == lista->cant) {
    insertarFinal(lista, dato);
    return;
  }

  NodoD *actual = lista->inicio;
  for(int i = 0; i < pos; i++) {
    actual = actual->sig;
  }

  NodoD *nuevo = crearNodoD(dato);
  nuevo->sig = actual;
  nuevo->ant = actual->ant;
  actual->ant->sig = nuevo;
  actual->ant = nuevo;
  lista->cant++;
}

void eliminarEnPosicion(ListaD *lista, int pos) {
  // VALIDAR
  if(pos < 0 || pos >= lista->cant || lista->inicio == NULL) {
    return;
  }

  NodoD *actual = lista->inicio;

  if(pos == 0) {
    lista->inicio = actual->sig;
    if(lista->inicio != NULL) {
      lista->inicio->ant = NULL;
    } else {
      lista->fin = NULL;
    }
    free(actual);
    lista->cant--;
    return;
  }

  if(pos == lista->cant - 1) {
    actual = lista->fin;
    lista->fin = actual->ant;
    if(lista->fin != NULL) {
      lista->fin->sig = NULL;
    }
    free(actual);
    lista->cant--;
    return;
  }

  for(int i = 0; i < pos; i++) {
    actual = actual->sig;
  }

  actual->ant->sig = actual->sig;
  actual->sig->ant = actual->ant;
  free(actual);
  lista->cant--;
}

void reordenar(ListaD *listaOrigen, int (*comparar)(void*, void*)) {
  ListaD aux;
  aux.inicio = NULL;
  aux.fin = NULL;
  aux.cant = 0;
  aux.comparar = comparar;
  aux.imprimir = listaOrigen->imprimir;

  NodoD *actual = listaOrigen->inicio;
  NodoD *siguiente;

  while(actual != NULL) {
    siguiente = actual->sig;
    insertarOrdenado(&aux, actual->dato);
    free(actual);
    actual = siguiente;
  }

  listaOrigen->inicio = aux.inicio;
  listaOrigen->fin = aux.fin;
  listaOrigen->cant = aux.cant;
}
