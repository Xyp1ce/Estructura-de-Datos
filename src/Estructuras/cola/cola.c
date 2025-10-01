#include "cola.h"
#include <stdio.h>

Cola inicializarCola(void) {
	return (Cola) {NULL,NULL,-1,0,NULL,NULL};
}

int llenaC(Cola cola) {
  return cola.cantidad == cola.capacidad;
}

int vaciaC(Cola cola) {	
  return cola.cantidad == 0;
}

void enqueue(Cola *cola,void *dato) {	
  if(llenaC(*cola)) {
    printf("Overflow");
  } else {
    Nodo *nuevo = crearNodo(dato);
    nuevo->sig = NULL;
    if(cola->inicio == NULL) { // cola vacia 
      cola->inicio = nuevo;
      cola->fin = nuevo;
    } else {
      cola->fin->sig = nuevo;
      cola->fin = nuevo;
    }
    cola->cantidad++;
  }
}

void* peekC(Cola cola) {	
	return cola.inicio->dato;
}

void* dequeue(Cola *cola) {
  if(vaciaC(*cola)) {
    printf("Underflow");
    return NULL;
  } else {
		//DESENCADENAR EL NODO
		Nodo *aux = cola->inicio;		
		cola->inicio = aux->sig;
		aux->sig = NULL;
		//EXTRAER EL DATO
		void *dato = aux->dato;
		//LIBERAR EL NODO
		free(aux);
		cola->cantidad--;
		return dato;
  }
	return NULL;
}

void imprimirCola(Cola cola) {
  printf("Cola[%d]: ", cola.cantidad);
	Cola aux = (Cola){NULL,NULL,cola.capacidad,0,NULL,NULL};
	Nodo *nodo;
	while( !vaciaC(cola) )
	{
		nodo = dequeue_nodo(&cola);
		printf(" -> ");
		cola.imprimir(nodo->dato);
		enqueue_nodo(&aux,nodo);
	}
	while( !vaciaC(aux) )
		enqueue_nodo(&cola,dequeue_nodo(&aux));
}

void eliminarCola(Cola *cola) {
	void *dato;
	while(!vaciaC(*cola))
	{
		dato = dequeue(cola);
		if( cola->liberar )
			cola->liberar(dato);
	}
	return;
}

void* buscarC(Cola cola,void *dato,int (*comparar)(void*,void*)) {
  Cola aux = (Cola){NULL,NULL,cola.capacidad,0,NULL,NULL};
  void *encontrado = NULL;
  while(!vaciaC(cola)){
    if(comparar(cola.inicio->dato, dato) == 0){
      encontrado = cola.inicio->dato;
      break;
    } else {
      enqueue(&aux, dequeue(&cola));
    }
  }
  while(!vaciaC(aux)){
    enqueue(&cola,dequeue(&aux));
  }
	return encontrado;
}

void enqueue_nodo(Cola *cola ,Nodo *nuevo) {
	if(llenaC(*cola)) {
		printf("\n Overflow");
	}
	else {
		nuevo->sig = cola->inicio;
		cola->inicio= nuevo;
		cola->cantidad++;
	}
}

Nodo* dequeue_nodo(Cola *cola) {
	if(vaciaC(*cola)) {
		printf("\n Underflow");
		return NULL;
	}
	else {
		//DESENCADENAR EL NODO
		Nodo *aux = cola->inicio;		
		cola->inicio = aux->sig;
    if(cola->inicio == NULL)
      cola->fin = NULL;
		aux->sig = NULL;
    cola->cantidad--;
		return aux;
	}
}
