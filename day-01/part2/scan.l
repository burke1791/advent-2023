%option case-insensitive

%{

#include <ctype.h>
#include <string.h>

int num1 = 0;
int num2 = 0;
int total = 0;

void compute();
int parseTextNumber(char* str);

%}

%s FIRST

%%

<FIRST>[0-9]    { num2 = atoi(yytext); }

  /* because some numbers can nest inside others */
<FIRST>ONEIGHT   |
<FIRST>NINEIGHT  |
<FIRST>THREEIGHT |
<FIRST>FIVEIGHT  {
    num2 = 8;
  }
<FIRST>TWONE     {
    num2 = 1;
  }
<FIRST>SEVENINE  {
    num2 = 9;
  }
<FIRST>EIGHTWO   {
    num2 = 2;
  }
<FIRST>EIGHTHREE {
    num2 = 3;
  }


<FIRST>ONE   |
<FIRST>TWO   |
<FIRST>THREE |
<FIRST>FOUR  |
<FIRST>FIVE  |
<FIRST>SIX   |
<FIRST>SEVEN |
<FIRST>EIGHT |
<FIRST>NINE    {
    num2 = parseTextNumber(yytext);
  }

[0-9]   {
    num1 = atoi(yytext);
    num2 = atoi(yytext);
    BEGIN FIRST;
  }

ONE   |
TWO   |
THREE |
FOUR  |
FIVE  |
SIX   |
SEVEN |
EIGHT |
NINE    {
    num1 = parseTextNumber(yytext);
    num2 = parseTextNumber(yytext);
    BEGIN FIRST;
  }

<FIRST>[\r\n]  {
    compute();
    BEGIN INITIAL;
  }

<FIRST><<EOF>> {
    compute();
    return 0;
  }

.   /* everything else - do nothing */

%%

int main(int argc, char** argv) {
  if (argc > 1) {
    if (!(yyin = fopen(argv[1], "r"))) {
      perror(argv[1]);
      return 1;
    }
  }

  yylex();
  printf("Total: %d\n", total);
}

int concatenate(int n1, int n2) {
  return (n1 * 10) + n2;
}

void compute() {
  if (num1 == 0 || num2 == 0) printf("wtf\n");
  total += concatenate(num1, num2);
  num1 = 0;
  num2 = 0;
}

void toLowerCase(char* str) {
  for (int i = 0; str[i]; i++) {
    str[i] = tolower(str[i]);
  }
}

int parseTextNumber(char* str) {
  toLowerCase(str);

  if (strcmp(str, "one") == 0) return 1;
  if (strcmp(str, "two") == 0) return 2;
  if (strcmp(str, "three") == 0) return 3;
  if (strcmp(str, "four") == 0) return 4;
  if (strcmp(str, "five") == 0) return 5;
  if (strcmp(str, "six") == 0) return 6;
  if (strcmp(str, "seven") == 0) return 7;
  if (strcmp(str, "eight") == 0) return 8;
  if (strcmp(str, "nine") == 0) return 9;

  printf("ended up here somehow\n");

  return 0;
}