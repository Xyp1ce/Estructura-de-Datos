#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../captura/captura.h"
#include "../Estructuras/heap/heap.h"
#include "../Estructuras/arbol/arbol.h"

int compararEntero(void *, void *);
void imprimirEntero(void *);

int compararArchivo(void *, void *);
void imprimirArchivo(void *);

void imprimirPaginas(void *);

void eliminarArchivoHeap(char *nombre, Heap *heap);

void mostrarEstado(Heap heap);
void cambioPrioridad(Heap *heap);
void mostrarColaImpresion(Heap heap);
void limpiarColaImpresion(Heap *heap);
void agregarArchivo(Heap *heap);
void procesarArchivo(Heap *heap);

typedef struct Archivo
{
	char *nombre;
	int numPaginas;
} Archivo;

int main(void) {
	Heap heap = inicializarHeap(&imprimirArchivo, &compararArchivo); // SE INICIALIZA MIN POR DEFAULT
	char *nombres[] =
	{
		"Acta de matrimonio",
		"Acta de nacimiento",
		"CURP",
		"Declaracion de impuestos",
		"Codigos del GTA San Andreas",
		"Archivos del Pentagono",
		"Script filtrado de GTA VI"
	};
	int paginas[] = {11, 15, 12, 16, 17, 14, 13};
	int cant = 7;
	
	for (int i = 0; i < cant; i++)
	{
		Archivo *nuevoArchivo = (Archivo*) malloc(sizeof(Archivo));
		nuevoArchivo->nombre = (char*) malloc(strlen(nombres[i]) + 1);
		strcpy(nuevoArchivo->nombre, nombres[i]);
		nuevoArchivo->numPaginas = paginas[i];
		insertarHeap(&heap, nuevoArchivo);
	}

	int opcion = 0;
	do {
		mostrarEstado(heap);
		printf("\n\n 0. Cambiar prioridad");
		printf("\n 1. Mostrar cola de impresion");
		printf("\n 2. Agregar archivo");
		printf("\n 3. Procesar/imprimir archivo");
		printf("\n 4. Eliminar archivo");
		printf("\n 5. Eliminar todos los archivos");
		printf("\n 6. Terminar programa");
		inputEntero("\n Seleccione una opcion: ", &opcion);
		printf("\n");

		switch (opcion) {
		case 0: // Cambiar prioridad
			cambioPrioridad(&heap);
			break;
		case 1: // Mostrar cola de impresion
			mostrarColaImpresion(heap);
			break;
		case 2: // Agregar archivo
			agregarArchivo(&heap);
			break;
		case 3: // Procesar/imprimir archivo
			procesarArchivo(&heap);
			break;
		case 4: // Eliminar archivo
			if (heap.cantidad == 0) {
				printf("\n La cola de impresion esta vacia\n");
				break;
			}
			printf("\n");
			imprimirHeap(heap);
			printf("\n");

			char *nombreArchivoEliminar = NULL;
			inputCadenaDinamica("\n Ingrese el nombre del archivo a eliminar: ", &nombreArchivoEliminar, 100);

			eliminarArchivoHeap(nombreArchivoEliminar, &heap);

			free(nombreArchivoEliminar);
			break;
		case 5: // Eliminar todos los archivos
			limpiarColaImpresion(&heap);
			break;
		case 6: // Terminar programa
			// Liberar memoria restante
			while (heap.cantidad) {
				Archivo *archivo = (Archivo *)quitarHeap(&heap);
				if (archivo) {
					free(archivo->nombre);
					free(archivo);
				}
			}
			printf("\n FIN DEL PROGRAMA\n\n");
			break;
		default:
			printf("\n Ingrese de nuevo");
		}
	} while (opcion != 6);
	return 0;
}

void imprimirArchivo(void *a) {
	Archivo *aa = a;
	printf("%s (%d pgs)", aa->nombre, aa->numPaginas);
}

void imprimirPaginas(void *a) {
	Archivo *aa = a;
	printf("%d pgs", aa->numPaginas);
}

int compararArchivo(void *a, void *b) {
	Archivo *aa = a, *bb = b;
	if (aa->numPaginas == bb->numPaginas)
		return 0;
	if (aa->numPaginas < bb->numPaginas)
		return -1;
	return 1;
}

