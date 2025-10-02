
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h>
#include <time.h>
#include "../captura/captura.h"
#include "../Estructuras/arbol/arbol.h"

int* crearEntero(int);
int compararEntero(void*,void*);
void imprimirEntero(void*);

void myprintf(char *formato,...);

int main(void)
{
	Arbol arbol;
	arbol.raiz = NULL;
	arbol.cantidad = 0;
	arbol.imprimir = &imprimirEntero;
	arbol.comparar = &compararEntero;
  arbol.liberar = free;
	insertarArbol(&arbol, crearEntero(4));
	insertarArbol(&arbol, crearEntero(2));
	insertarArbol(&arbol, crearEntero(6));
	insertarArbol(&arbol, crearEntero(3));
	insertarArbol(&arbol, crearEntero(7));
	insertarArbol(&arbol, crearEntero(1)); 

	imprimirArbol(arbol);
	//
	// printf("\n PREORDEN: ");
	// imprimirOrden(arbol,PREORDEN);
	// printf("\n ORDEN: ");
	// imprimirOrden(arbol,ORDEN);
	// printf("\n INVERSO: ");
	// imprimirOrden(arbol,INVERSO);
	// printf("\n POSTORDEN: ");
	// imprimirOrden(arbol,POSTORDEN);

  printf("\nAltura: %d", altura(arbol));
  NodoA bool;
  bool.dato = NULL;
  buscarEnArbol(arbol.raiz, 1, &bool);
  if(bool.dato) {
    printf("\nEncontrado\n");
    printf("%d", (*(int*)(bool.dato)));
  } else 
    printf("\nNo encontrado\n");
  // equilibrar(&arbol);
	
	printf("\n\n FIN DE PROGRAMA\n");
	return 0;
}

int* crearEntero(int dato)
{
	int *nuevo = malloc(sizeof(int));
	*nuevo = dato;
	return nuevo;
}

int compararEntero(void*a,void*b)
{
	int *aa = a,*bb=b;
	if(*aa==*bb)return 0;
	else if(*aa<*bb)return -1;
	else return 1;
}

void imprimirEntero(void *a)
{
	int *aa=a;
	printf("%d",*aa);
}
