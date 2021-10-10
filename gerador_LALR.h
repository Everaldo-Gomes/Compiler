#ifndef GERADOR_LALR_H
#define GERADOR_LALR_H

#include <bits/stdc++.h>
#include "func.h"

using namespace std;

class Gerador_LALR : public Objeto_base {

public:

	Gerador_LALR(string fita_saida_lexica[TAMANHO_FITA_SAIDA]);
	string fita_saida[TAMANHO_FITA_SAIDA];
	string LALR_acao[TAMANHO_LINHA_TAB_LALR][TAMANHO_COLUNA_TAB_LALR];
	string LALR_transicao[TAMANHO_LINHA_TAB_LALR][TAMANHO_COLUNA_TAB_LALR];
	
	void gerar_cabecalho_LALR();
	void exibir_LARL();
	int encontrar_coluna_terminal(string terminal);
	short encontrar_coluna_nao_terminal(string nao_terminal);

private:

    
protected:
	
	void exibir_cabecalho_acao_LALR();
	void exibir_cabecalho_transicao_LALR();
	void exibir_corpo_acao_LALR();
	void exibir_corpo_transicao_LALR();
	void gerar_carga_tabela_LALR();
	void criar_tabela_transicao(string term_ou_nao_term, string acao, string estado, int estado_atual);
	void criar_tabela_acao(string term_ou_nao_term, string acao, string estado, int estado_atual);	
};


#endif
