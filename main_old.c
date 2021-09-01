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

/* gera o automato */
void gerar_matriz_automato_estados() {

	/* com problemas precisa consertar */
	//s.push_back(c); std::cout << s << std::endl;
	/* preenche a 1ª linha da matriz */
	for(int i = 1; i < COLUNA; i++) {
		//printf("-%s-", (char[2]){simbolos[i-1], 0});
		//char *p1 = simbolos;  
		//printf("%c", p1[i-1]);
		//matriz_automato[0][i] = p1[i-1];
	}
	matriz_automato[0][0] = " ";
	matriz_automato[1][0] = "S";

	/* passando valores manualmente mas precisa-se passa no loop anterior */
	matriz_automato[0][1] = "s";
	matriz_automato[0][2] = "f";
	matriz_automato[0][3] = "i";
	matriz_automato[0][4] = "n";
	matriz_automato[0][5] = "q";
	matriz_automato[0][6] = "m";
	matriz_automato[0][7] = "a";
	matriz_automato[0][8] = "+";
	matriz_automato[0][9] = "-";
	matriz_automato[0][10] = "*";
	matriz_automato[0][11] = "/";
	matriz_automato[0][12] = "=";


	/* adiciona os estados ao autômato */
	FILE* arquivo = fopen("./arquivo.txt","rt");

	char linha[5];
	char tokens[5];

	while(fgets(linha, 5, arquivo)) {

		sscanf(linha, "%s", tokens);

		for (int i = 0; i < strlen(tokens); i++) {
			
			/* se for o 1º caracter do token, deve-se gerar uma transição pelo estado S */
			if (i == 0) {

				//short p = retorna_coluna_simbolo((char[2]){tokens[i], 0});
				//printf("%c ", (char[2]){tokens[i], 0});
				//printf("%d <----\n", p);
				//matriz_automato[1][p];
			}
		}
	}

	fclose(arquivo);
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
 
