%{

int num1 = -1;
int num2 = -2;
int total = 0;

void compute();

%}

%s FIRST

%%

<FIRST>[0-9]    { num2 = atoi(yytext); }

[0-9]   {
    num1 = atoi(yytext);
    num2 = atoi(yytext);
    BEGIN FIRST;
  }

[\r\n]  {
    compute();
    BEGIN INITIAL;
  }

<<EOF>> {
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

int concatenate(int x, int y) {
  int pow = 10;
  while (y >= pow) {
    pow *= 10;
  }

  return x * pow + y;
}

void compute() {
  total += concatenate(num1, num2);
  num1 = -1;
  num2 = -1;
}