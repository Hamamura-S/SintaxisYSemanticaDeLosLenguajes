%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "y.tab.h"
	#define T_ENTRADA 11
	#define T_SALIDA 12
	#define T_VARIABLE 22
	void doNothing();
	int tipoIdentificador(char* constante);
%}
DIGITO [0-9]

LETRA [a-zA-Z]

identificador {LETRA}({LETRA}|{DIGITO})*

constEntera {DIGITO}({DIGITO})*
%%

":=" {return ASIGNACION;}
";" {return PYCOMA;}
"inicio" {return INICIO;}
"fin" {return FIN;}
" " {doNothing();}
"," {return COMA;}
"(" {return PARENIZQUIERDO;}
")" {return PARENDERECHO;}
"+" {return SUMA;}
"-" {return RESTA;}
{constEntera} {yylval.num=atoi(yytext);return CONSTANTE;}
{identificador} {
	sscanf(yytext, "%s", yylval.cadena);
	switch (tipoIdentificador(yytext)) {
		case T_ENTRADA:
			return ENTRADA;
			break;
		case T_SALIDA: 
			return SALIDA;
			break;
		case T_VARIABLE:
			return IDENTIFICADOR;
			break;
		default:
			printf("identificador no reconocido\n");
			return -1;
	}
}

%%

void doNothing(){
	return;
}