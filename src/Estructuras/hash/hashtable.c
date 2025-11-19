#include "hashtable.h"
#include <string.h>
#include "../../practica10/Libro.h"

int hash(int clave,int tam)
{
  return clave % tam;
}

int rehash(int indice,int k,int tam)
{
  return (indice + k * k) % tam;
}

int validarHashTable(HashTable *hashtable)
{
  if(!hashtable->tabla)
  {
    printf("\n No se ha reservado espacio");
    return 0;
  }
  if(!hashtable->folding )
  {
    printf("\n No se ha asignado alguna de estas funciones: folding,hash,rehash");
    return 0;		
  }
  if(!hashtable->comparar || !hashtable->imprimir)
  {
    printf("\n No se ha asignado alguna de estas funciones: comparar,imprimir");
    return 0;		
  }
  return 1;	
}

HashTable inicializarHashTable(int tam,void (*imprimir)(void*),int (*comparar)(void*,void*), int (*folding)(void*))
{
  HashTable hashtable = (HashTable) {NULL,tam,0,folding,imprimir,comparar};
  while(!hashtable.tabla)
    hashtable.tabla = (void**) calloc(tam,sizeof(void*));
  return hashtable;	
}

int insertarClave(HashTable* hashtable,void *dato)
{
  if(!validarHashTable(hashtable))
    return 0;
  int clave,indice,nuevo_indice,k;
  clave = hashtable->folding(dato);
  indice = hash(clave,hashtable->tam);
  if(hashtable->tabla[indice] == NULL)
    hashtable->tabla[indice] = dato;
  else
  {
    k = 0;
    do
    {
      k++;
      nuevo_indice = rehash(indice,k,hashtable->tam);
    }while( hashtable->tabla[nuevo_indice] != NULL);		
    hashtable->tabla[nuevo_indice] = dato;
  }
  hashtable->cant++;

  // Redimensionar si la carga es mayor al 0.6
  if (10 * hashtable->cant > 6 * hashtable->tam) {
    int new_tam = (5 * hashtable->cant + 2) / 3;

    if (new_tam <= hashtable->tam)
      new_tam = hashtable->tam * 2 + 1;
    remapHashTable(hashtable, new_tam);
  }

  return 1;		
}

Cola buscarClave(HashTable* hashtable,void *dato)
{
  Cola cola = inicializarCola();
  if (!validarHashTable(hashtable)){
    return cola;	
  }

  cola.imprimir = hashtable->imprimir;

  int clave,indice,nuevo_indice,k;
  clave = hashtable->folding(dato);
  indice = hash(clave,hashtable->tam);
  if(hashtable->tabla[indice] == NULL)
    return cola;
  else
  {
    k = 0;
    do
    {
      nuevo_indice = rehash(indice,k,hashtable->tam);

      if(hashtable->tabla[nuevo_indice]!=NULL)
      {
        if(hashtable->comparar(hashtable->tabla[nuevo_indice],dato)==0)
          enqueue(&cola,hashtable->tabla[nuevo_indice]);			
      }
      k++;
    }while( hashtable->tabla[nuevo_indice] != NULL);	
    return cola;
  }
}

void imprimirHashTabla(HashTable *hashtable)
{
  if(!validarHashTable(hashtable))
    return;
  int i,cont=0;
  for(i = 0; i < hashtable->tam ; i++)
  {
    if(hashtable->tabla[i]!=NULL)
    {
      printf("\n [%d] = ",i);
      hashtable->imprimir(hashtable->tabla[i]);
      cont++;
      if( cont == hashtable->cant)
        break;
    }
    else
    printf("\n [%d] = ",i);
  }		
}

int minuscula(int c){
  char cc = (char)c;
  if (cc >= 'A' && cc <= 'Z')
    return (int)(cc + ('a' - 'A'));
  return (int)cc;
}

int folding_cadena(char *cadena){
  int clave = 0;
  int segmento = 0;
  int n = 1;
  int i;
  int pos = 0;

  for (i = 0; cadena[i] != '\0'; i++){
    segmento += minuscula((int)cadena[i]);
    pos++;         

    if (pos == 3){
      clave += segmento * n;
      segmento = 0;
      n++;
      pos = 0;
    }
  }

  if (pos != 0)
    clave += segmento * n;

  return clave;
}

int folding_isbn(void *dato)
{
  if (!dato) 
    return 0;
  Libro *lib = (Libro*) dato;
  return folding_cadena(lib->isbn);
}

int folding_titulo(void *dato)
{
  if (!dato) 
    return 0;
  Libro *lib = (Libro*) dato;
  return folding_cadena(lib->titulo);
}

int folding_autor(void *dato)
{
  if (!dato) 
    return 0;
  Libro *lib = (Libro*) dato;
  return folding_cadena(lib->autor);
}

int folding_fecha(void *dato)
{
  if (!dato) 
    return 0;
  Libro *lib = (Libro*) dato;
  return lib->fecha;
}

