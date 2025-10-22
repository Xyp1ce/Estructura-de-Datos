cflags = -Wall -Werror -pedantic -std=c99 -O2
dflags = -Wall -Werror -pedantic -std=c99 -g
includes = -I ../src/captura -I ../src/Estructuras
libs = ../../lib -lCaptura -lnoPila -lCola -lArbol
source = $(wildcard *.c) 
output = ../../bin/practica8

build :
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!! :D"
rebuild:
	make -C ../captura
	make -C ../Estructuras/nodos
	make -C ../Estructuras/arbol
	make -C ../Estructuras/pila
	make -C ../Estructuras/cola
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!! :D"
run:
	../../bin/practica8
