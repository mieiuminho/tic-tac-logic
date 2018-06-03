#ifndef ___CGI_H___
#define ___CGI_H___
#include <stdio.h>

/**
@file cgi.h
Macros úteis para gerar CGIs
*/

/**
* Caminho para as imagens
*/
#define IMAGE_PATH "http://localhost/images/"

/**
* Caminho para os tabuleiros
*/
#define TAB_PATH "/var/www/html/tabuleiros/"

/**
* Pergunta ao usuário o seu nome e coloca-o no link
*/
#define ASK_USER printf("<script>user_name = prompt(\"Escreva o seu nome ou jogue como convidado.\"); if(user_name!=null && user_name !=\"\"){ window.open('http://localhost/cgi-bin/GandaGalo?' + user_name, '_self')};</script>\n")

/**
\brief Macro para começar o html
*/
#define COMECAR_HTML printf("Content-Type: text/html\n\n<html>\n<title>GandaGalo</title>\n")

/**
\brief Macro para abrir um svg
@param tamx O comprimento do svg
@param tamy A altura do svg
@param color A cor de fundo do svg
*/
#define ABRIR_SVG(tamx, tamy, color) printf("<svg width=%d height=%d style='background: %s'>\n", tamx, tamy, color)

/**
\brief Macro para fechar um svg
*/
#define FECHAR_SVG printf("</svg>\n")

/**
\brief Macro para criar uma imagem
@param X A coordenada X do canto superior esquerdo
@param Y A coordenada Y do canto superior esquerdo
@param ESCALA A escala da imagem
@param FICHEIRO O caminho para o link do ficheiro
@param PATH Diretoria onde se podem encontrar as imagens
*/
#define IMAGEM(X, Y, ESCALA, FICHEIRO, PATH)		printf("<image x=%d y=%d width=%d height=%d xlink:href=%s%s />\n", \
												ESCALA * X, ESCALA * Y, ESCALA, ESCALA, PATH, FICHEIRO)

/**
\brief Macro para criar uma imagem usando valores absolutos
@param X A coordenada X do canto superior esquerdo
@param Y A coordenada Y do canto superior esquerdo
@param ESCALA_X A escala da imagem segundo o X
@param ESCALA_Y A escala da imagem segundo o Y
@param FICHEIRO O caminho para o link do ficheiro
@param PATH Diretoria onde se podem encontrar as imagens
*/
#define IMAGEM_ABS(X, Y, ESCALA_X, ESCALA_Y, FICHEIRO, PATH)		printf("<image x=%d y=%d width=%d height=%d xlink:href=%s%s />\n", \
												X, Y, ESCALA_X, ESCALA_Y, PATH, FICHEIRO)

/**
\brief Macro para escrever Tabuleiro N
@param X A coordenada X do canto superior esquerdo
@param Y A coordenada Y do canto superior esquerdo
@param COR Cor do texto
@param N O número do tabuleiro correspondente
*/
#define TEXTO(X, Y, COR, N) printf("<text x=%d y=%d fill=%s>Tabuleiro %d</text>\n", X, Y, COR, N)

/**
\brief Macro para criar um quadrado
@param X A coordenada X do canto superior esquerdo
@param Y A coordenada Y do canto superior esquerdo
@param ESCALA A escala do quadrado
@param COR A cor de preenchimento do quadrado
*/
#define QUADRADO(X, Y, ESCALA, COR)			printf("<rect x=%d y=%d width=%d height=%d fill=%s />\n", \
												ESCALA * X, ESCALA* Y, ESCALA, ESCALA, COR)

/**
\brief Macro para abrir um link
@param link O caminho para o link
*/
#define ABRIR_LINK(link)					printf("<a xlink:href=%s>\n", link)

/**
\brief Macro para abrir uma acção
@param link O caminho para o acção
*/
#define ABRIR_LINK_ABS(link)				printf("<a xlink:href=http://localhost/cgi-bin/GandaGalo?%s>\n", link)

/**
\brief Macro para fechar o link
*/
#define FECHAR_LINK							printf("</a>\n")

/**
\brief Macro para fechar o HTML
*/
#define FECHAR_HTML							printf("</html>\n")

#endif
