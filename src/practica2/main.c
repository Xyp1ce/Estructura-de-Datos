#include <stdio.h>

#include "../Estructuras/listadoble/listadoble.h"
#include "../captura/captura.h"

#define LONGITUD 5

int main(void)
{
  ListaD lista;
  lista = inicializarListaD(lista);
  Alumno nuevo;
  nuevo.nombre = "Ramon";
  nuevo.promedio = "89";
  nuevo.semestres = 5;
  nuevo.matricula = 123;
  insertarFinal(&lista, &nuevo);
  nuevo.nombre = "Juan";
  nuevo.promedio = "76";
  nuevo.semestres = 7;
  nuevo.matricula = 321;
  insertarFinal(&lista, &nuevo);
  nuevo.nombre = "Mario";
  nuevo.promedio = "96";
  nuevo.semestres = 2;
  nuevo.matricula = 12345;
  insertarFinal(&lista, &nuevo);
  mostrarListaD(lista, 0);
	return 0;
}

