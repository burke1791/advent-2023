%define api.pure true
%parse-param { struct List** l }

%{

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#include "game.h"

void yyerror(List** l, char* s, ...);

%}

%union {
  char* str;
  int i;

  struct Game* game;
  struct List* list;
  struct Set* set;
  struct Cube* cube;
}

%token GAME NEWLINE

%token <i> NUMBER
%token <str> COLOR

%type <game> game
%type <list> set_list cube_list game_list
%type <set> set
%type <cube> cube

%start result

%%

result: game_list {
      *l = $1;
      YYACCEPT;
    }
  ;

game_list: game {
      List* l = new_list(L_GAME, $1);
      $$ = l;
    }
  | game_list NEWLINE game {
      list_append($1, $3);
    }
  ;

game: GAME NUMBER ':' set_list {
      Game* game = new_game();
      game->gameId = $2;
      game->sets = $4;

      $$ = game;
    }
  ;

set_list: set {
      List* l = new_list(L_SET, $1);
      $$ = l;
    }
  | set_list ';' set {
      list_append($1, $3);
    }
  ;

set: cube_list {
      Set* s = new_set();
      s->cubes = $1;

      $$ = s;
    }
  ;

cube_list: cube {
      List* l = new_list(L_CUBE, $1);
      $$ = l;
    }
  | cube_list ',' cube {
      list_append($1, $3);
    }
  ;

cube: NUMBER COLOR {
      $$ = new_cube($1, $2);
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

