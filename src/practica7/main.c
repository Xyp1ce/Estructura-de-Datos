#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Estructuras/pila/pila.h"
#include "../captura/captura.h"
#include "../Estructuras/arbol/arbol.h"

void imprimirCadena(void *a);
void imprimirCaracter(void *a);
void liberarCadena(void *a);
int valido(char* cadena);
int precedencia(char c);
void postfix(char* infix, Pila *postfixPila);
int esApertura(char c);
int esCierre(char c);
int haceMatch(char apertura, char cierre);
int esRightAssoc(char c);

int main(void) {
  char *cadena = NULL;
  Pila postfixPila = {NULL,-1,0,&imprimirCaracter,&liberarCadena};
  inputCadenaDinamica("Ingresa una cadena>> ", &cadena, 255);
  while(!valido(cadena)) {
    printf("La cadena no es correcta\n");
  inputCadenaDinamica("Ingresa una cadena>> ", &cadena, 255);
  }
  printf("La cadena es correcta\n");
  postfix(cadena, &postfixPila);
  // imprime la cadena en postfix
  imprimirPila(postfixPila);
  printf("\n");
  eliminarPila(&postfixPila);
  free(cadena);

  return 0;
}

int valido(char* cadena) {
  Pila pilaC = {NULL,-1,0,&imprimirCaracter,&liberarCadena};
  int esCorrecto = 1;
  int cerrado = 1;

  /* Verificar si los parentesis, corchetes o llaves
   * se cierran correctamente. Ejemplo:
   * {[()]} este caso si es correcto porque sus respectivos
   * pares se cierran. Ejemplo:
   * {[)]} este caso no es correcto porque hay un parentesis
   * sin abrir */

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

void postfix(char* infix, Pila *postfixPila) {
  Pila pila = {NULL,-1,0,&imprimirCaracter,&liberarCadena};
  for(int i = 0; infix[i] != '\0'; i++) {
    char c = infix[i];

    // Si el caracter es un operando, añadirlo al output
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
      char *tmp = malloc(sizeof(char));
      *tmp = c;
      push(postfixPila, tmp);
    }
    // Si el caracter es '(', hacer push a la pila
    else if(esApertura(c)) {
      char *tmp = malloc(sizeof(char));
      *tmp = c;
      push(&pila, tmp);
    }
    else if(esCierre(c)) {
      // Hacer pop de la pila hasta encontrar el paréntesis de apertura correspondiente
      char *top = (char*)pop(&pila);
      while(top != NULL && !haceMatch(*top, c)) {
        // si top es una apertura distinta, entonces hubo mismatch pero valido() ya lo verificó
        // mover operadores intermedios al output
        push(postfixPila, top); // transferir ownership a postfixPila
        top = (char*)pop(&pila);
      }
      // top puede ser NULL (no matching) o la apertura correspondiente
      if(top) {
        // descartamos la apertura (no debe ir a la salida)
        free(top);
      }
    }
    // Si el caracter es un operador
    else {
      while(!vacia(pila)) {
        char *topPtr = (char*)pila.cima->dato;
        if(!topPtr) break;
        char top = *topPtr;
        int top_prec = precedencia(top); // top
        int cur_prec = precedencia(c); // current
        // pop mientras top tenga mayor precedencia o igual precedencia y current sea left-assoc
        if(top == '(' || top == '[' || top == '{') break;
        if( (top_prec < cur_prec) || (top_prec == cur_prec && !esRightAssoc(c)) ) {
          // pop desde pila y push a postfixPila
          char *moved = (char*)pop(&pila);
          if(moved) push(postfixPila, moved); // ownership transferred
          else break;
        } else {
          break;
        }
      }
      char *tmp = malloc(sizeof(char));
      *tmp = c;
      push(&pila, tmp);
    }
  }

  // Hacer pop de todos los operadores restantes en la pila
  while(!vacia(pila)) {
    char *top = (char*)pop(&pila);
    if(!top) continue;
    // no incluir paréntesis de apertura en la salida
    if(*top == '(' || *top == '[' || *top == '{') {
      free(top);
      continue;
    }
    push(postfixPila, top); 
  }

  eliminarPila(&pila);
}

int esApertura(char c){
  return c == '(' || c == '[' || c == '{';
}

int esCierre(char c){
  return c == ')' || c == ']' || c == '}';
}

int haceMatch(char apertura, char cierre){
  return (apertura == '(' && cierre == ')') ||
         (apertura == '[' && cierre == ']') ||
         (apertura == '{' && cierre == '}');
}

int esRightAssoc(char c){
  return c == '^';
}

int precedencia(char c) {
  switch (c)
  {
  case '+':
  case '-':
    return 3;
  case '*':
  case '/':
    return 2;
  case '^':
    return 1;
  default:
    break;
  }
  return 3;
}