#include <stdio.h>
#include <stdlib.h>
int main(){
    printf("%s", "Hello, world!"); //imprimiendo por stdout
    FILE* archivo = fopen("output.txt", "w");
    fprintf(archivo, "Hola mundo! Pero en un .txt!");  //imprimiendo en archivo .txt
    fclose(archivo);  
}