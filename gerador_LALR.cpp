#include <bits/stdc++.h>
#include "gerador_LALR.h"
using namespace std;

// construtor
Gerador_LALR::Gerador_LALR(string fita_saida_lexica[TAMANHO_FITA_SAIDA]) {
	
	gerar_cabecalho_LALR();
	gerar_carga_tabela_LALR();

}

void Gerador_LALR::gerar_cabecalho_LALR() {

	FILE* arquivo = fopen("./acao_transicao.txt","rt");

	char linha[121];
	short terminal = 0, nao_terminal = 0, contador_coluna = 0;
	    
	while(fgets(linha, 121, arquivo)) {

		char item[20];
		char terminais[] = "terminais";
		char naoterminais[] = "naoterminais";
		sscanf(linha, "%s", item);


		// inseri cabeçalho array ação
		if (terminal) { 
			LALR_acao[0][++contador_coluna] = item;
		}

		// inseri cabeçalho array transiçãoi
		else if (nao_terminal) {
			LALR_transicao[0][++contador_coluna] = item;
		}

	    
		if (!strcmp(item,terminais)) {
			
			terminal = 1;
			nao_terminal = 0;
			contador_coluna = 0;
		}
		else if (!strcmp(item, naoterminais)) {

			// remover o nome "nao terminais da última posicao
			LALR_acao[0][contador_coluna] = " "; 
			
			terminal = 0;
			nao_terminal = 1;
			contador_coluna = 0;
		}
	}
	
	fclose(arquivo);


	
	short len_acao = sizeof(LALR_acao) / sizeof(LALR_acao[0]);
	short len_tran = sizeof(LALR_transicao) / sizeof(LALR_transicao[0]);
	
	for (int i = 0; i < len_acao; i++) {

		if (LALR_acao[0][i] != "") {
			cout << LALR_acao[0][i] << " ";
		}
	}


	
	for (int i = 0; i < len_tran; i++) {

		if (LALR_transicao[0][i] != "") {
			cout << LALR_transicao[0][i] << " ";
		}
	}

	cout << "\n\n";
}


//lê o arquivo e preenche as os arrays (tabela de ação e transição)
void Gerador_LALR::gerar_carga_tabela_LALR() {

	FILE* arquivo = fopen("./acao_transicao.txt","rt");

	char linha[121];
	    
	while(fgets(linha, 121, arquivo)) {

		
		// char ip[12];

		// sscanf(linha, "%d %d %s", &id, &porta, ip);
	
	}
	
	fclose(arquivo);
}

// criar tabela de transição
void Gerador_LALR::criar_tabela_transicao() {

	
	//LALR_transicao[TAMANHO_LINHA_TAB_LALR][TAMANHO_COLUNA_TAB_LALR];
}


// criar tabela de ações
void Gerador_LALR::criar_tabela_acao() {


	//LALR_acao[TAMANHO_LINHA_TAB_LALR][TAMANHO_COLUNA_TAB_LALR];
}





