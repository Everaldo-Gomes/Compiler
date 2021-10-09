#include <bits/stdc++.h>
#include "analisador_sintatico.h"

using namespace std;

// construtor
Analisador_sintatico::Analisador_sintatico(string fita_saida[TAMANHO_FITA_SAIDA],
										   string identificador_tokens[QNT_SIMBOLO]) {
	
	// cria o obj que vai comandar a tabela LALR
	gerar_LALR = new Gerador_LALR(fita_saida);
	
	gerar_LALR->exibir_LARL();

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

			LALR_acao[i][j] = gerar_LALR->LALR_acao[i][j];
			LALR_transicao[i][j] = gerar_LALR->LALR_transicao[i][j];
		}
	}

	analise_sintatica();
}

// destrutor
Analisador_sintatico::~Analisador_sintatico() {
	
	delete gerar_LALR;
}

void Analisador_sintatico::analise_sintatica() {

	inicializar_pilha();
	
	int posicao_id = 0, topo_pilha = 0;
	string terminal;
	
	for(int i = 0; i < TAMANHO_FITA_SAIDA; i++) {
		
		// converte os IDs do tokens na fita de saida para inteiros
		if (fita[i] == "$") { break; }
		posicao_id = stoi(fita[i]); // recebe o próprio índice para encontrar o token na LALR
		
		//obtem o topo da pilha e o início da fita
		terminal = identificadores[posicao_id];
		topo_pilha = stoi(top_pilha());  

		string acao = encontrar_acao_LALR(terminal, topo_pilha);

		// interpretando a ação: empilhamento, redução ou aceite
		int acao_numero = retorna_numero(acao);
		
		if (acao[0] == 's') {     //empilhamento
			empilha(acao_numero);
		}
		else if (acao[0] == 'r') { //redução
			
		}
		else if (acao[0] == 'a') { //aceite

		}
		else { // erro
			
		}

		exibe_fita_saida();
		exibe_pilha();
	}
}

// retorna o top da pilha
string Analisador_sintatico::top_pilha() {

	string simbolo = "0";
	
	for (int i = TAMANHO_PILHA-1; i >= 0; i--) {

		if (pilha[i] != ESPACO_LIVRE) {

			simbolo = pilha[i];
			break;
		}
	}
	
	if (!isdigit(simbolo[0])) {
		simbolo = "0";
	}

	return simbolo;
}

void Analisador_sintatico::inicializar_pilha() {

	pilha[0] = ESTADO_INICIO;
	
	for(int i = 1; i < TAMANHO_PILHA; i++) {

		pilha[i] = ESPACO_LIVRE;
	}
}


string Analisador_sintatico::encontrar_acao_LALR(string terminal, int topo_pilha) {

	int coluna_LALR_acao = gerar_LALR->encontrar_coluna_terminal(terminal);


	//+1 porque 0 é o cabeçalho
	return LALR_acao[topo_pilha+1][coluna_LALR_acao];
}

int Analisador_sintatico::retorna_numero(string str) {

	if (str == "") return 0; //previne erro ao passar string vazia
	
	string retorno = "";
	
	for (int i = 0; i < (int)str.size(); i++) {

		if (isdigit(str[i])) {
			retorno += str[i];
		}
	}

	return stoi(retorno);
}


void Analisador_sintatico::exibe_fita_saida() {

	cout << "\n\nFITA SAIDA: \n";
	
	for (int i = 0; i < TAMANHO_FITA_SAIDA; i++) {

		if (fita[i] == "$") {
			cout << fita[i] << " ";
		}
		else if (fita[i] != ESPACO_LIVRE && fita[i] != "") {
			cout << retorna_numero(fita[i]) + 1 << " ";
		}
	}
	cout << "\n\n";
}

void Analisador_sintatico::exibe_pilha() {

	cout << "\n\nPILHA: \n";

	for (int i = 0; i < TAMANHO_PILHA; i++) {
		
		if (pilha[i] != ESPACO_LIVRE && pilha[i] != "") {
			cout << retorna_numero(pilha[i]) << " ";
		}
	}
	cout << "\n\n";
}

void Analisador_sintatico::empilha(int acao) {

	string terminal_a_ser_empilhado = ESPACO_LIVRE;
	
	// remove o terminal da fita
	for (int i = 0; i < TAMANHO_FITA_SAIDA; i++) {

		if (fita[i] != ESPACO_LIVRE) {

			terminal_a_ser_empilhado = fita[i];
			fita[i] = ESPACO_LIVRE;
			break;
		}
	}
	
	// empilha o terminal + o número da ação
	for (int i = 0; i < TAMANHO_PILHA; i++) {

		if (pilha[i] == ESPACO_LIVRE) {

			pilha[i] = terminal_a_ser_empilhado;

			//evitar segmantation fault
			if (i + 1 < TAMANHO_PILHA) {
				i++;
				pilha[i] = to_string(acao);
			}
			break;
		}
	}
}
