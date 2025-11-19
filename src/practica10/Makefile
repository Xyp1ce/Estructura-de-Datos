cflags = -Wall -Werror -pedantic -std=c99 -O2
dflags = -Wall -Werror -pedantic -std=c99 -g
includes = -I ../src/captura -I ../src/Estructuras
libs = ../../lib -lHashTable -lCola -lCaptura -lArbol
source = $(wildcard *.c) 
output = ../../bin/practica10

build :
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"
rebuild:
	make -C ../captura
	make -C ../Estructuras/cola
	make -C ../Estructuras/hash
	make -C ../Estructuras/arbol
	make -C ../Estructuras/nodos
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"
run:
	../../bin/practica10
