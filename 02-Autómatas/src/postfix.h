#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

// Se define una constante para el tamaño máximo de la cadena de la expresión
#define MAX 100
// Se define una constante para el número de operadores posibles
#define NUM_OP 4

// Se declara una estructura para representar una pila
struct pila_postfix {
    double datos[MAX]; // Se declara un arreglo para guardar los datos de la pila
    int tope; // Se declara un entero para guardar el índice del elemento superior de la pila
};

// Se declara una función para crear una pila vacía
struct pila_postfix *crearPilaPostfix() {
    struct pila_postfix *p; // Se declara un puntero a una estructura pila
    p = (struct pila_postfix *)malloc(sizeof(struct pila_postfix)); // Se reserva memoria dinámica para la estructura pila
    if (p == NULL) { // Se comprueba si se ha reservado correctamente la memoria
        printf("Error al reservar memoria\n");
        exit(1); // Se termina el programa con error
    }
    p->tope = -1; // Se inicializa el tope de la pila a -1, indicando que está vacía
    return p; // Se devuelve el puntero a la pila creada
}

// Se declara una función para insertar un elemento en la pila
void push_postfix(struct pila_postfix *p, double x) {
    if (p->tope == MAX - 1) { // Se comprueba si la pila está llena
        printf("La pila está llena\n");
        return; // Se termina la función sin hacer nada
    }
    p->tope++; // Se incrementa el tope de la pila en uno
    p->datos[p->tope] = x; // Se guarda el elemento x en la posición del tope de la pila
}

// Se declara una función para sacar un elemento de la pila
double pop_postfix(struct pila_postfix *p) {
    double x; // Se declara una variable para guardar el elemento a sacar
    if (p->tope == -1) { // Se comprueba si la pila está vacía
        printf("La pila está vacía\n");
        return 0; // Se devuelve cero como valor por defecto
    }
    x = p->datos[p->tope]; // Se guarda el elemento del tope de la pila en x
    p->tope--; // Se decrementa el tope de la pila en uno
    return x; // Se devuelve el elemento sacado
}

// Se declara una función para leer una cadena del teclado
char *leerCadena() {
    char *cadena; // Se declara un puntero a char para guardar la cadena leída
    cadena = (char *)malloc(MAX); // Se reserva memoria dinámica para la cadena, usando la constante MAX como tamaño máximo
    if (cadena == NULL) { // Se comprueba si se ha reservado correctamente la memoria
        printf("Error al reservar memoria\n");
        exit(1); // Se termina el programa con error
    }
    printf("Ingrese una expresión postfija: "); // Se pide al usuario que ingrese una expresión postfija
    if (fgets(cadena, MAX, stdin) == NULL) { // Se lee la cadena del teclado con fgets y se comprueba si se ha leído correctamente
        printf("Error al leer la expresión\n");
        free(cadena); // Se libera la memoria reservada para la cadena
        exit(1); // Se termina el programa con error
    }
    return cadena; // Se devuelve la cadena leída
}

