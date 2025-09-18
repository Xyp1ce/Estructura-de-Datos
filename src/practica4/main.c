#include <stdio.h>
#include <stdlib.h>
#include "../captura/captura.h"
#include "../Estructuras/pila/pila.h"

#define ARRIBA 1
#define ABAJO 2
#define DERECHA 4
#define IZQUIERDA 8

#define REN 27
#define COL 26

typedef struct Coordenada {
	int x,y;
} Coordenada;

unsigned char **crear_laberinto(void);
void imprimirLab(unsigned char **lab);

Coordenada* crearCoordenada(int x,int y);
int compararCoordenada(void *a, void *b);
void imprimirCoordenada(void *dato);
void liberarCoordenada(void *dato);

unsigned char alternativas(unsigned char **lab, Coordenada *coordenada);
void imprimirPosibles(unsigned char);

void liberarLaberinto(unsigned char **lab);

Pila solucion(unsigned char **lab);

int main(void) {
	unsigned char **lab; 
	lab = (unsigned char**) crear_laberinto();
	imprimirLab(lab);

	Pila pila = {NULL, REN * COL, 0, &imprimirCoordenada, &liberarCoordenada};

	pila = solucion(lab);
	printf("\n\nSolucion:\n");
	imprimirPila(pila);

	liberarLaberinto(lab);

	printf("\n\n");
	return 0;
}

unsigned char **crear_laberinto(void) {
	int i,j;
	char *tmp = 
"xxxxxxxxxxxxxxxxxxxxxxxxxx\
xAx*****x****************x\
x*xxx*x*x*xxxxxxxxx*xxxx*x\
x*****x*x******x**x****x*x\
xxxxxxx*xxxxxx*xx*xxxx*xxx\
x*****x*x****x*x****xx***x\
x*xxx*x*xxxx*x*x*xxxxx*x*x\
x***x*x****x*****xxxxxxx*x\
xxx*x*xxxx*xxxxxxx****x**x\
x*x*x***xx****xx***xx*x*xx\
x*x*x*x*xxxxx**x*xxxx*x**x\
x*x*x*x***x*xx*x****x*xx*x\
x*x*x*xxx****x*x*xx*x****x\
x*x*x*xxxxxxxx*x**x*xxxx*x\
x***x********x*xx*x*x****x\
x*xxxxxxxxxx*x**xxx*x*xxxx\
x***x******x**x*****x**x*x\
xxx*x*xxxxxxx*xxxxxxxx*x*x\
x*x*x*******x****xx****x*x\
x*x*x*xxxxx*xxxx*xx*xxxx*x\
x*x*x****xx***x**xx*x****x\
x*x*xxxxxxx*x**x*xx*x*x*xx\
x*x*********xx*x*xx*xxx*xx\
x*xxxxxxxxxxx**x*********x\
x***x***x***x*xxxxxxxxxx*x\
x*x***x***x*************Bx\
xxxxxxxxxxxxxxxxxxxxxxxxxx\0";

	unsigned char **lab;
	lab = (unsigned char**) malloc(sizeof(unsigned char*) * REN);
	if (!lab) {
		printf("\n Error de memoria.\n");
		exit(1);
	}
	
	for (i = 0; i < REN; i++) {
		lab[i] = (unsigned char*) malloc(sizeof(unsigned char) * COL);
		if (!lab[i]) {
			printf("\n Error de memoria.\n");
			exit(1);
		}
	}
	
	for (i = 0; i < REN; i++) {
		//printf("\n\r");
		for (j = 0; j < COL; j++) {
			//printf("%c",tmp[(i*COL)+j]);
			lab[i][j] = tmp[(i * COL) + j];
		}   
	}
	return lab;
}


void imprimirLab(unsigned char **lab) {
	int i,j;
	for (i = 0; i < REN; i++) {
		printf("\n\r");
		for (j = 0; j < COL; j++) {
			if (lab[i][j] == '*')
				printf("  ");
			else
				printf("%c ", lab[i][j]);
		}   
	}
}

Coordenada* crearCoordenada(int x, int y) {
	Coordenada *nueva = malloc(sizeof(Coordenada));
	if (!nueva) {
		printf("\n Error de memoria.\n");
		exit(1);
	}
	nueva->x = x;
	nueva->y = y;
	return nueva;
}

