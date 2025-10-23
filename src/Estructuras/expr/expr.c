#include "expr.h"
#include "../pila/pila.h"
#include <string.h>
#include <stdio.h>

void liberarCadena(void *a){
    char *aa = a;
    free(aa);
}

int esApertura(char c){
  return c == '(' || c == '[' || c == '{';
}

int esCierre(char c){
  return c == ')' || c == ']' || c == '}';
}

int haceMatch(char apertura, char cierre){
  return (apertura == '(' && cierre == ')') ||
         (apertura == '[' && cierre == ']') ||
         (apertura == '{' && cierre == '}');
}

int esRightAssoc(char c){
  return c == '^';
}

int validarParentesis(char *cadena)
{
    Pila pila = {NULL, -1, 0, NULL, &liberarCadena};
    int bandera = 1;

    for (int i = 0; cadena[i] != '\0'; i++)
    {
        if (cadena[i] == '(' || cadena[i] == '{' || cadena[i] == '[')
        {
            char *tmp = malloc(sizeof(char));
            *tmp = cadena[i];
            push(&pila, tmp);
        }

        else if (cadena[i] == ')' || cadena[i] == '}' || cadena[i] == ']')
        {
            if (pila.cantidad == 0)
            {
                bandera = 0;
                break;
            }

            char *parentesis = pop(&pila);

            if ((cadena[i] == ')' && *parentesis != '(') ||
                (cadena[i] == '}' && *parentesis != '{') ||
                (cadena[i] == ']' && *parentesis != '['))
            {
                bandera = 0;
                if (parentesis) free(parentesis);
                break;
            }
            if (parentesis) free(parentesis);
        }
    }
    int empty = vacia(pila);
    eliminarPila(&pila);
    if (bandera == 1 && empty)
    {
        printf("\n Expresion valida, comenzamos con el proceso.\n");
        return 1;
    }
    else
    {
        printf("\n Expresion Invalida.\n");
        return 0;
    }
}

char *inFixtoPostfix(char *expresion)
{
    if (!validarParentesis(expresion))
        return NULL;

    Pila pila = {NULL, -1, 0, NULL, &liberarCadena};
    int len = strlen(expresion);
    char *postfix = calloc(len + 1, sizeof(char));
    int j = 0;

    for (int i = 0; expresion[i] != '\0'; i++)
    {
        char c = expresion[i];

        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        {
            postfix[j++] = c;
        }
        else if (esApertura(c))
        {
            char *parentesis = malloc(sizeof(char));
            *parentesis = c;
            push(&pila, parentesis);
        }
        else if (esCierre(c))
        {
            char *op = pop(&pila);
            while (op != NULL && !haceMatch(*op, c))
            {
                postfix[j++] = *op;
                free(op);
                op = pop(&pila);
            }
            if (op)
                free(op);
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
        {
            while (!vacia(pila))
            {
                char *tope = (char *)pila.cima->dato;
                if (!tope)
                    break;
                char top = *tope;
                if (top == '(' || top == '[' || top == '{')
                    break;
                int top_prec = (top == '+'||top=='-')?1: (top=='*'||top=='/')?2:3;
                int cur_prec = (c == '+'||c=='-')?1: (c=='*'||c=='/')?2:3;
                if (top_prec > cur_prec || (top_prec == cur_prec && !esRightAssoc(c)))
                {
                    char *op = pop(&pila);
                    postfix[j++] = *op;
                    free(op);
                }
                else
                    break;
            }

            char *oper = malloc(sizeof(char));
            *oper = c;
            push(&pila, oper);
        }
    }

    while (!vacia(pila))
    {
        char *op = pop(&pila);
        if (!op)
            continue;
        if (*op == '(' || *op == '[' || *op == '{')
        {
            free(op);
            continue;
        }
        postfix[j++] = *op;
        free(op);
    }

    postfix[j] = '\0';
    return postfix;
}
