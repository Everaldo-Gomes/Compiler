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

	
	
	void gerar_carga_tabela_LALR();
	void criar_tabela_transicao();
	void criar_tabela_acao();
	
};


#endif
