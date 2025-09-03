#ifndef ALUMNOS_H
#define ALUMNOS_H

#include "../Estructuras/listadoble/listadoble.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../captura/captura.h"

typedef struct {
  unsigned int matricula;
  char nombre[64];
  int semestres;
  float promedio;
}Alumno;

Alumno *llenarInfo(ListaD l);
void* crearAlumno(Alumno a);

int compararSemestres(void *a, void *b);
int compararMatricula(void *a, void *b);
int compararPromedio(void *a, void *b);
int compararNombre(void *a,void *b);

void imprimirMatricula(void *a);
void imprimirNombre(void *a);
void imprimirPromedio(void *a);
void imprimirSemestres(void *a);

void imprimirAlumno(void *a);

#endif
