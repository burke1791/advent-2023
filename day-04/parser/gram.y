%define api.pure true

%{

#include "card.h"

%}

%union {
  int i;
}

%token CARD

%