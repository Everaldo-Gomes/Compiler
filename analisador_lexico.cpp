#include <bits/stdc++.h>
#include "analisador_lexico.h"
using namespace std;


Analizador_lexico::Analizador_lexico(string matriz_automato[LINHA][COLUNA], string identificador_tokens[QNT_SIMBOLO]) {

	// Faz uma cópia da matriz_automato para uma chamada "automato"
	// para poder ser usada pelo analizador lexico
	
	for(int i = 0; i < LINHA; i++) {
        for(int j = 0; j < COLUNA; j++) {
			automato[i][j] = matriz_automato[i][j];
        }
	}

	// Faz uma cópia dos identificadores (nomes e IDs)
	
	for(int i = 0; i < QNT_SIMBOLO; i++) {
		identificadores[i] = identificador_tokens[i];
	}

	analise_lexica();
}


void Analizador_lexico::analise_lexica() {

	FILE* arquivo = fopen("./programa.txt","rt");

	char linha[20];  //cada linha do arquivo
	char tokens[20]; //faz um loop na string de cada linha (letra por letra)
	
	while(fgets(linha, 20, arquivo)) {
		
		sscanf(linha, "%s", tokens); //copia conteúdo da linha para o "tokens"
		strcpy(tokens,linha); //ajuste
		
		short tamanho_token = strlen(tokens);
		
		for (int i = 0; i < tamanho_token; i++) {
			
			// lexico aqui
		}
	}

	fclose(arquivo);
}






