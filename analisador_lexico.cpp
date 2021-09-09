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
	short contador_linha = 1;
	string estado_inicial = "S";
	string estado_corrente = "S";

	while(fgets(linha, 20, arquivo)) {
		
		sscanf(linha, "%s", tokens); //copia conteúdo da linha para o "tokens"
		strcpy(tokens,linha); //ajuste
		
		short tamanho_token = strlen(tokens);
		string caracter_atual;
		
		for (int i = 0; i < tamanho_token; i++) {

			caracter_atual = tokens[i];

			// procurar na matriz a posição do caracter e estado
			short posicao_caracter_coluna = retorna_coluna_simbolo(caracter_atual);
			short posicao_estado_linha = retorna_linha_estado(estado_corrente);

			if (caracter_atual != " " && caracter_atual != "\t" && caracter_atual != "\n") {
				estado_corrente = automato[posicao_estado_linha][posicao_caracter_coluna];
				cout << caracter_atual << " " << estado_corrente << endl;
			}
			
			// verifica aceitação do token (se é separador ou não)

			if (caracter_atual == " ") {

				// se for aceiteação
				// adiciona na fita de saída

				//se for erro
				//adiciona o erro na fita

				// alterar o estado corrente pra S

				//criar a fita de saída aceite e erro
				
				cout << verifica_estado_aceitacao(estado_corrente) << " " << estado_corrente << endl;
			}
		}
	}

	fclose(arquivo);
}


short Analizador_lexico::retorna_coluna_simbolo(string s) {

	short posicao = -1;
	
	for (int i = 1; i < COLUNA; i++) {
		if (automato[0][i] == s) {
			posicao = i;
			break;
		}
	}

	return posicao;
}


short Analizador_lexico::retorna_linha_estado(string s) {

	short posicao = -1;
	
	for (int i = 1; i < LINHA; i++) {

		string aux;
		aux.append(s + "*");
		
		if (automato[i][0] == s || automato[i][0] == aux) {
			posicao = i;
			break;
		}
	}

	return posicao;
}

short Analizador_lexico::verifica_estado_aceitacao(string s) {

	short eh_aceitacao = 0;
	
	for (int i = 1; i < LINHA; i++) {

		string aux;
		aux.append(s + "*");
		
		if (automato[i][0] == aux) {
			eh_aceitacao = 1;
			break;
		}
	}

	return eh_aceitacao;
}
