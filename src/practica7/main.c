#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Estructuras/pila/pila.h"
#include "../captura/captura.h"
#include "../Estructuras/arbol/arbol.h"

void imprimirCadena(void *a);
void imprimirCaracter(void *a);
void liberarCadena(void *a);
int valido();

int main(void) {
  while(!valido()) {
    printf("La cadena no es correcta\n");
    printf("Por favor infresa otra\n");
  }
  printf("La cadena es correcta\n");
  
  return 0;
}

int valido() {
  Pila pilaC = {NULL,-1,0,&imprimirCaracter,&liberarCadena};
  int esCorrecto = 1;
  char *cadena = NULL;
  int cerrado = 1;

  /* Verificar si los parentesis, corchetes o llaves
        * se cierran correctamente. Ejemplo: 
        * {[()]} este caso si es correcto porque sus respectivos
        * pares se cierran. Ejemplo: 
        * {[)]} este caso no es correcto porque hay un parentesis 
        * sin abrir */ 

  inputCadenaDinamica("Ingresa una cadena>> ", &cadena, 255);

  for(int i = 0; cadena[i] != '\0' ; i++){
    cerrado = 1;
    // Si hay un caracter de apertura ( [ { hacemos push de ese caracter
    if(cadena[i] == '(' || cadena[i] == '{' || cadena[i] == '['){
      char *tmp = malloc(sizeof(char));
      *tmp = cadena[i];
      push(&pilaC, tmp);
    }

    if(cadena[i] == ')' || cadena[i] == '}' || cadena[i] == ']'){
      char *popped = (char*)pop(&pilaC);

      if(!popped){ // underflow
        cerrado = 0;
        esCorrecto = 0;
        break;
      }

      char a = cadena[i]; // caracter de cierre 
      char b = *popped; // caracter de apertura 
      free(popped); // liberar inmediatamente el elemento desempilado

      if((b == '(' && a == ')') || (b == '[' && a == ']') || (b == '{' && a == '}')){
        continue;
      } else {
        cerrado = 0;
        esCorrecto = 0;
        break;
      }
    }
  }

  int estaVacia = vacia(pilaC);
  free(cadena);
  eliminarPila(&pilaC);

  // La cadena es válida solo si no se detectó error durante el recorrido,
  // la pila quedó vacía (no hay aperturas sin cerrar) y el último cierre fue correcto.
  return (esCorrecto && estaVacia && cerrado);
}

void imprimirCadena(void *a){
  char *aa = a;
  printf("%s",aa);
}

// Se agrego funcion para imprimir un solo caracter
// Se imprimian caracteres vacias con la de cadena
void imprimirCaracter(void *a){
  char *aa = a;
  printf("%c",*aa);
}

void liberarCadena(void *a){
  char *aa = a;
  free(aa);
}

