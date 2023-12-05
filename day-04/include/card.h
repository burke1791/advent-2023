#ifndef CARD_H
#define CARD_H

typedef enum ListType {
  L_CARD,
  L_NUM
} ListType;

typedef struct ListItem {
  void* ptr;
  int i;      // for storing a list of numbers instead of pointers
  void* next;
} ListItem;

typedef struct List {
  ListType type;
  int numItems;
  ListItem* root;
} List;

typedef struct Card {
  int cardId;
  List* winningNumbers;
  List* myNumbers;
  int winCount;
} Card;

List* new_list(ListType lt, void* ptr);
List* new_list_int(ListType lt, int i);
void list_append(List* l, void* ptr);
void list_append_int(List* l, int i);
void free_list(List* l);

Card* new_card();
void free_card(Card* c);

#endif /* CARD_H */