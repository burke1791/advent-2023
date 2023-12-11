#include <stdlib.h>
#include <stdio.h>

#include "almanac.h"

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

List* new_list_int(ListType lt, int i) {
  List* l = malloc(sizeof(List));
  l->type = lt;
  
  ListItem* li = malloc(sizeof(ListItem));
  li->next = NULL;
  li->i = i;

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

void list_append_int(List* l, int i) {
  ListItem* curr = l->root;

  while (1) {
    if (curr->next == NULL) {
      ListItem* li = malloc(sizeof(ListItem));
      li->next = NULL;
      li->i = i;
      curr->next = li;

      break;
    }

    curr = curr->next;
  }

  l->numItems++;
}

static void free_map(Map* m) {
  free(m);
}

static void free_seed(Seed* s) {
  free(s);
}

static void free_listitem(ListItem* li, ListType lt) {
  switch (lt) {
    case L_MAP:
      free_map((Map*)li->ptr);
      break;
    case L_SEED:
      free_seed((Seed*)li->ptr);
      break;
    case L_NUM:
      /* do nothing */
      break;
    default:
      printf("Unrecognized ListType\n");
  }
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

Almanac* new_almanac() {
  Almanac* a = malloc(sizeof(Almanac));
  return a;
}

Map* new_map(int sourceStart, int destStart, int length) {
  Map* m = malloc(sizeof(Map));
  m->sourceStart = sourceStart;
  m->destStart = destStart;
  m->length = length;

  return m;
}

void free_almanac(Almanac* a) {
  if (a->seeds != NULL) free_list(a->seeds);
  if (a->seedToSoil != NULL) free_list(a->seedToSoil);
  if (a->soilToFertilizer != NULL) free_list(a->soilToFertilizer);
  if (a->fertilizerToWater != NULL) free_list(a->fertilizerToWater);
  if (a->waterToLight != NULL) free_list(a->waterToLight);
  if (a->lightToTemp != NULL) free_list(a->lightToTemp);
  if (a->tempToHumidity != NULL) free_list(a->tempToHumidity);
  if (a->humidityToLoc != NULL) free_list(a->humidityToLoc);

  free(a);
}