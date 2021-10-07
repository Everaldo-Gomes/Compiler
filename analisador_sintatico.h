#ifndef ANALISADOR_SINTATICO_H
#define ANALISADOR_SINTATICO_H
#define TAMANHO_PILHA 100
#define ESPACO_LIVRE "-1"
#define ESTADO_INICIO "0"


#include <bits/stdc++.h>
#include "func.h"

using namespace std;

class Analisador_sintatico : public Objeto_base {

public:

	Analisador_sintatico(string fita_saida[TAMANHO_FITA_SAIDA], string identificador_tokens[QNT_SIMBOLO]);

	
	
private:
	
	// fita que vem da análise léxica
	string fita[TAMANHO_FITA_SAIDA];
	string identificadores[QNT_SIMBOLO];

	string LALR_acao[TAMANHO_LINHA_TAB_LALR][TAMANHO_COLUNA_TAB_LALR];
	string LALR_transicao[TAMANHO_LINHA_TAB_LALR][TAMANHO_COLUNA_TAB_LALR];
	string pilha[TAMANHO_PILHA];
	
	void inicializar_pilha();
	void analise_sintatica();
	
};


#endif
