#ifndef GERADOR_AUTOMATO_H
#define GERADOR_AUTOMATO_H

#include <bits/stdc++.h>
#include "func.h"

using namespace std;


class Gerador_automato : public Objeto_base {
	
public:

	Gerador_automato();
	string matriz_automato[LINHA][COLUNA];
	string identificador_tokens[QNT_SIMBOLO];
	string identificador_tokens_goldparser[QNT_SIMBOLO];

private:

	/* métodos */
	void criar_matriz();
	string simbolos[QNT_SIMBOLO];
	void gerar_simbolo_token();
	void gerar_simbolo_glc();
	void gerar_matriz_automato_estados_tokens();
	void gerar_matriz_automato_estados_GLC();
	int retorna_coluna_simbolo(string);
	void adicionar_estado_erro();
	void cria_cabecalho_automato();
	void criar_identificadores_tokens_goldparser();

	/* variáveis */
	short coluna_livre_automato = 0;
	short linha_livre_automato = 0;
	char estado = 'A';
	short contador_id_tokens = 0;
};


#endif
