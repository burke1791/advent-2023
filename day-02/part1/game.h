#ifndef GAME_H
#define GAME_H

typedef enum ListType {
  SET,
  CUBE
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

#endif /* GAME_H */