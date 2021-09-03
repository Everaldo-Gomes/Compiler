#include<bits/stdc++.h>
using namespace std;

#define QNT_SIMBOLO 30
#define LINHA 30
#define COLUNA 14

string simbolos[QNT_SIMBOLO];
string matriz_automato[LINHA][COLUNA];	
void gerar_simbolo_token();
void gerar_simbolo_glc();
void gerar_matriz_automato_estados();
int retorna_coluna_simbolo(string);

short n = 0;

int main () {

	/* inicializa a matriz_automato */
	for(int i = 0; i < LINHA; i++) {
        for(int j = 0; j < COLUNA; j++) {
            matriz_automato[i][j] = "-";
        }
	}

	gerar_simbolo_token();
	gerar_matriz_automato_estados();
	//gerar_simbolo_glc();

	
	/* mostra a matriz automato */
	for(int i = 0; i < LINHA; i++) {
        for(int j = 0; j < COLUNA; j++) {
			cout << matriz_automato[i][j] << "\t";
        }
		cout << "\n";
	}
    
	cout << "\n\n";
    
	return 0;
}

/* encontra todos os caracteres dos tokens */
void gerar_simbolo_token() {

	FILE* arquivo = fopen("arquivo.txt", "r");
	string ch;
	
	while (!feof(arquivo)) {

		ch = fgetc(arquivo);
      
		if (ch == "<") { break; }
		if ((ch != "\n" && ch != " ")) {
			
			/* procura se o simbolo já existe no array */
			int salva_novo_estado = 1;
				
			for (int i = 0; i < n; i++) {
				if (simbolos[i] == ch) {
					salva_novo_estado = 0;
					break;
				}
			}

			/* salva o simbolo se não existir no array */
			if (salva_novo_estado) {
				simbolos[n] = ch;
				n++;
			}
		}
	}

	fclose(arquivo);
}


void gerar_matriz_automato_estados() {

	// gera 1ª linha do autômoto
	for(int i = 1; i < COLUNA; i++) {
		matriz_automato[0][i] = simbolos[i-1];
	}
	
	matriz_automato[0][0] = " ";
	matriz_automato[1][0] = "S";
	
	
	/* adiciona os estados ao autômato */
	FILE* arquivo = fopen("./arquivo.txt","rt");

	char linha[5];  //cada linha do arquivo
	char tokens[5]; //faz um loop na string de cada linha (letra por letra)
	char estado = 'A'; 

	//linha 0 -> espaço em branco da linha dos símbolos da linguagem
	//linha 1 -> "S estado inicial"
	short contador_linha_livre = 2;
	
	while(fgets(linha, 5, arquivo)) {

		sscanf(linha, "%s", tokens); //copia conteúdo da linha para o "tokens"

		short tamanho_token = strlen(tokens);
		string estado_anterior;
		short linha_estado_anterior = 0;
		
		for (int i = 0; i < tamanho_token; i++) {

			//convert char em string
			string s(1, tokens[i]); 
			string novo_estado(1, estado);
			short coluna = retorna_coluna_simbolo(s);
			
			/* se for o 1º caracter do token, deve-se gerar uma transição pelo estado S */
			if (i == 0) {

				// evitar os tracinhos ou vígulas em lugares indevidos
				if (matriz_automato[1][coluna] == "-") {
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

		// reconhecou o token, e é um estado de aceitação
		matriz_automato[linha_estado_anterior][0].append("*");
	}
	fclose(arquivo);
}

int retorna_coluna_simbolo(string s) {

	short posicao = -1;
	
	for (int i = 1; i < COLUNA; i++) {
		if (matriz_automato[0][i] == s) {
			posicao = i;
			break;
		}
	}

	return posicao;
}
