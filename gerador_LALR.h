#ifndef GERADOR_LALR_H
#define GERADOR_LALR_H

#include <bits/stdc++.h>
#include "func.h"

using namespace std;

class Gerador_LALR : public Objeto_base {

public:

	Gerador_LALR(string fita_saida_lexica[TAMANHO_FITA_SAIDA]);
	void gerar_cabecalho_LALR();
	string fita_saida[TAMANHO_FITA_SAIDA];
	
private:

	string LALR_acao[TAMANHO_LINHA_TAB_LALR][TAMANHO_COLUNA_TAB_LALR];
	string LALR_transicao[TAMANHO_LINHA_TAB_LALR][TAMANHO_COLUNA_TAB_LALR];

	void exibir_cabecalho_LALR();
	void exibir_corpo_LALR();
	void gerar_carga_tabela_LALR();
	void criar_tabela_transicao(string term_ou_nao_term, string acao, string estado, int estado_atual);
	void criar_tabela_acao(string term_ou_nao_term, string acao, string estado, int estado_atual);
	int encontrar_coluna_terminal(string terminal);
	short encontrar_coluna_nao_terminal(string nao_terminal);
	
};


#endif
