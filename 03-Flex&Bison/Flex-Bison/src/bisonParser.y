%{
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <string.h>
extern char *yytext;
extern int yyleng;
extern int yylex(void);
extern void yyerror(char*);
int variable=0;
extern void verificarLongitudIdentificador(char*);
extern int tipoIdentificador(char*);
extern void verificarParsing();
extern int tipoIdentificador(char*);
extern void inicioPrograma();
extern void finPrograma();
extern void declararVariable(char*);
extern void verificarDeclaracionPrevia(char*);
extern int estaDeclarada(char* var);

#define T_ENTRADA 11
#define T_SALIDA 12
#define T_VARIABLE 22

typedef char* symbolEntry;
symbolEntry symbolTable[1024];
int entryCount=0;

int parsing = 0;

%}
%union{
   char cadena[1024];
   int num;
} 
%token ASIGNACION PYCOMA SUMA RESTA PARENIZQUIERDO PARENDERECHO COMA INICIO FIN
%token <cadena> IDENTIFICADOR ENTRADA SALIDA
%token <num> CONSTANTE
%start programa
%type <cadena> identif_variable

%%

programa:
  {
    //inicializaciones del parser si las hubiese
    printf("Parser inicializado.\n");
  }
  sentencias
;

sentencias: 
  sentencia sentencias 
  |sentencia
;
sentencia:
  INICIO {inicioPrograma();} fin_sentencia
  | FIN fin_sentencia {finPrograma(); exit(0);}
  | {verificarParsing();} entrada_salida fin_sentencia
  | {verificarParsing();} asignacion fin_sentencia
;
fin_sentencia:
  PYCOMA {printf("\t|Fin de sentencia.\n");}
;
asignacion:
  identif_variable ASIGNACION {printf("\t|Asignando...\n");} expresion {declararVariable($1);}
;
entrada_salida:
  ENTRADA {printf("\t|Leyendo\n");}PARENIZQUIERDO entrada_argumentos PARENDERECHO
  | SALIDA {printf("\t|Escribiendo\n");} PARENIZQUIERDO salida_argumentos PARENDERECHO
;
entrada_argumentos:
  identif_variable COMA{printf("\t|Otro parametro.\n");} entrada_argumentos {declararVariable($1);}
  | identif_variable {declararVariable($1);}
;
salida_argumentos:
  expresion COMA{printf("\t|Otro parametro.\n");} salida_argumentos
  | expresion
;
expresion: 
  primaria 
  | expresion operadorAditivo primaria 
; 
primaria: 
  identif_variable {verificarDeclaracionPrevia($1);}
  | CONSTANTE {printf("\t|Valor <%d>\n",yylval.num);}
  | PARENIZQUIERDO expresion PARENDERECHO
;
identif_variable:
  IDENTIFICADOR {verificarLongitudIdentificador($1); strcpy($$, $1);}
;
operadorAditivo: 
  SUMA{printf("\t|adición\n");}
  | RESTA{printf("\t|resta\n");}
;
%%
int main() {
  yyparse();
}
void yyerror (char *s){
  printf ("Error: %s\n",s);
  exit(1);
}
int yywrap()  {
  return 1;  
}

void inicioPrograma()
{
  printf("Inicio del programa.\n");
  parsing = 1;
}

void finPrograma()
{
  printf("Fin de programa.\n");
  parsing = 0;
}

int estaDeclarada(char* var)
{
  for(int i=0; i<entryCount; i++){
    if (strcmp(var, symbolTable[i])==0){
      return 1;
    }
  }
  return 0;
}

void verificarLongitudIdentificador(char* identificador)
{
    printf("Identificador <%s> de %d caracteres\n",identificador,yyleng);
    if(yyleng>32) yyerror("Identificador en LHS excede 32c.");
}

// Implementar al menos 2 rutinas semanticas ...

int tipoIdentificador(char* constante)
{
    int tipo = T_VARIABLE;

    if (strcmp(constante, "leer")==0) {
      tipo = T_ENTRADA;
    }
    else if (strcmp(constante, "escribir")==0) {
      tipo = T_SALIDA;
    }
    return tipo;
}

void verificarParsing(){
  if (!parsing) {
    printf("No se esta parseando un programa de Micro. -- inicio;\n");
    exit(1);
  }
}

void verificarDeclaracionPrevia(char* var)
{
  if (estaDeclarada(var)){
    return;
  }
  printf("Se utilizo una variable no declarada.\n");
  exit(1);
}

void declararVariable(char* var)
{
  if (estaDeclarada(var)){
    return;
  }
  symbolEntry new_entry = (char*)malloc(strlen(var)+1);
  strcpy(new_entry, var);
  symbolTable[entryCount]=new_entry;
  entryCount++;
  printf("\t|variable <%s> declarada.\n", var);
}