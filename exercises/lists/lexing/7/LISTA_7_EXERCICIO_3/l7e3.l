/* Nao usar a biblioteca do flex*/
%option noyywrap

%%


"aba"+		  	   { printf("ACTION1(%s)\n", yytext); }
"a"[b]*"a"		   { printf("ACTION2(%s)\n", yytext); }
"a"|"b"		       { printf("ACTION3(%s)\n", yytext); }
[\n]			   { }
.          		   { printf("ERRO\n"); }

%%

int main(int argc, char **argv){
	yylex();
	return 0;
}