#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "game.h"


int get_cube_count(List* cubes, char* color) {
  int count = 0;

  ListItem* li = cubes->root;
  while (li != NULL) {
    Cube* c = (Cube*)li->ptr;
    if (strcmp(c->color, color) == 0) {
      return c->count;
    }
    li = li->next;
  }

  return count;
}

static void print_cube(Cube* c) {
  printf("%s: %d | ", c->color, c->count);
}

static void print_set(Set* s) {
  printf("== S: ");
  print_list(s->cubes);
  printf("\n");
}

static void print_game(Game* g) {
  printf("=======   Game   =======\n");
  if (g != NULL) printf("= Game: %d", g->gameId);
  if (g->sets != NULL) {
    printf(" | Sets: %d\n", g->sets->numItems);

    print_list(g->sets);
  }

  printf("\n");
}

static void print_listitem(ListItem* li, ListType lt) {
  switch (lt) {
    case L_CUBE:
      print_cube((Cube*)li->ptr);
      break;
    case L_SET:
      print_set((Set*)li->ptr);
      break;
    case L_GAME:
      print_game((Game*)li->ptr);
      break;
  }
}

void print_list(List* l) {
  ListItem* li = l->root;

  while (li != NULL) {
    print_listitem(li, l->type);
    li = li->next;
  }
}

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
      curr->next = li;

      break;
    }

    curr = curr->next;
  }

  l->numItems++;
}

void free_cube(Cube* c) {
  if (c->color != NULL) free(c->color);
}

static void free_listitem(ListItem* li, ListType lt) {
  switch (lt) {
    case L_CUBE:
      free_cube((Cube*)li->ptr);
      break;
    case L_SET:
      free_set((Set*)li->ptr);
      break;
    case L_GAME:
      free_game((Game*)li->ptr);
      break;
    default:
      printf("Unrecognized ListType\n");
  }

  free(li->ptr);
}

void free_list(List* l) {
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
  free_list(s->cubes);
}

void free_game(Game* g) {
  if (g->sets != NULL) free_list(g->sets);
}