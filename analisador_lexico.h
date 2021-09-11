#ifndef ANALISADOR_LEXICO_H
#define ANALISADOR_LEXICO_H

#include <bits/stdc++.h>
#include "func.h"

#define ESTADO_INICIAL "S"

using namespace std;

class Analizador_lexico : public Objeto_base {

public:
	
	Analizador_lexico(string matriz_automato[LINHA][COLUNA], string identificador_tokens[QNT_SIMBOLO]);

private:

	string fita_saida[100]; //MUDAR DEPOIS
	string fita_erro[100];
	string automato[LINHA][COLUNA];
	string identificadores[QNT_SIMBOLO];
	short retorna_coluna_simbolo(string s);
	short retorna_linha_estado(string s);
	short verifica_estado_aceitacao(string s);
	
	void analise_lexica(); // executa o algorítimo de análise léxica
};


#endif
