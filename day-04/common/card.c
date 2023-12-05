#include <stdlib.h>
#include <stdio.h>

#include "card.h"

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

static void free_listitem(ListItem* li, ListType lt) {
  switch (lt) {
    case L_CARD:
      free_card((Card*)li->ptr);
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

Card* new_card() {
  Card* c = malloc(sizeof(Card));
  c->winningNumbers = NULL;
  c->myNumbers = NULL;
  return c;
}

void free_card(Card* c) {
  if (c->winningNumbers != NULL) free_list(c->winningNumbers);
  if (c->myNumbers != NULL) free_list(c->myNumbers);
  free(c);
}