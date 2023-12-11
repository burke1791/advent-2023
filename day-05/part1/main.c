#include <stdlib.h>
#include <stdio.h>

#include "gram.tab.h"
#include "almanac.h"

extern FILE* yyin;

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("Please provide the input file\n");
    printf("E.g. d5p1 [input_file]\n");

    return 0;
  }

  printf("File: %s\n", argv[1]);

  if (!(yyin = fopen(argv[1], "r"))) {
    perror(argv[1]);
    return 1;
  }

  Almanac* a;

  yyparse(&a);

  printf("Num seeds: %d\n", a->seeds->numItems);

  free_almanac(a);
}