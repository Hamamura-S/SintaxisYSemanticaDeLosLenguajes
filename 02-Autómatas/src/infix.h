#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Estructura para representar un nodo de la pila
typedef struct nodo_infix {
    char dato; // El dato puede ser un operador o un operando
    struct nodo_infix *siguiente; // El puntero al siguiente nodo
} NodoInfix;

// Estructura para representar una pila
typedef struct pila {
    NodoInfix *tope; // El puntero al nodo que está en el tope de la pila
    int tamano; // El tamaño de la pila
} PilaInfix;

// Función para crear una pila vacía
PilaInfix *crearPilaInfix() {
    PilaInfix *p = (PilaInfix *)malloc(sizeof(PilaInfix)); // Se reserva memoria para la pila
    p->tope = NULL; // Se inicializa el tope a NULL
    p->tamano = 0; // Se inicializa el tamaño a 0
    return p; // Se retorna la pila creada
}

// Función para verificar si una pila está vacía
int estaVacia(PilaInfix *p) {
    return p->tamano == 0; // Se retorna verdadero si el tamaño es 0, falso en caso contrario
}

// Función para obtener el dato que está en el tope de una pila, sin desapilarlo
char tope(PilaInfix *p) {
    if (estaVacia(p)) { // Si la pila está vacía, se retorna un caracter nulo
        return '\0';
    }
    return p->tope->dato; // Si no, se retorna el dato del nodo que está en el tope
}

// Función para apilar un dato en una pila
void apilar(PilaInfix *p, char dato) {
    NodoInfix *n = (NodoInfix *)malloc(sizeof(NodoInfix)); // Se reserva memoria para el nuevo nodo
    n->dato = dato; // Se asigna el dato al nodo
    n->siguiente = p->tope; // Se hace que el siguiente del nodo sea el tope actual de la pila
    p->tope = n; // Se hace que el tope de la pila sea el nuevo nodo
    p->tamano++; // Se incrementa el tamaño de la pila
}

// Función para desapilar un dato de una pila y retornarlo
char desapilar(PilaInfix *p) {
    if (estaVacia(p)) { // Si la pila está vacía, se retorna un caracter nulo
        return '\0';
    }
    char dato = p->tope->dato; // Se guarda el dato del nodo que está en el tope
    NodoInfix *temp = p->tope; // Se guarda un puntero temporal al nodo que está en el tope
    p->tope = p->tope->siguiente; // Se hace que el tope de la pila sea el siguiente del nodo actual
    free(temp); // Se libera la memoria del nodo que se desapiló
    p->tamano--; // Se decrementa el tamaño de la pila
    return dato; // Se retorna el dato desapilado
}

// Función para liberar la memoria de una pila
void liberarPila(PilaInfix *p) {
    while (!estaVacia(p)) { // Mientras la pila no esté vacía, se desapilan los nodos y se liberan
        desapilar(p);
    }
    free(p); // Se libera la memoria de la estructura de la pila
}

