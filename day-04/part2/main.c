#include <stdlib.h>
#include <stdio.h>

#include "card.h"
#include "gram.tab.h"

extern FILE* yyin;

int count_winning_numbers(List* w, List* n) {
  ListItem* li_n = n->root;
  int count = 0;
  
  while(li_n != NULL) {
    int myNum = li_n->i;
    ListItem* li_w = w->root;
    while (li_w != NULL) {
      int wNum = li_w->i;
      if (wNum == myNum) count++;
      li_w = li_w->next;
    }
    li_n = li_n->next;
  }

  return count;
}

int compute_winning_cards(List* lc, Card* c) {
  int winCount = count_winning_numbers(c->winningNumbers, c->myNumbers);
  if (winCount == 0) return 0;

  int maxCardId = c->cardId + winCount;
  ListItem* li_c = lc->root;
  while (li_c != NULL) {
    Card* cc = (Card*)li_c->ptr;
    if (cc->cardId > c->cardId && cc->cardId <= maxCardId) {
      winCount += compute_winning_cards(lc, cc);
    }
    li_c = li_c->next;
  }
  return winCount;
}

int compute_num_cards(List* cards) {
  ListItem* li = cards->root;
  int totalCards = 0;
  while (li != NULL) {
    Card* c = (Card*)li->ptr;
    totalCards += compute_winning_cards(cards, c);
    totalCards++; // couting the original card
    li = li->next;
  }

  return totalCards;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("Please provide the input file\n");
    printf("E.g. d3p2 [input_file]\n");

    return 0;
  }

  printf("File: %s\n", argv[1]);

  if (!(yyin = fopen(argv[1], "r"))) {
    perror(argv[1]);
    return 1;
  }

  List* l;

  yyparse(&l);

  int numCards = compute_num_cards(l);
  printf("Total Cards: %d\n", numCards);

  free_list(l);
}