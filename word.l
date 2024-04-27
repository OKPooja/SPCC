//word.l

%{
#include <stdio.h>
void display(char[], int);
int flag;
%}

%%

[a-zA-Z ]+     { flag = 1; display(yytext,flag); return 0; }
[0-9 ]+        { flag = 0; display(yytext,flag); return 0; }
.+            { flag = -1; display(yytext,flag); return 0; }

%%

void display(char a[], int flag) {
    if (flag == 1)
        printf("The given string '%s' is a word\n", a);
    if (flag == 0)
        printf("The given string '%s' is a number\n", a);
    if (flag == -1)
        printf("The given string '%s' is everything\n", a);
}
int main() {
    printf("Enter a string: ");
    yylex();
    return 0;
}
int yywrap() {
    return 1;
}


