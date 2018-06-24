#include "AnaLex.h"

using namespace std;

//#define DEBUG true
//#define debug if(DEBUG) cout

//enum token_type {ERROR, HEXA, DECI, FLOT, EOFT};
string token_names[] = {"ERROR", "HEXA", "DECI", "FLOT", "PLUS", "PLUSPLUS", "MINUS", "MINUSMINUS", 
                        "ASSIGN", "EQUALTO", "DIV", "MULT", "LESSTHAN", "MORETHAN", "EXCLA", "AND", 
                        "OR", "XOR", "LPAREN", "RPAREN", "SEMICOLON", "COLON", "COMMA", "MAIN", "ENDMAIN", 
						"INT", "FLOAT", "FOR", "FUNC", "IF", "ENDIF", "ENDFOR", "ENDFUNC", "CALL", "IDENT", "EOFT"};
int state=0;
int pos=0;
enum token_type T;
string lexeme = "";
string cadena="";
string line="";
char c;

std::ifstream input_file;
int ln = 0;
char opers[] = "/*<>!&|^();,:"; //not inclued: _.%~?
char*oper=NULL;
int errors=0;

//enum token_type get_token(string line);
//void runLexical();
//string get_lexeme();

//enum token_type get_token(string line)
enum token_type get_token(ifstream &input_file)
{
    debug << "Inside get_token()..."<<endl;
    state = 0;

    lexeme = "";

    if(pos >= line.length())
    {
        debug << "Getting a new line..." << endl;
        getline(input_file, line);
        if(input_file.eof())
        {
			debug << "End of file reached."<<endl;
            return EOFT;
        }
        ln++;
        pos = 0;
        debug << "line " << ln << ": " << line << endl;
    }

    //Remove leading whitespace
    while(isspace(line[pos]))
        pos++;
    //Remove trailing whitespace
    while(line[line.size()-1] == ' ')
        line = line.substr(0, line.size()-1);

