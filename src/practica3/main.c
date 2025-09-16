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
  // {INICIO NULO, SIN LIMITE, CANTIDAD 0, COMO IMPRIMIR, COMO LIBERAR}
  Pila pilaP = {NULL,-1,0,&imprimirCaracter,&liberarCadena};
  Pila pilaC = {NULL,-1,0,&imprimirCaracter,&liberarCadena};
  char *cadena;
  char *c;
  // banderas
  int esCorrecto = 1;
  int esPalindromo = 1;  

  do{
    printf("\n---MENU---\n[1] Palindromo [2] Cerraduras [3] Salir\n");
    inputEntero("Opcion>> ", &opc);
    switch(opc){
      case 1:
        esPalindromo = 1;
        cadena = NULL;
        c = NULL;
        pilaP.cantidad = 0;
        pilaP.cima = NULL;
        inputCadenaDinamica("Ingresa una cadena palindroma>> ", &cadena, 255);
        for (int i = 0; cadena[i] != '\0'; i++){
          if (cadena[i] == ' ')
            continue;
          // Creacion de direcciones de memorias diferentes
          // habia un problema si no se hacia esto
          c = malloc(sizeof(char));
          *c = cadena[i];
          push(&pilaP, c);
        }

        /* Logica de palindromo
         * Hacemos pop(&pila) y comparamos con cadena[i]
         * si son iguales entonces continuamos, en cuanto falle
         * o haya un underflow, paramos, no hay diferencia 
         * entre MAYUSCULAS y minusculas 
         */ 

        for(int i = 0; !vacia(pilaP) ;i++){

          c = (char*)pop(&pilaP);

          // Comprobamos si es un espacio en caso de cadenas con espacio
          while(cadena[i] == ' ' && cadena[i + 1] != '\0'){
            i++;
          }

          char a = cadena[i];
          char b = *c;

          /* Conversion de minusculas a MAYUSCULAS
          * Como fucniona:
          * en ASCII las minusculas estan 32 posiciones
          * mas adelante que sus respectiva mayusculas
          * por lo tanto solo es necesario restar 32 al caracter
          * para convertirlo a MAYUSCULA, es como hacer un toUpper() 
          */

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
        break;

      case 2:
        esCorrecto = 1;
        cadena = NULL;
        c = NULL;

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
          printf("\nLa cadena es corecta!!\n");
        } else {
          printf("\nLa cadena no esta bien :(\n");
        }
        eliminarPila(&pilaC);
        break;
      case 3:
        printf("Finalizando programa...\n");
        eliminarPila(&pilaP);
        eliminarPila(&pilaC);
        return 1;
      default:
        printf("Opcion invalida...");
        break;

    }
  }while(opc != 3);

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

