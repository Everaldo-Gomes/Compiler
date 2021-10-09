#ifndef ANALISADOR_SINTATICO_H
#define ANALISADOR_SINTATICO_H
#define TAMANHO_PILHA 100
#define ESPACO_LIVRE "-1"
#define ESTADO_INICIO "0"


#include <bits/stdc++.h>
#include "func.h"
#include "gerador_LALR.h"

using namespace std;

class Analisador_sintatico : public Objeto_base {

public:

	Analisador_sintatico(string fita_saida[TAMANHO_FITA_SAIDA], string identificador_tokens[QNT_SIMBOLO]);
	~Analisador_sintatico();
	
	
private:

	Gerador_LALR *gerar_LALR;
	
	// fita que vem da análise léxica
	string fita[TAMANHO_FITA_SAIDA];
	string identificadores[QNT_SIMBOLO];

	string LALR_acao[TAMANHO_LINHA_TAB_LALR][TAMANHO_COLUNA_TAB_LALR];
	string LALR_transicao[TAMANHO_LINHA_TAB_LALR][TAMANHO_COLUNA_TAB_LALR];
	string pilha[TAMANHO_PILHA];
	
	void inicializar_pilha();
	void analise_sintatica();

	string top_pilha();
	string encontrar_acao_LALR(string, int);

	int retorna_numero(string str);
	void exibe_fita_saida();
	void exibe_pilha();
	void empilha(int acao);
	void reducao(int);
	int tamanho_producao(int);
	string nome_regra_producao(int);
	void reduz_pilha(int tamnanho_reducao);
	void empilha_estado_apos_reducao(string nome_regra, string estado);
};


#endif
