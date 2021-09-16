#include <bits/stdc++.h>
#include "analisador_lexico.h"
using namespace std;

// fazer
// exibir lista erro e fita saida


Analizador_lexico::Analizador_lexico(string matriz_automato[LINHA][COLUNA], string identificador_tokens[QNT_SIMBOLO]) {

	// Faz uma cópia da matriz_automato para uma chamada "automato"
	// para poder ser usada pelo analizador lexico
	
	for(int i = 0; i < LINHA; i++) {
        for(int j = 0; j < COLUNA; j++) {
			automato[i][j] = matriz_automato[i][j];
        }
	}

	// Faz uma cópia dos identificadores (nomes e IDs)
	
	for(int i = 0; i < QNT_SIMBOLO; i++) {
		identificadores[i] = identificador_tokens[i];
	}

	analise_lexica();
}


void Analizador_lexico::analise_lexica() {

	FILE* arquivo = fopen("./programa.txt","rt");

	char linha[20];  //cada linha do arquivo
	char tokens[20]; //faz um loop na string de cada linha (letra por letra)
	short contador_linha = 1;
	short contador_fita_saida = 0;
	short contador_fita_erro = 0;
	string estado_corrente = ESTADO_INICIAL;

	while(fgets(linha, 20, arquivo)) {
		
		sscanf(linha, "%s", tokens); //copia conteúdo da linha para o "tokens"
		strcpy(tokens,linha); //ajuste
		
		short tamanho_token = strlen(tokens);
		string token_atual = ""; //usada para mostrar o erro

		//percorre a linha lida
		for (int i = 0; i < tamanho_token; i++) {

			string caracter_atual(1, tokens[i]);
			token_atual += caracter_atual;
			
			// procurar na matriz a posição do caracter e estado
			short posicao_caracter_coluna = retorna_coluna_simbolo(caracter_atual);
			short posicao_estado_linha = retorna_linha_estado(estado_corrente);
			
			//chegou final do token
			if (caracter_atual != " " && caracter_atual != "\t" && caracter_atual != "\n") {

				//confere se o estado tem virgula (mais de uma transição por um token)
				size_t found = estado_corrente.find(",");

				// quando se tem mais de um estado
				if (found != string::npos) {
				    	
					string estado = "";

					//separa os estados que tem vírgula, Ex: I,N verifica o I e depois o N
					for (int j = 0; j < estado_corrente.size(); j++) {

						//pega todo o estado Ex AA...., e para na virgula
						if (estado_corrente[j] != ',') {
							estado += estado_corrente[j];
						}

						// se chegou na vírgula ou no final do estado foi porque
						// encontrou um estado
						if (estado_corrente[j] == ',' || j == estado_corrente.size()-1) {

							// vê se o token atual possui uma transição por alguma dos
							// estados encontrados
							string ss(1, linha[i]);

							// encontra posicao automato do estado de erro ou aceitação
							short cl = retorna_coluna_simbolo(ss);
							short li = retorna_linha_estado(estado);

							// é estado correto para seguir para outro estado
							if (automato[li][cl] != "$") {
								estado_corrente = automato[li][cl];
								break;
							}
							
							estado = "";
						}
					}
				}
				else {

					//quando uma transiacao por S tem apenas uma
					estado_corrente = automato[posicao_estado_linha][posicao_caracter_coluna];
				}
			}

			// verifica aceitação do token (se é separador ou não)

			if (caracter_atual == " " || caracter_atual == "\n") {
				
				// se for aceiteação, adiciona na fita de saída
				if (verifica_estado_aceitacao(estado_corrente)) {
					fita_saida[contador_fita_saida] = estado_corrente;
				}

				//caso de erro
				else { 
					
					fita_saida[contador_fita_saida] = sinal_erro;
					fita_erro[contador_fita_erro].append("Error na linha " + to_string(contador_linha) + " próximo à " + token_atual);
					contador_fita_erro++;
					token_atual = "";
				}
				
				contador_fita_saida++;
			    
				// alterar o estado corrente pra S
				estado_corrente = ESTADO_INICIAL;
			}
		}
		contador_linha++;
	}

	fclose(arquivo);
}


short Analizador_lexico::retorna_coluna_simbolo(string s) {

	short posicao = -1;
	
	for (int i = 1; i < COLUNA; i++) {
		if (automato[0][i] == s) {
			posicao = i;
			break;
		}
	}

	return posicao;
}


short Analizador_lexico::retorna_linha_estado(string s) {

	short posicao = -1;
	
	for (int i = 1; i < LINHA; i++) {

		string aux;
		aux.append(s + "*");
		
		if (automato[i][0] == s || automato[i][0] == aux) {
			posicao = i;
			break;
		}
	}

	return posicao;
}

short Analizador_lexico::verifica_estado_aceitacao(string s) {

	short eh_aceitacao = 0;
	
	for (int i = 1; i < LINHA; i++) {

		string aux;
		aux.append(s + "*");
		
		if (automato[i][0] == aux) {
			eh_aceitacao = 1;
			break;
		}
	}

	return eh_aceitacao;
}
