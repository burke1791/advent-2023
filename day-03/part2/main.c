#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "engine.h"



int main(int argc, char** argv) {
  printf("File: %s\n", argv[1]);
  FILE* fp = fopen(argv[1], "r");
  List* s = new_list(L_SYMBOL);
  List* n = new_list(L_NUMBER);

  map_engine(fp, s, n);

  // printf("Symbols: %d\n", s->numItems);
  // print_list(s);

  // printf("Numbers: %d\n", n->numItems);
  // print_list(n);

  printf("======================================\n");
  
  

  free_list(s);
  free_list(n);
  fclose(fp);
}