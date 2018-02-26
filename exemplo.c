/**
@file exemplo.c
Esqueleto do programa
*/

#include <stdlib.h>
#include <string.h>

#include "cgi.h"
#include "estado.h"

#define MAX_BUFFER		10240
#define GRELHA			4
#define TAM			40

/**
Função que inicializa o estado

Esta função está vazia

@returns Um novo estado
*/
ESTADO inicializar() {
	ESTADO e = {0};
	return e;
}

/**
Lê o estado a partir da variável de ambiente QUERY_STR. Caso não seja passado um valor, chama a função inicializar
@param args O valor da variável (o que é passado depois de ? no URL)
@returns O estado
*/
ESTADO ler_estado(char *args) {
	if(strlen(args) == 0)
		return inicializar();
	return str2estado(args);
}

/**
Função principal do programa
@returns 0 se tudo correr bem
*/
int main() {
	//ESTADO e = ler_estado(getenv("QUERY_STRING"));

	COMECAR_HTML;
	ABRIR_SVG(600, 600);

	IMAGEM(0,0,40, "vazio.png");
	IMAGEM(1,0,40, "bloq.png");
	IMAGEM(2,0,40, "vazio.png");
	IMAGEM(3,0,40, "X.png");
	IMAGEM(0,1,40, "vazio.png");
	IMAGEM(1,1,40, "O.png");
	IMAGEM(2,1,40, "vazio.png");
	IMAGEM(3,1,40, "vazio.png");
	IMAGEM(0,2,40, "X.png");
	IMAGEM(1,2,40, "vazio.png");
	IMAGEM(2,2,40, "vazio.png");
	IMAGEM(3,2,40, "vazio.png");
	IMAGEM(0,3,40, "vazio.png");
	IMAGEM(1,3,40, "vazio.png");
	IMAGEM(2,3,40, "vazio.png");
	IMAGEM(3,3,40, "O.png");

	ABRIR_LINK("http://localhost/cgi-bin/GandaGalo");
	IMAGEM(0, 4, 80, "novo.png");
	FECHAR_LINK;

	FECHAR_SVG;
	FECHAR_HTML;

	return 0;
}
