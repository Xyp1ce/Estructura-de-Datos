#include "cola.h"
#include <stdio.h>


Cola inicializarCola(void) {
	return (Cola) {NULL,NULL,-1,0,NULL,NULL};
}

int llenaC(Cola cola) {
  if(cola.cantidad == cola.capacidad)
	  return 1;
  else 
    return 0;
}

int vaciaC(Cola cola) {	
  if(cola.cantidad == 0)
	  return 0;
  else 
    return 1;
}

void enqueue(Cola *cola,void *dato) {	
  if(llenaC(*cola)) {
    printf("Overflow");
  } else {
    Nodo *nuevo = crearNodo(dato);
    nuevo->sig = cola->fin;
    cola->fin = nuevo;
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
void imprimirCola(Cola cola)
{
	Cola aux = (Cola){NULL,NULL,cola.capacidad,0,NULL,NULL};
	Nodo *nodo;
	printf("\n\nCola [%d]:",cola.cantidad);
	while( !vaciaC(cola) )
	{
		nodo = dequeue_nodo(&cola);
		printf("\n ");
		cola.imprimir(nodo->dato);
		enqueue_nodo(&aux,nodo);
	}
	while( !vaciaC(aux) )
		enqueue_nodo(&cola,dequeue_nodo(&aux));
}

void eliminarCola(Cola *cola)
{
	void *dato;
	while(!vaciaC(*cola))
	{
		dato = dequeue(cola);
		if( cola->liberar )
			cola->liberar(dato);
	}
	return;
}

void* buscarC(Cola cola,void *dato,int (*comparar)(void*,void*))
{
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
