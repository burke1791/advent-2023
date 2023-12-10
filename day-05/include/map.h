#ifndef MAP_H
#define MAP_H

typedef enum ListType {
  L_NUM,
  L_MAP
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

typedef struct Almanac {
  List* seeds;
  List* seedToSoil;
  List* soilToFertilizer;
  List* fertilizerToWater;
  List* waterToLight;
  List* lightToTemp;
  List* tempToHumidity;
  List* humidityToLoc;
} Almanac;

typedef struct Map {
  int sourceStart;
  int destStart;
  int length;
} Map;

List* new_list(ListType lt, void* ptr);
List* new_list_int(ListType lt, int i);
void list_append(List* l, void* ptr);
void list_append_int(List* l, int i);
void free_list(List* l);



#endif /* MAP_H */