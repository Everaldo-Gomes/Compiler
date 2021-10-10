#include <bits/stdc++.h>
#include "gerador_automato.h"
#include "analisador_lexico.h"
#include "analisador_sintatico.h"
using namespace std;


int main () {
	
	// quando é instanciado, tem um contructor que já chama todas as funções necessárias


	// para criar o autômato.
	Gerador_automato Automato;


	// Análise lexica da linguagem
	Analizador_lexico Analize_lexica(Automato.matriz_automato, Automato.identificador_tokens_goldparser);


	// Análise sintática da linguagem
    Analisador_sintatico Analise_sintatica(Analize_lexica.fita_saida, Automato.identificador_tokens_goldparser);

	return 0;
}

