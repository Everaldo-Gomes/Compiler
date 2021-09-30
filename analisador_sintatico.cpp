#include <bits/stdc++.h>
#include "analisador_sintatico.h"
#include "gerador_LALR.h"

using namespace std;

// construtor
Analisador_sintatico::Analisador_sintatico(string fita_saida[TAMANHO_FITA_SAIDA]) {
	
	// cria o obj que vai comandar a tabela LALR
	Gerador_LALR gerar_LALR(fita_saida);
}



