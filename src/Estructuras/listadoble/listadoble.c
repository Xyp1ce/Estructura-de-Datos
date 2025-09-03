#include "listadoble.h"
#include <stdio.h>

ListaD inicializarListaD(void)
{
	return (ListaD) {NULL,NULL,0,NULL,NULL};
}

void mostrarListaD(ListaD lista, int opc)
{
	NodoD *p;	
	printf("\n Lista[%d]: ",lista.cant);
  if(opc == 0){
    // Imprimir en fin a inicio
    for(p = lista.fin; p!=NULL; p = p->ant){
      printf(" ");
      lista.imprimir(p->dato);
      printf("->");
    }
  } else {
    // Imprimir de inicio a fin
    for( p = lista.inicio ;  p!=NULL ; p = p->sig  )
    {
      printf(" ");
      lista.imprimir(p->dato);
      printf("->");
    }
  }
	printf("NULL");
}

void borrarLista(ListaD *lista){
  NodoD *actual, *anterior = NULL;
  for(actual = lista->inicio; actual!=NULL;){
    anterior = actual;
    actual = actual->sig;
    free(anterior);
  }
  lista->inicio = lista->fin= NULL;
}

void* buscarDato(ListaD lista,void *dato, int (*comparar)(void*, void*))
{
	NodoD *actual;//,*anterior=NULL;
	for( actual = lista.inicio ; actual!=NULL ;  actual = actual->sig)
	{
		if( comparar(dato,actual->dato) == 0)
		{
			return actual->dato;
		}
		// anterior = actual;
	}	
	return NULL;
}

void insertarOrdenado(ListaD *lista,void* dato)
{
	NodoD *nuevo = crearNodoD(dato);
	NodoD *actual,*anterior=NULL;
	for( actual = lista->inicio ; actual!=NULL ;  actual = actual->sig)
	{
		if( lista->comparar(dato,actual->dato) < 0)
		//if( dato < actual->dato) //CONDICION DE PARO: AQUI VOY A INSERTAR
		{
			if(anterior!=NULL) {
				//INSERTO EN MEDIO
				anterior->sig = nuevo;
        nuevo->ant = anterior;
				nuevo->sig = actual;
        actual->ant = nuevo;
			}
			else {
				//INSERTAR EN EL INICIO
				nuevo->sig = actual;
        nuevo->ant = NULL;
				lista->inicio = nuevo;
			}
			break;
		}
		anterior = actual;
	}		
	if(lista->inicio == NULL) {
    // Lista vacia: insertamos al inicio
		lista->inicio = nuevo;
    lista->fin = nuevo;
  }
	else if ( anterior !=NULL) {
    // Recorri toda la lista: insertamos al final
		anterior->sig = nuevo;	
    nuevo->sig = NULL;
    nuevo->ant = anterior;
    lista->fin = nuevo;
  }
	lista->cant++;	
}

// void mostrarLista(ListaD lista)
// {
// 	NodoD *p;	
// 	printf("\n Lista[%d]: ",lista.cant);
// 	for( p = lista.inicio ;  p!=NULL ; p = p->sig  )
// 	{
// 		printf(" ");
// 		lista.imprimir(p->dato);
// 		printf(" -> ");
// 	}
// 	printf("NULL\n");
// }

void insertarFinal(ListaD *lista,void* dato) {
	//CREAR NODO
	NodoD *nuevo = crearNodoD(dato);
	if(lista->inicio == NULL && lista->cant == 0) {
		//LISTA VACIA ASOCIAMOS AL INICIO
		lista->inicio = lista->fin = nuevo;
	}
	else {
		//RECORRER Y ENCONTRAR EL ULTIMO NODO INSERTAR
    lista->fin->sig = nuevo;
    nuevo->ant = lista->fin;
    lista->fin = nuevo;
	}
	lista->cant++;
}

void insertarInicio(ListaD *lista,void* dato)
{
	NodoD *nuevo = crearNodoD(dato);
	nuevo->sig = lista->inicio;
	lista->inicio = nuevo;	
	lista->cant++;
}

void insertarEnPosicion(ListaD *lista,void* dato,int pos)
{	
	//VALIDAR
	if( pos==0 ||(pos > 0  && pos <= lista->cant ))
	{			
		NodoD *anterior ,*actual;
		anterior = NULL;
		actual = lista->inicio;
		for (int i=0; i<=lista->cant  ; i++)
		{
			if( i==pos)
			{
				if(anterior == NULL)
				{
					insertarInicio(lista,dato);
					return;
				}
				else if (i == lista->cant) {
          // insertar hasta el final
          insertarFinal(lista, dato);
        } else {
					NodoD *nuevo = crearNodoD(dato);
					nuevo->sig = actual;
          actual->ant = nuevo;
					anterior->sig = nuevo;
          nuevo->ant = anterior;
					lista->cant++;
					return;
				}
			}
			anterior = actual;
			actual = actual->sig;
		}
	}
}

void eliminarEnPosicion(ListaD *lista,int pos)
{
	//VALIDAR
	if( pos==0 ||(pos > 0  && pos < lista->cant ))
	{			
		NodoD *anterior ,*actual;
		anterior = NULL;
		actual = lista->inicio;
		for (int i=0; i<lista->cant  ; i++)
		{
			if( i==pos)
			{
				if(anterior == NULL)
					lista->inicio = actual->sig;
				else
					anterior->sig = actual->sig;
	
				free(actual);
				lista->cant--;
				break;
			}
			anterior = actual;
			actual = actual->sig;
		}			
	}	
}

void reordenar(ListaD *listaOrigen, int (*comparar)(void*, void*)){
  ListaD aux = (ListaD) {NULL, NULL, 0};
  aux.comparar = comparar;
  aux.imprimir = listaOrigen->imprimir;
  NodoD *actual;
  for(actual = listaOrigen->inicio ; actual != NULL;){
    insertarOrdenado(&aux, actual->dato);
    actual = actual->sig;
    eliminarEnPosicion(listaOrigen, 0);
  }
  *listaOrigen = aux;
}

