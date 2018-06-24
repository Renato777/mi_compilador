#include <string.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include "../lib/AnaLex.h"

using namespace std;
string filename="";
enum token_type t;

int main(int argc, char *argv[])
{
    debug << "Inside main()..."<<endl;

    if(argc < 2)
    {
        cout << "USAGE: Introduzca string argumento de entrada al ejecutar: analex <string>" << endl;
        exit(1);
    }
 
    filename = argv[1];   

    if(runLexical(filename) != 0)
    {
        cout << "Compilation failed in Lexical Analizer." << endl;
    }

    
    return 0;
}

 