// Se declara una función para validar la entrada del usuario
int validarCadena(char *cadena) {
    int i; // Se declara una variable para recorrer la cadena
    int longitud; // Se declara una variable para guardar la longitud de la cadena
    int numOperandos; // Se declara una variable para contar el número de operandos en la cadena
    int numOperadores; // Se declara una variable para contar el número de operadores en la cadena
    longitud = strlen(cadena); // Se obtiene la longitud de la cadena con strlen
    numOperandos = 0; // Se inicializa el contador de operandos a cero
    numOperadores = 0; // Se inicializa el contador de operadores a cero
    for (i = 0; i < longitud; i++) { // Se recorre la cadena desde el inicio hasta el final
        if (isdigit(cadena[i])) { // Se comprueba si el caracter actual es un dígito con isdigit
            numOperandos++; // Se incrementa el contador de operandos en uno
            while (isdigit(cadena[i])) { // Se salta los posibles dígitos siguientes que formen parte del mismo operando
                i++;
            }
        }
        else if (cadena[i] == '+' || cadena[i] == '-' || cadena[i] == '*' || cadena[i] == '/') { // Se comprueba si el caracter actual es un operador con un if-else anidado
            numOperadores++; // Se incrementa el contador de operadores en uno
        }
        else if (cadena[i] == ' ' || cadena[i] == '\n') { // Se comprueba si el caracter actual es un espacio o un salto de línea con un if-else anidado
            continue; // Se ignora el caracter y se pasa al siguiente
        }
        else { // Si el caracter no es ni un dígito ni un operador ni un espacio ni un salto de línea, se asume que es un caracter inválido
            printf("La expresión contiene un caracter inválido: %c\n", cadena[i]); // Se imprime el caracter inválido encontrado
            return 0; // Se devuelve cero indicando que la cadena no es válida
        }
    }
    if (numOperandos == 0) { // Se comprueba si la cadena no tiene ningún operando
        printf("La expresión no tiene ningún operando\n"); // Se imprime el error encontrado
        return 0; // Se devuelve cero indicando que la cadena no es válida
    }
    if (numOperadores == 0) { // Se comprueba si la cadena no tiene ningún operador
        printf("La expresión no tiene ningún operador\n"); // Se imprime el error encontrado
        return 0; // Se devuelve cero indicando que la cadena no es válida
    }
    if (numOperandos != numOperadores + 1) { // Se comprueba si la cadena cumple con la regla de que el número de operandos debe ser igual al número de operadores más uno
        printf("La expresión no cumple con la regla de los operandos y operadores\n"); // Se imprime el error encontrado
        return 0; // Se devuelve cero indicando que la cadena no es válida
    }
    return 1; // Si se llega hasta aquí, se asume que la cadena es válida y se devuelve uno
}
/*
// Función que evalúa una expresión postfija y devuelve su resultado como un double
double evaluarPostfijo(char *expresion) {
    int i; // Variable para recorrer la expresión 
    int longitud; // Variable para guardar la longitud de la expresión 
    double a, b, resultado; // Variables para guardar los operandos y el resultado de cada operación 
    char operador; // Variable para guardar el operador de cada operación 
    struct pila_postfix *p = crearPilaPostfix(); // Se crea una pila vacía para guardar los operandos
    longitud = strlen(expresion); // Se obtiene la longitud de la expresión con strlen
    for (i = 0; i < longitud; i++) { // Se recorre la expresión desde el inicio hasta el final
        if (isdigit(expresion[i])) { // Se comprueba si el caracter actual es un dígito con isdigit
            resultado = 0; // Se inicializa el resultado a cero
            while (isdigit(expresion[i])) { // Se convierte la cadena de dígitos en un número double con un bucle while
                                resultado = resultado * 10 + (expresion[i] - '0'); // Se multiplica el resultado por 10 y se le suma el valor numérico del dígito actual
                i++; // Se incrementa el índice en uno
            }
            push_postfix(p, resultado); // Se inserta el número obtenido en la pila
        }
        else if (expresion[i] == '+' || expresion[i] == '-' || expresion[i] == '*' || expresion[i] == '/') { // Se comprueba si el caracter actual es un operador con un if-else anidado
            operador = expresion[i]; // Se guarda el operador en una variable
            b = pop_postfix(p); // Se saca el primer operando de la pila y se guarda en b
            a = pop_postfix(p); // Se saca el segundo operando de la pila y se guarda en a
            switch (operador) { // Se usa un switch-case para evaluar el tipo de operador y realizar la operación correspondiente
                case '+': // Si el operador es +
                    resultado = a + b; // Se suma a y b y se guarda el resultado
                    break; // Se sale del switch-case
                case '-': // Si el operador es -
                    resultado = a - b; // Se resta a y b y se guarda el resultado
                    break; // Se sale del switch-case
                case '*': // Si el operador es *
                    resultado = a * b; // Se multiplica a y b y se guarda el resultado
                    break; // Se sale del switch-case
                case '/': // Si el operador es /
                    if (b == 0) { // Se comprueba si b es cero para evitar una división por cero
                        printf("Error: división por cero\n"); // Se imprime el error encontrado
                        exit(1); // Se termina el programa con error
                    }
                    resultado = a / b; // Se divide a entre b y se guarda el resultado
                    break; // Se sale del switch-case
                default: // Si el operador no es ninguno de los anteriores, se asume que es un error
                    printf("Error: operador inválido\n"); // Se imprime el error encontrado
                    exit(1); // Se termina el programa con error
            }
            push_postfix(p, resultado); // Se inserta el resultado de la operación en la pila
        }
        else if (expresion[i] == ' ' || expresion[i] == '\n') { // Se comprueba si el caracter actual es un espacio o un salto de línea con un if-else anidado
            continue; // Se ignora el caracter y se pasa al siguiente
        }
    }
    resultado = pop_postfix(p); // Se saca el último elemento de la pila, que corresponde al resultado final de la expresión postfija 
    return resultado; // Se devuelve el resultado final como un double 
}*/

/*
// Función principal que muestra un ejemplo de uso de las funciones leerCadena, validarCadena y evaluarPostfijo
int main() {
    char *expresion= (char*)malloc(100); // Se declara un puntero a char para guardar la expresión postfija
    double resultado; // Se declara una variable para guardar el resultado de la evaluación
    char opcion; // Se declara una variable para guardar la opción del usuario
    FILE *archivo; // Se declara un puntero a FILE para guardar el archivo donde se guardarán las expresiones y sus resultados
    archivo = fopen("expresiones.txt", "w"); // Se abre el archivo en modo escritura con fopen
    if (archivo == NULL) { // Se comprueba si se ha abierto correctamente el archivo
        printf("Error al abrir el archivo\n");
        exit(1); // Se termina el programa con error
    }
    expresion = leerCadena(); // Se llama a la función leerCadena para leer una expresión postfija del teclado
    if (validarCadena(expresion)) { // Se llama a la función validarCadena para comprobar si la expresión es válida
        resultado = evaluarPostfijo(expresion); // Se llama a la función evaluarPostfijo para evaluar la expresión y obtener su resultado
        printf("La expresión postfija es: %s\n", expresion); // Se imprime la expresión postfija
        printf("El resultado de evaluarla es: %.2f\n", resultado); // Se imprime el resultado de la evaluación
        fprintf(archivo, "%s = %f\n", expresion, resultado); // Se guarda la expresión y su resultado en el archivo con fprintf
    }
    else { // Si la expresión no es válida, se imprime un mensaje de error
        printf("La expresión no es válida\n");
    }
    free(expresion); // Se libera la memoria reservada para la expresión
    fclose(archivo); // Se cierra el archivo con fclose
    printf("Gracias por usar este programa. Hasta pronto.\n"); // Se imprime un mensaje de despedida
    return 0; // Se termina el programa con éxito
}
*/
