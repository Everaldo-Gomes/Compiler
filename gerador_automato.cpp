#include<bits/stdc++.h>
#include "gerador_automato.h"
#include "func.h"

using namespace std;

Gerador_automato::Gerador_automato() {

	criar_matriz();

	// definindo os IDs dos identificadores de acordo com o GoldParser
	criar_identificadores_tokens_goldparser();
}

void Gerador_automato::criar_matriz() {

	/* inicializa a matriz_automato */
	for(int i = 0; i < LINHA; i++) {
        for(int j = 0; j < COLUNA; j++) {
            matriz_automato[i][j] = sinal_erro;
        }
	}
	
	gerar_simbolo_token();
	gerar_simbolo_glc();

	cria_cabecalho_automato();
	
	gerar_matriz_automato_estados_tokens();
	gerar_matriz_automato_estados_GLC();

	adicionar_estado_erro();

	
	/* mostra a matriz automato */
	for(int i = 0; i < LINHA; i++) {
        for(int j = 0; j < COLUNA; j++) {
			cout << matriz_automato[i][j] << "\t";
        }
		cout << "\n";
	}
}

void Gerador_automato::cria_cabecalho_automato() {

	// gera 1ª linha do autômoto
	for(int i = 1; i < COLUNA; i++) {
		matriz_automato[0][i] = simbolos[i-1];
	}
	
	matriz_automato[0][0] = " ";
	matriz_automato[1][0] = "S";
}

/* encontra todos os caracteres dos tokens */
void Gerador_automato::gerar_simbolo_token() {

	FILE* arquivo = fopen("./txt/arquivo.txt", "r");
	string ch;
	
	while (!feof(arquivo)) {

		ch = fgetc(arquivo);
		
		if (ch == "<") { break; }
		if ((ch != "\n" && ch != " ")) {
			
			/* procura se o simbolo já existe no array */
			int salva_novo_estado = 1;
				
			for (int i = 0; i < coluna_livre_automato; i++) {
				if (simbolos[i] == ch) {
					salva_novo_estado = 0;
					break;
				}
			}

			/* salva o simbolo se não existir no array */
			if (salva_novo_estado) {
				simbolos[coluna_livre_automato] = ch;
				coluna_livre_automato++;
			}
		}
	}

	fclose(arquivo);
}

void Gerador_automato::gerar_matriz_automato_estados_tokens() {

    
	/* adiciona os estados ao autômato */
	FILE* arquivo = fopen("./txt/arquivo.txt","rt");

	char linha[5];  //cada linha do arquivo
	char tokens[5]; //faz um loop na string de cada linha (letra por letra)

	//linha 0 -> espaço em branco da linha dos símbolos da linguagem
	//linha 1 -> "S estado inicial"
	short contador_linha_livre = 2;
	
	while(fgets(linha, 5, arquivo)) {

		sscanf(linha, "%s", tokens); //copia conteúdo da linha para o "tokens"

		// interromper leitura do arquivo quando chegar na GLC
		if (tokens[0] == '<') {
			break;
		}		
		
		short tamanho_token = strlen(tokens);
		string estado_anterior;
		short linha_estado_anterior = 0;


		for (int i = 0; i < tamanho_token; i++) {

			//converte char em string
			string s(1, tokens[i]); 
			string novo_estado(1, estado);
			short coluna = retorna_coluna_simbolo(s);
			
			/* se for o 1º caracter do token, deve-se gerar uma transição pelo estado S */
			if (i == 0) {

				// evitar os tracinhos ou vígulas em lugares indevidos
				if (matriz_automato[1][coluna] == sinal_erro) {
					matriz_automato[1][coluna] = "";	
				}

				if (matriz_automato[1][coluna].size() == 0) {
					matriz_automato[1][coluna].append(novo_estado);	
				}
				else {
					matriz_automato[1][coluna].append("," + novo_estado);
				}				
			}
			// faz a transição de um não terminal para um novo estado
			else {
				matriz_automato[linha_estado_anterior][coluna] = novo_estado;
			}
			
			estado_anterior = novo_estado;
			estado++;
			
			// pular o estado "S" porque já é usado como início
			if (estado == 'S') { estado++; }
			
			matriz_automato[contador_linha_livre][0] = estado_anterior;
			linha_estado_anterior = contador_linha_livre;
			contador_linha_livre++;
		}

		//diz qual vai ser a próxima linha no autômato a ser usada
		linha_livre_automato = contador_linha_livre;
		
		// reconhecou o token, e é um estado de aceitação
		matriz_automato[linha_estado_anterior][0].append("*");

		// define os IDs dos tokens
		identificador_tokens[++contador_id_tokens] = tokens;
	}
	fclose(arquivo);
}

