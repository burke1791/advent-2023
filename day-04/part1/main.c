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

int compute_card_points(Card* c) {
  int numWinners = count_winning_numbers(c->winningNumbers, c->myNumbers);
  if (numWinners == 0) return 0;
  return (1 << (numWinners - 1));
}

int compute_total_points(List* cards) {
  ListItem* li = cards->root;
  int totalPoints = 0;
  while (li != NULL) {
    Card* c = (Card*)li->ptr;
    totalPoints += compute_card_points(c);
    li = li->next;
  }

  return totalPoints;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("Please provide the input file\n");
    printf("E.g. d4p1 [input_file]\n");

    return 0;
  }

  printf("File: %s\n", argv[1]);

  if (!(yyin = fopen(argv[1], "r"))) {
    perror(argv[1]);
    return 1;
  }

  List* l;

  yyparse(&l);

  int points = compute_total_points(l);
  printf("Total Points: %d\n", points);

  free_list(l);
}