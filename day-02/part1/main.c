#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "game.h"
#include "gram.tab.h"

extern FILE* yyin;

static bool set_is_valid(Set* s, int maxRed, int maxGreen, int maxBlue) {
  bool isValid = true;

  int red = get_cube_count(s->cubes, "red");
  int green = get_cube_count(s->cubes, "green");
  int blue = get_cube_count(s->cubes, "blue");

  if (red > maxRed || green > maxGreen || blue > maxBlue) isValid = false;

  return isValid;
}

static bool game_is_valid(Game* g, int maxRed, int maxGreen, int maxBlue) {
  bool isValid = true;

  ListItem* li = g->sets->root;
  while (li != NULL) {
    Set* s = (Set*)li->ptr;
    if (!set_is_valid(s, maxRed, maxGreen, maxBlue)) return false;
    li = li->next;
  }

  return isValid;
}

static int evaluate_games(List* games, int maxRed, int maxGreen, int maxBlue) {
  ListItem* li = games->root;
  int total = 0;

  while (li != NULL) {
    Game* g = (Game*)li->ptr;
    if (game_is_valid(g, maxRed, maxGreen, maxBlue)) total += g->gameId;
    li = li->next;
  }

  return total;
}

int main(int argc, char** argv) {

  if (argc != 5) {
    printf("Please provide the max number of each color cube as command line arguments\n");
    printf("in the order: red green blue, followed by the input filename\n");
    printf("E.g. d2p1 [red] [green] [blue] [input_file]\n");

    return 0;
  }

  int red = atoi(argv[1]);
  int green = atoi(argv[2]);
  int blue = atoi(argv[3]);

  printf("Max number of cubes:\n");
  printf("  Red:   %d\n", red);
  printf("  Green: %d\n", green);
  printf("  Blue:  %d\n", blue);
  printf("File: %s\n", argv[4]);

  if (!(yyin = fopen(argv[4], "r"))) {
    perror(argv[4]);
    return 1;
  }

  List* l;

  yyparse(&l);

  if (l->numItems <= 5) print_list(l);

  int gameIdTotal = evaluate_games(l, red, green, blue);
  printf("GameId Total: %d\n", gameIdTotal);

  free_list(l);
}