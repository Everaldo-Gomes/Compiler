#include <bits/stdc++.h>
#include <cctype>
//#include <cstring>
#include "gerador_LALR.h"
#include <boost/algorithm/string.hpp>
using namespace boost::algorithm;
using namespace std;

// construtor
Gerador_LALR::Gerador_LALR(string fita_saida_lexica[TAMANHO_FITA_SAIDA]) {
	
	gerar_cabecalho_LALR();
	gerar_carga_tabela_LALR();

	cout << "Tabela LALR\n\n";
	exibir_cabecalho_LALR();
	exibir_corpo_LALR();
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
}


//lê o arquivo e preenche as os arrays (tabela de ação e transição)
void Gerador_LALR::gerar_carga_tabela_LALR() {

	FILE* arquivo = fopen("./LALR.txt","rt");

	char linha[20];
	
	//terminal ou não terminal
	char term_ou_nao_term[5], acao[2];//, estado[5];
	int estado, estado_atual = 0;
	string str_term_ou_nao_term, str_acao, str_estado, str_estado_atual;
	
	while(fgets(linha, 20, arquivo)) {

		memset(term_ou_nao_term, '\0', 5);
		memset(acao, '\0', 2);
	    
		sscanf(linha, "%s %s %d", term_ou_nao_term, acao, &estado);

		// converte valores lidos para string
		str_term_ou_nao_term = convertToString(term_ou_nao_term);
		str_acao = convertToString(acao);
		str_estado = to_string(estado);
		
		// se no arquivo lido achar a palavra "State"
		if (str_equal(str_term_ou_nao_term, "State")) {

			estado_atual = estado; 
		}
		else {

			// inseri no array transicao
			if (isupper(term_ou_nao_term[0])) {
				//if (islower(term_ou_nao_term[0]) || isdigit(term_ou_nao_term[0])) {
				criar_tabela_transicao(str_term_ou_nao_term, str_acao, str_estado, estado_atual);
			}
			
			// inseri no array acao_transicao
			else {
				//cout << "----> "<< str_term_ou_nao_term << endl;
				if (estado_atual == -1) cout << "Estado -1\n";
				criar_tabela_acao(str_term_ou_nao_term, str_acao, str_estado, estado_atual);
			}		   
		}
	}
	
	fclose(arquivo);
}

// criar tabela de ações
void Gerador_LALR::criar_tabela_acao(string term_ou_nao_term, string acao, string estado, int estado_atual) {
	
	// +1 porque na posição 0 está o cabeçalho da tabela
	int estado_insercao = estado_atual + 1;
	string str_estado_atual = to_string(estado_atual);
    
	LALR_acao[estado_insercao][0] = str_estado_atual;
	
	// encontrar a coluna que está o term_ou_nao_term
	int coluna_terminal = encontrar_coluna_terminal(term_ou_nao_term);

	LALR_acao[estado_insercao][coluna_terminal].clear();

    // acao a ser realizada	
	LALR_acao[estado_insercao][coluna_terminal] = acao + estado;
	
	// cout << "linha: " << estado_insercao << "\n"
	// 	 << "coluna: " << coluna_terminal << "\n"
	// 	 << LALR_acao[estado_insercao][coluna_terminal] << endl;

	exibir_cabecalho_LALR();
	
}

// criar tabela de transição
void Gerador_LALR::criar_tabela_transicao(string term_ou_nao_term, string acao, string estado, int estado_atual) {
	
	// +1 porque na posição 0 está o cabeçalho da tabela
	short estado_insercao = estado_atual + 1;
	string str_estado_atual = to_string(estado_atual);
    
	//LALR_transicao[estado_insercao][0] = str_estado_atual;
	
	// encontrar a coluna que está o term_ou_nao_term
	short coluna_nao_terminal = encontrar_coluna_nao_terminal(term_ou_nao_term);
	//if (coluna_nao_terminal == -1) return;
	
	//cout << "Token: " << term_ou_nao_term << endl;
	// acao a ser realizada
	LALR_transicao[estado_insercao][coluna_nao_terminal] = acao + estado;
	
	// cout << "linha: " << estado_insercao-1 << "\n"
	// 	 << "coluna: " << coluna_nao_terminal << "\n"
	// 	 << LALR_transicao[estado_insercao][coluna_nao_terminal] << endl;
	
}


void Gerador_LALR::exibir_cabecalho_LALR() {

	short len_acao = sizeof(LALR_acao) / sizeof(LALR_acao[0]);
	short len_tran = sizeof(LALR_transicao) / sizeof(LALR_transicao[0]);

	//for (int i = len_acao-1; i >= 0; i--) {
	for (int i = 0; i < len_acao; i++) {

		if (LALR_acao[0][i] != "") {
			cout.width(10);
			cout << LALR_acao[0][i];
		}
	}
	
	// for (int i = 0; i < len_tran; i++) {

	// 	if (LALR_transicao[0][i] != "") {
	// 		cout.width(12);
	// 		cout << LALR_transicao[0][i];
	// 	}
	// }

	cout << "\n\n";
}

void Gerador_LALR::exibir_corpo_LALR() {

	short len_acao = sizeof(LALR_acao) / sizeof(LALR_acao[0]);
	short len_tran = sizeof(LALR_transicao) / sizeof(LALR_transicao[0]);

	
	for (int j = 1; j < 64; j++) {
		
		for (int i = 0; i < len_acao; i++) {
			//for (int i = len_acao-1; i >= 0; i--) {
		
			if (LALR_acao[j][i] != "") {
				cout << LALR_acao[j][i];
				cout.width(10);
			}
			else {
				//cout << " ";
			}
		}
	
		// for (int k = 0; k < len_tran; k++) {

		// 	if (LALR_transicao[j][k] != "") {
		// 		cout << LALR_transicao[j][k] << "   ";
		// 	}
		// 	else {
		// 		cout << " ";
		// 	}
		// }
		cout << "\n";
	}

	cout << "\n\n";
}


int Gerador_LALR::encontrar_coluna_terminal(string terminal) {

	int len_acao = sizeof(LALR_acao) / sizeof(LALR_acao[0]);
 
	int posicao = -1;
	
	for (int i = 0; i < len_acao; i++) {

		if (str_equal(LALR_acao[0][i], terminal)) {
			
			posicao = i;
			break;
		}
	}

	return posicao;
}

short Gerador_LALR::encontrar_coluna_nao_terminal(string nao_terminal) {

	short len_transicao = sizeof(LALR_transicao) / sizeof(LALR_transicao[0]);

	short posicao = -1;
	
	for (int i = 0; i < len_transicao; i++) {

		if (str_equal(LALR_transicao[0][i], nao_terminal)) {
			
			posicao = i;
			break;
		}
	}

	return posicao;
}


