cflags = -Wall -Werror -pedantic -std=c99 -O2
dflags = -Wall -Werror -pedantic -std=c99 -g
includes = -I ../captura -I ../Estructuras/pila
libs = -L ../../lib -lnoPila -L ../../lib -lCaptura
source = $(wildcard *.c) 
output = ../../bin/practica3

build :
	gcc $(cflags) $(source) -o $(output) $(includes) $(libs)
	@echo "Compilo Exitosamente!!!"
rebuild: 
	make -C ../captura/ 
	make -C ../Estructuras/nodos/ 
	make -C ../Estructuras/pila/ 
	gcc -m64 $(cflags) $(source) -o $(output) $(includes) $(libs)
	@echo "Compilo Exitosamente!!!"
