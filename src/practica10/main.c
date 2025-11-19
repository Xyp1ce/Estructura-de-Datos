#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../captura/captura.h"
#include "../Estructuras/hash/hashtable.h"
#include "../Estructuras/arbol/arbol.h"

#include "Libro.h"

Arbol convertirColaAArbol(Cola *cola, int (*comparar)(void*, void*), void (*imprimir)(void*));

void buscarPorISBN(HashTable *hashtable, Arbol *arbolISBN);
void buscarPorTitulo(HashTable *hashtable, Arbol *arbolTitulo);
void buscarPorAutor(HashTable *OrAutor, Arbol *arbolAutor);
void buscarPorFecha(HashTable *OrFecha, Arbol *arbolFecha);
void eliminarPorISBN(HashTable *OrIsbn, HashTable *OrTitulo, HashTable *OrAutor, HashTable *OrFecha);
void agregarLibro(HashTable *OrIsbn, HashTable *OrTitulo, HashTable *OrAutor, HashTable *OrFecha);

int main(void){
	//VARIABLE PARA MANEJAR INDICES
    int i;
	//PUNTERO QUE ALMACENA LA REFERENCIA DEL INICIO DE LOS DATOS
    Libro *libros;
    libros = obtener_libros();
    
    HashTable OrISBN   = inicializarHashTable(84, imprimirLibro, compararISBN, folding_isbn);
    HashTable OrTITULO = inicializarHashTable(84, imprimirLibro, compararTitulo, folding_titulo);
    HashTable OrAUTOR  = inicializarHashTable(84, imprimirLibro, compararAutor, folding_autor);
    HashTable OrFECHA = inicializarHashTable(84,imprimirLibro,compararFecha, folding_fecha);

    Arbol arbolISBN = {NULL,0,imprimirLibro,compararISBN,NULL};
    Arbol arbolTITULO = {NULL,0,imprimirLibro,compararTitulo,NULL};
    Arbol arbolAUTOR = {NULL,0,imprimirLibro,compararAutor,NULL};
    Arbol arbolFECHA = {NULL,0,imprimirLibro,compararFecha,NULL};

    int opcion;

    for (int i = 0; i < CANT_LIBROS; i++){
        insertarClave(&OrISBN, &libros[i]);
        insertarClave(&OrTITULO, &libros[i]);
        insertarClave(&OrAUTOR, &libros[i]);
        insertarClave(&OrFECHA, &libros[i]);
    }

    printf("\n Biblioteca: ");

    for(i = 0 ; i < CANT_LIBROS ; i++){
        printf("\n");
        imprimirLibro(&libros[i]);
    }

    do{
        printf("\n MENU DE BUSQUEDAS ");
        printf("\n [1] Buscar por ISBN ");
        printf("\n [2] Buscar por Titulo ");
        printf("\n [3] Buscar por Autor ");
        printf("\n [4] Buscar por Fecha ");
        printf("\n [5] Eliminar libro por ISBN");
        printf("\n [6] Agregar libro");
        printf("\n [7] Salir ");
        inputEntero("\n Ingrese una opcion: ", &opcion);

        switch (opcion){

            case 1:
                buscarPorISBN(&OrISBN, &arbolISBN);
                break;

            case 2:
                buscarPorTitulo(&OrTITULO, &arbolTITULO);
                break;

            case 3:
                buscarPorAutor(&OrAUTOR, &arbolAUTOR);
                break;

            case 4:
                buscarPorFecha(&OrFECHA, &arbolFECHA);
                break;

            case 5:
                eliminarPorISBN(&OrISBN, &OrTITULO, &OrAUTOR, &OrFECHA);
                break;

            case 6:
                agregarLibro(&OrISBN, &OrTITULO, &OrAUTOR, &OrFECHA);
                break;
            case 7:
                printf("\n Saliendo del programa... ");
                return 0;
            
            default:
                printf("\n Opcion invalida, intente de nuevo. ");
                break;
        }

    }while (opcion != 7);

    for(i = 0 ; i < CANT_LIBROS ; i++){
        printf("\n ");
        imprimirLibro(&libros[i]);
    }
	
    printf("\n\n FIN DE PROGRAMA \n");
    return 0;
}

Arbol convertirColaAArbol(Cola *cola, int (*comparar)(void*, void*), void (*imprimir)(void*)) {
    Arbol arbol = {NULL, 0, imprimir, comparar, NULL};

    while (!vaciaC(*cola)) {
        void *dato = dequeue(cola); 
        
        if (dato)
            insertarArbol(&arbol, dato); 
    }
    
    return arbol;
}

void buscarPorISBN(HashTable *hashtable, Arbol *arbolISBN) {

    Libro clave = {0};
    char *isbn = NULL;
    Cola resultados;

    inputCadenaDinamica("\n Ingrese el ISBN a buscar: ", &isbn, MAX_ISBN);
    strncpy(clave.isbn, isbn, sizeof(clave.isbn) - 1);
    resultados = buscarClave(hashtable, &clave);

    if (vaciaC(resultados))
    {
        printf("\n No se encontraron libros con el ISBN proporcionado.");
        free(isbn);
        isbn = NULL;
        return;
    }

    *arbolISBN = convertirColaAArbol(&resultados, compararISBN, imprimirLibro);
    imprimirArbol(*arbolISBN);
    printf("\n");
    free(isbn);
    isbn = NULL;
}

