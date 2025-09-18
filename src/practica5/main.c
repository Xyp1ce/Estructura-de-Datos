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


void generar_articulos(Caja *);
void deshabilitarCaja(Caja *cajas);
void habilitarCaja(Caja *cajas);
void scannProd(Caja *cajas);

int main(void)
{
	Caja cajas[5];
	int opcion;	
	do
	{
		opcion = 0;
		//DESPLEGAR LAS CAJAS
		printf("\n [1] AVANZAR TICK");
		printf("\n [2] CONFIGURAR");
		printf("\n [3] HABILITAR/DESHABILITAR");
		printf("\n [4] TERMINAR");
		inputEntero("\n Selecciona opcion: ",&opcion);
		switch(opcion)
		{
      case 1: // Agregar clientes
        printf("\n [1]");
        generar_articulos(cajas);
        break;
      case 2: // Scanear productos
        printf("\n [2]");
        break;
      case 3: // Habilitar caja
        printf("\n [3]");
        habilitarCaja(cajas);
        break;
      case 4: // Desahbilitar caja
        printf("\n [4]");
        deshabilitarCaja(cajas);
        break;
      case 5: // Terminar programa
        printf("\n [5]");
        printf("Terminando programa...");
        break;
      default:
        printf("\nOpcion invalida...");

		}	
	}while(opcion!=5);
	
	printf("\n\n FIN DE PROGRAMA");
	return 0;
}


void generar_articulos(Caja *cajas) {
  for(int i = 0; i <= 4; i++){
    int cantidad = rand() % (MAX_ARTICULOS - MIN_ARTICULOS + 1) + MIN_ARTICULOS;
    if(cajas[i].estado && !llenaC(cajas[i].cola)){
      void* cliente = malloc(sizeof(int));
      *cliente = cantidad;
      enqueue(&cajas[i].cola, cliente);
    }
  }
}

void deshabilitarCaja(Caja *cajas){
  int opc;
  do {
    inputEntero("Que caja quieres deshabilitar? 1 - 4\n>>", &opc);
  } while(opc > 4 || opc < 1);
  if(!(cajas[opc - 1].estado))
    printf("Esa caja ya esta deshabilitada");
  else
    cajas[opc - 1].estado = DESHABILITADA;
}

void habilitarCaja(Caja *cajas){
  int opc;
  do {
    inputEntero("Que caja quieres habilitar? 1 - 4\n>>", &opc);
  } while(opc > 4 || opc < 1);
  if(cajas[opc - 1].estado)
    printf("Esa caja ya esta habilitada");
  else 
    cajas[opc - 1].estado = HABILITADA;
}

void scannProd(Caja *cajas){
  for(int i = 0; i <= 4; i++){
    if(!(vaciaC(cajas[i].cola))){
      if(*(cajas[i].cola.inicio->dato) == 1)
        dequeue(cajas[i]);
    }
  }
}

