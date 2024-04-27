//vowel.l

%{
#include <stdio.h>
%}

%%
[aeiouAEIOU]              { printf("Input is a vowel\n"); }
[A-Za-z(^aeiouAEIOU)]   { printf("Input is not a vowel\n"); }
%%

int main() {
    printf("Enter a character: ");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}