void Gerador_automato::gerar_simbolo_glc() {

	FILE* arquivo = fopen("./txt/arquivo.txt", "r");
	char ch;
	
	while (!feof(arquivo)) {

		// caracter lido do arquivo
		ch = fgetc(arquivo);

		// criar uma cópia do que está no ch que é character, e salva no aux como string
		// porque para o vetor simbolo é preciso passar uma string
		string aux(1, ch); 

		// quando lê a GLC, se for números ou letras minúsculas adiciona aos símbolos da
		// linguagem, lê o arquivo novamente do começo mas sempre verifica se já foi adicionado
		
		if (isdigit(ch) || islower(ch)) {			

			/* procura se o simbolo já existe no array */
			int salva_novo_estado = 1;
			
			for (int i = 0; i < coluna_livre_automato; i++) {
				if (simbolos[i] == aux) {
					salva_novo_estado = 0;
					break;
				}
			}

			/* salva o simbolo se não existir no array */
			if (salva_novo_estado) {
				simbolos[coluna_livre_automato] = aux;
				coluna_livre_automato++;
			}
		}
	}
}

void Gerador_automato::gerar_matriz_automato_estados_GLC() {

    // gerando fixo transição por S para as GLCs

	//1, 0
	matriz_automato[1][14] = "A1";  
	matriz_automato[1][15] = "A1"; 

	//x, y
	matriz_automato[1][16] = "A2";
	matriz_automato[1][17] = "A2";

    
	// Adiciona os estados

	// 1, 0
	matriz_automato[linha_livre_automato][0] = "A1*";
	matriz_automato[linha_livre_automato][14] = "A1";  
	matriz_automato[linha_livre_automato][15] = "A1";
	
	linha_livre_automato++;

	// x, y
	matriz_automato[linha_livre_automato][0] = "A2*";
	matriz_automato[linha_livre_automato][16] = "A2";  
	matriz_automato[linha_livre_automato][17] = "A2";
	
	linha_livre_automato++;

	// define os IDs da GLC
	identificador_tokens[++contador_id_tokens] = "variaveis";
	identificador_tokens[++contador_id_tokens] = "numeros";
	identificador_tokens[++contador_id_tokens] = "Error";
}

int Gerador_automato::retorna_coluna_simbolo(string s) {

	short posicao = -1;
	
	for (int i = 1; i < COLUNA; i++) {
		if (matriz_automato[0][i] == s) {
			posicao = i;
			break;
		}
	}

	return posicao;
}

void Gerador_automato::adicionar_estado_erro() {

	matriz_automato[0][18] = "#";
}

void Gerador_automato::criar_identificadores_tokens_goldparser() {

	/* adiciona os estados ao autômato */
	FILE* arquivo = fopen("./txt/identificadores_goldparser.txt","rt");

	char linha[5];  
	char tokens[5]; 
	short contador = 0;
	
	while(fgets(linha, 5, arquivo)) {

		sscanf(linha, "%s", tokens); 

		identificador_tokens_goldparser[contador] = tokens;
		contador++;
	}

	fclose(arquivo);

	identificador_tokens_goldparser[++contador] = "variaveis";
	identificador_tokens_goldparser[++contador] = "numeros";
}
