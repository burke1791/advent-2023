%define api.pure true
%parse-param { struct List** l }

%{

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#include "card.h"

void yyerror(List** l, char* s, ...);

%}

%union {
  int i;

  struct Card* card;
  struct List* list;
}

%token CARD NEWLINE
%token <i> NUMBER

%type <card> card
%type <list> num_list card_list winning_numbers my_numbers

%start result

%%

result: card_list {
      *l = $1;
      YYACCEPT;
    }
  ;

card_list: card {
      List* l = new_list(L_CARD, $1);
      $$ = l;
    }
  | card_list NEWLINE card {
      list_append($1, $3);
    }
  ;

card: CARD NUMBER ':' winning_numbers '|' my_numbers {
      Card* c = new_card();
      c->cardId = $2;
      c->winningNumbers = $4;
      c->myNumbers = $6;

      $$ = c;
    }
  ;

winning_numbers: num_list
  ;

my_numbers: num_list
  ;

num_list: NUMBER {
      List* l = new_list_int(L_NUM, $1);
      $$ = l;
    }
  | num_list NUMBER {
      list_append_int($1, $2);
    }
  ;

%%

void yyerror(List** l, char* s, ...) {
  va_list ap;
  va_start(ap, s);

  fprintf(stderr, "error: ");
  vfprintf(stderr, s, ap);
  fprintf(stderr, "\n");
}