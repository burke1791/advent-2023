#ifndef GAME_H
#define GAME_H

typedef enum ListType {
  L_SET,
  L_CUBE,
  L_GAME
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

typedef struct Game {
  int gameId;
  List* sets;
} Game;

typedef struct Set {
  List* cubes;
} Set;

typedef struct Cube {
  int count;
  char* color;
} Cube;

Game* new_game();
Set* new_set();
Cube* new_cube(int count, char* color);
List* new_list(ListType lt, void* ptr);

void list_append(List* l, void* ptr);

void free_game(Game* g);
void free_set(Set* s);
void free_cube(Cube* c);
void free_list(List* l);

int get_cube_count(List* cubes, char* color);

void print_list(List* l);

#endif /* GAME_H */