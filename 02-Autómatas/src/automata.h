#include <stdio.h>
#include <stdbool.h>

/*
    SE DEFINEN AQUI FUNCIONES AUXILIARES AL RECONOCIMIENTO DE CADENAS
*/

//algunas listas de utilizad

#define NUM_DIGITS_AMOUNT 10
char digitos_numericos[NUM_DIGITS_AMOUNT]={'0','1','2','3','4','5','6','7','8','9'};

#define POSITIVE_DIGITS_AMOUNT 9
char digitos_positivos[POSITIVE_DIGITS_AMOUNT]={'1','2','3','4','5','6','7','8','9'};

#define OCTAL_DIGITS_AMOUNT 8
char digitos_octales[OCTAL_DIGITS_AMOUNT]={'0','1','2','3','4','5','6','7'};

#define LETTERS_AMOUNT 12
char letras[LETTERS_AMOUNT]={'A','B','C','D','E','F','a','b','c','d','e','f'};

#define SIGNS_AMOUNT 2
char signos[SIGNS_AMOUNT]={'+', '-'};

//devuelve verdadero si value esta contenido en el vector array[]
bool isContainedBy(char array[], int len, char value){
    for(int i=0; i<len; i++){
        if(array[i]==value){
            return true;
        }
    }
    return false;
}

    //LA NUMERACION DE LAS TRANSICIONES ES ACORDE AL AUTOMATA DOCUMENTADO

//devuelve el nuevo estado a partir del actual, -1 en caso de estado de rechazo o invalido
int transition(int actualState, char consumed){

    int newState;

    //defino cada caso de transicion segun el estado actual
    switch (actualState)
    {
    case 0:
        //el estado actual es inicial
        if(consumed=='0'){
            //el nuevo estado es un cero decimal
            newState=1;
        }
        else if 
           (isContainedBy(signos, SIGNS_AMOUNT, consumed)){
                //el nuevo estado es decimal SIGNADO
                newState=2;
            }
        else if(isContainedBy(digitos_positivos, POSITIVE_DIGITS_AMOUNT, consumed)){
            //el nuevo estado es decimal NO SIGNADO
            newState=5;
        }
        else{
            newState=-1;
        }
        break;
    
    case 1:
        //el estado actual es un cero decimal
        if(isContainedBy(digitos_octales, OCTAL_DIGITS_AMOUNT, consumed)){
            //el nuevo estado es octal
            newState=4;
        }
        else if(consumed=='x' || consumed=='X'){
            //el nuevo estado es hexadecimal
            newState=3;
        }
        else{
            newState=-1;
        }
        break;

    case 2:
        //el estado actual es decimal SIGNADO
        if(isContainedBy(digitos_numericos, NUM_DIGITS_AMOUNT, consumed)){
            
            //el estado siguiente es DECIMAL
            newState=5;
        }
        else{
            newState=-1;
        }
        break;
    
    case 3:
        //el estado actual es hexadecimal
        if
           (isContainedBy(digitos_numericos, NUM_DIGITS_AMOUNT, consumed) ||
            isContainedBy(letras, LETTERS_AMOUNT, consumed)){
                //el estado actual es el unico posible
                newState=3;
            }
        else{
            newState=-1;
        }
        break;

    case 4:
        //el estado actual es octal
        if(isContainedBy(digitos_octales, OCTAL_DIGITS_AMOUNT, consumed)){
            //el estado actual es el unico posible
            newState=4;
        }
        else{
            newState=-1;
        }
        break;

    case 5:
        //el estado actual es DECIMAL
        if(isContainedBy(digitos_numericos, NUM_DIGITS_AMOUNT, consumed)){
            //el actual es el unico posible
            newState=5;
        }
        else{
            newState=-1;
        }
        break;
    default:
        newState=-1;
        break;
    }

    return newState;
}

