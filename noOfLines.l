//No. of lines, words, characters
%{
#include<stdio.h>
#include<string.h> 
int wc=0,cc=0,lc=0,sc=0;
%}

%%

[\n] { lc++ ;  }
[  \t] { sc++ ;  }
[^\t\n ]+ { 
    if(strcmp(yytext, "-1") == 0) {
        return 0;     
    }
    wc++;
    cc+=yyleng;
}
%%
int main( int argc , char * argv[])
{
    printf("Enter the input: \n");
    yylex();
    printf("The number of lines are : %d\n",lc);
    printf("The number of words are : %d\n",wc);  
    printf("The number of spaces are : %d\n",sc);  
    printf("The number of characters are : %d\n",cc);
    return 0;
}
int yywrap(){
    return 1;
}

