#include <bits/stdc++.h>
#include "analisador_sintatico.h"

using namespace std;

// construtor
Analisador_sintatico::Analisador_sintatico(string fita_saida[TAMANHO_FITA_SAIDA],
										   string identificador_linha_aux[QNT_SIMBOLO]) {
	
	// cria o obj que vai comandar a tabela LALR
	gerar_LALR = new Gerador_LALR(fita_saida);
	
	gerar_LALR->exibir_LARL();

	// Faz uma cópia da fita da análise lexica para o array fita_siada_analise_lexica
	for(int i = 0; i < TAMANHO_FITA_SAIDA; i++) {
		fita[i] = fita_saida[i];    
	}

	// Faz uma cópia dos identificadores (nomes e IDs)
	for(int i = 0; i < QNT_SIMBOLO; i++) {
		identificadores[i] = identificador_linha_aux[i];
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
		
		// converte os IDs do linha_aux na fita de saida para inteiros
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
			reducao(acao_numero);	
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

// empilha apenas terminais
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

void Analisador_sintatico::reducao(int numero_acao) {

	//numero_acao = 6;  // LEMBRAR DE APAGAR !!

	cout << "Nome regra: " << nome_regra_producao(numero_acao) << "\n";
	cout << "tamanho regra: " << tamanho_producao(numero_acao) << "\n";
	
	int tamnanho_reducao = tamanho_producao(numero_acao) * 2;
	string nome_regra = nome_regra_producao(numero_acao);

	// reduz da pilha o valor do tamanho da produção * 2
	reduz_pilha(tamnanho_reducao);

	//retorna top_pilha
	short topo_pilha = stoi(top_pilha());  

	//encontrar estado da transicao usando o que está no topo da pilha e o nome da regra
	int coluna_transicao = gerar_LALR->encontrar_coluna_nao_terminal(nome_regra);

	//+1 porque 0 é o cabeçalho, string retornada do goldparset Ex: g10
	string transicao = gerar_LALR->LALR_transicao[topo_pilha+1][coluna_transicao]; 

	// empilhada o estado após reducao
	empilha_estado_apos_reducao(nome_regra, to_string(retorna_numero(transicao)));


	// cout << "TOPO pilha: " << topo_pilha <<"\n"
	// 	 <<"Transicao: " << coluna_transicao << "\n"
	// 	 << "Estado: " << transicao << "\n"
	// 	 << "Estado Int: " << retorna_numero(transicao);
}	

void Analisador_sintatico::empilha_estado_apos_reducao(string nome_regra, string estado) {

	// empilha a regra + o estado
	for (int i = 0; i < TAMANHO_PILHA; i++) {

		if (pilha[i] == ESPACO_LIVRE) {

			pilha[i] = nome_regra;

			//evitar segmantation fault
			if (i + 1 < TAMANHO_PILHA) {
				i++;
				pilha[i] = estado;
			}
			break;
		}
	}
}

void Analisador_sintatico::reduz_pilha(int tamnanho_reducao) {

	int quantidade_reduzida = 0;

	for (int i = TAMANHO_PILHA-1; i >= 0; i--) {

		if (pilha[i] != ESPACO_LIVRE) {

			pilha[i] = ESPACO_LIVRE;
			quantidade_reduzida++;
		}

		if (quantidade_reduzida == tamnanho_reducao) {
			break;
		}
	}
}

int Analisador_sintatico::tamanho_producao(int numero_regra) {

	FILE* arquivo = fopen("./txt/reducao.txt","rt");

	char linha[30]; 
	char linha_aux[30];
	string regra_atual = "";
	int contador_linha = 0, contador_espaco_vazio = 0, primeiro_igual = 0;

	while(fgets(linha, 30, arquivo)) {
		
		if (contador_linha == numero_regra) {

			sscanf(linha, "%s", linha_aux); //copia conteúdo da linha para o "linha_aux"
			strcpy(linha_aux,linha); //ajuste

			//percorre a linha lida
			for (int i = 0; linha_aux[i] != '\n'; i++) {
				
				if (linha[i] == '=') {
					primeiro_igual = 1;
				}

				if (primeiro_igual && linha_aux[i] == ' ') {
					contador_espaco_vazio++;
				}
			}
			
			break;
		}
		contador_linha++;
	}

	return contador_espaco_vazio;
}

string Analisador_sintatico::nome_regra_producao(int numero_regra) {

	FILE* arquivo = fopen("./txt/reducao.txt","rt");

	char linha[30]; 
	char linha_aux[30];
	string regra_atual = "";
	int contador_linha = 0;

	while(fgets(linha, 30, arquivo)) {
		
		if (contador_linha == numero_regra) {

			sscanf(linha, "%s", linha_aux); //copia conteúdo da linha para o "linha_aux"
			strcpy(linha_aux,linha); //ajuste
			
			

			//percorre a linha lida
			for (int i = 0; linha_aux[i] != ' '; i++) {
				
				string caracter_atual(1, linha_aux[i]);
				regra_atual += caracter_atual;
			}
			
			break;
		}
		contador_linha++;
	}

	return regra_atual;
}