    //Loop through character in line
    while(true)
    {
        //Consume next available char
        if(state && state!= 6 && state!=7 && state!=8 && state!=15 && state!=22 && state!=17 && state!=23 && state!=19 && state!=24 &&
		   state!=21 && state!=34 && state!=41 && state!=47 && state!=50 && state!=54 && state!=58 && state!=63 && state!=69 && state!=75 &&
		   state!=82 && state!=86) //states that return a valid token
            pos++;
        c = line[pos];
        if(c!=' ')
        lexeme += c;
        
        debug << "---------------" << endl;
        debug << "pos = " << pos << endl;
        debug << "char = " << c << endl;
        debug << "lexeme = " << lexeme << endl;

        switch(state)
        {   debug<<"Inside switch()..."<<endl;
            case 0:
                debug<<"Inside state 0..."<<endl; sleep(1);
                if(c == '0') {state=1; break;}
                else if(c == '1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9') {state=2; break;}
                else if(c=='.'){state=3; break;}
                else if((oper=strchr(opers,c))!=NULL){state=11;break;}
                else if(c=='+'){state=12;break;}
                else if(c=='-'){state=13;break;}
                else if(c=='='){state=14;break;}  
                else if(c=='M'){state=30;break;}
                else if(c=='E'){state=35;break;}
                else if(c=='I'){state=38;break;}
                else if(c=='F'){state=42;break;}	
                else if(c=='C'){state=78;break;}
                else if(islower(c)){state=85;break;}
                else {state=4; break;}
            case 1:
                debug<<"Inside state 1..."<<endl; sleep(1);
                if(c=='x'||c=='X'){state=5;break;}
                else if(c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9') {state=2; break;}
                else if(c=='.'){state=3;break;}
                else {state=4; break;}
            case 2:
                debug<<"Inside state 2..."<<endl; sleep(1);                
                if(c==' '||c=='\0'){state=7;break;}
                else if(c=='.'){state=3;break;}
                else if(c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9'){break;}//state=2
                else {state=4; break;}
            case 3:
                debug<<"Inside state 3..."<<endl; sleep(1);
                if(c==' '||c=='\0'){state=8;break;}
                else if(c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9'){break;}//state=3
                else {state=4; break;}
            case 4:
                debug<<"Inside state 4..."<<endl; sleep(1);
                state=0;
                print_error();
                errors++;
                return ERROR;
            case 5:
                debug<<"Inside state 5..."<<endl; sleep(1);
                if(c==' '||c=='\0'){state=6;break;}
                else if(c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9'){break;}//state=5
                else if(c=='a'||c=='b'||c=='c'||c=='d'||c=='e'||c=='f'||c=='A'||c=='B'||c=='C'||c=='D'||c=='E'||c=='F'){break;}//state=5
                else {state=4; break;}
            case 6:
                debug<<"Inside state 6..."<<endl; sleep(1);
                state=0;
                return HEXA;
            case 7:
                debug<<"Inside state 7..."<<endl; sleep(1);
                state=0;
                return DECI;
            case 8:
                debug<<"Inside state 8..."<<endl; sleep(1);
                state=0;
                return FLOT;
            case 9:
            case 10:
            case 11:
                debug<<"Inside state 11..."<<endl; sleep(1);
		        if(c==' '||c=='\0'){state=21;break;}
                else {state=25;break;}
            case 12:
                debug<<"Inside state 12..."<<endl; sleep(1);
                if(c==' '){state=15;break;}//PLUS
                if(c=='+'){state=16;break;}//PLUSPLUS
                else {state=25;break;}
            case 13:
                debug<<"Inside state 13..."<<endl; sleep(1);
                if(c==' '){state=17;break;}
                else if(c=='-'){state=18;break;}
                else {state=25;break;} 
            case 14:
                debug<<"Inside state 14..."<<endl; sleep(1);
                if(c==' '){state=19;break;}
                else if(c=='='){state=20;break;}
                else {state=25;break;} 
            case 15:
                debug<<"Inside state 15..."<<endl; sleep(1);
                state=0;
                return PLUS;
            case 16:
			    debug<<"Inside state 16..."<<endl; sleep(1);
                if(c==' '||c=='\0'){state=22;break;}
				else {state=25;break;}
            case 17:
                debug<<"Inside state 17..."<<endl; sleep(1);
                state=0;
                return MINUS;
            case 18:
                debug<<"Inside state 18..."<<endl; sleep(1);
                if(c==' '||c=='\0'){state=23;break;}
				else {state=25;break;}
            case 19:
                debug<<"Inside state 19..."<<endl; sleep(1);
                state=0;
                return ASSIGN;
            case 20:
                debug<<"Inside state 20..."<<endl; sleep(1);
				if(c==' '||c=='\0'){state=24;break;}
				else {state=25;break;}              
            case 21:
                debug<<"Inside state 21..."<<endl; sleep(1);
                state=0;
                if(*oper == '/')return DIV;
                else if(*oper == '*')return MULT;
                else if(*oper == '<')return LESSTHAN;
                else if(*oper == '>')return MORETHAN;
                else if(*oper == '!')return EXCLA;
                else if(*oper == '&')return AND;
                else if(*oper == '|')return OR;
                else if(*oper == '^')return XOR;
                else if(*oper == '(')return LPAREN;
                else if(*oper == ')')return RPAREN;
                else if(*oper == ';')return SEMICOLON;
                else if(*oper == ',')return COMMA;
                else if(*oper == ':')return COLON;
                else return ERROR;
            case 22:
                debug<<"Inside state 22..."<<endl; sleep(1);
                state=0;
                return PLUSPLUS; 
            case 23:
                debug<<"Inside state 23..."<<endl; sleep(1);
				state=0;
                return MINUSMINUS;
            case 24:
                debug<<"Inside state 24..."<<endl; sleep(1);
				state=0;
                return EQUALTO;  
            case 25:
                debug<<"Inside state 25..."<<endl; sleep(1);
				state=0;
                print_error();
                errors++;
                return ERROR;
			case 26:
			case 27:
			case 28:
			case 29:
			case 30:
                debug<<"Inside state 30..."<<endl; sleep(1);
                if(c=='A'){state=31;break;}
			    else {state=100;break;}  
			case 31:
                debug<<"Inside state 31..."<<endl; sleep(1);
                if(c=='I'){state=32;break;}
			    else {state=100;break;}     
			case 32:
                debug<<"Inside state 32..."<<endl; sleep(1);
                if(c=='N'){state=33;break;}
			    else {state=100;break;} 
			case 33:
                debug<<"Inside state 33..."<<endl; sleep(1);
                if(c==' '||c=='\0'){state=34;break;}
			    else {state=100;break;}
            case 34:
                debug<<"Inside state 34..."<<endl; sleep(1);
				state=0;
                if(lexeme=="MAIN")return MAIN;
				if(strncmp (lexeme.c_str(),"MAIN",4) == 0) return MAIN;
                else return ENDMAIN;				
			case 35:
                debug<<"Inside state 35..."<<endl; sleep(1);
                if(c=='N'){state=36;break;}
			    else {state=100;break;}
			case 36:
                debug<<"Inside state 36..."<<endl; sleep(1);
                if(c=='D'){state=37;break;}
			    else {state=100;break;}
			case 37:
                debug<<"Inside state 37..."<<endl; sleep(1);
                if(c=='M'){state=30;break;}
                if(c=='I'){state=61;break;}               
				if(c=='F'){state=66;break;}
				else {state=100;break;}
			case 38:
                debug<<"Inside state 38..."<<endl; sleep(1);
                if(c=='N'){state=39;break;}
				if(c=='F'){state=57;break;}
			    else {state=100;break;}
			case 39:
                debug<<"Inside state 39..."<<endl; sleep(1);
                if(c=='T'){state=40;break;}
			    else {state=100;break;}
			case 40:
                debug<<"Inside state 40..."<<endl; sleep(1);
                if(c==' ' || c=='\0'){state=41;break;}
			    else {state=100;break;}	
			case 41:
                debug<<"Inside state 41..."<<endl; sleep(1);				
				state=0;
                return INT;
			case 42:
                debug<<"Inside state 42..."<<endl; sleep(1);
                if(c=='L'){state=43;break;}//to FLOAT
				if(c=='O'){state=48;break;}//to FOR
				if(c=='U'){state=51;break;}//to FUNC
			    else {state=100;break;}	
			case 43:
                debug<<"Inside state 43..."<<endl; sleep(1);
                if(c=='O'){state=44;break;}
			    else {state=100;break;}					
			case 44:
                debug<<"Inside state 44..."<<endl; sleep(1);
                if(c=='A'){state=45;break;}
			    else {state=100;break;}				
			case 45:
                debug<<"Inside state 45..."<<endl; sleep(1);
                if(c=='T'){state=46;break;}
			    else {state=100;break;}
			case 46:
                debug<<"Inside state 46..."<<endl; sleep(1);
                if(c==' ' || c=='\0'){state=47;break;}
			    else {state=100;break;}	
			case 47:
                debug<<"Inside state 47..."<<endl; sleep(1);				
				state=0;
                return FLOAT;				
			case 48:
                debug<<"Inside state 48..."<<endl; sleep(1);
                if(c=='R'){state=49;break;}
			    else {state=100;break;}
			case 49:
                debug<<"Inside state 49..."<<endl; sleep(1);
                if(c==' ' || c=='\0'){state=50;break;}
			    else {state=100;break;}					
			case 50:
                debug<<"Inside state 50..."<<endl; sleep(1);				
				state=0;
                return FOR;	
			case 51:
                debug<<"Inside state 51..."<<endl; sleep(1);
                if(c=='N'){state=52;break;}
			    else {state=100;break;}
			case 52:
                debug<<"Inside state 52..."<<endl; sleep(1);
                if(c=='C'){state=53;break;}
			    else {state=100;break;}
			case 53:
                debug<<"Inside state 53..."<<endl; sleep(1);
                if(c==' ' || c=='\0'){state=54;break;}
			    else {state=100;break;}					
			case 54:
                debug<<"Inside state 54..."<<endl; sleep(1);				
				state=0;
                return FUNC;					
			case 55:
            case 56:
			case 57:
                debug<<"Inside state 57..."<<endl; sleep(1);
                if(c==' ' || c=='\0'){state=58;break;}
			    else {state=100;break;}					
			case 58:
                debug<<"Inside state 58..."<<endl; sleep(1);				
				state=0;
                return IF;			
			case 59:
            case 60:
			case 61:
                debug<<"Inside state 61..."<<endl; sleep(1);
                if(c=='F'){state=62;break;}
			    else {state=100;break;}
			case 62:
                debug<<"Inside state 62..."<<endl; sleep(1);
                if(c==' ' || c=='\0'){state=63;break;}
			    else {state=100;break;}					
			case 63:
                debug<<"Inside state 63..."<<endl; sleep(1);				
				state=0;
                return ENDIF;	
            case 64:
			case 65:
            case 66:
			    debug<<"Inside state 66..."<<endl; sleep(1);
                if(c=='O'){state=67;break;}
				if(c=='U'){state=72;break;}
			    else {state=100;break;}
			case 67:
			    debug<<"Inside state 67..."<<endl; sleep(1);
                if(c=='R'){state=68;break;}
			    else {state=100;break;}
            case 68:
			    debug<<"Inside state 68..."<<endl; sleep(1);
                if(c==' ' || c=='\0'){state=69;break;}
			    else {state=100;break;}		
			case 69:
	            debug<<"Inside state 69..."<<endl; sleep(1);				
				state=0;
                return ENDFOR;
            case 70:
            case 71:
            case 72:			
			    debug<<"Inside state 72..."<<endl; sleep(1);
                if(c=='N'){state=73;break;}
			    else {state=100;break;}		
            case 73:			
			    debug<<"Inside state 73..."<<endl; sleep(1);
                if(c=='C'){state=74;break;}
			    else {state=100;break;}					
            case 74:
			    debug<<"Inside state 74..."<<endl; sleep(1);
                if(c==' ' || c=='\0'){state=75;break;}
			    else {state=100;break;}
			case 75:
	            debug<<"Inside state 75..."<<endl; sleep(1);				
				state=0;
                return ENDFUNC;
            case 76:
            case 77:
            case 78:		
			    debug<<"Inside state 78..."<<endl; sleep(1);
                if(c=='A'){state=79;break;}
			    else {state=100;break;}					
            case 79:		
			    debug<<"Inside state 79..."<<endl; sleep(1);
                if(c=='L'){state=80;break;}
			    else {state=100;break;}
            case 80:		
			    debug<<"Inside state 80..."<<endl; sleep(1);
                if(c=='L'){state=81;break;}
			    else {state=100;break;}				
            case 81:		
			    debug<<"Inside state 81..."<<endl; sleep(1);			
                if(c==' ' || c=='\0'){state=82;break;}
			    else {state=100;break;}
			case 82:
	            debug<<"Inside state 82..."<<endl; sleep(1);				
				state=0;
                return CALL;
			case 83:
			case 84:
			case 85:			
			    debug<<"Inside state 85..."<<endl; sleep(1);
                if(isalpha(c)){break;}
                else if(c=='_'){break;}
				if(c==' ' || c=='\0'){state=86;break;}
			    else {state=100;break;}
			case 86:
	            debug<<"Inside state 86..."<<endl; sleep(1);				
				state=0;
                return IDENT;				
				
			case 100:
                debug << "CASE 100" << endl;
                print_error();
                errors++;
                return ERROR;
            default: printf("default case...\n");
        }
    }
}

string get_lexeme()
{
    //debug<<"Inside get_lexeme()..."<<endl;
    return lexeme;
}

int runLexical(string filename)
{
    debug<<"Inside runLexical()..."<<endl;
 
    input_file.open(filename);
    if(!input_file)
    { 
        cout << "Error: could not open \"" << filename << "\"" << endl;
        return 1;
    }
    
    while((T = get_token(input_file)) != EOFT)
    {
        debug << "\t"<<std::left << token_names[T] <<" : "<< get_lexeme() << endl;
    }
    if(errors != 0)  
    return 1;
}
 
void print_error()
{
    cout << "Error at " << ln << "," << pos << ": ";
    cout << "Invalid character found: " << lexeme << endl;
}
