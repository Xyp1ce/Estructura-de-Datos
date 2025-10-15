#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Estructuras/pila/pila.h"
#include "../captura/captura.h"
#include "../Estructuras/arbol/arbol.h"

void imprimirCadena(void *a);
void imprimirCaracter(void *a);
void liberarCadena(void *a);

int main(void) {

  return 0;
}

int valido() {
  Pila pilaC = {NULL,-1,0,&imprimirCaracter,&liberarCadena};
  int esCorrecto = 1;
  char *cadena = NULL;
  char *c = NULL;

  /* Verificar si los parentesis, corchetes o llaves
        * se cierran correctamente. Ejemplo: 
        * {[()]} este caso si es correcto porque sus respectivos
        * pares se cierran. Ejemplo: 
        * {[)]} este caso no es correcto porque hay un parentesis 
        * sin abrir */ 

  inputCadenaDinamica("Ingresa una cadena>> ", &cadena, 255);

  for(int i = 0; cadena[i] != '\0' ; i++){
    // Si hay un caracter de apertura ( [ { hacemos push de ese caracter
    if(cadena[i] == '(' || cadena[i] == '{' || cadena[i] == '['){
      char *c = malloc(sizeof(char));
      *c = cadena[i];
      push(&pilaC, c);
    }

    if(cadena[i] == ')' || cadena[i] == '}' || cadena[i] == ']'){
      c = (char*)pop(&pilaC);

      if(!c){ // underflow
        esCorrecto = 0;
        break;
      }

      char a = cadena[i]; // caracter de cierre 
      char b = *c; // caracter de apertura 

      if((b == '(' && a == ')') || (b == '[' && a == ']') || (b == '{' && a == '}')){
        continue;
      } else {
        esCorrecto = 0;
        break;
      }
    }
  }

  if(esCorrecto && vacia(pilaC)){
    return esCorrecto;
  } else {
    printf("\nLa cadena no esta bien :(\n");
  }
  eliminarPila(&pilaC);
  return esCorrecto;
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

