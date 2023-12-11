%define api.pure true
%parse-param { struct Almanac** a }

%{

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#include "almanac.h"

void yyerror(Almanac** a, char* s, ...);

%}

%union {
  int i;

  struct Almanac* alm;
  struct List* list;
  struct Map* map;
}

%token SEEDS SEED_SOIL SOIL_FERTILIZER FERTILIZER_WATER WATER_LIGHT LIGHT_TEMP TEMP_HUMIDITY HUMIDITY_LOCATION

%token <i> NUMBER

%type <list> seeds map_list
%type <map> map

%start almanac

%%

almanac:  SEEDS seeds
          SEED_SOIL map_list
          SOIL_FERTILIZER map_list
          FERTILIZER_WATER map_list
          WATER_LIGHT map_list
          LIGHT_TEMP map_list
          TEMP_HUMIDITY map_list
          HUMIDITY_LOCATION map_list   {
            Almanac* alm = new_almanac();
            alm->seeds = $2;
            alm->seedToSoil = $4;
            alm->soilToFertilizer = $6;
            alm->fertilizerToWater = $8;
            alm->waterToLight = $10;
            alm->lightToTemp = $12;
            alm->tempToHumidity = $14;
            alm->humidityToLoc = $16;

            *a = alm;
            YYACCEPT;
          }
  ;

seeds: NUMBER {
      List* l = new_list_int(L_NUM, $1);
      $$ = l;
    }
  | seeds NUMBER {
      list_append_int($1, $2);
    }
  ;

map_list: map {
      List* l = new_list(L_MAP, $1);
      $$ = l;
    }
  | map_list map {
      list_append($1, $2);
    }
  ;

map: NUMBER NUMBER NUMBER {
      Map* m = new_map($1, $2, $3);
      $$ = m;
    }
  ;


%%

void yyerror(Almanac** a, char* s, ...) {
  va_list ap;
  va_start(ap, s);

  fprintf(stderr, "error: ");
  vfprintf(stderr, s, ap);
  fprintf(stderr, "\n");
}