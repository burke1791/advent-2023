#include <stdlib.h>
#include <stdio.h>

#include "engine.h"

List* new_list(ListType lt) {
  List* l = malloc(sizeof(List));
  l->type = lt;
  l->numItems = 0;
  l->root = NULL;

  return l;
}

void list_append(List* l, void* ptr) {
  if (l->root == NULL) {
    ListItem* li = malloc(sizeof(ListItem));
    li->next = NULL;
    li->ptr = ptr;
    l->root = li;
    l->numItems++;
    return;
  }

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

static void free_listitem(ListItem* li, ListType lt) {
  switch (lt) {
    case L_NUMBER:
    case L_SYMBOL:
      free(li->ptr);
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

Number* new_number(int row, int startCol, int endCol, int val) {
  Number* n = malloc(sizeof(Number));
  n->row = row;
  n->startCol = startCol;
  n->endCol = endCol;
  n->val = val;
  return n;
}

Symbol* new_symbol(int row, int col, char sym) {
  Symbol* s = malloc(sizeof(Symbol));
  s->row = row;
  s->col = col;
  s->sym = sym;
  return s;
}

CharType parse_char(char c) {
  if (isdigit(c)) return C_NUM;
  if (c == '.') return C_REG;
  return C_SYM;
}

void print_number(Number* n) {
  printf("Number: %d | {%d, %d}\n", n->val, n->row, n->startCol);
}

void print_symbol(Symbol* s) {
  printf("Symbol: {%d, %d}\n", s->row, s->col);
}

void print_list(List* l) {
  ListItem* li = l->root;

  while (li != NULL) {
    switch (l->type) {
      case L_NUMBER:
        print_number((Number*)li->ptr);
        break;
      case L_SYMBOL:
        print_symbol((Symbol*)li->ptr);
        break;
    }
    li = li->next;
  }
}

static void append_num(List* n, int row, int col, int totalNum) {
  int startCol = col - num_digits(totalNum) + 1;
  Number* num = new_number(row, startCol, col, totalNum);
  list_append(n, num);
}

static int concatenate_digit(int curr, int n) {
  return (curr * 10) + n;
}

void map_engine(FILE* fp, List* s, List* n) {
  int row = 0;
  int col = 0;
  bool isNum = false;
  int totalNum = 0;

  while (true) {
    char c = fgetc(fp);

    if (c == '\n') {
      if (isNum) {
        append_num(n, row, col - 1, totalNum);
      }
      row++;
      col = 0;
      isNum = false;
      totalNum = 0;
      continue;
    }

    CharType ct = parse_char(c);

    switch (ct) {
      case C_NUM:
        totalNum = concatenate_digit(totalNum, c - '0');
        isNum = true;
        break;
      case C_SYM:
        Symbol* sym = new_symbol(row, col, c);
        list_append(s, sym);
        // fallthrough
      case C_REG:
        if (isNum) {
          append_num(n, row, col - 1, totalNum);
          isNum = false;
          totalNum = 0;
        }
        break;
    }

    if (feof(fp)) break;

    col++;
  }
}

int num_digits(int val) {
  if (val < 10) return 1;
  return 1 + num_digits(val / 10);
}

bool is_adjacent(Symbol* s, Number* n) {
  // int startCol = n->col - num_digits(n->val) + 1;

  // starting at {row-1, startCol - 1}, check for a symbol clockwise
  // we're not going to optimize away the negative coordinates
  int row = n->row - 1;
  for (int j = n->startCol - 1; j <= n->endCol + 1; j++) {
    if (s->row == row && s->col == j) return true;
  }
  row++;

  if (s->row == row && s->col == n->startCol - 1) return true;
  if (s->row == row && s->col == n->endCol + 1) return true;
  row++;

  for (int j = n->startCol - 1; j <= n->endCol + 1; j++) {
    if (s->row == row && s->col == j) return true;
  }

  return false;
}