#ifndef ANALISADOR_LEXICO_H
#define ANALISADOR_LEXICO_H

#define ESTADO_INICIAL "S"

#include <bits/stdc++.h>
#include "func.h"
using namespace std;

class Analizador_lexico : public Objeto_base {

public:
	
	Analizador_lexico(string matriz_automato[LINHA][COLUNA], string identificador_tokens[QNT_SIMBOLO]);	
	string fita_saida[TAMANHO_FITA_SAIDA];
	
private:

	string fita_erro[TAMANHO_FITA_SAIDA]; //fazer o detalhamento
	string automato[LINHA][COLUNA];
	string identificadores[QNT_SIMBOLO];

	short retorna_coluna_simbolo(string s);
	short retorna_linha_estado(string s);
	short verifica_estado_aceitacao(string s);
	void exibir_fita_saida();
	void exibir_fita_erro();
	short retorna_id_token(string s);
	void analise_lexica(); // executa o algorítimo de análise léxica
};


#endif