void buscarPorTitulo(HashTable *hashtable, Arbol *arbolTitulo) {

    Libro clave = (Libro){0};
    int opc;
    char *cadena = NULL;
    Cola resultados_local;

    inputEntero("\n ¿Desea manejarlo por rango? (0 = No, 1 = Si): ", &opc);

    if (opc == 1) {
        char lower, upper;
        inputChar("\n Ingrese el caracter inicial del rango: ", &lower);
        inputChar("\n Ingrese el caracter final del rango: ", &upper);
        resultados_local = buscarRangoTitulo(hashtable, lower, upper);
        *arbolTitulo = convertirColaAArbol(&resultados_local, compararTitulo, imprimirLibro);
        imprimirArbol(*arbolTitulo);
        printf("\n");
        return;
    }

    inputCadenaDinamica("\n Ingrese el Titulo a buscar: ", &cadena, MAX_TITULO);
    strncpy(clave.titulo, cadena, sizeof(clave.titulo) - 1);
    resultados_local = buscarClave(hashtable, &clave);
    *arbolTitulo = convertirColaAArbol(&resultados_local, compararTitulo, imprimirLibro);
    imprimirArbol(*arbolTitulo);
    printf("\n");
    free(cadena);
    cadena = NULL;
}

void buscarPorAutor(HashTable *OrAUTOR, Arbol *arbolAUTOR) {
    Libro clave = {0};
    int opcion;
    char *cadena = NULL;
    Cola resultados;

    inputEntero("\n ¿Desea manejarlo por rango? (0 = No, 1 = Si): ", &opcion);
    if (opcion == 1) {
        char lower, upper;
        inputChar("\n Ingrese el caracter inicial del rango: ", &lower);
        inputChar("\n Ingrese el caracter final del rango: ", &upper);
        resultados = buscarRangoAutor(OrAUTOR, lower, upper);
        *arbolAUTOR = convertirColaAArbol(&resultados, compararAutor, imprimirLibro);
        imprimirArbol(*arbolAUTOR);
        printf("\n");
        free(cadena);
        cadena = NULL;
        return;
    }

    inputCadenaDinamica("\n Ingrese el Autor a buscar: ", &cadena, MAX_AUTOR);
    strncpy(clave.autor, cadena, sizeof(clave.autor) - 1);
    resultados = buscarClave(OrAUTOR, &clave);
    *arbolAUTOR = convertirColaAArbol(&resultados, compararAutor, imprimirLibro);
    imprimirArbol(*arbolAUTOR);
    printf("\n");
    free(cadena);
    cadena = NULL;
}

void buscarPorFecha(HashTable *OrFECHA, Arbol *arbolFECHA) {
    Libro clave = {0};
    int opcion;
    char *cadena = NULL;
    Cola resultados;

    inputEntero("\n ¿Desea manejarlo por rango? (0 = No, 1 = Si): ", &opcion);
    if (opcion == 1) {
        int min, max;
        inputEntero("\n Ingrese fecha minima: ", &min);
        inputEntero("\n Ingrese fecha maxima: ", &max);
        resultados = buscarRangoFecha(OrFECHA, min, max);
        *arbolFECHA = convertirColaAArbol(&resultados, compararFecha, imprimirLibro);
        imprimirArbol(*arbolFECHA);
        printf("\n");
        free(cadena);
        cadena = NULL;
        return;
    }

    inputEntero("\n Ingrese la Fecha a buscar: ", &clave.fecha);
    resultados = buscarClave(OrFECHA, &clave);
    *arbolFECHA = convertirColaAArbol(&resultados, compararFecha, imprimirLibro);
    imprimirArbol(*arbolFECHA);
    printf("\n");
    free(cadena);
    cadena = NULL;
}

void eliminarPorISBN(HashTable *OrISBN, HashTable *OrTITULO, HashTable *OrAUTOR, HashTable *OrFECHA) {
    char *cadena = NULL;
    inputCadenaDinamica("\n Ingrese el ISBN del libro a eliminar: ", &cadena, MAX_ISBN);
    eliminarDatoHashTable(OrISBN, cadena, NULL);
    eliminarDatoHashTable(OrTITULO, cadena, NULL);
    eliminarDatoHashTable(OrAUTOR, cadena, NULL);
    eliminarDatoHashTable(OrFECHA, cadena, NULL);
    free(cadena);
    cadena = NULL;
}

void agregarLibro(HashTable *OrISBN, HashTable *OrTITULO, HashTable *OrAUTOR, HashTable *OrFECHA) {
    Libro *nuevo = malloc(sizeof(Libro));
    if (!nuevo) return;
    inputCadena("\n Ingrese el ISBN del nuevo libro: ", nuevo->isbn, MAX_ISBN);
    inputCadena("\n Ingrese el Titulo del nuevo libro: ", nuevo->titulo, MAX_TITULO);
    inputCadena("\n Ingrese el Autor del nuevo libro: ", nuevo->autor, MAX_AUTOR);
    inputEntero("\n Ingrese la Fecha del nuevo libro: ", &nuevo->fecha);
    nuevo->disponible = 1;
    insertarClave(OrISBN, nuevo);
    insertarClave(OrTITULO, nuevo);
    insertarClave(OrAUTOR, nuevo);
    insertarClave(OrFECHA, nuevo);
}
