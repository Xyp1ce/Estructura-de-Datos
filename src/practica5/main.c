#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../captura/captura.h"
#include "../Estructuras/cola/cola.h"

#define NUMERO_CAJAS 5
#define HABILITADA 1
#define DESHABILITADA 0
#define MIN_ARTICULOS 1
#define MAX_ARTICULOS 50

typedef struct
{
	Cola cola;
	int estado;
}Caja;


void generar_articulos(Caja *cajas);
void deshabilitarCaja(Caja *cajas);
void habilitarCaja(Caja *cajas);
void scannProd(Caja *cajas);
int compararEnteros(void* a, int b);
void imprimirCajero(Caja *cajas);
void imprimirProducto(void*);

int main(void) {
	Caja cajas[5];
	int opcion;	
  
  // Inicializar colas 
  for(int i = 0; i < 5; i++) {
    cajas[i].cola = inicializarCola();
    cajas[i].cola.capacidad = 20;
    cajas[i].cola.imprimir = &imprimirProducto;
    cajas[i].estado = HABILITADA;
  }

	do {
    imprimirCajero(cajas);
		opcion = 0;
		//DESPLEGAR LAS CAJAS
		printf("\n [1] AVANZAR TICK");
		printf("\n [2] SCANNEAR PRODUCTO");
		printf("\n [3] HABILITAR");
		printf("\n [4] DESHABILITAR");
		printf("\n [5] TERMINAR");
		inputEntero("\n Selecciona opcion: ",&opcion);
		switch(opcion) {
      case 1: // Agregar clientes
        generar_articulos(cajas);
        break;
      case 2: // Scanear productos
        scannProd(cajas);
        break;
      case 3: // Habilitar caja
        habilitarCaja(cajas);
        break;
      case 4: // Desahbilitar caja
        deshabilitarCaja(cajas);
        break;
      case 5: // Terminar programa
        printf("Terminando programa...\n");
        break;
      default:
        printf("\nOpcion invalida...\n");
        break;
		}	
	}while(opcion!=5);
	return 0;
}

void generar_articulos(Caja *cajas) {
  for(int i = 0; i <= 4; i++){
    int cantidad = rand() % (MAX_ARTICULOS - MIN_ARTICULOS + 1) + MIN_ARTICULOS;
    if(cajas[i].estado && !llenaC(cajas[i].cola)){
      int* cliente = malloc(sizeof(int));
      *cliente = cantidad;
      enqueue(&cajas[i].cola, cliente);
    }
  }
}

void deshabilitarCaja(Caja *cajas){
  int opc;
  do {
    inputEntero("Que caja quieres deshabilitar? 1 - 5\n>> ", &opc);
  } while(opc > 5 || opc < 1);
  if(!(cajas[opc - 1].estado))
    printf("Esa caja ya esta deshabilitada\n");
  else {
    printf("Caja [%d] deshabilitada\n", opc);
    cajas[opc - 1].estado = DESHABILITADA;
  }
}

void habilitarCaja(Caja *cajas){
  int opc;
  do {
    inputEntero("Que caja quieres habilitar? 1 - 5\n>> ", &opc);
  } while(opc > 5 || opc < 1);
  if(cajas[opc - 1].estado)
    printf("Esa caja ya esta habilitada\n");
  else {
    printf("Caja [%d] habilitada\n", opc);
    cajas[opc - 1].estado = HABILITADA;
  }
}

void scannProd(Caja *cajas){
  for(int i = 0; i < NUMERO_CAJAS; i++){
    if(!(vaciaC(cajas[i].cola))){
      if(compararEnteros(cajas[i].cola.inicio->dato, 1)) {
        // es el ultimo dato a scanear por lo que lo sacamos de la pila
        free(dequeue(&cajas[i].cola));
      } else {
        int *cliente =  cajas[i].cola.inicio->dato;
        (*cliente)--;
      }
    }
  }
}

int compararEnteros(void* a, int b) {
  int *aa = a;
  if(*aa == b)
    return 1;
  else 
    return 0;
}

void imprimirCajero(Caja *cajas) {
  imprimirCola(cajas[0].cola);
  printf("\n");
  imprimirCola(cajas[1].cola);
  printf("\n");
  imprimirCola(cajas[2].cola);
  printf("\n");
  imprimirCola(cajas[3].cola);
  printf("\n");
  imprimirCola(cajas[4].cola);
  printf("\n");
}

void imprimirProducto(void *a) {
  int *aa;
  aa = a;
  printf("{%d}",*aa);
}
