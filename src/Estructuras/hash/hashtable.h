#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> //ELIPSIS
#include "../nodos/nodo.h"
#include "../cola/cola.h"

typedef struct
{
	void **tabla;
	int tam;
	int cant;
	int (*folding)(void*);
	void (*imprimir)(void*);
	int (*comparar)(void*,void*);
}HashTable;

int hash(int clave,int tam);
int rehash(int indice,int k,int tam);
HashTable inicializarHashTable(int tam,void (*imprimir)(void*),int (*comparar)(void*,void*), int (*folding)(void*));
int insertarClave(HashTable *hashtable,void *dato);
Cola buscarClave(HashTable *hashtable,void *dato);
void imprimirHashTabla(HashTable *hashtable);
int folding_isbn(void *dato);
int folding_titulo(void *dato);
int folding_autor(void *dato);
int folding_fecha(void *dato);
int folding_cadena(char *cadena);
Cola buscarRangoTitulo(HashTable *hashtable, char lower, char upper);
Cola buscarRangoAutor(HashTable *hashtable, char lower, char upper);
Cola buscarRangoFecha(HashTable *hashtable, int min, int max);
int eliminarDatoHashTable(HashTable *hashtable, const char *isbn, void (*liberar)(void*));
int insertarSinResize(HashTable *hashtable, void *dato);
void remapHashTable(HashTable *hashtable, int new_tam);
#endif