void imprimirCoordenada(void *dato) {
	Coordenada *a = dato;
	printf("[%d,%d]", a->x, a->y);
}

void liberarCoordenada(void *dato) {
	Coordenada *a = dato;
	free(a);
}

int compararCoordenada(void *a,void *b) {
	Coordenada *aa = a, *bb = b;
	if (aa->x == bb->x && aa->y == bb->y)
		return 0;
	return 1;
}

unsigned char alternativas(unsigned char **lab,Coordenada *coordenada) {		
	unsigned char caracter;
	unsigned char banderas;
	banderas = 0;

	//EVALUAR ALTERNATIVA Y REGISTRAR POSIBILIDAD DE MOVIMIENTO EN UN REGISTRO DE BITS/BANDERAS

	caracter = lab[coordenada->x - 1][coordenada->y];	// arriba
	if (caracter != 'x' && caracter != '.' && caracter != 'o' && caracter != 'A')
		banderas |= ARRIBA;
	
	caracter = lab[coordenada->x + 1][coordenada->y];	// abajo
	if (caracter != 'x' && caracter != '.' && caracter != 'o' && caracter != 'A')
		banderas |= ABAJO;
	
	caracter = lab[coordenada->x][coordenada->y + 1];	// derecha
	if (caracter != 'x' && caracter != '.' && caracter != 'o' && caracter != 'A')
		banderas |= DERECHA;
	
	caracter = lab[coordenada->x][coordenada->y - 1];	// izquierda
	if (caracter != 'x' && caracter != '.' && caracter != 'o' && caracter != 'A')
		banderas |= IZQUIERDA;

	return banderas;
}

void imprimirPosibles(unsigned char caminos) {
	if (caminos & ARRIBA)
		printf("\n ARRIBA");
	if (caminos & ABAJO)
		printf("\n ABAJO");
	if (caminos & IZQUIERDA)
		printf("\n IZQUIERDA");
	if (caminos & DERECHA)
		printf("\n DERECHA");
}

void liberarLaberinto(unsigned char **lab) {
	int i;
	for (i = 0; i < REN; i++)
		free(lab[i]);
	free(lab);
}

Pila solucion(unsigned char **lab) {
	Pila respuesta = {NULL, REN * COL, 0, &imprimirCoordenada, &liberarCoordenada};
	Pila basura = {NULL, REN * COL, 0, &imprimirCoordenada, &liberarCoordenada};
	respuesta.imprimir = basura.imprimir = &imprimirCoordenada;
	respuesta.liberar = basura.liberar = &liberarCoordenada;
	
	Coordenada *coordenada, *fin;
	coordenada = fin = NULL;
	
	for (int i = 0; i < REN; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (lab[i][j] == 'A')
				coordenada = crearCoordenada(i, j);
			if (lab[i][j] == 'B')
				fin = crearCoordenada(i, j);
		}
	}
	
	push(&respuesta, coordenada);
	
	while (!vacia(respuesta) && compararCoordenada(coordenada, fin) != 0) {
		coordenada = peek(respuesta);
		unsigned char posibles = alternativas(lab, coordenada);
		imprimirCoordenada(coordenada);
		imprimirPosibles(posibles);
		imprimirPila(respuesta);
		
		if (posibles) {
			if (posibles & ARRIBA) {
				Coordenada *nueva = crearCoordenada(coordenada->x - 1, coordenada->y);
				lab[coordenada->x][coordenada->y] = '.';
				push(&respuesta, nueva);
			}
			else if (posibles & ABAJO) {
				Coordenada *nueva = crearCoordenada(coordenada->x + 1, coordenada->y);
				lab[coordenada->x][coordenada->y] = '.';
				push(&respuesta, nueva);
			}
			else if (posibles & IZQUIERDA) {
				Coordenada *nueva = crearCoordenada(coordenada->x, coordenada->y - 1);
				lab[coordenada->x][coordenada->y] = '.';
				push(&respuesta, nueva);
			}
			else if (posibles & DERECHA) {
				Coordenada *nueva = crearCoordenada(coordenada->x, coordenada->y + 1);
				lab[coordenada->x][coordenada->y] = '.';
				push(&respuesta, nueva);
			}
		}
		else {
			lab[coordenada->x][coordenada->y] = 'o';	// marcar visitado
			push(&basura, pop(&respuesta));
		}
		printf("\n\n");
		imprimirLab(lab);
	}
	return respuesta;
}
