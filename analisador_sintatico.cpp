#include <bits/stdc++.h>
#include "analisador_sintatico.h"
#include "gerador_LALR.h"

using namespace std;

// construtor
Analisador_sintatico::Analisador_sintatico(string fita_saida[TAMANHO_FITA_SAIDA],
										   string identificador_tokens[QNT_SIMBOLO]) {
	
	// cria o obj que vai comandar a tabela LALR
	Gerador_LALR gerar_LALR(fita_saida);

	//gerar_LALR.exibir_LARL();

	// Faz uma cópia da fita da análise lexica para o array fita_siada_analise_lexica
	for(int i = 0; i < TAMANHO_FITA_SAIDA; i++) {
		fita[i] = fita_saida[i];    
	}

	// Faz uma cópia dos identificadores (nomes e IDs)
	for(int i = 0; i < QNT_SIMBOLO; i++) {
		identificadores[i] = identificador_tokens[i];
	}

	// Faz uma cópia da tabela LALR (transiação e ação)
	for(int i = 0; i < TAMANHO_LINHA_TAB_LALR; i++) {
		for(int j = 0; j < TAMANHO_COLUNA_TAB_LALR; j++) {

			LALR_acao[i][j] = gerar_LALR.LALR_acao[i][j];
			LALR_transicao[i][j] = gerar_LALR.LALR_transicao[i][j];
		}
	}

	analise_sintatica();
}


void Analisador_sintatico::analise_sintatica() {

	int posicao_id = 0, estado_LALR = 0, coluna_LALR = 0;
	
	for(int i = 0; i < TAMANHO_FITA_SAIDA; i++) {
		
		// converte os IDs do tokens na fita de saida para inteiros
		if (fita[i] == "$") { break; }
		posicao_id = stoi(fita[i]);

		// retorna o top da pilha
		
	}
}

string Analisador_sintatico::top_pilha() {

	// fazendo...
	
}

void Analisador_sintatico::inicializar_pilha() {

	pilha[0] = ESTADO_INICIO;
	
	for(int i = 1; i < TAMANHO_PILHA; i++) {

		pilha[i] = ESPACO_LIVRE;
	}
}


