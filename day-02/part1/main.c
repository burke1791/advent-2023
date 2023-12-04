#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "gram.tab.h"
// #include "scan.lex.h"

extern FILE* yyin;

Game* new_game() {
  Game* g = malloc(sizeof(Game));
  g->sets = NULL;
  return g;
}

Set* new_set() {
  Set* s = malloc(sizeof(Set));
  s->cubes = NULL;
  return s;
}

Cube* new_cube(int count, char* color) {
  Cube* c = malloc(sizeof(Cube));
  c->count = count;
  c->color = color;
  return c;
}

List* new_list(ListType lt, void* ptr) {
  List* l = malloc(sizeof(List));
  l->type = lt;
  
  ListItem* li = malloc(sizeof(ListItem));
  li->next = NULL;
  li->ptr = ptr;

  l->numItems = 1;
  l->root = li;

  return l;
}

void list_append(List* l, void* ptr) {
  ListItem* curr = l->root;

  while (1) {
    if (curr->next == NULL) {
      ListItem* li = malloc(sizeof(ListItem));
      li->next = NULL;
      li->ptr = ptr;

      break;
    }

    curr = curr->next;
  }

  l->numItems++;
}

void free_cube(Cube* c) {
  printf("free cube");
  if (c->color != NULL) free(c->color);
}

static void free_listitem(ListItem* li, ListType lt) {
  printf("free listitem");
  switch (lt) {
    case CUBE:
      printf(" | type: CUBE\n");
      free_cube((Cube*)li->ptr);
      break;
    case SET:
      printf(" | type: SET\n");
      free_set((Set*)li->ptr);
      break;
    default:
      printf("Unrecognized ListType\n");
  }

  free(li->ptr);
}

void free_list(List* l) {
  printf("free list");
  switch (l->type) {
    case SET:
      printf(" | type: SET");
      break;
    case CUBE:
      printf(" | type: CUBE");
      break;
  }
  printf(" | size: %d\n", l->numItems);
  ListItem* li = l->root;

  while (li != NULL) {
    free_listitem(li, l->type);
    ListItem* curr = li;
    li = li->next;
    free(curr);
  }

  free(l);
}

void free_set(Set* s) {
  printf("free set\n");
  free_list(s->cubes);
}

void free_game(Game* g) {
  printf("free game\n");
  if (g->sets != NULL) free_list(g->sets);
  free(g);
}

static void print_game(Game* g) {
  if (g != NULL) printf("Game: %d", g->gameId);
  if (g->sets != NULL) {
    printf(" | Sets: %d", g->sets->numItems);
  }

  printf("\n");
}

int main(int argc, char** argv) {

  // if (argc != 5) {
  //   printf("Please provide the max number of each color cube as command line arguments\n");
  //   printf("in the order: red green blue, followed by the input filename\n");
  //   printf("E.g. d2p1 [red] [green] [blue] [input_file]\n");

  //   return 0;
  // }

  // int red = atoi(argv[1]);
  // int green = atoi(argv[2]);
  // int blue = atoi(argv[3]);

  // printf("Max number of cubes:\n");
  // printf("  Red:   %d\n", red);
  // printf("  Green: %d\n", green);
  // printf("  Blue:  %d\n", blue);
  // printf("File: %s\n", argv[4]);

  if (!(yyin = fopen(argv[4], "r"))) {
    perror(argv[4]);
    return 1;
  }

  Game* g;

  yyparse(&g);

  print_game(g);
  free_game(g);
}