#include <bits/stdc++.h>
#include <string.h>
#include "gerador_automato.h"

using namespace std;


Objeto_base::Objeto_base() {

}

int Objeto_base::str_equal(string first, string second) {

	trim(first);
	trim(second);
	
	return (first.compare(second) == 0) ? 1 : 0;
}

string Objeto_base::char_to_str(char *chars) {
	
	int len = strlen(chars);
	string word = "";
	
	for (int i = 0; i <= len; ++i) 
		word.append(1, chars[i]);
	
	return word;
}

string Objeto_base::convertToString(char* a) {

	int b_size = strlen(a);
	
    int i;
    string s = "";

	for (i = 0; i < b_size; i++) {
        s = s + a[i];
    }

	return s;
}
