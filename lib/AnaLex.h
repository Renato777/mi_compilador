
#ifndef __ANALEX_H__
#define __ANALEX_H__

#include <string.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>

#define DEBUG true
#define debug if(DEBUG) cout

using namespace std;

enum token_type {ERROR, HEXA, DECI, FLOT, PLUS, PLUSPLUS, MINUS, MINUSMINUS, 
                 ASSIGN, EQUALTO, DIV, MULT, LESSTHAN, MORETHAN, EXCLA, AND, 
                 OR, XOR, LPAREN, RPAREN, SEMICOLON, COLON, COMMA, MAIN, ENDMAIN, 
				 INT, FLOAT, FOR, FUNC, IF, ENDIF, ENDFOR, ENDFUNC, CALL, IDENT, EOFT};
				 
//string token_names[] = {"ERROR", "HEXA", "DECI", "FLOT","EOFT"};

enum token_type get_token(string line);
int runLexical(string input_file);
string get_lexeme();
void print_error();

#endif

