#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <ctype.h>

typedef enum ListType {
  L_SYMBOL,
  L_NUMBER
} ListType;

typedef struct ListItem {
  void* ptr;
  void* next;
} ListItem;

typedef struct List {
  ListType type;
  int numItems;
  ListItem* root;
} List;

typedef enum CharType {
  C_NUM,
  C_SYM,
  C_REG
} CharType;

typedef struct Symbol {
  int row;
  int col;
} Symbol;

typedef struct Number {
  int row;
  int col;
  int val;
} Number;

void map_engine(FILE* fp, List* s, List* n);

Number* new_number(int row, int col, int val);
Symbol* new_symbol(int row, int col);


List* new_list(ListType lt);
Symbol* new_symbol(int row, int col);
Number* new_number(int row, int col, int val);

CharType parse_char(char c);

void list_append(List* l, void* ptr);

int num_digits(int val);
bool is_adjacent(Symbol* s, Number* n);

void free_list(List* l);

void print_list(List* l);
void print_number(Number* n);

#endif /* LIST_H */