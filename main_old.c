// #include <stdio.h>
// #include <stdlib.h>
// #include <ctype.h>
// #include <string.h>
#include "func.h"

#define QNT_SIMBOLO 30
#define LINHA 3
#define COLUNA 13

char simbolos[QNT_SIMBOLO];
char *matriz_automato[LINHA][COLUNA];	
void gerar_simbolo_token();
void gerar_simbolo_glc();
void gerar_matriz_automato_estados();
int retorna_coluna_simbolo(char *s);

short n = 0;

int main () {

	/* inicializa a matriz_automato */
	for(int i = 0; i < LINHA; i++) {
        for(int j = 0; j < COLUNA; j++) {
            matriz_automato[i][j] = "-";
        }
	}

	gerar_simbolo_token();
	gerar_matriz_automato_estados();
	//gerar_simbolo_glc();


	/* mostra a matriz automato */
	for(int i = 0; i < LINHA; i++) {
        for(int j = 0; j < COLUNA; j++) {
			printf("%s  ", matriz_automato[i][j]);
        }
		printf("\n");
	}
    
	printf("\n\n");
	return 0;
}


/* encontra todos os caracteres dos tokens */
void gerar_simbolo_token() {

	FILE* arquivo = fopen("arquivo.txt", "r");
	char ch;
	
	while ((ch = fgetc(arquivo)) != EOF) {

		if (ch == '<') { break; }
		if ((ch != '\n' && ch != ' ')) {
			
			/* procura se o simbolo já existe no array */
			int salva_novo_estado = 1;
				
			for (int i = 0; i < n; i++) {
				if (simbolos[i] == ch) {
					salva_novo_estado = 0;
					break;
				}
			}

			/* salva o simbolo se não existir no array */
			if (salva_novo_estado) {
				simbolos[n] = ch;
				n++;
			}
		}
	}

	fclose(arquivo);
}


void gerar_simbolo_glc() {

	FILE* arquivo = fopen("arquivo.txt", "r");
	short int comeca_glc = 0;
	char ch;
	
	while ((ch = fgetc(arquivo)) != EOF) {

		if (ch == '<') { comeca_glc = 1; }
		
		if ((comeca_glc && islower(ch)) || isdigit(ch)) {
			
			/* procura se o simbolo já existe no array */
			int salva_novo_estado = 1;
				
			for (int i = 0; i < n; i++) { 
				if (simbolos[i] == ch) {
					salva_novo_estado = 0;
					break;
				}
			}

			/* salva o simbolo se não existir no array */
			if (salva_novo_estado) {
				simbolos[n] = ch;
				n++;
			}
		}
	}
    
	fclose(arquivo);	
}

int retorna_coluna_simbolo(char *s) {

	short posicao = -1;
	
	for (int i = 1; i < COLUNA; i++) {
		if (matriz_automato[0][i] == s) {
			posicao = i;
			break;
		}
	}

	return posicao;
}



string getString(char x)
{
    // string class has a constructor
    // that allows us to specify size of
    // string as first parameter and character
    // to be filled in given size as second
    // parameter.
    string s(1, x);
 
    return s;  
}
 
