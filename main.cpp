#include <bits/stdc++.h>
#include "gerador_automato.h"
#include "analisador_lexico.h"
using namespace std;


int main () {
	
	// quando é instanciado, tem um contructor que já chama todas as funções necessárias
	// para criar o autômato.
	Gerador_automato Automato;


	// Análise lexica da linguagem
	Analizador_lexico Analize_lexica(Automato.matriz_automato, Automato.identificador_tokens);
    
    
	return 0;
}

