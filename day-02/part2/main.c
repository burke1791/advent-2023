#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "game.h"
#include "gram.tab.h"

extern FILE* yyin;

int get_min_cubes(List* sl, char* color) {
  int minCount = 0;

  ListItem* li = sl->root;
  while (li != NULL) {
    Set* s = (Set*)li->ptr;
    int count = get_cube_count(s->cubes, color);
    if (count > minCount) minCount = count;
    li = li->next;
  }

  return minCount;
}

int compute_min_set_power(Game* g) {
  int minRed = get_min_cubes(g->sets, "red");
  int minGreen = get_min_cubes(g->sets, "green");
  int minBlue = get_min_cubes(g->sets, "blue");

  return minRed * minGreen * minBlue;
}

int compute_power_sum(List* games) {
  ListItem* li = games->root;

  int totalPower = 0;

  while (li != NULL) {
    Game* g = (Game*)li->ptr;
    totalPower += compute_min_set_power(g);
    li = li->next;
  }

  return totalPower;
}

int main(int argc, char** argv) {

  if (argc != 2) {
    printf("Please provide the input file\n");
    printf("E.g. d2p2 [input_file]\n");

    return 0;
  }

  printf("File: %s\n", argv[1]);

  if (!(yyin = fopen(argv[1], "r"))) {
    perror(argv[1]);
    return 1;
  }

  List* l;

  yyparse(&l);

  if (l->numItems <= 5) print_list(l);

  int totalPower = compute_power_sum(l);
  printf("Total Power: %d\n", totalPower);

  free_list(l);
}