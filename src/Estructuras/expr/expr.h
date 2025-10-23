#ifndef EXPR_H
#define EXPR_H

#include <stdlib.h>

int validarParentesis(char *cadena);
char *inFixtoPostfix(char *expresion);
int esApertura(char c);
int esCierre(char c);
int haceMatch(char apertura, char cierre);
int esRightAssoc(char c);
void liberarCadena(void *a);

#endif
