#include <bits/stdc++.h>
#include "gerador_LALR.h"
using namespace std;

// construtor
Gerador_LALR::Gerador_LALR(string fita_saida_lexica[TAMANHO_FITA_SAIDA]) {
	cout << "G L\n";
	gerar_cabecalho_LALR();
	gerar_carga_tabela_LALR();

}

void Gerador_LALR::gerar_cabecalho_LALR() {
	cout << "Gerar cabeçalho\n";
	FILE* arquivo = fopen("./acao_transicao.txt","rt");

	char linha[121];
	    
	while(fgets(linha, 121, arquivo)) {

		char item[20];

		sscanf(linha, "%s", item);
		cout << item << "\n";
	
	}
	
	fclose(arquivo);
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





