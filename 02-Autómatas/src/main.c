#include "library.h"

int main(){

    //Dicen que ser cordiales sube la nota
    saludar();

    char s;

    do
    {   //SE EJECUTARA HASTA QUE EL USUARIO DECIDA SALIR

        printf("Seleccionar opción\n");
        printf("\t| Reconocer una cadena de constantes [1]\n");
        printf("\t| Reconocer un dígito [2]\n");
        printf("\t| Realizar una operacion aritmetica [3]\n");
        printf("\t| Salir [Cualquier otro]\n");
        
        s = keyRequest();

        switch (s)
        //procesar la seleccion(s) del usuario
        {
        case '1':

            // se pidio reconocer una cadena de constantes.
            automata_uno();

            break;
        case '2':
            
            //se pidio convertir un digito char a uno numerico
            reconocer_int();

            break;
        case '3':

            //se pidio resolver una operacion aritmetica
            operacion_aritmetica();
            
        default:
            continue;
        }

        printf("Volver al menú? s/n\n");
        s = keyRequest();
        if(s=='s'||s=='S'){ s = '1'; }

    } while ( s == '1' || s == '2' || s == '3' );
    
    printf("Hasta luego!\n");

}