void eliminarArchivoHeap(char *nombre, Heap *heap) {
	int posicion = -1;
	
	// Buscar el archivo
	for (int i = 0; i < heap->cantidad; i++) {
		Archivo *check = (Archivo*) heap->arr[i]->dato;
		if (strcmp(check->nombre, nombre) == 0) {
			posicion = i;
			break; }
	}
	
	if (posicion == -1) {
		printf("\n Archivo '%s' no encontrado\n", nombre);
		return;
	}
	
	// Guardar referencia al archivo a eliminar
	Archivo *archivoAEliminar = (Archivo*) heap->arr[posicion]->dato;
	
	// Intercambiar con el último elemento
	NodoA *tmp = heap->arr[posicion];
	heap->arr[posicion] = heap->arr[heap->cantidad - 1];
	heap->arr[heap->cantidad - 1] = tmp;
	
	// Eliminar el último elemento (que ahora contiene el archivo buscado)
	heap->cantidad--;
	free(heap->arr[heap->cantidad]);
	heap->arr = realloc(heap->arr, sizeof(NodoA*) * heap->cantidad);
	
	// Reajustar el heap
	heapify(heap);
	
	// Liberar memoria del archivo
	free(archivoAEliminar->nombre);
	free(archivoAEliminar);
	
	printf("\n Archivo '%s' eliminado\n", nombre);
}

void mostrarEstado(Heap heap) {
	// Si hay mas de 5 archivos, mostrar solo los primeros 5
	if (heap.cantidad > 5) {
		printf("\n Primeros 5 archivos (de %d) del Heap (tipo %s):\n\n", heap.cantidad, (heap.tipo == MIN) ? "MINIMO": "MAXIMO");
		for (int i = 0; i < 5; i++) {
			heap.imprimir(heap.arr[i]->dato);
			if (i < 4)
				printf(" -> ");
		}
	} else {
		printf("\n Archivos del Heap (tipo %s):\n\n", (heap.tipo == MIN) ? "MINIMO": "MAXIMO");
		for (int i = 0; i < heap.cantidad; i++) {
			heap.imprimir(heap.arr[i]->dato);
			if (i < heap.cantidad - 1)
				printf(" -> ");
		}
	}
}

void cambioPrioridad(Heap *heap) {
	// Alterna entre MIN y MAX
	heap->tipo = (heap->tipo == MIN) ? MAX : MIN;
	printf("\n Prioridad cambiada exitosamente\n");
	heapify(heap);
}

void mostrarColaImpresion(Heap heap) {
	//Mostrar toda la cola de impresion
	printf("\n HEAP\n");
	for(int i = 0; i < heap.cantidad; i++) {
		heap.imprimir(heap.arr[i]->dato);
		if (i < (heap.cantidad < 5 ? heap.cantidad : 5) - 1) {
			 printf(" -> ");
		}
	}
	printf("\n\n ARBOL:\n");
	heap.arbol.imprimir = &imprimirPaginas;
	imprimirArbol(heap.arbol);
	heap.arbol.imprimir = &imprimirArchivo;
	printf("\n");
}

void agregarArchivo(Heap *heap) {
	int noPaginas = 0;
	char *nombreArchivo = NULL;
	inputEntero("\n Ingrese el numero de paginas: ", &noPaginas);
	inputCadenaDinamica("\n Ingrese el nombre del archivo: ", &nombreArchivo, 100);

	Archivo *nuevoArchivo = (Archivo*) malloc(sizeof(Archivo));
	nuevoArchivo->nombre = nombreArchivo;
	nuevoArchivo->numPaginas = noPaginas;

	insertarHeap(heap, nuevoArchivo);

	printf("\n Archivo '%s' agregado\n", nombreArchivo);
}

void procesarArchivo(Heap *heap) {
	// Se procesa (elimina/saca) el archivo de mayor prioridad en la cola de impresión (heap).
	Archivo *archivoProcesado = (Archivo*) quitarHeap(heap);
	if (archivoProcesado) {
		printf("\n Procesando archivo: ");
		imprimirArchivo(archivoProcesado);
		printf("\n");

		// Liberar memoria del archivo procesado
		free(archivoProcesado->nombre);
		free(archivoProcesado);
	} else {
		printf("\n No hay archivos para procesar\n");
	}
}

void limpiarColaImpresion(Heap *heap) {
	// Liberar memoria restante
	while (heap->cantidad) {
		Archivo *archivo = (Archivo *)quitarHeap(heap);
		if (archivo) {
			free(archivo->nombre);
			free(archivo);
		}
	}
	printf("\n Cola de impresion limpiada \n");
}