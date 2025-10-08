
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h>
#include <time.h>
#include "../captura/captura.h"
#include "../Estructuras/arbol/arbol.h"

int *crearEntero(int);
int compararEntero(void *, void *);
void imprimirEntero(void *);

int main(void)
{
	Arbol arbol;
	Arbol arbolA;

	arbol.raiz = NULL;
	arbol.cantidad = 0;
	arbol.imprimir = &imprimirEntero;
	arbol.comparar = &compararEntero;
	arbol.liberar = free;

	arbolA.raiz = NULL;
	arbolA.cantidad = 0;
	arbolA.imprimir = &imprimirEntero;
	arbolA.comparar = &compararEntero;
	arbolA.liberar = free;

	insertarArbol(&arbol, crearEntero(8));
	insertarArbol(&arbol, crearEntero(7));
	insertarArbol(&arbol, crearEntero(10));
	insertarArbol(&arbol, crearEntero(6));
	insertarArbol(&arbol, crearEntero(4));
	insertarArbol(&arbol, crearEntero(1));
	insertarArbol(&arbol, crearEntero(5));
	insertarArbol(&arbol, crearEntero(9));
	insertarArbol(&arbol, crearEntero(11));

	printf("\n");
	imprimirArbol(arbol);
	printf("\n\n");

	insertarArbol(&arbolA, crearEntero(8));
	insertarArbol(&arbolA, crearEntero(7));
	insertarArbol(&arbolA, crearEntero(10));
	insertarArbol(&arbolA, crearEntero(6));
	insertarArbol(&arbolA, crearEntero(4));
	insertarArbol(&arbolA, crearEntero(1));
	insertarArbol(&arbolA, crearEntero(5));
	insertarArbol(&arbolA, crearEntero(2));
	insertarArbol(&arbolA, crearEntero(11));

	imprimirArbol(arbolA);

	// Inicializamos en uno asumiendo que son iguales
	int estructura = 1;
	int datos = 1;

	compararArboles(arbol, arbolA, &estructura, &datos);

	if(estructura) 
		printf("\nLa estrucutra de los arboles es la misma\n");
	else
		printf("\nLa estructura es diferente\n");

	if(datos) 
		printf("\nLos datos entre los arboles son los mismos\n");
	else
		printf("\nLos datos entre los arboles son diferentes\n");

	// printf("\n PREORDEN: ");
	// imprimirOrden(arbol,PREORDEN);
	// printf("\n ORDEN: ");
	// imprimirOrden(arbol,ORDEN);
	// printf("\n INVERSO: ");
	// imprimirOrden(arbol,INVERSO);
	// printf("\n POSTORDEN: ");
	// imprimirOrden(arbol,POSTORDEN);

	// printf("\nAltura: %d", altura(arbol));
  
	NodoA bool = {NULL, NULL, NULL};

  NodoA buscar = {NULL, NULL, crearEntero(1)};
	buscarEnArbol(arbol.raiz, buscar.dato, &bool, arbol.comparar);
	if(bool.dato) {
		printf("\nEncontrado\n");
		printf("%d", (*(int *)(bool.dato)));
	}
	else
		printf("\nNo encontrado\n");

  NodoA padre = {NULL, NULL, NULL};
  buscarPadre(arbol.raiz, &padre, buscar.dato, arbol.comparar);
	if(padre.dato) {
		printf("\nPadre encontrado\n");
		printf("%d", (*(int *)(padre.dato)));
	}
	else
		printf("\nNo encontrado\n");
	// printf("\n\nArbol equilibrado");
	// equilibrar(&arbol);
	// imprimirArbol(arbol);

	printf("\n\n FIN DE PROGRAMA\n");
	return 0;
}

int *crearEntero(int dato)
{
	int *nuevo = malloc(sizeof(int));
	*nuevo = dato;
	return nuevo;
}

int compararEntero(void *a, void *b)
{
	int *aa = a, *bb = b;
	if (*aa == *bb)
		return 0;
	else if (*aa < *bb)
		return -1;
	else
		return 1;
}

void imprimirEntero(void *a)
{
	int *aa = a;
	printf("%d", *aa);
}
