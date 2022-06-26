%option noyywrap
%{

#include <sintatico.tab.h>
#include <string.h>

%}
%%

"$"      {return DOLLAR;}
"int"    {return INT;}
"float"  {return FLOAT;}
"char"   {return CHAR; }
[,]      {return COMMA;}
[a-z]+   {strcpy(yylval.string, yytext); return ID;}
\n       {return EOL;}
[ \t]    {}
<<EOF>>  {return _EOF;}
.        {}

%%
