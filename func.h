#ifndef FUNC_H
#define FUNC_H

#define QNT_SIMBOLO 30
#define LINHA 30
#define COLUNA 19
#define sinal_erro "$"
#define TAMANHO_FITA_SAIDA 100
#define TAMANHO_COLUNA_TAB_LALR 100
#define TAMANHO_LINHA_TAB_LALR 100
#define COUT_SIZE 9

#include <string.h>
using namespace std;

class Objeto_base {

public:

	Objeto_base();

	string convertToString(char* a);
	string char_to_str(char *chars);
	int str_equal(string first, string second);
};


#endif
