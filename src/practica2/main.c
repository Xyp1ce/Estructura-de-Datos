#include "../Estructuras/listadoble/listadoble.h"
#include "../captura/captura.h"
#include "alumnos.h"

int main(void){
  ListaD lista;
  Alumno *buscarAlumno;
  Alumno *alumno;
  int opc;
  lista = inicializarListaD();
  lista.imprimir = &imprimirAlumno;
  lista.comparar = &compararMatricula;

  while(1){
    printf("\n--MENU--\n");
    printf("[1] Registrar Alumno [4] Buscar Alumno\n");
    printf("[2] Reordenar        [5] Borar Alumno\n");
    printf("[3] Mostrar Alumnos  [6] Terminar Programa\n");
    inputEntero("Ingresa una opcion>> ", &opc);
    switch(opc){
      case 1: // Registrar Alumno
        insertarOrdenado(&lista, llenarInfo(lista));
        // Reordenamos con cada nuevo elemento para manterer un orden 
        // por matriculas
        reordenar(&lista, &compararMatricula); 
        break;
      case 2: // Reordenar
        do{
          printf("Modos de ordenar\n");
          printf("[1] Nombre    [3] Matricula\n[2] Semestres [4] Promedio\n");
          inputEntero("Ingrese una opcion>> ", &opc);
          switch(opc){
            case 1: // Nombre
              reordenar(&lista, &compararNombre);
              break;
            case 2: // Semestres
              reordenar(&lista, &compararSemestres);
              break;
            case 3: // Matricula
              reordenar(&lista, &compararMatricula);
              break;
            case 4: // Proemdio
              reordenar(&lista, &compararPromedio);
              break;
            default:
              printf("Opcion invalida...\n");
              break;
          }
        }while(opc > 4 && opc < 1);
        break;
      case 3: // Mostrar Alumnos
        do{
          inputEntero("Como quiere mostrar los datos?\n[1] Ascendente [0] Descendente\n>> ", &opc);
        }while(opc != 1 && opc != 0);
        mostrarListaD(lista, opc);
        break;
      case 4: // Bucsar Alumno
        printf("Que dato quiere buscar?\n");
        printf("[1] Nombre   [3] Matricula\n");
        printf("[2] Promedio [4] Semestres\n");
        inputEntero("Ingrese una opcion>> ", &opc);
        clear_buffer();
        switch(opc){
          case 1:
            inputCadena("Ingresa el nombre>> ", buscarAlumno->nombre, 255);
            remover_salto(buscarAlumno->nombre);
            alumno = buscarDato(lista, &buscarAlumno, &compararNombre);
            if(alumno != NULL){
              printf("Se ha encontrado un alumno>>\n");
              imprimirNombre(alumno);
              imprimirMatricula(alumno);
              imprimirSemestres(alumno);
              imprimirPromedio(alumno);
            } else {
              printf("No se encontro ninguna alumno\n");
            }
            break;
          case 2:
            inputFloat("Ingrese el promedio del alumno>> ", &buscarAlumno->promedio);
            clear_buffer();
            alumno = buscarDato(lista, &buscarAlumno, &compararPromedio);
            if(alumno != NULL){
              printf("Se ha encontrado un alumno>>\n");
              imprimirNombre(alumno);
              imprimirMatricula(alumno);
              imprimirSemestres(alumno);
              imprimirPromedio(alumno);
            } else {
              printf("No se encontro ninguna alumno\n");
            }
            break;
          case 3:
            printf("Ingrese la matricula del alumno>> ");
            scanf("%u", &buscarAlumno->matricula);
            clear_buffer();
            alumno = buscarDato(lista, &buscarAlumno, &compararMatricula);
            if(alumno != NULL){
              printf("Se ha encontrado un alumno>>\n");
              imprimirNombre(alumno);
              imprimirMatricula(alumno);
              imprimirSemestres(alumno);
              imprimirPromedio(alumno);
            } else {
              printf("No se encontro ninguna alumno\n");
            }
            break;
          case 4:
            inputEntero("Ingrese los semestres del alumno>> ", &buscarAlumno->semestres);
            clear_buffer();
            alumno = buscarDato(lista, &buscarAlumno, &compararSemestres);
            if(alumno != NULL){
              printf("Se ha encontrado un alumno>>\n");
              imprimirNombre(alumno);
              imprimirMatricula(alumno);
              imprimirSemestres(alumno);
              imprimirPromedio(alumno);
            } else {
              printf("No se encontro ninguna alumno\n");
            }
            break;
          case 5: // Borrar Alumno
            printf("Ingrese la matricula del alumno a eliminar>> ");
            scanf("%u", &buscarAlumno->matricula);
            clear_buffer();
            alumno = buscarDato(lista, &buscarAlumno, &compararMatricula);
            if(alumno != NULL){
              borrarDato(&lista, &buscarAlumno, &compararMatricula);
              printf("Alumno eliminador exitosamente\n");
            } else {
              printf("No se encontro algun alumno con la matricula %d\n", buscarAlumno->matricula);
            }
            break;
          case 6: // Terminar programa
            printf("Finalizando programa...\n");
            return 0;
          default:
            printf("Opcion invalida...\n");
            break;
        }
    }
  }
}
