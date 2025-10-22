#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "../captura/captura.h"
#include "../Estructuras/pila/pila.h"
#include "../Estructuras/cola/cola.h"
#include "../Estructuras/arbol/arbol.h"
#include "../Estructuras/nodos/nodoarbol.h"

typedef struct
{
	char caracter;
	float *valor;
}Dato;

void imprimirCadena(void *a);
void liberarCadena(void *a);
int verificarParentesis(char *);
char* InfixToPostfix(char *cadena);

Dato* crearDato(char caracter);
void imprimirDato(void *dato);
int compararCaracteres(void *a, void *b);
Cola* expresionACola(char *expresion);
int esOperador(char caracter);
void capturarValores(Arbol *arbol);
void capturarValoresR(NodoA *raiz);
void resolverArbol(NodoA *raiz);
void reiniciarValor(NodoA *raiz);
Arbol crearArbolExpresion(Cola *cola);

int main(void)
{
	int opc,n;
	char *cadena,*aux;
	Cola *cola = NULL;
	Arbol arbol;
	arbol.raiz = NULL;
	arbol.cantidad = 0;
	arbol.imprimir = &imprimirDato;
	arbol.comparar = &compararCaracteres;
	arbol.liberar = &free;
	
  do {
		printf("\n[1]Infix a Postfix");
		printf("\n[2]Imprimir arbol");
		printf("\n[3]Evaluar expresion");
		printf("\n[4]Finalizar programa");
		printf("\nCapturar opcion:");
		scanf("%d",&opc);
		clear_buffer();
		
		switch(opc)
		{
			case 1:
				cadena = NULL;
				inputCadenaDinamica("Captura una expresion:",&cadena,64);
				if(cadena == NULL)
					break;
				n = verificarParentesis(cadena);
				if(n != 1)
					break;
				else {
					aux = InfixToPostfix(cadena);
					printf("%s\n",aux);
				}
				//Crear arbol
				cola = expresionACola(aux);
        arbol = crearArbolExpresion(cola);
        imprimirArbol(arbol);
				break;
			case 2:
				if(cadena == NULL)
					break;
        imprimirArbol(arbol);
				break;
			case 3:
				if(cadena == NULL)
					break;
				reiniciarValor(arbol.raiz);
				capturarValores(&arbol);
				resolverArbol(arbol.raiz);
				imprimirArbol(arbol);
				
				Dato *dato = arbol.raiz->dato;
				printf("\nResultado: %f",*(dato->valor)); //valor es ptr
				break;
			case 4:
				break;
		}
	} while(opc != 4);
	printf("\n\n FIN DE PROGRAMA");
	return 0;
}
void imprimirCadena(void *a)
{
	char *aa = a;
	printf("%s",aa);
	
}
void liberarCadena(void *a)
{
	char *aa = a;
	free(aa);
}

int verificarParentesis(char *cadena) {
	Pila pila = {NULL,-1,0,&imprimirCadena,&liberarCadena};
	int invalido = 0;
	for(int i = 0; cadena[i] != '\0'; i++)
	{
		if(cadena[i]=='(')
		{
			push(&pila,&cadena[i]);
		}
		if(cadena[i]==')')
		{
			if(pila.cantidad==0)
			{
				invalido = 1;
				break;
			}
			char *dato = (char *)pop(&pila);

			if(*dato != '(')
			{
				invalido = 1;
				break;
			}
		}
	}
	if(pila.cantidad!=0 || invalido!=0) {
		printf("\nInvalido");
		eliminarPila(&pila);
		return 0;
	}
	
	return 1;
}
char* InfixToPostfix(char *cadena) {
	Pila pila = {NULL,-1,0,&imprimirCadena,&liberarCadena};
	int i,j,old,new;
	old = 0;
	new = 0;
	j = 0;
	for(i = 0; cadena[i] != '\0'; i++) {
		if(cadena[i] == '(' || cadena[i] == ')')
			old++;
	}
	new = (strlen(cadena)+1) - old;
	char *newcadena = calloc(new,sizeof(char));
	char *dato;
	for(i = 0; cadena[i] != '\0'; i++) {
		dato = NULL;
		if(cadena[i] == '(')
			push(&pila,&cadena[i]);
		if(cadena[i] == ')') {
			if(pila.cantidad != 0)
				dato = (char *)peek(pila);
			while(dato != NULL && *dato != '(') {
				dato = (char *)pop(&pila);
				newcadena[j++] = *dato;
				dato = (char *)peek(pila);
			}
			if(*dato == '(')
				dato = (char *)pop(&pila);
			dato = NULL;
		}
		if(cadena[i] == '^') {
			if(pila.cantidad != 0)
				dato = (char *)peek(pila);
			if(dato != NULL && *dato == '^') {
				dato = (char *)pop(&pila);
				newcadena[j++] = *dato;
			}
			push(&pila,&cadena[i]);
		}
		if(cadena[i] == '*' || cadena[i] == '/') {
			if(pila.cantidad != 0)
				dato = (char *)peek(pila);
			while(dato != NULL && *dato != '(' && *dato != '+' && *dato != '-') {
				if(*dato == '^' || *dato == '*' || *dato == '/') {
					dato = (char *)pop(&pila);
					newcadena[j++] = *dato;
				}
				if(pila.cantidad != 0)
					dato = (char *)peek(pila);
				else
					dato = NULL;
			}
			push(&pila,&cadena[i]);
		}
		if(cadena[i] == '+' || cadena[i] == '-') {
			if(pila.cantidad != 0)
				dato = (char *)peek(pila);
			while(dato != NULL && *dato != '(' && pila.cantidad != 0) {
				if(*dato == '^' || *dato == '*' || *dato == '/' || *dato == '+' || *dato == '-') {
					dato = (char *)pop(&pila);
					newcadena[j++] = *dato;
				}
				if(pila.cantidad != 0)
					dato = (char *)peek(pila); 
				else
					dato = NULL;
			}
			push(&pila,&cadena[i]);
		}
		if(cadena[i] >= 'A' && cadena[i] <= 'Z')
			newcadena[j++] = cadena[i];
		if(cadena[i] >= 'a' && cadena[i] <= 'z')
			newcadena[j++] = cadena[i];	
	}
	while(pila.cantidad != 0)
	{
		dato = (char *)pop(&pila);
		newcadena[j++] = *dato;
	}	
	return newcadena;
}

