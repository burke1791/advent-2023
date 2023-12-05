#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "engine.h"


static int compute_gear_ratio_sum(List* s, List* n) {
  ListItem* li_s = s->root;
  int adjacentNums;
  int totalGearRatio = 0;
  int currentRatio;

  while (li_s != NULL) {
    adjacentNums = 0;
    currentRatio = 0;
    Symbol* sym = (Symbol*)li_s->ptr;
    if (sym->sym != '*') {
      li_s = li_s->next;
      continue;
    }

    ListItem* li_n = n->root;
    while (li_n != NULL) {
      Number* num = (Number*)li_n->ptr;
      if (is_adjacent(sym, num)) {
        adjacentNums++;
        currentRatio = currentRatio == 0 ? num->val : currentRatio * num->val;
      }
      li_n = li_n->next;
    }

    if (adjacentNums == 2) {
      totalGearRatio += currentRatio;
    }
    li_s = li_s->next;
  }

  return totalGearRatio;
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
  int totalGearRatio = compute_gear_ratio_sum(s, n);
  printf("Total gear ratio: %d\n", totalGearRatio);

  free_list(s);
  free_list(n);
  fclose(fp);
}