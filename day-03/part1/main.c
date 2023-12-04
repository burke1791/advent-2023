#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "engine.h"

static int compute_engine_part_sum(List* s, List* n) {
  int total = 0;

  ListItem* li_n = n->root;
  while (li_n != NULL) {
    Number* num = (Number*)li_n->ptr;
    ListItem* li_s = s->root;
    while (li_s != NULL) {
      Symbol* sym = (Symbol*)li_s->ptr;
      if (is_adjacent(sym, num)) {
        total += num->val;
        break;
      }
      li_s = li_s->next;
    }
    li_n = li_n->next;
  }

  return total;
}


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
  
  int total = compute_engine_part_sum(s, n);
  printf("Total Part Sum: %d\n", total);

  free_list(s);
  free_list(n);
  fclose(fp);
}