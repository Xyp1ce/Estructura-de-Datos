#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../captura/captura.h"
#include "../Estructuras/hash/hashtable.h"


#include "Libro.h"


int main(void)
{
	//VARIABLE PARA MANEJAR INDICES
    int i;
	//PUNTERO QUE ALMACENA LA REFERENCIA DEL INICIO DE LOS DATOS
    Libro *libros;
    libros = obtener_libros();
    
    for(i = 0 ; i < CANT_LIBROS ; i++)
    {
        printf("\n ");
        imprimirLibro(&libros[i]);
		//AGREGAR A TABLAS
		//TABLA ISBN
		//TABLA TITULO
		//TABLA INICIAL TITULO
		//TABLA AUTOR		
		//TABLA AUTOR TITULO
		//TABLA FECHAS
    }
	
	//MENU DE BUSQUEDAS
	
	
    printf("\n\n FIN DE PROGRAMA \n");
    return 0;
}

