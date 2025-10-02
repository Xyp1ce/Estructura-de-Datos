#include "arbol.h"

void insertarArbolOrdenado(NodoA *raiz,void *dato,int (*comparar)(void*,void*))
{
	if(comparar(dato,raiz->dato)<=0)
	{
		//IZQUIERDA
		if(raiz->izq)
			insertarArbolOrdenado(raiz->izq,dato,comparar);
		else
			raiz->izq = crearNodoA(dato);
	}
	else
	{
		//DERECHA
		if(raiz->dch)
			insertarArbolOrdenado(raiz->dch,dato,comparar);
		else
			raiz->dch = crearNodoA(dato);
	}
}

void insertarArbol(Arbol *arbol,void *dato)
{
	if(!arbol->raiz)
		arbol->raiz = crearNodoA(dato);
	else 
		insertarArbolOrdenado(arbol->raiz,dato,arbol->comparar);
	arbol->cantidad++;
}

NodoA* buscarEnArbol(NodoA *raiz, int dato, NodoA *encontrado) {
  if(encontrado->dato == NULL) {
    if(!raiz) 
      return NULL;
    printf("\nComparando con %d", (*(int*)(raiz->dato)));
    if(*((int*)(raiz->dato)) == dato) {
      encontrado->dato = raiz->dato;
    }
    if(dato > (*((int*)(raiz->dato))))
      buscarEnArbol(raiz->dch, dato, encontrado);
    else
      buscarEnArbol(raiz->izq, dato, encontrado);
    return NULL;
  }
  return encontrado;
}

void imprimir_arbol(NodoA* nodo, int nivel,void (*imprimir)(void*))
{
    int i;
    if (nodo != NULL)
        {
        printf(" ");
		imprimir(nodo->dato);
        if(nodo->dch)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____R ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->dch, nivel + 1,imprimir);
        }
        if(nodo->izq)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                printf(" |      ");
                //printf(" |      ");
            }
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____L ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->izq, nivel + 1,imprimir);
        }
    }
}

void imprimirArbol(Arbol arbol)
{
	imprimir_arbol(arbol.raiz,0,arbol.imprimir);
}

void preorden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	printf(" ");
	imprimir(raiz->dato);
	preorden(raiz->izq,imprimir);
	preorden(raiz->dch,imprimir);
}

void orden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	orden(raiz->izq,imprimir);
	printf(" ");
	imprimir(raiz->dato);
	orden(raiz->dch,imprimir);	
}

void inverso(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	inverso(raiz->dch,imprimir);	
	printf(" ");
	imprimir(raiz->dato);
	inverso(raiz->izq,imprimir);
}

void postorden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	postorden(raiz->izq,imprimir);
	postorden(raiz->dch,imprimir);
	printf(" ");
	imprimir(raiz->dato);	
}

void imprimirOrden(Arbol arbol,int opcion)
{
	switch(opcion)
	{
		case PREORDEN: 
			preorden(arbol.raiz,arbol.imprimir);
			break;
		case ORDEN: 
			orden(arbol.raiz,arbol.imprimir);
			break;
		case INVERSO: 
			inverso(arbol.raiz,arbol.imprimir);
			break;
		case POSTORDEN: 
			postorden(arbol.raiz,arbol.imprimir);
			break;
	}
}

void calcularAltura(NodoA *raiz, int *altura) {
  int izquierdo, derecho;
  izquierdo = derecho = *altura;
  if(raiz->izq && izquierdo++)
    calcularAltura(raiz->izq,&izquierdo);
  if(raiz->dch && derecho++)
    calcularAltura(raiz->dch, &derecho);
  *altura = (izquierdo>derecho) ? izquierdo:derecho;
}

int altura(Arbol arbol) {
  if(!arbol.raiz)
    return 0;
  int altura = 1;
  calcularAltura(arbol.raiz, &altura);
  return altura;
}

void extraccionDatos(NodoA *raiz, void **datos, int *indice) {
  if(!raiz) 
    return;
  extraccionDatos(raiz->izq, datos, indice);
  datos[*indice] = raiz->dato;
  (*indice)++;
  extraccionDatos(raiz->dch, datos, indice);
}

void equilibrar(Arbol *arbol) {
  void (*liberar)(void*) = arbol->liberar;
  arbol->liberar = NULL;
  int indice = 0;
  int cantidad = arbol->cantidad;
  int *indices = calloc(cantidad, sizeof(int));
  void **datos = calloc(cantidad, sizeof(void*));
  //void **ordenados = calloc(cantidad, sizeof(void*));

  extraccionDatos(arbol->raiz, datos, &indice);
  
  eliminarArbol(arbol->raiz);

  arbol->liberar = liberar;
  // ARBOL VACIO 
  // DATOS EN EL ARREGLO 
  // HACER INSERCIONES EN EL ARBOL PARA QUE QUEDE EQUILIBRADO 
  // SACAR INDICES Y COLOCARLOS EN EL ARREGLO 
  // DE INDICES
 
  //ordenarRaices(datos, ordenados,  datos+(cantidad-1), &indice);

  for(int i = 0; i < cantidad; i++) {
    insertarArbol(arbol, datos[indices[i]]);
  }
  free(datos);
  free(indices);
}

void eliminarArbol(NodoA *raiz) {
	if(!raiz)
		return;
  if(raiz->izq)
    eliminarArbol(raiz->izq);
  if(raiz->dch)
	  eliminarArbol(raiz->dch);	
  free(raiz->dato);
}

// void ordenarRaices(void **datos, void **ordenados, int final, int *indice) {
//   int cant = 0;
//   for(int i = 0; datos[i]!=null ;i++)
//     cant++;
//   cant = cant/2;
//   if() {
//     ordenados[(*indice)++] = datos[cant];
//     ordenarRaices(datos, ordenados, datos+(cant-1), indice, cant)
//   }
// }