Cola buscarRangoTitulo(HashTable *hashtable, char lower, char upper)
{
  Cola cola = inicializarCola();
  if (!validarHashTable(hashtable)) 
    return cola;

  cola.imprimir = hashtable->imprimir;

  char lo = (char) minuscula((int)lower);
  char hi = (char) minuscula((int)upper);

  if (lo > hi){
    char tmp = lo; lo = hi; hi = tmp;
  }

  for (int i = 0; i < hashtable->tam; i++) {
    if (hashtable->tabla[i] != NULL) {
      Libro *lib = (Libro*) hashtable->tabla[i];

      if (lib->titulo[0] == '\0') 
        continue;

      char c = (char) minuscula((int)lib->titulo[0]);

      if (c >= lo && c <= hi) 
        enqueue(&cola, lib);
    }
  }
  return cola;
}

Cola buscarRangoAutor(HashTable *hashtable, char lower, char upper)
{
  Cola cola = inicializarCola();
  if (!validarHashTable(hashtable)) 
    return cola;

  cola.imprimir = hashtable->imprimir;

  char lo = (char) minuscula((int)lower);
  char hi = (char) minuscula((int)upper);

  if (lo > hi) {
    char tmp = lo; lo = hi; hi = tmp; 
  }

  for (int i = 0; i < hashtable->tam; i++) {
    if (hashtable->tabla[i] != NULL) {

      Libro *lib = (Libro*) hashtable->tabla[i];

      if (lib->autor[0] == '\0') 
        continue;

      char c = (char) minuscula((int)lib->autor[0]);

      if (c >= lo && c <= hi) 
        enqueue(&cola, lib);
    }
  }
  return cola;
}

Cola buscarRangoFecha(HashTable *hashtable, int min, int max)
{
  Cola cola = inicializarCola();
  if (!validarHashTable(hashtable)) 
    return cola;

  cola.imprimir = hashtable->imprimir;

  int lo = min, hi = max;

  if (lo > hi){
    int tmp = lo; lo = hi; hi = tmp;
  }

  for (int i = 0; i < hashtable->tam; i++) {
    if (hashtable->tabla[i] != NULL) {
      Libro *lib = (Libro*) hashtable->tabla[i];

      if (lib->fecha >= lo && lib->fecha <= hi) 
        enqueue(&cola, lib);
    }
  }
  return cola;
}

int insertarSinResize(HashTable* hashtable, void *dato){
  if(!validarHashTable(hashtable))
    return 0;

  int clave = hashtable->folding(dato);
  int indice = hash(clave, hashtable->tam);

  if(hashtable->tabla[indice] == NULL)
    hashtable->tabla[indice] = dato;

  else{
    int k = 0;
    int nuevo_indice;
    do{
      k++;
      nuevo_indice = rehash(indice,k,hashtable->tam);
    } while( hashtable->tabla[nuevo_indice] != NULL);
    hashtable->tabla[nuevo_indice] = dato;
  }
  hashtable->cant++;
  return 1;
}

int eliminarDatoHashTable(HashTable *hashtable, const char *isbn, void (*liberar)(void*))
{
  if (!validarHashTable(hashtable) || isbn == NULL)
    return 0;

  int tam = hashtable->tam;
  void **backup = (void **) malloc(tam * sizeof(void *));
  if (!backup) {
    return 0;
  }

  int n = 0;
  int encontrado = 0;

  for (int i = 0; i < tam; i++) {
    void *p = hashtable->tabla[i];

    if (p == NULL)
      continue;

    Libro *lib = (Libro *) p;
    if (strcmp(lib->isbn, isbn) == 0) {
      if (liberar)
        liberar(lib);
      encontrado = 1;
    } else {
      backup[n++] = p;
    }
  }

  memset(hashtable->tabla, 0, tam * sizeof(void *));
  hashtable->cant = 0;

  for (int i = 0; i < n; i++) {
    insertarClave(hashtable, backup[i]);
  }

  free(backup);

  if (hashtable->tam > 3) {
    if (10 * hashtable->cant < 3 * hashtable->tam) {
      int new_tam = (5 * hashtable->cant + 2) / 3;

      if (new_tam < 3) 
        new_tam = 3;

      if (new_tam < hashtable->tam)
        remapHashTable(hashtable, new_tam);
    }
  }

  return encontrado;
}

void remapHashTable(HashTable *hashtable, int new_tam)
{
  if (!validarHashTable(hashtable) || new_tam <= 0)
    return;

  if (new_tam == hashtable->tam)
    return;

  int old_tam = hashtable->tam;
  void **backup = (void **) malloc(old_tam * sizeof(void *));

  if (!backup) 
    return;

  int n = 0;
  for (int i = 0; i < old_tam; i++) {
    void *p = hashtable->tabla[i];
    if (p != NULL) {
      backup[n++] = p;
    }
  }

  free(hashtable->tabla);
  hashtable->tam = new_tam;
  hashtable->tabla = (void**) calloc(new_tam, sizeof(void*));
  hashtable->cant = 0;

  for (int i = 0; i < n; i++) {
    insertarSinResize(hashtable, backup[i]);
  }

  free(backup);
}
