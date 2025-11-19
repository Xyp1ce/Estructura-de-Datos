#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../captura/captura.h"
#include "../Estructuras/cola/cola.h"
#include "../Estructuras/hash/hashtable.h"

typedef struct
{
	unsigned int matricula;
	char nombre[40];
	char apellido[40];
}Alumno;

Alumno* obtenerDatos(void);

char minuscula(char caracter);
int compararCadenasIC(char *cadA,char *cadB);
int folding(void* dato);
void imprimir(void* dato);
int comparar(void* datoA,void *datoB);

int main(void) {	
	Cola cola;
	HashTable hashtable = inicializarHashTable(300,&imprimir,&comparar);
	hashtable.folding = &folding;
	
	Alumno *alumnos = obtenerDatos();
	int i,insertados = 0;
	for( i = 0 ; i < 103; i++) {
		insertados+=insertarClave(&hashtable, &alumnos[i]);
	}
	printf("\n Insertardos: %d", insertados);
	
	imprimirHashTabla(&hashtable);
	Alumno alumno = (Alumno){0,"Ramon",""};	
	printf("\n Resultado Folding: %d ",folding(&alumno));
	printf("\n BUSCAR Ramon ");	
	cola = buscarClave(&hashtable,&alumno);
	cola.imprimir = &imprimir;
	printf("\n RESULTADO %d: ",cola.cantidad);
	imprimirCola(cola);
	
	Alumno alumno2 = (Alumno){0,"rAmoN",""};	
	printf("\n Resultado Folding: %d ",folding(&alumno2));
	printf("\n BUSCAR rAmoN ");	
	cola = buscarClave(&hashtable,&alumno2);
	cola.imprimir = &imprimir;
	printf("\n RESULTADO %d: ",cola.cantidad);	
	imprimirCola(cola);
	
	printf("\n\n FIN DE PROGRAMA \n");
	return 0;
}

int folding(void* dato)
{
	Alumno *alumno = dato;
	char *cadena = alumno->nombre;
	int clave,segmento,n,i;
	clave = segmento = 0;
	n = 1;
	for( i = 0; cadena[i]!='\0' ; i++) {
		if( i!=0 && i%3==0 ) {
			clave+= segmento*n;
			segmento = 0;
			n++;
		}
		segmento+=minuscula(cadena[i]);
	}
	clave+= segmento*n;
	return clave;
}

void imprimir(void* dato)
{
	Alumno *alumno = dato;
	printf(" %u - %s %s",alumno->matricula,alumno->nombre,alumno->apellido);
	return;
}

char minuscula(char caracter)
{
	if( caracter>='A' && caracter<='Z')
		return caracter+32;
	return caracter;
}

int compararCadenasIC(char *cadA,char *cadB)
{
	int i;
	char a,b;	
	for( i = 0; cadA[i]!='\0' && cadB[i]!='\0';i++)
	{
		a = minuscula(cadA[i]);
		b = minuscula(cadB[i]);
		if( a == b)
			continue;
		else if( a < b)
			return -1;
		else
			return 1;
	}
	if(cadA[i]==cadB[i])
		return 0;
	else if(cadA[i]=='\0')
		return -1;
	else
		return 1;
}

int comparar(void* datoA,void *datoB)
{	
	Alumno *a=datoA;
	Alumno *b=datoB;
	return compararCadenasIC(a->nombre,b->nombre);
}

