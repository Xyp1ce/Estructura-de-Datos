//INCLUDES
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../captura/captura.h"
#include "../Estructuras/pila/pila.h"

//FUNCION MAIN
#define LONGITUD 64

void imprimirCadena(void *a);
void imprimirCaracter(void *a);
void liberarCadena(void *a);

int main(void){
  int opc;
  printf("Que quieres hacer?\n[1] Palindromo [2] Cerraduras\n>>");
  scanf("%d", &opc);
  clear_buffer();
  if(opc){
    // {INICIO NULO, SIN LIMITE, CANTIDAD 0, COMO IMPRIMIR, COMO LIBERAR}
    Pila pila = {NULL,-1,0,&imprimirCaracter,&liberarCadena};

    // Palabra a verificar
    char *cadena;
    char *c;
    inputCadenaDinamica("Ingresa una cadena palindroma>> ", &cadena, 255);
    for (int i = 0; cadena[i] != '\0'; i++){
      if (cadena[i] == ' ')
        continue;

      // Creacion de direcciones de memorias diferentes
      // habia un problema si no se hacia esto

      c = malloc(sizeof(char));
      *c = cadena[i];
      push(&pila, c);
    }

    /* Logica de palindromo
   * Hacemos pop(&pila) y comparamos con cadena[i]
   * si son iguales entonces continuamos, en cuanto falle
   * o haya un underflow, paramos, no hay diferencia 
   * entre MAYUSCULAS y minusculas*/ 

    int esPalindromo = 1; // bandera 
    for(int i = 0; i < strlen(cadena) ;i++){

      c = (char*)pop(&pila);

      // Comprobamos si es un espacio en caso de cadenas con espacio
      while(cadena[i] == ' ' && cadena[i + 1] != '\0'){
        i++;
      }

      char a = cadena[i];
      char b = *c;

      // Conversion de minusculas a MAYUSCULAS
      /* Como fucniona:
     * en ASCII las minusculas estan 32 posiciones
     * mas adelante que sus respectiva mayusculas
     * por lo tanto solo es necesario restar 32 al caracter
     * para convertirlo a MAYUSCULA, es como hacer un toUpper() */ 

      if(a >= 'a' && a <= 'z')
        a -= 32;
      if(b >= 'a' && b <= 'z')
        b -= 32;

      if(a != b){
        esPalindromo = 0;
        break;
      }
    }

    // Comprobamos 
    if(esPalindromo){
      printf("La cadena es palindroma!\n");
    } else {
      printf("La cadena no es palindroma\n");
    }
  } else {

  }
  printf("\n\n FIN DE PROGRAMA");
  return 0;
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