Dato* crearDato(char caracter) {
	Dato *nuevo = calloc(1,sizeof(Dato));
	nuevo -> caracter = caracter;
	return nuevo;
}

void imprimirDato(void *dato) {
	NodoA *nodo = dato;
	Dato *info = nodo->dato;
	if(info->valor && !(esOperador(info->caracter)))
		printf(" %c = %f",info->caracter,*info->valor);
	else 
		printf(" %c ",info->caracter);
}

int compararCaracteres(void *a, void *b) {
	char *datoa = a;
	//Dato *datoa = nodoa->dato;
	NodoA *nodob = b;
	Dato *datob = nodob->dato;
	if(*datoa == datob->caracter)
		return 0;
	return 1;
}

Cola* expresionACola(char *expresion) {
	Cola *cola = calloc(1,sizeof(Cola));
	*cola = inicializarCola();
	cola->imprimir = &imprimirDato;
	for(int i = 0; expresion[i]!='\0'; i++) {
		NodoA *nodo = buscarC(*cola,&expresion[i],&compararCaracteres);
    // NodoA *nodo = crearNodoA(buscarC(*cola, &expresion[i], &compararCaracteres));
		Dato *dato;
		if(nodo) {
      dato = nodo->dato;
    } else {
			dato = crearDato(expresion[i]);
    }
		NodoA *nodoa = crearNodoA(dato);
		enqueue(cola,nodoa);
	}
	return cola;
}

int esOperador(char caracter) {
	int i;
	char *operadores = "+-*/^";
	for(i = 0; operadores[i]!='\0' ;i++)
	{
		if(caracter == operadores[i])
			return 1;
	}
	return 0;
}

void capturarValores(Arbol *arbol) {
	if(!arbol)
		return;
	capturarValoresR(arbol->raiz);
}

void capturarValoresR(NodoA *raiz) {
	if(!raiz)
		return;
	capturarValoresR(raiz->izq);
	capturarValoresR(raiz->dch);
	Dato *dato = raiz->dato;
	if(dato->valor == NULL && !esOperador(dato->caracter)) {
		dato->valor = calloc(1,sizeof(float));
		printf("\n Captura valor de %c: ",dato->caracter);
		inputFloat("",dato->valor);
	}
}
void resolverArbol(NodoA *raiz) {
  if (!raiz)
    return;

  resolverArbol(raiz->izq);
  resolverArbol(raiz->dch);

  Dato *dato = raiz->dato;

  if (esOperador(dato->caracter)) {
    float *valorIzq, *valorDch;
    float resultado = 0;

    Dato *datoIzq = (Dato*) (raiz->izq ? raiz->izq->dato : NULL);
    Dato *datoDch = (Dato*) (raiz->dch ? raiz->dch->dato : NULL);

    valorIzq = datoIzq ? datoIzq->valor : NULL;
    valorDch = datoDch ? datoDch->valor : NULL;

    if (valorIzq && valorDch) {
      switch (dato->caracter) {
        case '+':
          resultado = *valorIzq + *valorDch;
          break;
        case '-':
          resultado = *valorIzq - *valorDch;
          break;
        case '*':
          resultado = *valorIzq * *valorDch;
          break;
        case '/':
          if (*valorDch != 0)
            resultado = *valorIzq / *valorDch;
          else
            printf("\n Error: Division por cero.\n");
          break;
        case '^':
          for(int i = 0; i < *valorDch; i++) {
            resultado = resultado * *valorIzq;
          }
          // resultado = pow(*valorIzq, *valorDch);
          break;
      }

      if (dato->valor)
        free(dato->valor);

      dato->valor = malloc(sizeof(float));
      *(dato->valor) = resultado;
    } 
    else {
      printf("\n Error: Faltan operandos para el operador %c.\n", dato->caracter);
    }
  }
}

void reiniciarValor(NodoA *raiz) {
	if(!raiz)
		return;
	reiniciarValor(raiz->izq);
	reiniciarValor(raiz->dch);
	
	Dato *dato = raiz->dato;
	if(dato->valor != NULL) {
		free(dato->valor);
		dato->valor = NULL;
	}
}

Arbol crearArbolExpresion(Cola *cola){
	Arbol arbol = {NULL, 0, &imprimirDato, &compararCaracteres, NULL};
	Pila pila = {NULL, -1, 0, &imprimirDato, NULL};
	int total = cola->cantidad;

	for(int i = 0; i < total; i++){
		NodoA *nodo = peekC(*cola);
		Dato *dato = nodo->dato;

		if((dato->caracter >= 'a' && dato->caracter <= 'z') || (dato->caracter >= 'A' && dato->caracter <= 'Z'))			
			push(&pila, dequeue(cola));
		else if(esOperador(dato->caracter)){
			NodoA *nodoOperador = dequeue(cola);
			nodoOperador->dch = pop(&pila);
			nodoOperador->izq = pop(&pila);
			push(&pila, nodoOperador);
		}
	}
	arbol.raiz = pop(&pila);
	arbol.cantidad = total;
	return arbol;
}