// Función para verificar si un caracter es un operador aritmético válido (+, -, *, /)
int esOperador(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Función para obtener la precedencia de un operador aritmético
// Se asume que el operador es válido
// Se retorna un valor mayor para mayor precedencia
int precedencia(char op) {
    if (op == '+' || op == '-') { // La suma y la resta tienen la menor precedencia
        return 1;
    }
    if (op == '*' || op == '/') { // La multiplicación y la división tienen mayor precedencia que la suma y la resta
        return 2;
    }
    return 0; // En caso de que el operador no sea válido, se retorna 0
}

// Función para convertir una expresión aritmética de notación infija a notación postfija
// Se asume que la expresión es válida y que solo contiene números enteros y operadores aritméticos
// Se retorna una cadena con la expresión en notación postfija, separando los elementos con espacios
char *infixToPostfix(char *expresion) {
    int n = strlen(expresion); // Se obtiene la longitud de la expresión
    char *salida = (char *)malloc(n * 2); // Se reserva memoria para la salida, que tendrá como máximo el doble de la longitud de la expresión
    int i = 0; // Se inicializa un índice para recorrer la expresión
    int j = 0; // Se inicializa un índice para escribir en la salida
    PilaInfix *p = crearPilaInfix(); // Se crea una pila vacía para almacenar los operadores

    while (i < n) { // Mientras no se haya recorrido toda la expresión
        char c = expresion[i]; // Se obtiene el caracter actual

        if (isdigit(c)) { // Si es un dígito, se escribe en la salida y se avanza el índice de escritura
            salida[j] = c;
            j++;
        } else if (esOperador(c)) { // Si es un operador, se verifica si hay que desapilar otros operadores de la pila
            salida[j] = ' '; // Se escribe un espacio en la salida para separar los elementos
            j++;
            while (!estaVacia(p) && precedencia(tope(p)) >= precedencia(c)) { // Mientras la pila no esté vacía y el operador en el tope tenga mayor o igual precedencia que el actual, se desapila y se escribe en la salida
                salida[j] = desapilar(p);
                j++;
                salida[j] = ' '; // Se escribe un espacio en la salida para separar los elementos
                j++;
            }
            apilar(p, c); // Se apila el operador actual en la pila
        } else if (c == '(') { // Si el caracter es un paréntesis izquierdo
            apilar(p, c); // Se apila en la pila de operadores
        } else if (c == ')') { // Si el caracter es un paréntesis derecho
            while (!estaVacia(p) && tope(p) != '(') { // Mientras la pila no esté vacía y el operador en el tope no sea un paréntesis izquierdo
                salida[j] = ' '; // Se escribe un espacio en la salida para separar los elementos
                j++;
                salida[j] = desapilar(p); // Se desapila el operador de la pila y se escribe en la salida
                j++;
            }
            if (!estaVacia(p)) { // Si la pila no está vacía
                desapilar(p); // Se desapila y se descarta el paréntesis izquierdo
            }
        }

        i++; // Se avanza el índice de lectura
    }

    while (!estaVacia(p)) { // Mientras queden operadores en la pila, se desapilan y se escriben en la salida
        salida[j] = ' '; // Se escribe un espacio en la salida para separar los elementos
        j++;
        salida[j] = desapilar(p);
        j++;
    }

    salida[j] = '\0'; // Se termina la cadena con un caracter nulo

    liberarPila(p); // Se libera la memoria de la pila

    return salida; // Se retorna la cadena con la expresión postfija
}

/*
// Este programa lee una operación aritmética infija del usuario y la convierte a notación postfija
// También imprime la operación infija y postfija en la pantalla
// Para convertir la operación infija a postfija se usa una función llamada infixToPostfix
// Para evaluar el resultado de la operación postfija se usa una función llamada evaluarPostfijo
// Estas funciones se definen en otro archivo o en la parte superior de este archivo

int main()
{
  char* operacion = (char*)malloc(100); // Se reserva memoria para la cadena de la operación
  if (operacion == NULL) // Se comprueba si se ha reservado correctamente la memoria
  {
    printf("Error al reservar memoria\n");
    return 1; // Se devuelve el código de salida 1 en caso de error
  }
  printf("Ingrese una operación aritmética: "); // Se pide al usuario que ingrese una operación
  if (fgets(operacion, 100, stdin) == NULL) // Se lee la cadena de la operación con fgets y se comprueba si se ha leído correctamente
  {
    printf("Error al leer la operación\n");
    free(operacion); // Se libera la memoria reservada para la operación
    return 1; // Se devuelve el código de salida 1 en caso de error
  }
  
  char* postfija = infixToPostfix(operacion); // Se llama a la función que convierte la expresión infija a postfija
  
  
  printf("La operación ingresada es: %s\n", operacion); // Se imprime la cadena de la operación infija
  printf("La operación en notación postfija es: %s\n", postfija); // Se imprime la cadena de la operación postfija
//  printf("El resultado es: %d", evaluarPostfijo(postfija));

  free(operacion); // Se libera la memoria reservada para la operación
  free(postfija); // Se libera la memoria reservada para la expresión postfija
return 0; // Se devuelve el código de salida 0
}
*/