Alumno* obtenerDatos(void) {
	static Alumno alumnos[103] = {
		{1229947, "Abraham", "Jimenez"},
		{1229947, "Nicol", "Canales"},
		{1229947, "Ramon", "Manriquez"},
		// 10 Alumnos
		{1229948, "Edgar", "Betancourt"},
		{1229949, "Alberto", "Juarez"},
		{1229950, "Maria", "Lopez"},
		{1229951, "Jose", "Gomez"},
		{1229952, "Ana", "Martinez"},
		{1229953, "Carlos", "Perez"},
		{1229954, "Laura", "Rodriguez"},
		{1229955, "David", "Sanchez"},
		{1229956, "Sofia", "Ramirez"},
		{1229957, "Ricardo", "Morales"},
		
		// 20 Alumnos
		{1229958, "Elena", "Torres"},
		{1229959, "Fernando", "Diaz"},
		{1229960, "Isabel", "Herrera"},
		{1229961, "Miguel", "Ruiz"},
		{1229962, "Lucia", "Flores"},
		{1229963, "Javier", "Garcia"},
		{1229964, "Andrea", "Soto"},
		{1229965, "Pedro", "Vargas"},
		{1229966, "Diana", "Reyes"},
		{1229967, "Jorge", "Mendoza"},

		// 30 Alumnos
		{1229968, "Carmen", "Castro"},
		{1229969, "Roberto", "Ortiz"},
		{1229970, "Alejandra", "Guerrero"},
		{1229971, "Daniel", "Betancourt"}, // Apellido repetido
		{1229972, "Esther", "Juarez"}, // Apellido repetido
		{1229973, "Sergio", "Lopez"}, // Apellido repetido
		{1229974, "Monica", "Gomez"}, // Apellido repetido
		{1229975, "Raul", "Martinez"}, // Apellido repetido
		{1229976, "Natalia", "Perez"}, // Apellido repetido
		{1229977, "Emilio", "Rodriguez"}, // Apellido repetido

		// 40 Alumnos
		{1229978, "Jessica", "Sanchez"}, // Apellido repetido
		{1229979, "Gustavo", "Ramirez"}, // Apellido repetido
		{1229980, "Lorena", "Morales"}, // Apellido repetido
		{1229981, "Alfredo", "Torres"}, // Apellido repetido
		{1229982, "Virginia", "Diaz"}, // Apellido repetido
		{1229983, "Ruben", "Herrera"}, // Apellido repetido
		{1229984, "Paula", "Ruiz"}, // Apellido repetido
		{1229985, "Hugo", "Flores"}, // Apellido repetido
		{1229986, "Maria", "Garcia"}, // Nombre y apellido repetidos
		{1229987, "Jose", "Soto"}, // Nombre y apellido repetidos

		// 50 Alumnos
		{1229988, "Sara", "Vargas"},
		{1229989, "Diego", "Reyes"},
		{1229990, "Adriana", "Mendoza"},
		{1229991, "Marco", "Castro"},
		{1229992, "Silvia", "Ortiz"},
		{1229993, "Jorge", "Guerrero"}, // Nombre repetido
		{1229994, "Patricia", "Betancourt"}, // Apellido repetido
		{1229995, "Felipe", "Juarez"}, // Apellido repetido
		{1229996, "Valeria", "Lopez"}, // Apellido repetido
		{1229997, "Christian", "Gomez"}, // Apellido repetido

		// 60 Alumnos
		{1229998, "Gabriela", "Martinez"}, // Apellido repetido
		{1229999, "Mario", "Perez"}, // Apellido repetido
		{1230000, "Carolina", "Rodriguez"}, // Apellido repetido
		{1230001, "Armando", "Sanchez"}, // Apellido repetido
		{1230002, "Viviana", "Ramirez"}, // Apellido repetido
		{1230003, "Omar", "Morales"}, // Apellido repetido
		{1230004, "Camila", "Torres"}, // Apellido repetido
		{1230005, "Ivan", "Diaz"}, // Apellido repetido
		{1230006, "Tamara", "Herrera"}, // Apellido repetido
		{1230007, "Benjamin", "Ruiz"}, // Apellido repetido

		// 70 Alumnos
		{1230008, "Paola", "Flores"}, // Apellido repetido
		{1230009, "Arturo", "Garcia"}, // Apellido repetido
		{1230010, "Regina", "Soto"}, // Apellido repetido
		{1230011, "Hector", "Vargas"}, // Apellido repetido
		{1230012, "Alejandro", "Reyes"}, // Nombre repetido, apellido repetido
		{1230013, "Veronica", "Mendoza"}, // Apellido repetido
		{1230014, "Luis", "Castro"}, // Apellido repetido
		{1230015, "Daniela", "Ortiz"}, // Apellido repetido
		{1230016, "Esteban", "Guerrero"}, // Apellido repetido
		{1230017, "Edgar", "Juarez"}, // Nombre repetido, apellido repetido

		// 80 Alumnos
		{1230018, "Lucia", "Betancourt"}, // Nombre repetido, apellido repetido
		{1230019, "Marco", "Lopez"}, // Nombre repetido, apellido repetido
		{1230020, "Sofia", "Gomez"}, // Nombre repetido, apellido repetido
		{1230021, "Ricardo", "Martinez"}, // Nombre repetido, apellido repetido
		{1230022, "Elena", "Perez"}, // Nombre repetido, apellido repetido
		{1230023, "Fernando", "Rodriguez"}, // Nombre repetido, apellido repetido
		{1230024, "Isabel", "Sanchez"}, // Nombre repetido, apellido repetido
		{1230025, "Miguel", "Ramirez"}, // Nombre repetido, apellido repetido
		{1230026, "Javier", "Morales"}, // Nombre repetido, apellido repetido
		{1230027, "Andrea", "Torres"}, // Nombre repetido, apellido repetido

		// 90 Alumnos
		{1230028, "Pedro", "Diaz"}, // Nombre repetido, apellido repetido
		{1230029, "Diana", "Herrera"}, // Nombre repetido, apellido repetido
		{1230030, "Jose", "Ruiz"}, // Nombre repetido, apellido repetido
		{1230031, "Carmen", "Flores"}, // Nombre repetido, apellido repetido
		{1230032, "Roberto", "Garcia"}, // Nombre repetido, apellido repetido
		{1230033, "Alejandra", "Soto"}, // Nombre repetido, apellido repetido
		{1230034, "Daniel", "Vargas"}, // Nombre repetido, apellido repetido
		{1230035, "Esther", "Reyes"}, // Nombre repetido, apellido repetido
		{1230036, "Sergio", "Mendoza"}, // Nombre repetido, apellido repetido
		{1230037, "Monica", "Castro"}, // Nombre repetido, apellido repetido

		// 100 Alumnos
		{1230038, "Raul", "Ortiz"}, // Nombre repetido, apellido repetido
		{1230039, "Natalia", "Guerrero"}, // Nombre repetido, apellido repetido
		{1230040, "Emilio", "Betancourt"}, // Nombre repetido, apellido repetido
		{1230041, "Jessica", "Juarez"}, // Nombre repetido, apellido repetido
		{1230042, "Gustavo", "Lopez"}, // Nombre repetido, apellido repetido
		{1230043, "Lorena", "Gomez"}, // Nombre repetido, apellido repetido
		{1230044, "Alfredo", "Martinez"}, // Nombre repetido, apellido repetido
		{1230045, "Virginia", "Perez"}, // Nombre repetido, apellido repetido
		{1230046, "Ruben", "Rodriguez"}, // Nombre repetido, apellido repetido
		{1230047, "Paula", "Sanchez"} // Nombre repetido, apellido repetido
	};
	return (Alumno*)alumnos;
}
