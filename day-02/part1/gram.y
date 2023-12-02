%define api.pure true

%{

typedef struct SetList {
  int numSets;
  Set** sets;
};

typedef struct Cube {
  char* color;
  int count;
};

typedef struct Set {
  int numCubes;
  Cube** cubes;
};

typedef struct Game {
  int gameId;
  SetList* sets;
};

%}

%union {
  char* str;
  int i;

  struct Game* game;
  struct Set* set;
  struct SetList* setlist;
  struct Cube* cube;
}

%token <str> GAME

%token <i> NUMBER

%token <str> RED GREEN BLUE

%type <set> set
%type <cube> cube
%type <setlist> set_list

%%

game: GAME num ':' set_list {
      Game* g = malloc(sizeof(Game));
      g->gameId = $2;
      g->sets = $4;

      return g;
    }
  ;

set_list: set {
      SetList* sl = malloc(sizeof(SetList));
      sl->numSets = 1;
      sl->sets = malloc(sizeof(void*));
      sl->sets[0] = $1;

      $$ = sl;
    }
  | set_list ';' set {
      $1->sets = realloc($1->sets, sizeof(void*) * ($1->numSets + 1));
      $1->sets[$1->numSets] = $3;
      $1->numSets++;

      $$ = $1;
    }
  ;

set: cube {
      Set* s = malloc(sizeof(Set));
      s->numCubes = 1;
      s->cubes = malloc(sizeof(void*));
      s->cubes[0] = $1;
    }
  | set ',' cube {
      $1->cubes = realloc($1->cubes, sizeof(void*) * ($1->numCubes + 1));
      $1->cubes[$1->numCubes] = $3;
      $1->numCubes++;

      $$ = $1;
    }
  ;

cube: num color {
      Cube* c = malloc(sizeof(Cube));
      c->count = $1;
      c->color = $2;

      $$ = c;
    }
  ;

num: NUMBER

color: RED |
  GREEN |
  BLUE


%%

int main(int argc, char** argv) {
  
}