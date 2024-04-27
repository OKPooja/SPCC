//lexical anaylser
%{
#include<stdio.h>
int ke=0,op=0,va=0,co=0,se=0,ch=0;
%}

%%

int|float|const|string {printf("keywords: %s\n",yytext);ke++;ch++;}
[+|%|*|=] {printf("Operators: %s\n",yytext);op++;ch++;}
[a-zA-Z][a-zA-Z0-9]* {printf("Variables: %s\n",yytext);va++;ch++;}
[0-9]+ {printf("Constants: %s\n",yytext);co++;ch++;}
[;|,|:|"] {printf("Seprators: %s\n",yytext);se++;ch++;}
[-] {printf("Operators: %s\n",yytext);op++;ch++;}


%%

int main(){
	printf("Enter a string: \n");
	yylex();
	printf("The total number of tokens : %d\n",ch);
	printf("The total number of keywords: %d\n",ke);
    printf("The total number of operators: %d\n",op);
    printf("The total number of variables: %d\n",va);
    printf("The total number of constants: %d\n",co);
    printf("The total number of separators: %d\n",se);
	return 0;
}
int yywrap(){
	return 1;
}



