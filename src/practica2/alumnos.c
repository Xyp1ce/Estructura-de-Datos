#include "alumnos.h"
int compararMatricula(void *a, void *b)
{
  Alumno *ea,*eb;
  ea = a;
  eb = b;
  if( ea->matricula < eb->matricula )
    return -1;
  else if ( ea->matricula > eb->matricula)
    return 1;
  else
    return 0;	
}

int compararSemestres(void *a, void *b)
{
  Alumno *ea,*eb;
  ea = a;
  eb = b;
  if( ea->semestres < eb->semestres )
    return 1;
  else if ( ea->semestres > eb->semestres)
    return -1;
  else
    return 0;	
}

void imprimirMatricula(void *a)
{
  Alumno *ea;
  ea = a;
  printf("Matricula: %d\n",ea->matricula);
}

void imprimirNombre(void *a)
{
  Alumno *ea;
  ea = a;
  printf("Nombre: %s\n",ea->nombre);
}


void imprimirSemestres(void *a)
{
  Alumno *ea;
  ea = a;
  printf("Semestres: %d\n",ea->semestres);
}

int compararPromedio(void *a, void *b)
{
  Alumno *ea,*eb;
  ea = a;
  eb = b;
  if( ea->promedio < eb->promedio )
    return 1;
  else if ( ea->promedio > eb->promedio)
    return -1;
  else
    return 0;	
}

void imprimirPromedio(void *a)
{
  Alumno *ea;
  ea = a;
  printf("Promedio: %.2f\n",ea->promedio);
}

void* crearAlumno(Alumno a)
{
  Alumno *nuevo = malloc(sizeof(Alumno));
  *nuevo = a;
  return nuevo;	
}

int compararNombre(void *a,void *b)
{
  Alumno *aa,*ab;
  aa = a;
  ab = b;
  int pos = strcmp( aa->nombre,ab->nombre);
  return pos;
}

void imprimirAlumno(void *a)
{
  Alumno *aa;
  aa = a;
  printf("%s_%d_%d_%.2f",aa->nombre,aa->matricula,aa->semestres,aa->promedio);

}
Alumno *llenarInfo(Lista lista){
  Alumno new;
  printf("Nombre>> ");
  fgets(new.nombre, 64, stdin);
  new.nombre[strcspn(new.nombre, "\n")] = '\0';
  // new.nombre[1] = '\0';
  printf("Matricula>> ");
  scanf("%u", &new.matricula);
  while(buscarDato(lista, &new.matricula, &compararMatricula) != NULL){
    printf("Matricula>> ");
    scanf("%u", &new.matricula);
  }
  CleanBuffer();
  printf("Semestres>> ");
  scanf("%d", &new.semestres);
  CleanBuffer();
  printf("Promedio>> ");
  scanf("%f", &new.promedio);
  CleanBuffer();
  return crearAlumno(new);
}
