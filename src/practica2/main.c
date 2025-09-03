#include "../Estructuras/listadoble/listadoble.h"
#include "../captura/captura.h"
#include "alumnos.h"

int main(void){
  ListaD lista;
  lista = inicializarListaD();
  lista.imprimir = &imprimirAlumno;
  Alumno nuevo;
  inputCadena("Ingresa el nombre>> ", nuevo.nombre,255);
  inputFloat("Ingresa el promedio>> ", &nuevo.promedio);
  inputEntero("Ingresa los semestres>> ", &nuevo.semestres);
  printf("Ingresa la matricula>> ");
  scanf("%u", &nuevo.matricula);
  clear_buffer();
  insertarFinal(&lista, &nuevo);
  printf("%d\n", lista.cant);
  mostrarListaD(lista, 0);
	return 0;
}

