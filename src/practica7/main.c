#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Estructuras/pila/pila.h"
#include "../captura/captura.h"
#include "../Estructuras/arbol/arbol.h"
// Implementaciones locales de validacion y conversión (antes en Estructuras/expr)

void liberarCadena(void *a){
  char *aa = a;
  free(aa);
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

int validarParentesis(char *cadena)
{
  Pila pila = {NULL, -1, 0, NULL, &liberarCadena};
  int bandera = 1;

  for (int i = 0; cadena[i] != '\0'; i++)
  {
    if (cadena[i] == '(' || cadena[i] == '{' || cadena[i] == '[')
    {
      char *tmp = malloc(sizeof(char));
      *tmp = cadena[i];
      push(&pila, tmp);
    }

    else if (cadena[i] == ')' || cadena[i] == '}' || cadena[i] == ']')
    {
      if (pila.cantidad == 0)
      {
        bandera = 0;
        break;
      }

      char *parentesis = pop(&pila);

      if ((cadena[i] == ')' && *parentesis != '(') ||
        (cadena[i] == '}' && *parentesis != '{') ||
        (cadena[i] == ']' && *parentesis != '['))
      {
        bandera = 0;
        if (parentesis) free(parentesis);
        break;
      }
      if (parentesis) free(parentesis);
    }
  }
  int empty = vacia(pila);
  eliminarPila(&pila);
  if (bandera == 1 && empty)
  {
    printf("\n Expresion valida, comenzamos con el proceso.\n");
    return 1;
  }
  else
  {
    printf("\n Expresion Invalida.\n");
    return 0;
  }
}

char *inFixtoPostfix(char *expresion)
{
  if (!validarParentesis(expresion))
    return NULL;

  Pila pila = {NULL, -1, 0, NULL, &liberarCadena};
  int len = strlen(expresion);
  char *postfix = calloc(len + 1, sizeof(char));
  int j = 0;

  for (int i = 0; expresion[i] != '\0'; i++)
  {
    char c = expresion[i];

    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
    {
      postfix[j++] = c;
    }
    else if (esApertura(c))
    {
      char *parentesis = malloc(sizeof(char));
      *parentesis = c;
      push(&pila, parentesis);
    }
    else if (esCierre(c))
    {
      char *op = pop(&pila);
      while (op != NULL && !haceMatch(*op, c))
      {
        postfix[j++] = *op;
        free(op);
        op = pop(&pila);
      }
      if (op)
        free(op);
    }
    else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
    {
      while (!vacia(pila))
      {
        char *tope = (char *)pila.cima->dato;
        if (!tope)
          break;
        char top = *tope;
        if (top == '(' || top == '[' || top == '{')
          break;
        int top_prec = (top == '+'||top=='-')?1: (top=='*'||top=='/')?2:3;
        int cur_prec = (c == '+'||c=='-')?1: (c=='*'||c=='/')?2:3;
        if (top_prec > cur_prec || (top_prec == cur_prec && !esRightAssoc(c)))
        {
          char *op = pop(&pila);
          postfix[j++] = *op;
          free(op);
        }
        else
          break;
      }

      char *oper = malloc(sizeof(char));
      *oper = c;
      push(&pila, oper);
    }
  }

  while (!vacia(pila))
  {
    char *op = pop(&pila);
    if (!op)
      continue;
    if (*op == '(' || *op == '[' || *op == '{')
    {
      free(op);
      continue;
    }
    postfix[j++] = *op;
    free(op);
  }

  postfix[j] = '\0';
  return postfix;
}

void imprimirCadena(void *a);
void imprimirCaracter(void *a);
void liberarCadena(void *a);
int valido(char* cadena);
int precedencia(char c);
// usamos inFixtoPostfix de src/Estructuras/expr
int esApertura(char c);
int esCierre(char c);
int haceMatch(char apertura, char cierre);
int esRightAssoc(char c);

int main(void) {
  char *cadena = NULL;
  inputCadenaDinamica("Ingresa una cadena>> ", &cadena, 255);
  while(!valido(cadena)) {
    printf("La cadena no es correcta\n");
  inputCadenaDinamica("Ingresa una cadena>> ", &cadena, 255);
  }
  printf("La cadena es correcta\n");
  char *post = inFixtoPostfix(cadena);
  if(post){
    printf("\n Expresion Postfix: %s\n", post);
    free(post);
  }
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

// usamos las implementaciones compartidas en src/Estructuras/expr

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