/* Nao usar a biblioteca do flex*/
%option noyywrap

%%

"if"			   			  { printf("IF\n"); }
[a-z][a-z0-9]* 	   			  { printf("%s ID\n",yytext); }
[0-9]+ 						  { printf("%s NUM\n",yytext); }
("."[0-9]+)|([0-9]+"."[0-9]*) { printf("%s REAL\n",yytext); }
"--"[a-z]*[\n]				  { int len = strlen(yytext); 
							    yytext[len-1] = '\0';
								printf("%s comment\n",yytext); }
" "+						  { printf("white space\n"); }
[\n]			   			  { }
.          		              { printf("%s error\n",yytext); }

%%

int main(int argc, char **argv){
	yylex();
	return 0;
}