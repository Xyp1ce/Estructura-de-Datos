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
	Arbol arbolB;
	// Arbol arbolA;

	arbol.raiz = NULL;
	arbol.cantidad = 0;
	arbol.imprimir = &imprimirEntero;
	arbol.comparar = &compararEntero;
	arbol.liberar = free;

	arbolB.raiz = NULL;
	arbolB.cantidad = 0;
	arbolB.imprimir = &imprimirEntero;
	arbolB.comparar = &compararEntero;
	arbolB.liberar = free;

	// arbolA.raiz = NULL;
	// arbolA.cantidad = 0;
	// arbolA.imprimir = &imprimirEntero;
	// arbolA.comparar = &compararEntero;
	// arbolA.liberar = free;

	// menú interactivo
	int opcion = 0;
	while (opcion != 9) {
		printf("\n=== MENU ===\n");
		printf("1. Insertar en arbol A\n");
		printf("2. Insertar en arbol B\n");
		printf("3. Comparar Arboles\n");
		printf("4. Eliminar dato en arbol A\n");
		printf("5. Eliminar dato en arbol B\n");
		printf("6. Ver profundidades (altura)\n");
		printf("7. Equilibrar arboles (si factor fuera de [-1,1])\n");
		printf("8. Mostrar arboles (A y B)\n");
		printf("9. Terminar programa\n");
		printf("Seleccione una opcion: ");
		if (scanf("%d", &opcion) != 1) { 
			while(getchar()!='\n'); 
			opcion = 0; 
			continue; 
		}

		switch (opcion) {
			case 1:
			case 2: {
				int val;
				printf("Ingrese entero a insertar: ");
				if (scanf("%d", &val) != 1) { 
					while(getchar()!='\n'); 
					break; 
				}
				int *p = crearEntero(val);
				if (opcion == 1) 
					insertarArbol(&arbol, p); 
				else 
					insertarArbol(&arbolB, p);
				printf("Insertado %d en arbol %c\n", val, (opcion==1)?'A':'B');
				break;
			}
			case 3: {
				int estructura = 1, datos = 1;
				compararArboles(arbol, arbolB, &estructura, &datos);
				printf("Resultado comparacion:\n");
				printf("  Estructura igual: %s\n", estructura?"SI":"NO");
				printf("  Datos iguales: %s\n", datos?"SI":"NO");
				break;
			}
			case 4:
			case 5: {
				int val;
				printf("Ingrese entero a eliminar: ");
				if (scanf("%d", &val) != 1) { 
					while(getchar()!='\n'); 
					break; 
				}
				if (opcion == 4) 
					eliminarNodoA(&arbol, arbol.liberar, &val, arbol.comparar);
				else 
					eliminarNodoA(&arbolB, arbolB.liberar, &val, arbolB.comparar);
				printf("Solicitud de eliminacion de %d en arbol %c procesada\n", val, (opcion==4)?'A':'B');
				break;
			}
			case 6: {
				int ha = altura(arbol);
				int hb = altura(arbolB);
				printf("Altura arbol A: %d\n", ha);
				printf("Altura arbol B: %d\n", hb);
				break;
			}
			case 7: {
				int leftA = 0, rightA = 0, leftB = 0, rightB = 0;
				if (arbol.raiz) { 
					Arbol t = { arbol.raiz->izq, 0, arbol.imprimir, arbol.comparar, arbol.liberar }; 
					leftA = altura(t); Arbol t2 = { arbol.raiz->dch, 0, arbol.imprimir, arbol.comparar, arbol.liberar }; 
					rightA = altura(t2); 
				}
				if (arbolB.raiz) { 
					Arbol t = { arbolB.raiz->izq, 0, arbolB.imprimir, arbolB.comparar, arbolB.liberar }; 
					leftB = altura(t); 
					Arbol t2 = { arbolB.raiz->dch, 0, arbolB.imprimir, arbolB.comparar, arbolB.liberar }; 
					rightB = altura(t2); 
				}
				int factorA = leftA - rightA; int factorB = leftB - rightB;
				if (factorA < -1 || factorA > 1) { 
					equilibrar(&arbol); 
					printf("Arbol A equilibrado (factor=%d)\n", factorA); 
				}
				else 
					printf("Arbol A ya balanceado (factor=%d)\n", factorA);
				if (factorB < -1 || factorB > 1) { 
					equilibrar(&arbolB); 
					printf("Arbol B equilibrado (factor=%d)\n", factorB); 
				}
				else 
					printf("Arbol B ya balanceado (factor=%d)\n", factorB);
				break;
			}
			case 8:
				printf("\n--- Arbol A ---\n"); imprimirArbol(arbol);
				printf("\n--- Arbol B ---\n"); imprimirArbol(arbolB);
				printf("\n");
				break;
			case 9:
				printf("Saliendo...\n");
				break;
			default:
				printf("Opcion invalida\n");
		}
		// limpiar buffer
		while(getchar()!='\n');
	}
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
