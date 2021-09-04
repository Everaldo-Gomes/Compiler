#include <bits/stdc++.h>
#include "analisador_lexico.h"
using namespace std;


Analizador_lexico::Analizador_lexico(string matriz_automato[LINHA][COLUNA]) {

	cout << "Entrou constructor A. L\n";
	
	for(int i = 0; i < LINHA; i++) {
        for(int j = 0; j < COLUNA; j++) {
			cout << matriz_automato[i][j] << "\t";
        }
		cout << "\n";
	}


	cout << "\n\n";
}
