/* Nao usar a biblioteca do flex*/
%option noyywrap

%{
int lines = 1;
int blankLines = 0;
int linesWithComments = 0;
int nbNcLines = 0;
int semicolons = 0;
int preprocessingDirectives = 0;

int totalLines = 0;
int totalBlankLines = 0;
int totalLinesWithComments = 0;
int totalNbNcLines = 0;
int totalSemicolons = 0;
int totalPreprocessingDirectives = 0;
%}

%x N_LINE_COMMENT

%%

"/*"            		   {BEGIN(N_LINE_COMMENT);}
<N_LINE_COMMENT>[^*\n]+    {}
<N_LINE_COMMENT>\n   	   {linesWithComments++; lines++;}
<N_LINE_COMMENT>"*/" 	   {linesWithComments++; BEGIN(INITIAL);}

\/\/.*\n				   {linesWithComments++; lines++;}
^[ \t]*[\n]  			   {blankLines++; lines++;}
[\n]       				   {lines++;}
";"  	   				   {semicolons++;}
"#include"				   {preprocessingDirectives++;}
"#define"                  {preprocessingDirectives++;}
.						   {}

%%

int main(int argc, char **argv){

	if(argc < 2) { //The only argument is the program name itself. So, we finish the program.
		fprintf(stderr, "No input file provided.\n");
		return 1;
	}

	printf("%6s%9s%9s%9s%9s%9s%5s\n", "total", "blank", "lines w/", "nb, nc", "semi-", "prepoc.", "file");
	printf("%6s%9s%9s%9s%9s%9s\n", "lines", "lines", "comments", "lines", "colons", "direct.");
	printf("------+--------+--------+--------+--------+--------+----\n");
	
	

	//else, we are gonna scan each file which name was passed as input to this program. 
	int i;
	for(i = 1; i < argc; i++) {
		FILE *f = fopen(argv[i], "r");
		if(!f) {
			perror(argv[i]);
			return (1);
		}

		yyrestart(f); //sets the scanner stdin as being the just opened file "f".
		yylex();	  //scans the file.
		fclose(f);

		nbNcLines = lines - (blankLines + linesWithComments);

		printf("%6d%9d%9d%9d%9d%9d %s\n", lines, blankLines, linesWithComments, nbNcLines, semicolons, preprocessingDirectives, argv[i]);
		totalLines += lines; lines = 1;
		totalBlankLines += blankLines; blankLines = 0;
		totalLinesWithComments += linesWithComments; linesWithComments = 0;
		totalNbNcLines += nbNcLines;
		totalSemicolons += semicolons; semicolons = 0;
		totalPreprocessingDirectives += preprocessingDirectives; preprocessingDirectives = 0;
	}
	
	printf("%6d%9d%9d%9d%9d%9d %s\n", totalLines, totalBlankLines, totalLinesWithComments, totalNbNcLines, totalSemicolons, totalPreprocessingDirectives, "total");
	
	return 0;
	
}